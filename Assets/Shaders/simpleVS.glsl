#version 410
layout(location=0) in vec3 vertexPosition;
layout(location=1) in vec4 vertexColor;
layout(location=2) in vec2 uvCoords;

uniform mat4 MVP;
out vec4 vColorOut;
out vec2 outTexCoords;

void main()
{
		gl_Position = MVP * vec4(vertexPosition, 1.0);
		vColorOut = vertexColor;
		outTexCoords = uvCoords;
}