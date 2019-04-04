#pragma once
#include "drawHandler.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GL/glfw.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>//rotation
#include <glm/gtx/norm.hpp>//rotation
using namespace glm;

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>

class Wall
{
private:
	drawHandler H;
	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint Texture;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals; // Won't be used at the moment.
	const int numOfRows;
	const int numOfCols;
public:
	int** maze;
	Wall(drawHandler rH, int** maze, const int nr, const int nc);
	void Load();
	void Draw();
};
