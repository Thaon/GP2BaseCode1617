#ifndef _MyGame_H
#define _MyGame_H

#include "GameApplication.h"

class MyGame:public GameApplication
{
private:
	GLuint m_VBO, m_VAO;

public:
	GLuint m_shaderProgram;
	GLuint m_texture;
	GLuint m_sampler;

	//matrices
	glm::mat4 m_viewMatrix, m_projMatrix, m_modelMatrix;

	MyGame();
	~MyGame();

	void InitScene();
	void DestroyScene();
	void Update();
	void Render();

	//getters and setters
};
#endif
