#ifndef SHADER_PROGRAM_H_
#define SHADER_PROGRAM_H_

#include "utils.h"
#include <string>

class ShaderProgram {
public:
  const GLuint &getId() const { return id; }

  void load(const char* vertexPath, const char* fragmentPath);
  void use() const { glUseProgram(id); }

  void uniformSetBool(const std::string &name, bool value) const { glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value); }
  void uniformSetInt(const std::string &name, int value) const { glUniform1i(glGetUniformLocation(id, name.c_str()), value); }
  void uniformSetFloat(const std::string &name, float value) const { glUniform1f(glGetUniformLocation(id, name.c_str()), value); }
  void uniformSetVec2(const std::string &name, const glm::vec2 &value) const { glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value)); }
  void uniformSetVec3(const std::string &name, const glm::vec3 &value) const { glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value)); }
  void uniformSetVec4(const std::string &name, const glm::vec4 &value) const { glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value)); }
  void uniformSetMat2(const std::string &name, const glm::mat2 &mat) const { glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat)); }
  void uniformSetMat3(const std::string &name, const glm::mat3 &mat) const { glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat)); }
  void uniformSetMat4(const std::string &name, const glm::mat4 &mat) const { glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat)); }

private:
  GLuint id;

  void checkShaderCompileStatus(GLuint shader);
  void checkProgramLinkStatus(GLuint program);
};
#endif // SHADER_PROGRAM_H_
