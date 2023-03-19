#version 330 core
out vec4 Frame;

uniform vec3 objectColor;

void main(){
	Frame = vec4(objectColor, 1.0f);
}