#pragma once
#include<vector>
// Include GLEW
#include <GL/glew.h>
// Include GLFW
#include <GL/glfw.h>
#include <glm/glm.hpp>
using namespace std;

class drawHandler
{
	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
public:
	GLuint MatrixID;
	GLuint  programID;
	GLuint	vertexPosition_modelspaceID;
	GLuint	vertexUVID;
	GLuint	TextureID;
	glm::mat4 getProjection();
	glm::mat4 getView();
};