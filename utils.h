#ifndef UTILS_H_
#define UTILS_H_

#include "dbg.h"
#include <GL/glew.h>
#include <GL/freeglut_std.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define ARRAY_LEN(arr) sizeof(arr) / sizeof((arr)[0])

namespace Utils {
char *slurpFile(const char *path);
GLuint loadTexture(char const *path);
}

#endif // !UTILS_H_
