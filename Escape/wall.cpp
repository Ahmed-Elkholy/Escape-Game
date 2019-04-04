#include "wall.hpp"

Wall::Wall(drawHandler rH, int** Maze, const int nr, const int nc) : numOfRows(nr), numOfCols(nc)
{
	H = rH;
	maze = Maze;
}


void Wall::Load()
{
	// Load the texture
	//Texture = loadBMP_custom("wall.bmp");
	Texture = loadBMP_custom("images/wallt7.bmp");

	//Load Object
	bool res = loadOBJ("models/wallNew.obj", vertices, uvs, normals);
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

}

void Wall::Draw()
{
	for (int i = 0; i < numOfRows; i++)
	{
		for (int j = 0; j < numOfCols; j++)
		{
			if (maze[i][j] == 1)
			{
				glm::mat4 ProjectionMatrix = getProjectionMatrix();
				glm::mat4 ViewMatrix = getViewMatrix();
				glm::mat4 InitTranslationMatrix = translate(mat4(), vec3(-1 * numOfCols + 1.0f, 3.5f, -1 * numOfRows + 1.0f));
				glm::mat4 RotationMatrix = eulerAngleYXZ(0.0f, 0.0f, 0.0f);//yaw, pitch and roll. Measured in radians
				glm::mat4 TranslationMatrix = translate(mat4(), vec3(j*2.0f, 0.0f, i*2.0f));
				glm::mat4 ScalingMatrix = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));
				glm::mat4 ModelMatrix = TranslationMatrix*InitTranslationMatrix*RotationMatrix*ScalingMatrix;

				glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

				// Send our transformation to the currently bound shader, 
				// in the "MVP" uniform
				glUniformMatrix4fv(H.MatrixID, 1, GL_FALSE, &MVP[0][0]);
				// Bind our texture in Texture Unit 0
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, Texture);

				glUniform1i(H.TextureID, 0);

				// 1rst attribute buffer : vertices
				glEnableVertexAttribArray(H.vertexPosition_modelspaceID);
				glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
				glVertexAttribPointer(
					H.vertexPosition_modelspaceID,  // The attribute we want to configure
					3,                            // size
					GL_FLOAT,                     // type
					GL_FALSE,                     // normalized?
					0,                            // stride
					(void*)0                      // array buffer offset
				);

				// 2nd attribute buffer : UVs
				glEnableVertexAttribArray(H.vertexUVID);
				glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
				glVertexAttribPointer(
					H.vertexUVID,                   // The attribute we want to configure
					2,                            // size : U+V => 2
					GL_FLOAT,                     // type
					GL_FALSE,                     // normalized?
					0,                            // stride
					(void*)0                      // array buffer offset
				);

				// Draw the triangles !
				glDrawArrays(GL_TRIANGLES, 0, vertices.size());

				glDisableVertexAttribArray(H.vertexPosition_modelspaceID);
				glDisableVertexAttribArray(H.vertexUVID);
			}
		}
	}
}