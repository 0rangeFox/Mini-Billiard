#version 440 core

layout (location = 0) in vec3 textureVector;

uniform samplerCube skybox;

layout (location = 0) out vec4 fColor; // Cor final do fragmento

void main()
{
	fColor = texture(skybox, textureVector);
}
