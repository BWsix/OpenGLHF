#include "shaderProgram.h"

void ShaderProgram::load(const char *vertexPath, const char *fragmentPath) {
  id = glCreateProgram();

  GLuint vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  const char *vertexShaderSource = slurpFile(vertexPath);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  checkShaderCompileStatus(vertexShader);
  glAttachShader(id, vertexShader);

  GLuint fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  const char *fragmentShaderSource = slurpFile(fragmentPath);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  checkShaderCompileStatus(fragmentShader);
  glAttachShader(id, fragmentShader);

  glLinkProgram(id);
  checkProgramLinkStatus(id);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void ShaderProgram::checkShaderCompileStatus(GLuint shader) {
  int success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    log_err("Failed to compile vertex shader:");
    char infoLog[1024];
    glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
    fprintf(stderr, "%s", infoLog);
    exit(1);
  }
}

void ShaderProgram::checkProgramLinkStatus(GLuint program) {
  int success;
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    log_err("Failed to link program");
    char infoLog[1024];
    glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog);
    fprintf(stderr, "%s", infoLog);
    exit(1);
  }
}

char *ShaderProgram::slurpFile(const char *filename) {
  FILE *fp = NULL;
  char *src = NULL;
  size_t sz = 0, bytes_read = 0;

  fp = fopen(filename, "rb");
  check(fp, "Failed to open %s", filename);
  fseek(fp, 0, SEEK_END);
  sz = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  src = new char[sz + 1];
  bytes_read = fread(src, sizeof(char), sz, fp);
  check(bytes_read == sz, "Failed to read from %s", filename);
  src[sz] = '\0';
  fclose(fp);
  return src;
error:
  if (fp) fclose(fp);
  if (src) free(src);
  exit(1);
}
