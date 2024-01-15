#include "shaderProgram.h"

void ShaderProgram::load(const char* vertexPath, const char* fragmentPath) {
  id = glCreateProgram();

  GLuint vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  const char *vertexShaderSource = Utils::slurpFile(vertexPath);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  checkShaderCompileStatus(vertexShader);
  glAttachShader(id, vertexShader);

  GLuint fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  const char *fragmentShaderSource = Utils::slurpFile(fragmentPath);
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

