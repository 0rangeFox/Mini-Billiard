#version 410 core

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;
uniform mat4 Zoom;
uniform mat4 ObjModel;

in vec3 vVertices;
in vec3 vNormals;
in vec2 vUVs;

out vec3 vPositionEyeSpace;
out vec3 normalMapping;
out vec2 uvMapping;

void main() {
	mat4 modelTranslated = View * Model * Zoom * ObjModel;
	vec4 vertices = vec4(vVertices, 1.f);

	gl_Position = Projection * modelTranslated * vertices;
	normalMapping = normalize(mat3(transpose(inverse(View * ObjModel))) * vNormals);
	uvMapping = vUVs;
	vPositionEyeSpace = (View * ObjModel * vertices).xyz;
}
