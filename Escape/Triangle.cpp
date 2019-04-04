#include "Triangle.h"
#include "TextRendering.h"
#include "ForShader.h"
#include "common/controls.hpp"
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
Triangle::Triangle(drawHandler rH, int keyr, int keyc, int nr, int nc) :numOfRows(nr), numOfCols(nc)
{
	cout << "triangle construktor()" << endl;

	H = rH;
	r = keyr;
	c = keyc;
}


Triangle::~Triangle()
{
	glDeleteProgram(shaders_animated_model);
}


void Triangle::init()
{

	// shader for animated model
	shaders_animated_model = ForShader::makeProgram("shaders/animated_model.vert", "shaders/animated_model.frag");
	//matr_model = glm::scale(matr_model, glm::vec3(0.1f, 0.1f, 0.1f));
	model_astroboy.loadModel("models/mario/model3.dae");
	model_astroboy.initShaders(shaders_animated_model);
	/*
	glm::mat4 ProjectionMatrix = getProjectionMatrix();
	glm::mat4 ViewMatrix = getViewMatrix();
	glm::mat4 InitTranslationMatrix = translate(mat4(), vec3(-1 * numOfCols + 1.0f, 1.4f, -1 * numOfRows + 1.0f));
	glm::mat4 RotationMatrix = eulerAngleYXZ((float)glm::radians(90.0), 0.0f, 0.0f);//yaw, pitch and roll. Measured in radians
	glm::mat4 TranslationMatrix = translate(mat4(), vec3(c*2.0f, 0.0f, r*2.0f));
	glm::mat4 ScalingMatrix = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));
	glm::mat4 ModelMatrix = TranslationMatrix*InitTranslationMatrix*RotationMatrix * ScalingMatrix;
	matr_model_2 = ModelMatrix;*/
	//matr_model_2 = glm::rotate(matr_model_2, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    GLfloat angle = Isforward() ? 270 : 0;
	glm::mat4 RotationMatrix = eulerAngleYXZ(0.0f,(float)glm::radians(angle), 0.0f);//yaw, pitch and roll. Measured in radians
	glm::mat4 TranslationMatrix = translate(mat4(), vec3(0.0f, -0.4f, 0.0f));
	matr_model_2 = TranslationMatrix*RotationMatrix;
	perspective_projection = getProjectionMatrix();
	perspective_view = getViewMatrix();

}

void Triangle::update()
{
	GLfloat angle = Isforward() ? 270 : 0;
	glm::mat4 RotationMatrix = eulerAngleYXZ(0.0f, (float)glm::radians(angle), 0.0f);//yaw, pitch and roll. Measured in radians
	glm::mat4 TranslationMatrix = translate(mat4(), vec3(0.0f, -0.4f, 0.0f));
	glm::mat4 ScalingMatrix = scale(mat4(), vec3(0.8f, 1.0f, 1.0f));
	matr_model_2 = TranslationMatrix*ScalingMatrix*RotationMatrix;
	//matr_model_2 = glm::rotate(matr_model_2, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	/*
	GLfloat current_frame = glfwGetTime();
	delta_time = (current_frame - last_frame);
	last_frame = current_frame;

	// camera
	//camera.updateKey(delta_time, speed);
	// mouse
	perspective_view = getViewMatrix();
	//perspective_projection = glm::perspective(glm::radians(camera.fov), (float)Game::Instance()->screen_width / (float)Game::Instance()->screen_height, 1.0f, 2000.0f); // пирамида
	//our_model2.update();

	// model 1 matrix (MAN)
	matr_model_1 = glm::translate(matr_model_1, glm::vec3(0.0f, -0.05f, 0.0f));
	//matr_model = glm::scale(matr_model, glm::vec3(0.1f, 0.1f, 0.1f));
	matr_model_1 = glm::rotate(matr_model_1, glm::radians(0.1f), glm::vec3(0.0f, 0.0f, 1.0f));

	// text 3D
	glm::mat4 scale = glm::scale(glm::mat4(), glm::vec3(0.02f, 0.02f, 0.0f));
	

	glm::mat4 text_translate_to_model_1 = glm::translate(glm::mat4(), glm::vec3(matr_model_1[3].x, matr_model_1[3].y + 10.0f, matr_model_1[3].z));
	text_matrix_3D_model_1 = perspective_projection * perspective_view * text_translate_to_model_1 * text_rotate_y * text_rotate_x * set_text_to_origin * scale;

	glm::mat4 text_translate_to_model_2 = glm::translate(glm::mat4(), glm::vec3(matr_model_2[3].x, matr_model_2[3].y + 7.0f, matr_model_2[3].z));
	text_matrix_3D_model_2 = perspective_projection * perspective_view * text_translate_to_model_2 * text_rotate_y * text_rotate_x * set_text_to_origin * scale;

	// delete translation from view matrix
	SkyBox::Instance()->update(perspective_projection * glm::mat4(glm::mat3(perspective_view)));*/
}

