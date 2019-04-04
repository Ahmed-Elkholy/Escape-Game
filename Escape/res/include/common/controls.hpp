#ifndef CONTROLS_HPP
#define CONTROLS_HPP
#include <glm/gtx/euler_angles.hpp>//rotation

void computeMatricesFromInputs();
void camera(int mode);
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();
glm::vec3 getCameraPos();
bool Isforward();
GLfloat GetstartTime();
void SetForward(bool x);
void setMaze(int* mz, int xstart, int zstart);
void checkInput();
void moveForward();
void moveBackward();
void rotateRight();
void rotateLeft();

#endif