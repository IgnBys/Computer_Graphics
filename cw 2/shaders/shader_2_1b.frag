#version 430 core
out vec4 fragColor;

flat in float hue;
out vec4 out_color;

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}
void main()
{
	out_color  = vec4(hsv2rgb(vec3(hue,1,1)), 1.0);
}