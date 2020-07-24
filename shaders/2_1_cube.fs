#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

in vec2 TexCoords;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct Flashlight {
    vec3  position;
    vec3  direction;
    float cutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform Material material;
uniform Light light;
uniform Flashlight flashlight;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;

void main()
{
    vec3 lightDir = normalize(flashlight.position - FragPos);
    float theta = dot(lightDir, normalize(-flashlight.direction));
    if(theta > flashlight.cutOff) {
        // ambient
        vec3 ambient = flashlight.ambient * texture(material.diffuse, TexCoords).rgb;

        // diffuse
        vec3 norm = normalize(Normal);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = flashlight.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

        // specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = flashlight.specular * spec * texture(material.specular, TexCoords).rgb;

        // attenuation
        float distance    = length(flashlight.position - FragPos);
        float attenuation = 1.0 / (flashlight.constant + flashlight.linear * distance + flashlight.quadratic * (distance * distance));

        // remove attenuation from ambient,
        // as otherwise at large distances the light would be darker inside than outside the spotlight
        // due the ambient term in the else branche
//         ambient  *= attenuation;
        diffuse  *= attenuation;
        specular *= attenuation;

        vec3 result = ambient + diffuse + specular;
        FragColor = vec4(result, 1.0);
    } else {
        // else, use ambient light so scene isn't completely dark outside the spotlight.
        FragColor = vec4(flashlight.ambient * texture(material.diffuse, TexCoords).rgb, 1.0);
    }





//     // ambient
//     vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
//
//     // diffuse
//     vec3 norm = normalize(Normal);
//
// //     vec3 lightDir = normalize(-light.direction);
//     vec3 lightDir = normalize(light.position - FragPos);
//     float diff = max(dot(norm, lightDir), 0.0);
//     vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;
//
//     // specular
//     vec3 viewDir = normalize(viewPos - FragPos);
//     vec3 reflectDir = reflect(-lightDir, norm);
//     float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//     vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;
//
//     float distance  = length(light.position - FragPos);
//     float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
//     ambient  *= attenuation;
//     diffuse  *= attenuation;
//     specular *= attenuation;
//
//     vec3 result = ambient + diffuse + specular;
//     FragColor = vec4(result, 1.0);
}