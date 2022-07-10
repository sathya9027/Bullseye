#version 330
uniform mat4 _model;
uniform mat4 _view;
uniform mat4 _projection;
in vec2 _vertices;
in vec2 _uvcoords;
out vec2 _pixcoords;
void main()
{
	vec4 _local = vec4(_vertices, 0, 1);
	gl_Position = _projection * _view * _model * _local;
	_pixcoords = _uvcoords;
}