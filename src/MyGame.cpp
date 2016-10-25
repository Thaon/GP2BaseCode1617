#include "MyGame.h"

const std::string ASSET_PATH = "Assets";
const std::string SHADER_PATH = "/Shaders";
const std::string TEXTURE_PATH = "/Textures";

MyGame::MyGame()
{
	m_VBO = 0;
	m_VAO = 0;
}

MyGame::~MyGame()
{

}

void MyGame::InitScene()
{
	GameApplication::InitScene();

	//loading textures
	std::string texturePath = ASSET_PATH + TEXTURE_PATH + "/texture.png";
	m_texture =  loadTextureFromFile(texturePath);

	//loading sampler
	glGenSamplers(1, &m_sampler);
	glSamplerParameteri(m_sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glSamplerParameteri(m_sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_T, GL_CLAMP);


	glBindTexture(GL_TEXTURE_2D, m_texture);
	glGenerateMipmap(GL_TEXTURE_2D);


	//initialising vertices
	Vertex verts[] = { //position, color, UV
		{ glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec4(1, 1, 1, 1), glm::vec2(0, 0) },
		{ glm::vec3(0.5f, -0.5f, 0.0f), glm::vec4(1, 1, 1, 1), glm::vec2(1, 0) },
		{ glm::vec3(0.5f,  0.5f, 0.0f), glm::vec4(1, 1, 1, 1), glm::vec2(1, 1) },
		{ glm::vec3(0.5f,  0.5f, 0.0f), glm::vec4(1, 1, 1, 1), glm::vec2(1, 1) },
		{ glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec4(1, 1, 1, 1), glm::vec2(0, 1) },
		{ glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec4(1, 1, 1, 1), glm::vec2(0, 0) },
	};

	//------------------------------------------------------------------------------------------------------
	//filling VBO data
	glGenBuffers(1, &m_VBO); //generating VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO); //binding it to the pipeline
	//REMEMBER TO UPDATE THE NUMBER OF VERTS PASSED TO THE VBO!!!
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex), verts, GL_STATIC_DRAW); //filling it with buffer data

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

	//------------------------------------------------------------------------------------------------------
	//loading Vertex and Fragment shaders from file
	GLuint vertexShaderProgram = 0;
	std::string vsPath = ASSET_PATH + SHADER_PATH + "/simpleVS.glsl";
	vertexShaderProgram = loadShaderFromFile(vsPath, VERTEX_SHADER);
	GLuint fragmentShaderProgram = 0;
	std::string fsPath = ASSET_PATH + SHADER_PATH + "/textureFS.glsl";
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

void MyGame::DestroyScene()
{
	GameApplication::DestroyScene();

	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);

	glDeleteProgram(m_shaderProgram);

	glDeleteTextures(1, &m_texture);
	glDeleteSamplers(1, &m_sampler);
}

void MyGame::Update()
{
	GameApplication::Update();

	//using glm to calculate the various matrices
	m_projMatrix = glm::perspective(glm::radians(45.0f), (float)m_WindowWidth / (float)m_WindowHeight, 0.1f, 100.0f);
	m_viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	m_modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
}

void MyGame::Render()
{
	GameApplication::Render();

	glUseProgram(m_shaderProgram);
	glBindVertexArray(m_VAO);

	//getting position
	GLint MVPLocation = glGetUniformLocation(m_shaderProgram, "MVP");
	if (MVPLocation != -1)
	{
		glm::mat4 MVP = m_projMatrix * m_viewMatrix * m_modelMatrix;
		glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MVP));
	}

	//texture stuff
	glBindSampler(1, m_sampler);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	GLint textureLocation = glGetUniformLocation(m_shaderProgram, "diffuseSampler");
	glUniform1i(textureLocation, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}
