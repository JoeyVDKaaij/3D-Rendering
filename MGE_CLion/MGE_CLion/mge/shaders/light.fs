uniform float ambientIntensity;
uniform vec3 ambientLightColor;
uniform vec3 diffuseColor;

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

// 	fragment_color = vec4(ambient, 1) * diffuseTexture;
// 	fragment_color = vec4(diffuse, 1) * diffuseTexture;
// 	fragment_color = vec4(specular, 1) * diffuseTexture;
	fragment_color = vec4(ambient + diffuse + specular, 1) * diffuseTexture;
}
