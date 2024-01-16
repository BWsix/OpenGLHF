#include "camera.h"

void Camera::motionFunc(int x, int y) {
  if (mousePressed[GLUT_LEFT_BUTTON]) {
    int deltaX = x - lastMouseX;
    int deltaY = y - lastMouseY;

    yaw += sensitivity * deltaX;
    pitch -= sensitivity * deltaY;  
    if(pitch > 89.0f) {
      pitch =  89.0f;
    }
    if(pitch < -89.0f) {
      pitch = -89.0f;
    }

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);

    if (abs(deltaX) > 1 || abs(deltaY) > 1) {
      glutWarpPointer(lastMouseX, lastMouseY);
    }
  }
}

void Camera::mouseFunc(int button, int state, int x, int y) {
  mousePressed[button] = !state;

  if (state == GLUT_DOWN) {
    if (button == GLUT_LEFT_BUTTON) {
      lastMouseX = x;
      lastMouseY = y;
    }

    // scroll up
    if (button == 3) {
      fovy -= 3.0f;
    }
    // scroll down
    if (button == 4) {
      fovy += 3.0f;
    }
  }
}

void Camera::timerFunc() {
  deltaTime = (float)glutGet(GLUT_ELAPSED_TIME) / 1000.0f - timeElapsed;
  timeElapsed = (float)glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
  glm::vec3 cameraRight = glm::cross(cameraFront, glm::vec3(0.0f, 1.0f, 0.0f));
  glm::vec2 cameraFrontNormalizedXZ = glm::normalize(glm::vec2(cameraFront.x, cameraFront.z));
  glm::vec2 cameraRightNormalizedXZ = glm::normalize(glm::vec2(cameraRight.x, cameraRight.z));

  if (keyPressed[(size_t)'w']) {
    cameraPos += movementSpeed * deltaTime * glm::vec3(cameraFrontNormalizedXZ.x, 0.0f, cameraFrontNormalizedXZ.y);
  }
  if (keyPressed[(size_t)'s']) {
    cameraPos -= movementSpeed * deltaTime * glm::vec3(cameraFrontNormalizedXZ.x, 0.0f, cameraFrontNormalizedXZ.y);
  }
  if (keyPressed[(size_t)'d']) {
    cameraPos += movementSpeed * deltaTime * glm::vec3(cameraRightNormalizedXZ.x, 0.0f, cameraRightNormalizedXZ.y);
  }
  if (keyPressed[(size_t)'a']) {
    cameraPos -= movementSpeed * deltaTime * glm::vec3(cameraRightNormalizedXZ.x, 0.0f, cameraRightNormalizedXZ.y);
  }
  if (keyPressed[(size_t)' ']) {
    cameraPos.y += movementSpeed * deltaTime;
  }
  // (left) shift
  if (specialKeyPressed[112]) {
    cameraPos.y -= movementSpeed * deltaTime;
  }
}
