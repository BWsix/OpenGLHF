#include "dbg.h"
#include "utils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

char *Utils::slurpFile(const char *path) {
  FILE *fp = NULL;
  char *src = NULL;
  size_t sz = 0, bytes_read = 0;

  fp = fopen(path, "rb");
  check(fp, "Failed to open %s", path);
  fseek(fp, 0, SEEK_END);
  sz = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  src = new char[sz + 1];
  bytes_read = fread(src, sizeof(char), sz, fp);
  check(bytes_read == sz, "Failed to read from %s", path);
  src[sz] = '\0';
  fclose(fp);
  return src;
error:
  if (fp) fclose(fp);
  if (src) free(src);
  exit(1);
}

GLuint Utils::loadTexture(char const *path) {
  unsigned int textureID;
  glGenTextures(1, &textureID);

  int width, height, nrComponents;
  GLenum format = GL_RGB;
  unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
  check(data, "Failed to load texture. (Path: %s)", path)

  if (nrComponents == 1) {
    format = GL_RED;
  } else if (nrComponents == 3) {
    format = GL_RGB;
  } else if (nrComponents == 4) {
    format = GL_RGBA;
  }

  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  stbi_image_free(data);

  return textureID;

error:
  stbi_image_free(data);
  exit(1);
}
