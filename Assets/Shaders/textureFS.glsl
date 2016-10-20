#version 410

out vec4 FragColor;
in vec4 vColorOut;
in vec2 outTexCoords;

uniform sampler2D diffuseSampler;

void main()
{
	FragColor = texture(diffuseSampler, outTexCoords);
}