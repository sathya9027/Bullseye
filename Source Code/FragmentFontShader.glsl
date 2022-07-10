#version 330
uniform sampler2D _font;
uniform vec3 _fontcolor;
in vec2 _pixcoords;  

void main() 
{
	gl_FragColor = vec4(_fontcolor, texture( _font, _pixcoords));
}