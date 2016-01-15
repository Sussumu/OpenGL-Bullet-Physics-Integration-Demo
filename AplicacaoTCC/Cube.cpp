#include "Cube.h"
#include <iostream>
#include <SOIL/SOIL.h>

Cube::Cube(GLfloat* vertices, glm::vec3* position)
{
	memcpy(m_vertices, vertices, sizeof(vertices));
	memcpy(m_position, position, sizeof(position));
}

Cube::~Cube()
{
}

void Cube::setup()
{
#pragma region Draw
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
#pragma endregion

#pragma region Texture
						  // Load and create a texture 
						  // ====================
						  // Texture 1
						  // ====================
	glGenTextures(1, &m_texture1);
	glBindTexture(GL_TEXTURE_2D, m_texture1); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
											  // Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image("Textures/container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
									 // ===================
									 // Texture 2
									 // ===================
									 //glGenTextures(1, &texture2);
									 //glBindTexture(GL_TEXTURE_2D, texture2);
									 //// Set our texture parameters
									 //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
									 //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
									 //// Set texture filtering
									 //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
									 //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
									 //// Load, create texture and generate mipmaps
									 //image = SOIL_load_image("Textures/awesomeface.png", &width, &height, 0, SOIL_LOAD_RGB);
									 //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
									 //glGenerateMipmap(GL_TEXTURE_2D);
									 //SOIL_free_image_data(image);
									 //glBindTexture(GL_TEXTURE_2D, 0);
#pragma endregion
}

void Cube::update(ShaderProgram shaderProgram)
{
#pragma region Texture
	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture1);
	glUniform1i(glGetUniformLocation(shaderProgram.programID, "ourTexture1"), 0);
	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, m_texture2);
	//glUniform1i(glGetUniformLocation(shaderProgram.Program, "ourTexture2"), 1);
#pragma endregion

#pragma region Rendering
	// Create transformations
	glm::mat4 view;
	glm::mat4 projection;
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(45.0f, (GLfloat)800 / (GLfloat)600, 0.1f, 100.0f);
	// Get their uniform location
	GLint modelLoc = glGetUniformLocation(shaderProgram.programID, "model");
	GLint viewLoc = glGetUniformLocation(shaderProgram.programID, "view");
	GLint projLoc = glGetUniformLocation(shaderProgram.programID, "projection");
	// Pass the matrices to the shader
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	// Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(m_VAO);
	for (GLuint i = 0; i < 10; i++)
	{
		// Calculate the model matrix for each object and pass it to shader before drawing
		glm::mat4 model;
		model = glm::translate(model, m_position[i]);
		GLfloat angle = 20.0f * i;
		model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	glBindVertexArray(0);
#pragma endregion
}

void Cube::clean()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
}
