#version 410 core

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;
uniform mat4 Zoom;
uniform mat4 ObjModel;

in vec3 vVertices;

void main() {
    gl_Position = Projection * View * Model * Zoom * ObjModel * vec4(vVertices, 1.0f);
}
