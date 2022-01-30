#version 460 core

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;
uniform float shininess;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 gridColor;
uniform bool drawGrid;

vec3 calculateLight(vec3 norm) {
    vec3 lightDir = normalize(lightPos - FragPos);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    vec3 ambient = lightColor * ambientColor;

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = (diffuseColor * diff) * lightColor;

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess * 32);
    vec3 specular = (specularColor * spec) * lightColor;

    vec3 result = ambient + diffuse + specular;
    return result;
}

void main() {
    vec3 norm = normalize(Normal);
    if (drawGrid) {
        FragColor = vec4(gridColor, 1.0);
    } else {
       if (gl_FrontFacing) {
           FragColor = vec4(calculateLight(norm), 1.0);
       } else {
           FragColor = vec4(calculateLight(-norm), 1.0);
       }
    }
}
