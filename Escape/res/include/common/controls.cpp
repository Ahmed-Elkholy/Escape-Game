// Include GLFW
#include <GL/glfw.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "controls.hpp"

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;
glm::vec3 direction=vec3(5,0,0);
int* maze;
bool moveforward=false;
GLfloat startTime=0;
glm::mat4 getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix(){
	return ProjectionMatrix;
}

bool Isforward()
{
	return moveforward;
}
void SetForward(bool x)
{
	moveforward = false;
}

// Initial position : on +Z
glm::vec3 position = glm::vec3( 0, 0, 5 ); 
// Initial horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 2.0f; // 3 units / second
float mouseSpeed = 0.005f;


glm::vec3 getCameraPos()
{
	return position;
}
void setMaze(int* mz, int xstart, int zstart)
{
	maze = mz;
	position.x = xstart;
	position.z = zstart;
	position.y = 2;
}

void camera(int mode)
{
	if (mode == 0)
	{
		ProjectionMatrix = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f);
		ViewMatrix = glm::lookAt(
			glm::vec3(0.000000f, 10, 0.0000001f), // Camera is at (4,3,-3), in World Space
			glm::vec3(0, 0, 0), // and looks at the origin
			glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
	}
	else if (mode == 1)
	{
		// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
		ProjectionMatrix = glm::perspective(90.0f, 4.0f / 3.0f, 0.1f, 100.0f);
		// Camera matrix
		glm::vec3 dir= glm::vec3(position.x, position.y, position.z);
		dir = glm::vec3(dir.x + direction.x, dir.y, direction.z+dir.z);

		ViewMatrix = glm::lookAt(
			glm::vec3(position.x, position.y, position.z), // Camera is at (4,3,-3), in World Space
			glm::vec3(dir.x, dir.y, dir.z), // and looks at the origin
			glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
	}
	else if (mode == 2)
	{
		position.x = -1 * 18 + 1.0f + 15 * 2.0f;
		position.z = -1 * 18 + 1.0f + 16 * 2.0f;
		// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
		ProjectionMatrix = glm::perspective(90.0f, 4.0f / 3.0f, 0.1f, 100.0f);
		// Camera matrix
		ViewMatrix = glm::lookAt(
			glm::vec3(position.x - 1, position.y, position.z), // Camera is at (4,3,-3), in World Space
			glm::vec3(position.x + 5, position.y + 2, position.z), // and looks at the origin
			glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
	}
}

void moveForward()
{
	if (moveforward)
	{
		position.x += 0.005;
		return;
	}
	//check
	//if (maze[(int)(position.x - 1) * 18 + (int)(position.z)] != 1)
	//{
	startTime = glfwGetTime();
	moveforward = 1;
	position.x += 0;
	//}
}
void moveBackward()
{

}

GLfloat GetstartTime()
{
	return startTime;
}
void rotateRight()
{
	direction.x = 0;
	direction.y = 0;
	direction.z = 5;
}
void rotateLeft()
{

}

void checkInput()
{
	// Move forward
	if (glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS) 
	{
		moveForward();
	}
	// Move backward
	if (glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS) 
	{
		position.x -= 0.01;
		//moveBackward();
	}
	// Rotate right
	if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS) 
	{
		rotateRight();
	}
	// Rotate left
	if (glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS) 
	{
		rotateLeft();
	}
}

void computeMatricesFromInputs(){

	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	int xpos, ypos;
	glfwGetMousePos(&xpos, &ypos);

	// Reset mouse position for next frame
	// EDIT : Doesn't work on Mac OS, hence the code below is a bit different from the website's
	//glfwSetMousePos(1024/2, 768/2);

	// Compute new orientation
	horizontalAngle = 3.14f + mouseSpeed * float(1024/2 - xpos );
	verticalAngle   = mouseSpeed * float( 768/2 - ypos );

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);
	
	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f), 
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);
	
	// Up vector
	glm::vec3 up = glm::cross( right, direction );

	// Move forward
	if (glfwGetKey( GLFW_KEY_UP ) == GLFW_PRESS){
		position += direction * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey( GLFW_KEY_DOWN ) == GLFW_PRESS){
		position -= direction * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS){
		position += right * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey( GLFW_KEY_LEFT ) == GLFW_PRESS){
		position -= right * deltaTime * speed;
	}

	float FoV = initialFoV - 5 * glfwGetMouseWheel();

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	ViewMatrix       = glm::lookAt(
								position,           // Camera is here
								position+direction, // and looks here : at the same position, plus "direction"
								up                  // Head is up (set to 0,-1,0 to look upside-down)
						   );

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}