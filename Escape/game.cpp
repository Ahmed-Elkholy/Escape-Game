// Include standard headers
#include "drawHandler.hpp"
#include "floor.hpp"
#include "sky.hpp"
#include "wall.hpp"
#include "door.hpp"
#include "mazeGenerator.hpp"
#include "key.hpp"
#include "Player.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
// Include GLEW
#include <GL/glew.h>
#include "Triangle.h"

// Include GLFW
#include <GL/glfw.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>

using namespace std;

GLuint vertexbuffer;
GLuint uvbuffer;
drawHandler Dhandler;

void Init()
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
	}
	ilInit();
	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);

	// Open a window and create its OpenGL context
	if (!glfwOpenWindow(1024, 768, 0, 0, 0, 0, 32, 0, GLFW_WINDOW))
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
	}

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
	}
	glfwSetWindowTitle("Maze Game");
	glViewport(0, 0, 1024, 768);
	// Ensure we can capture the escape key being pressed below
	glfwEnable(GLFW_STICKY_KEYS);
	glfwSetMousePos(1024 / 2, 768 / 2);
	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.5f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	//glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	// Create and compile our GLSL program from the shaders
	Dhandler.programID = LoadShaders("shaders/TransformVertexShader.vertexshader", "shaders/TextureFragmentShader.fragmentshader");

	// GP" uniform
	Dhandler.MatrixID = glGetUniformLocation(Dhandler.programID, "MVP");

	// Get a handle for our buffers
	Dhandler.vertexPosition_modelspaceID = glGetAttribLocation(Dhandler.programID, "vertexPosition_modelspace");
	Dhandler.vertexUVID = glGetAttribLocation(Dhandler.programID, "vertexUV");

	// GetDhandler a handle for our "myTextureSampler" uniform
	Dhandler.TextureID = glGetUniformLocation(Dhandler.programID, "myTextureSampler");

}


int main(void)
{
	ilInit(); // init image load library
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);
	ilEnable(IL_ORIGIN_SET);
	// OpenGL have the 0.0 coordinate on the bottom y-axis, but images usually have 0.0 at the top of the y-axis.
	ilOriginFunc(IL_ORIGIN_UPPER_LEFT); // 0, 0 textures in upper left side
	Init();
	Floor floorobj(Dhandler);
	Sky skyobj(Dhandler);
	MazeGenerator mazegen(18, 18);
	mazegen.Generate();
	Wall wallobj(Dhandler, mazegen.maze, mazegen.maze_size_y + 2, mazegen.maze_size_x + 2);
	Door doorobj(Dhandler, mazegen.maze_size_y + 2, mazegen.maze_size_x + 2);
	Key keyobj(Dhandler, mazegen.keyr, mazegen.keyc, mazegen.maze_size_y + 2, mazegen.maze_size_x + 2);
	//Player mario(Dhandler, 1, 0, mazegen.maze_size_y + 2, mazegen.maze_size_x + 2);
	Triangle mario(Dhandler, 1, 0, mazegen.maze_size_y + 2, mazegen.maze_size_x + 2);
	skyobj.Load();
	floorobj.Load();
	wallobj.Load();
	keyobj.Load();
	doorobj.Load();
	//mario.Load();
	mario.init();
	//skybox->init("images/skybox_violentday");
	setMaze(*wallobj.maze, -1 * (mazegen.maze_size_x + 2), -1 * (mazegen.maze_size_y + 2) + 3.0f);
	do {

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(Dhandler.programID);

		// Compute the MVP matrix from keyboard and mouse input
	    //computeMatricesFromInputs();
		checkInput();
		mario.update();
		camera(1);
		//skybox->draw();
		floorobj.Draw();
		wallobj.Draw();
		doorobj.Draw();
		keyobj.Draw();
		mario.render();
		skyobj.Draw();

		// Swap buffers
		glfwSwapBuffers();
		//SetForward(0);

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS &&
		glfwGetWindowParam(GLFW_OPENED));

	// Cleanup VBO and shader
	glDeleteProgram(Dhandler.programID);
	glDeleteTextures(1, &Dhandler.TextureID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

