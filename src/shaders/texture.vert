#version 440 core

layout(location = 0) uniform mat4 MVP;

layout(location = 0) in vec3 vPosition;

layout(location = 0) out vec3 textureVector;

void main()
{ 
	gl_Position = MVP * vec4(vPosition, 1.0f);
	textureVector = vPosition;
}
