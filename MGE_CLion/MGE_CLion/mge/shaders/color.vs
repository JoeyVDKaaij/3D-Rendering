////DIFFUSE COLOR VERTEX SHADER
//
//#version 330 // for glsl version (12 is for older versions , say opengl 2.1
//
//in vec3 vertex;
//in vec3 normal;
//in vec2 uv;
//
//uniform	mat4 	projectionMatrix;
//uniform	mat4 	viewMatrix;
//uniform	mat4 	modelMatrix;
//
//void main( void ){
//    	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex, 1.f);
//}
//DIFFUSE COLOR VERTEX SHADER
#version 400
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

out vec3 fNormal;

uniform	mat4 	projectionMatrix;
uniform	mat4 	viewMatrix;
uniform	mat4 	modelMatrix;

uniform vec3 lightPosition;
uniform vec3 cameraPosition;

out vec3 lightDirection;
out vec3 V;
out float lightDistance;

uniform float lightIntensity;

void main( void ){
    vec3 worldPos = vec3(modelMatrix * vec4(vertex, 1));
    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
    fNormal = normalize(normalMatrix * normal);
    lightDirection = normalize(lightPosition - worldPos);
    lightDistance = length(worldPos - lightPosition);
    V = normalize(worldPos - cameraPosition);
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex, 1.f);
}