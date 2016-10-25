#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Common.h"
#include "Component.h"
#include "Vertex.h" //this should probably go in the render system...?

typedef std::map<std::string, Component> ComponentsMap;

class GameObject {
private:
	ComponentsMap m_components;

public:

	GameObject();
	~GameObject();

	virtual void Init();
	virtual void Render(glm::mat4 &view, glm::mat4 &projection);
	virtual void Update(float deltaTime);
	virtual void Destroy();

	Component* GetComponent(std::string commponentName);
	Component* AddComponent(std::string componentName); //use component factory?

	//getters and setters

};

#endif

/**
shaders manager [LoadShaders(const std::string &vsFilename, const std::string &fsFilename);]
shader
texture manager
texture
material manager
material
mesh manager
mesh [CopyVertexData(Vertex* pVerts, int numberOfVertices);] copy vertex data in the VBO
(model matrix, sampler)?
render system
scenegraph
COMPONENTS:
transform (create mat4 matrices for each sub-component)
mesh renderer
(colliders)
*/