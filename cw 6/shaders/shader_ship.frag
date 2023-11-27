#version 430 core

float AMBIENT = 0.1;

uniform vec3 lightPos;
uniform sampler2D ship;
uniform sampler2D rust;
uniform sampler2D asteroid;




in vec3 vecNormal;
in vec3 worldPos;
in vec2 fragTexCoord;
out vec4 outColor;

void main()
{
    vec3 lightDir = normalize(lightPos - worldPos);
    vec3 normal = normalize(vecNormal); 
    float diffuse = max(0, dot(normal, lightDir));

    
    vec4 asteroidColor = texture(asteroid, fragTexCoord);
    vec4 rustColor = texture(rust, fragTexCoord);
    vec4 shipColor = texture(ship, fragTexCoord);  
    vec3 mixedRust = mix(vec3(1.0), shipColor.rgb, rustColor.r);
    vec3 finalColor = mix(mixedRust, asteroidColor.rgb, asteroidColor.r);

    //outColor = vec4(finalColor, 1.0) * 5.5;
    outColor = vec4(finalColor * min(1, AMBIENT + diffuse), 1.0);
}
