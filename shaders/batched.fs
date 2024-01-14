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
    vec3 direction; // For directional light


    float cutoff;   // For spotlight
    float outerCone; // For spotlight
    int type;       // 0 for directional, 1 for spotlight

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float lightIntensity;

    //  property for controlling overall color
    vec3 colorMultiplier;
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

//depth buffer function
float near = 0.1f;
float far = 100.0f;

float linearizeDepth(float depth)
{
    return (2.0 * near * far) / (far + near - (depth * 2.0 - 1.0) * (far - near));
}

//create a fog effect with the depth buffer
float logisticDepth(float depth, float steepness = 0.1f, float offset = 0.80f)
{
    float zVal = linearizeDepth(depth);
    return (1 / (1 + exp(-steepness * (zVal - offset))));
}



//directional lighting

vec4 direcLight()
{
    vec3 result = vec3(0.0);
    vec3 texColor = texture(textureSampler, texCoord).rgb;
        for (int i = 0; i < MaxLights; ++i) 
        {
            if (lights[i].type == 0) // Directional light
            {
            // ambient
            vec3 ambient = lights[i].colorMultiplier * lights[i].ambient * material.ambient;
    
            // diffuse 
            vec3 norm = normalize(Normal);
            vec3 lightDir = normalize(-lights[i].direction);
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 diffuse = lights[i].colorMultiplier * lights[i].diffuse * (diff * material.diffuse);
            
            // specular
            vec3 viewDir = normalize(viewPos - FragPos);
            vec3 reflectDir = reflect(-lightDir, norm);  
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shine);
            vec3 specular = lights[i].colorMultiplier * lights[i].specular * (spec * material.specular);  
    
            // combined
            result += (ambient + diffuse + specular) * lights[i].lightIntensity;
            }
    }

    return vec4(result * texColor, 1.0);
}

vec4 spotLight()
{
    vec3 result = vec3(0.0);
    vec3 texColor = texture(textureSampler, texCoord).rgb;
    for (int i = 0; i < MaxLights; ++i)
    {
        if (lights[i].type == 1) // Spot light
        {
            // controls how big the area that is lit up is
            float outerCone = 0.90f;
            float innerCone = 0.95f;

            // ambient
            vec3 ambient = lights[i].colorMultiplier * lights[i].ambient * material.ambient;

            // diffuse 
            vec3 norm = normalize(Normal);
            vec3 lightDir = normalize(lights[i].position - FragPos);
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 diffuse = lights[i].colorMultiplier * lights[i].diffuse * (diff * material.diffuse);

            // specular
            vec3 viewDir = normalize(viewPos - FragPos);
            vec3 reflectDir = reflect(-lightDir, norm);  
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shine);
            vec3 specular = lights[i].colorMultiplier * lights[i].specular * (spec * material.specular);  

            // calculates the intensity of the crntPos based on its angle to the center of the light cone
            float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDir);

             // Calculate falloff based on the angle
            float falloff = pow(max(0.0, angle - outerCone) / (innerCone - outerCone), 2.0);
            
            // Apply falloff to diffuse and specular terms
            diffuse *= falloff;
            specular *= falloff;



            float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f)* lights[i].lightIntensity;

            // Assuming lightColor is the diffuse color of the light
            result += ((diffuse * inten + ambient) * lights[i].diffuse + specular * inten * lights[i].specular );
        }
    }

    return vec4(result * texColor, 1.0);
}


vec4 pointLight()
{	
     vec3 result = vec3(0.0);
     vec3 texColor = texture(textureSampler, texCoord).rgb;
     for (int i = 0; i < MaxLights; ++i)
     {
        if (lights[i].type == 2) // Point light
        {
              vec3 lightVec = lights[i].position - FragPos;
             
              // intensity of light with respect to distance
              float dist = length(lightVec);
              float a = 3.0;
              float b = 0.7;
              float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);
             
              // ambient
              vec3 ambient = lights[i].colorMultiplier * lights[i].ambient * material.ambient;
             
              // diffuse 
              vec3 norm = normalize(Normal);
              vec3 lightDir = normalize(lightVec);
              float diff = max(dot(norm, lightDir), 0.0);
              vec3 diffuse = lights[i].colorMultiplier * lights[i].diffuse * (diff * material.diffuse);
             
              // specular
              vec3 viewDir = normalize(viewPos - FragPos);
              vec3 reflectDir = reflect(-lightDir, norm);  
              float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shine);
              vec3 specular = lights[i].colorMultiplier * lights[i].specular * (spec * material.specular);  
             
              // Accumulate the lighting contributions
              result += (ambient + diffuse + specular) * lights[i].lightIntensity * inten;
        }  
     }

     return vec4(result * texColor, 1.0);
}




void main()
{
    // spotlight
    FragColor = spotLight() + direcLight() + pointLight();
    // Fog
    //float depth = logisticDepth(gl_FragCoord.z);
    //FragColor = spotLight() * (1.0f - depth) + vec4(depth * vec3(0.85f, 0.85f, 0.90f), 1.0f);
}