#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::Init()
{
}

void GameObject::Render(glm::mat4 & view, glm::mat4 & projection)
{
	/**
	glUseProgram(m_shaderProgram);
	glBindVertexArray(m_VAO);

	//getting position
	GLint MVPLocation = glGetUniformLocation(m_shaderProgram, "MVP");
	if (MVPLocation != -1)
	{
		glm::mat4 MVP = projection * view * m_modelMatrix;
		glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MVP));
	}

	//texture stuff
	glBindSampler(1, m_sampler);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	GLint textureLocation = glGetUniformLocation(m_shaderProgram, "diffuseSampler");
	glUniform1i(textureLocation, 0);

	glDrawArrays(GL_TRIANGLES, 0, m_numberOfVerts); this needs to be gathered from the mesh!
	*/
}

void GameObject::Update(float deltaTime)
{
	/**
	update matrices:
	m_TranslationMatrix = glm::translate(m_position);
	m_rotationMatrix = glm::eulerAngleXYZ(m_rotation.x, m_rotation.y, m_rotation.z);
	m_scaleMatrix = glm::scale(m_scale);

	m_modelMatrix = m_translationMatrix * m_rotationMatrix * m_scaleMatrix;
	*/
}

void GameObject::Destroy()
{
	/**
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);

	glDeleteProgram(m_shaderProgram);

	glDeleteTextures(1, &m_texture);
	glDeleteSamplers(1, &m_sampler);
	*/
}

Component * GameObject::GetComponent(std::string commponentName)
{
	return nullptr;
}

Component * GameObject::AddComponent(std::string componentName)
{
	return nullptr;
}


/**
void LoadShaders(const std::string vspath, const std::string fsPath)
{
GLuint vertexShaderProgram = 0;
vertexShaderProgram = loadShaderFromFile(vsPath, VERTEX_SHADER);
GLuint fragmentShaderProgram = 0;
fragmentShaderProgram = loadShaderFromFile(fsPath, FRAGMENT_SHADER);

//creating and linking the shader program
m_shaderProgram = glCreateProgram();
glAttachShader(m_shaderProgram, vertexShaderProgram);
glAttachShader(m_shaderProgram, fragmentShaderProgram);
glLinkProgram(m_shaderProgram);
checkForLinkErrors(m_shaderProgram);
logShaderInfo(m_shaderProgram);

//clearing the memory
glDeleteShader(vertexShaderProgram);
glDeleteShader(fragmentShaderProgram);
}
*/

/**
void CopyVertexData()
{
glGenBuffers(1, &m_VBO); //generating VBO
glBindBuffer(GL_ARRAY_BUFFER, m_VBO); //binding it to the pipeline
//REMEMBER TO UPDATE THE NUMBER OF VERTS PASSED TO THE VBO!!!
glBufferData(GL_ARRAY_BUFFER, m_numberOfVerts * sizeof(Vertex), verts, GL_STATIC_DRAW); //filling it with buffer data

//we now do the same for the VAO
glGenVertexArrays(1, &m_VAO);
glBindVertexArray(m_VAO);
glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

//defining vertex attributes
glEnableVertexAttribArray(0); //pos
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)offsetof(Vertex, position));

glEnableVertexAttribArray(1); //col
glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)offsetof(Vertex, colour));

glEnableVertexAttribArray(2); //UV
glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)offsetof(Vertex, texCoords));
}
*/