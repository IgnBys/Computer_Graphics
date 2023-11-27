#version 430 core

float AMBIENT = 0.1;

uniform vec3 lightPos;
uniform sampler2D earth;
uniform sampler2D clouds;




in vec3 vecNormal;
in vec3 worldPos;
in vec2 fragTexCoord;
out vec4 outColor;

void main()
{
    vec3 lightDir = normalize(lightPos - worldPos);
    vec3 normal = normalize(vecNormal); 
    float diffuse = max(0, dot(normal, lightDir));

    

    vec4 cloudColor = texture(clouds, fragTexCoord);
    vec4 earthColor = texture(earth, fragTexCoord);  
    vec3 finalColor = mix(vec3(1.0), earthColor.rgb, cloudColor.r);
    //outColor = vec4(finalColor, 1.0) * 5.5;
    outColor = vec4(finalColor * min(1, AMBIENT + diffuse), 1.0);
}
