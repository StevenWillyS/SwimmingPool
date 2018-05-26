#version 330 core
in vec3 ourColor;
in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

// Texture samplers
uniform sampler2D ourTexture;
struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirLight dirLight;
uniform vec3 viewPos;
uniform float shininess = 20;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

void main()
{
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
	
    //gl_FragColor = texture(ourTexture, TexCoord);
	gl_FragColor = vec4(result, 1.0);	
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(ourTexture, TexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(ourTexture, TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(ourTexture, TexCoord));
    return (ambient + diffuse + specular);
}