// //DIFFUSE TEXTURE FRAGMENT SHADER
// #version 330 // for glsl version (12 is for older versions , say opengl 2.1

// uniform sampler2D diffuseTexture;
// in vec2 texCoord;
// out vec4 fragment_color;

// void main( void ) {
// 	fragment_color = texture(diffuseTexture,texCoord);
// }
//DIFFUSE TEXTURE FRAGMENT SHADER
#version 400

uniform float ambientIntensity = 1.0;
uniform vec3 ambientLightColor = vec3(1,1,1);
uniform vec3 diffuseColor = vec3(1,1,1);
uniform bool lightInScene = false;

in vec3 lightDirection;
in float lightDistance;
in vec3 fNormal;
uniform vec3 lightColor;

in vec3 V;
uniform float shininess;
uniform vec3 specularColor;

uniform float constantAttenuation;
uniform float linearAttenuation;
uniform float quadraticAttenuation;

uniform sampler2D diffuseTexture;

in vec2 texCoord;

out vec4 fragment_color;

void main( void ) {
    vec4 diffuseTexture = texture(diffuseTexture, texCoord);

	vec3 ambient = ambientIntensity * ambientLightColor * diffuseColor.rgb;

	vec3 diffuse = max(dot(lightDirection, fNormal), 0) * lightColor * diffuseColor;

    vec3 R = reflect(lightDirection, fNormal);
	vec3 specular = pow(max(dot(V,R), 0), shininess) * specularColor * diffuseColor;

    float attenuationDivider = constantAttenuation + linearAttenuation * lightDistance + quadraticAttenuation * pow(lightDistance, 2);
    if (attenuationDivider > 0)
    {
        float attenuation = 1.0 / attenuationDivider;

        diffuse *= attenuation;

        specular *= attenuation;
    }

    // Use the default values of ambient if there is no light in the scene!
    if (lightInScene)
    {
    // For testing we keep every possible lighting combination here for quick switching!
    // 	fragment_color = vec4(ambient, 1) * diffuseTexture;
    // 	fragment_color = vec4(diffuse, 1) * diffuseTexture;
    // 	fragment_color = vec4(specular, 1) * diffuseTexture;
    // 	fragment_color = vec4(ambient + diffuse, 1) * diffuseTexture;
    // 	fragment_color = vec4(ambient + specular, 1) * diffuseTexture;
        fragment_color = vec4(diffuse + specular, 1) * diffuseTexture;
    // 	fragment_color = vec4(ambient + diffuse + specular, 1);
    }
    else
    {
	    fragment_color = vec4(ambient, 1) * diffuseTexture;
    }
}
