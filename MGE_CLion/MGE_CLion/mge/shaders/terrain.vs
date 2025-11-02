////DIFFUSE TEXTURE VERTEX SHADER
//#version 330 // for glsl version (12 is for older versions , say opengl 2.1
//
//uniform	mat4 	mvpMatrix;
//
//in vec3 vertex;
//in vec3 normal;
//in vec2 uv;
//
//out vec2 texCoord; //make sure the texture coord is interpolated
//
//void main( void ){
//    gl_Position = mvpMatrix * vec4(vertex, 1.f);
//	texCoord = uv;
//}
//DIFFUSE TEXTURE VERTEX SHADER
#version 400
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

out vec3 fNormal;

uniform	mat4 	modelMatrix;
uniform	mat4 	mvpMatrix;

uniform vec3 lightPosition;
uniform vec3 cameraPosition;

out vec3 lightDirection;
out vec3 V;
out float lightDistance;

out vec2 texCoord;

uniform sampler2D heightMap;

vec3 cross(vec3 a, vec3 b) {
    return vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}
void main( void )
{
    vec4 heightTexture = texture(heightMap, uv);
    float heightValue = ((heightTexture.r + heightTexture.g + heightTexture.b) / 3);
    float displacedY = vertex.y + heightValue;
    vec3 heightVertex = vec3(vertex.x, displacedY, vertex.z);
    vec3 worldPos = vec3(modelMatrix * vec4(heightVertex, 1));

	vec3 leftPoint = vec3(-.01, texture(heightMap, vec2(uv.x+0.01f, uv.y)).r, 0.0);
	vec3 rightPoint = vec3(.01, texture(heightMap, vec2(uv.x-0.01f, uv.y)).r, 0.0);
	vec3 LR = normalize(rightPoint - leftPoint);

	vec3 topPoint = vec3(0.0, texture(heightMap, vec2(uv.x, uv.y-0.01f)).r, -.01);
	vec3 bottomPoint = vec3(0.0, texture(heightMap, vec2(uv.x, uv.y+0.01f)).r, .01);
	vec3 TB = normalize(topPoint - bottomPoint);

	vec3 objectSpaceNormal = normalize(cross(LR,TB));

    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
    fNormal = normalize(normalMatrix * objectSpaceNormal);

    lightDirection = normalize(lightPosition - worldPos);
    lightDistance = length(worldPos - lightPosition);

    V = normalize(worldPos - cameraPosition);

    gl_Position = mvpMatrix * vec4(worldPos, 1.0);
	texCoord = uv;
}