#include "utils.h"
#include "shaderProgram.h"
#include "camera.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define TARGET_FRAME_RATE 120
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

ShaderProgram shaderProgram;
Camera camera = Camera(WINDOW_WIDTH, WINDOW_HEIGHT);

void setup();
void displayFunc();
void reshapeFunc(int width, int height);
void keyboardFunc(unsigned char key, int x, int y);
void keyboardUpFunc(unsigned char key, int x, int y);
void specialFunc(int key, int x, int y);
void specialUpFunc(int key, int x, int y);
void mouseFunc(int button, int state, int x, int y);
void motionFunc(int x, int y);
void timerFunc(int which);
void logInfo();

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutCreateWindow(argv[0]);
  glewInit();
  
  setup();

  glutDisplayFunc(displayFunc);
  glutReshapeFunc(reshapeFunc);
  glutKeyboardFunc(keyboardFunc);
  glutKeyboardUpFunc(keyboardUpFunc);
  glutSpecialFunc(specialFunc);
  glutSpecialUpFunc(specialUpFunc);
  glutMouseFunc(mouseFunc);
  glutMotionFunc(motionFunc);
  glutTimerFunc(1.0f / TARGET_FRAME_RATE, timerFunc, 0);
  logInfo();

  glutMainLoop();
  return 0;
}

void setup() {
	glEnable(GL_DEPTH_TEST);
  shaderProgram.load("./vertex.glsl", "./fragment.glsl");
  shaderProgram.use();
  shaderProgram.uniformSetMat4("projection", camera.getProjectionMatrix());
}

void displayFunc() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  shaderProgram.uniformSetMat4("view", camera.getViewMatrix());

  glutSwapBuffers();
}

void reshapeFunc(int width, int height) {
  log_info("reshapeFunc(width: %d, height: %d)", width, height);
  glViewport(0, 0, width, height);
  camera.reshapeFunc(width, height);
  shaderProgram.uniformSetMat4("projection", camera.getProjectionMatrix());
}

void keyboardFunc(unsigned char key, int x, int y) {
  log_info("keyboardFunc(key: %c, x: %d, y: %d)", key, x, y);
  camera.keyboardFunc(key);
}

void keyboardUpFunc(unsigned char key, int x, int y) {
  log_info("keyboardUpFunc(key: %c, x: %d, y: %d)", key, x, y);
  camera.keyboardUpFunc(key);
}

void specialFunc(int key, int x, int y) {
  log_info("specialFunc(key: %d, x: %d, y: %d)", key, x, y);
  camera.specialFunc(key);
}

void specialUpFunc(int key, int x, int y) {
  log_info("specialUpFunc(key: %d, x: %d, y: %d)", key, x, y);
  camera.specialUpFunc(key);
}

void mouseFunc(int button, int state, int x, int y) {
  // log_info("mouseFunc(button: %d, state: %d, x: %d, y: %d)", button, state, x, y);
  camera.mouseFunc(button, state, x, y);
  shaderProgram.uniformSetMat4("projection", camera.getProjectionMatrix());
}

void motionFunc(int x, int y) {
  // log_info("motionFunc(x: %d, y: %d)", x, y);
  camera.motionFunc(x, y);
}

void timerFunc(int which) {
  // log_info("timerFunc(which: %d)", which);
	glutPostRedisplay();
	glutTimerFunc(1.0f / TARGET_FRAME_RATE, timerFunc, which);
  camera.timerFunc();
}

void logInfo() {
	log_info("Vendor: %s", glGetString(GL_VENDOR));
	log_info("Renderer: %s", glGetString(GL_RENDERER));
	log_info("Version: %s", glGetString(GL_VERSION));
	log_info("GLSL: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
}
