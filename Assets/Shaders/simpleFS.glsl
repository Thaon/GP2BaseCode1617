#version 410

out vec4 FragColor;
in vec4 vColorOut;

void main()
{
	FragColor = vColorOut;
}