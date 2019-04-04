#include "drawHandler.hpp"
#include "Model.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include "common/texture.hpp"
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


class Triangle
{
public:
	drawHandler H;
	int r, c;
	GLuint view_pos;
	const int numOfRows, numOfCols;
	Triangle(drawHandler rH, int keyr, int keyc, int nr, int nc);
	~Triangle();

	GLfloat speed = 0.02f;
	//for camera
	GLfloat delta_time = 0.0f;
	GLfloat last_frame = 0.0f;
	GLfloat last_x;
	GLfloat last_y;
	//Vector2D mouse_position;
	GLboolean mouse_first_in;
	//Camera camera;

	GLuint shaders_animated_model;
	Model model_astroboy;

	// music
	//Mix_Music* music1 = nullptr;
	//Mix_Music* music2 = nullptr;

	glm::mat4 MVP;
	glm::mat4 perspective_view;
	glm::mat4 perspective_projection;
	glm::mat4 matr_model_2;

	// text
	glm::mat4 text_matrix_2D; // orthographic projection
	glm::mat4 text_matrix_3D_model_1; // perspective  projection
	glm::mat4 text_matrix_3D_model_2; // perspective  projection
	static GLuint Triangle::loadImageToTexture(const char* image_path);

	void init();
	void update();
	void render();

};

