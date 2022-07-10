#version 330
in vec2 _pixcoords;
uniform sampler2D _pixcolor;
void main()
{
	/*if (texture(_pixcolor, _pixcoords).a < 0.1) {
		discard;
	}*/
	gl_FragColor = texture(_pixcolor, _pixcoords);
}