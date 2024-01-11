#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

in vec3 FragPos;  
in vec2 texCoord;
in vec3 Normal; 


uniform sampler2D textureSampler;

uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform float lightIntensity; // Add light intensity uniform

void main()
{
    // ambient
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor * lightIntensity;

    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * lightIntensity;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor * lightIntensity;  


    vec3 texColor = texture(textureSampler, texCoord).rgb;


    vec3 result = (ambient + diffuse + specular) * texColor;

    FragColor = vec4(result, 1.0);
}