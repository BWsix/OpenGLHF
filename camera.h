#ifndef CAMERA_H_
#define CAMERA_H_

#include "utils.h"

class Camera {
private:
  glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
  glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 getCameraDir() const { return cameraPos + cameraFront; }
  
  float fovy = 45.0f;
  float aspect;
  float near = 0.1f;
  float far = 100.0f;

  float yaw = -90.0f;
  float pitch = 0.0f;
  float sensitivity = 0.15f;
  float movementSpeed = 10.0f;

  int lastMouseX;
  int lastMouseY;

  float timeElapsed = 0.0f;
  float deltaTime = 0.0f;

  bool mousePressed[16] = {0};
  bool keyPressed[512] = {0};
  bool specialKeyPressed[512] = {0};

public:
  Camera(int width, int height) { reshapeFunc(width, height); }

  void setNear(float value) { near = value; }
  void setFar(float value) { far = value; }

  void setSensitivity(float value) { sensitivity = value; }
  void setMovementSpeed(float value) { movementSpeed = value; }
  float getTimeElapsed() const { return timeElapsed; }
  float getDeltaTime() const { return deltaTime; }
  float getFovy() const { return fovy; }

  glm::mat4 getViewMatrix() const { return glm::lookAt(cameraPos, getCameraDir(), glm::vec3(0.0, 1.0, 0.0)); }
  glm::mat4 getProjectionMatrix() const { return glm::perspective(glm::radians(fovy), aspect, near, far); }

  bool isMousePressed(int mouse) const { return mousePressed[mouse]; }
  bool getKeyPressed(int key) const { return keyPressed[key]; }
  bool getSpecialKeyPressed(int key) const { return specialKeyPressed[key]; }

  void reshapeFunc(int width, int height) { aspect = (float)width / height; };
  void mouseFunc(int button, int state, int x, int y);
  void keyboardFunc(unsigned char key) { keyPressed[key] = true; }
  void keyboardUpFunc(unsigned char key) { keyPressed[key] = false; }
  void specialFunc(int key) { specialKeyPressed[key] = true; }
  void specialUpFunc(int key) { specialKeyPressed[key] = false; }
  void motionFunc(int x, int y);
  void timerFunc();
};
#endif // CAMERA_H_
