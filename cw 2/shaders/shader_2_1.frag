#version 430 core
flat in vec4 color;
out vec4 out_color;

uniform float time; 

void main()
{
    float mixFactor = 0.5 * (1.0 + sin(time));

    vec4 backgroundColor = vec4(0.0, 0.3, 0.3, 1.0); 
    vec4 objectColor = color;

    vec4 mixedColor = mix(backgroundColor, objectColor, mixFactor);
    
    out_color = mixedColor;
}
