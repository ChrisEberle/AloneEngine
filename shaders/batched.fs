#version 330 core

const int MaxLights = 4; // Adjust the number as needed

struct Material 
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shine;
};

struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

};

in vec3 FragPos;  
in vec2 texCoord;
in vec3 Normal; 

// Outputs colors in RGBA
out vec4 FragColor;

uniform sampler2D textureSampler;

uniform Material material;
uniform Light lights[MaxLights];

uniform vec3 viewPos; 

void main()
{
    vec3 result = vec3(0.0);
    vec3 texColor = texture(textureSampler, texCoord).rgb;
    for (int i = 0; i < MaxLights; ++i) {
    // ambient
    vec3 ambient = lights[i].ambient * material.ambient;

    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lights[i].position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lights[i].diffuse * (diff * material.diffuse);
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shine);
    vec3 specular = lights[i].specular * (spec * material.specular);  


    result += ambient + diffuse + specular;
    }

    FragColor = vec4(result * texColor, 1.0);
}