#ifndef COMPONENT_H
#define COMPONENT_H

#include "Common.h"

class Component {

private:

	std::string m_name;

public:

	Component(std::string name);
	Component();
	~Component();

	//getters and setters
	std::string GetName() { return m_name; }

};

#endif