void Triangle::render()
{

	glUseProgram(shaders_animated_model);

	glUniform3f(glGetUniformLocation(shaders_animated_model, "view_pos"), getCameraPos().x, getCameraPos().y, getCameraPos().z);
	glUniform1f(glGetUniformLocation(shaders_animated_model, "material.shininess"), 32.0f);
	glUniform1f(glGetUniformLocation(shaders_animated_model, "material.transparency"), 1.0f);
	// Point Light 1
	glUniform3f(glGetUniformLocation(shaders_animated_model, "point_light.position"), getCameraPos().x, getCameraPos().y, getCameraPos().z);

	glUniform3f(glGetUniformLocation(shaders_animated_model, "point_light.ambient"), 0.1f, 0.1f, 0.1f);
	glUniform3f(glGetUniformLocation(shaders_animated_model, "point_light.diffuse"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(shaders_animated_model, "point_light.specular"), 1.0f, 1.0f, 1.0f);

	glUniform1f(glGetUniformLocation(shaders_animated_model, "point_light.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(shaders_animated_model, "point_light.linear"), 0.007);	//0.14 0.09  0.07  0.045  0.027  0.022  0.014  0.007  0.0014 -	разное расстояние затухания
	glUniform1f(glGetUniformLocation(shaders_animated_model, "point_light.quadratic"), 0.0002);//0.07 0.032 0.017 0.0075 0.0028 0.0019 0.0007 0.0002 0.000007	расстояние -->
	MVP = perspective_projection * perspective_view * matr_model_2;
	glUniformMatrix4fv(glGetUniformLocation(shaders_animated_model, "MVP"), 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaders_animated_model, "M_matrix"), 1, GL_FALSE, &matr_model_2[0][0]);
	glm::mat4 matr_normals_cube2 = glm::mat4(glm::transpose(glm::inverse(matr_model_2)));
	glUniformMatrix4fv(glGetUniformLocation(shaders_animated_model, "normals_matrix"), 1, GL_FALSE, &matr_normals_cube2[0][0]);
	model_astroboy.draw(shaders_animated_model);
	glUseProgram(0);

	// draw skybox after scene
	//SkyBox::Instance()->draw();

	//glDepthFunc(GL_ALWAYS);
	// draw text after skybox so that antialiasing for lines works
	// text 2D
	/*
	glm::mat4 translate_2d_text = glm::translate(glm::mat4(), glm::vec3(20.0f, 65.0f, 0.0f));
	glm::mat4 scale_2d_text = glm::scale(glm::mat4(), glm::vec3(0.5f, 0.5f, 0.5f));
	//TextRendering::Instance()->draw("Buttons: 1,2,3,4 = controls head Agent_1", glm::vec3(0.1f, 1.0f, 0.0f), text_matrix_2D * translate_2d_text * scale_2d_text);

	translate_2d_text = glm::translate(glm::mat4(), glm::vec3(20.0f, 35.0f, 0.0f));
	//TextRendering::Instance()->draw("Buttons: 5,6,7,8,9,0 = change skybox", glm::vec3(0.1f, 1.0f, 0.0f), text_matrix_2D * translate_2d_text * scale_2d_text);

	translate_2d_text = glm::translate(glm::mat4(), glm::vec3(20.0f, 5.0f, 0.0f));
	//TextRendering::Instance()->draw("Buttons: W, S, A, D, SPACE = move  (ALT + F4 = stop)", glm::vec3(0.1f, 1.0f, 0.0f), text_matrix_2D * translate_2d_text * scale_2d_text);

	// text 3D 
	//TextRendering::Instance()->draw("Agent_1", glm::vec3(0.1f, 1.0f, 0.0f), text_matrix_3D_model_1);
	//TextRendering::Instance()->draw("Agent_2", glm::vec3(0.1f, 1.0f, 0.0f), text_matrix_3D_model_2);
	*/
	//glDepthFunc(GL_LESS);
	/*
	// music
	music1 = Mix_LoadMUS("music/modern_talking_jet_airliner.mp3");
	Mix_VolumeMusic(16);
	Mix_PlayMusic(music1, 0); // -1 = NONSTOP playing

	music2 = Mix_LoadMUS("music/02_modern_talking_you_can_win_if_you_want.mp3");*/

}

GLuint Triangle::loadImageToTexture(const char* image_path)
{

	//GLuint TextureID = loadBMP_custom("marioD.bmp");
	//return TextureID;

	ILuint ImageName; // The image name to return.
	ilGenImages(1, &ImageName); // Grab a new image name.
	ilBindImage(ImageName); // загрузит фотку в прикрепленную имаге
	if (!ilLoadImage((ILstring)image_path)) std::cout << "image NOT load " << std::endl;
	// we NEED RGB image (for not transparent)
	//ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE); //Convert image to RGBA with unsigned byte data type

	GLuint textureID;
	glGenTextures(1, &textureID); // создать текстуру
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_TYPE), ilGetData());
	glGenerateMipmap(GL_TEXTURE_2D);

	ilDeleteImages(1, &ImageName);
	glBindTexture(GL_TEXTURE_2D, 0);

	return textureID;
}
