#include "Common.h"
Shader::Shader() {
	this->programObj = NULL;
	this->vertexAttribute = NULL;
	this->uvAttribute = NULL;
	this->modelAttribute = NULL;
	this->viewAttribute = NULL;
	this->projectionAttribute = NULL;
}
Shader::~Shader() {

}
void Shader::ShaderInit() {
	//initializing glew after creating window
	glewInit();
	this->programObj = glCreateProgram();
}
string Shader::ReadShaderFile(const char* filename) {
	string code;
	ifstream file(filename);
	if (!file.good()) {
		cout << "Can't read file " << filename << endl;
		terminate();
	}
	else {
		file.seekg(0, ios::end);
		code.resize(file.tellg());
		file.seekg(0, ios::beg);
		file.read(&code[0], code.size());
		file.close();
	}
	return code;
}
void Shader::ProcessShaderFile(const char* filename, GLenum shaderType) {
	//initializing fragment shader
	string shaderCode = this->ReadShaderFile(filename);

	//reading fragment shader
	GLuint shaderObj = glCreateShader(shaderType);
	const char* code = shaderCode.c_str();
	const int size = shaderCode.size();
	glShaderSource(shaderObj, 1, &code, &size);

	//compiling fragment shader
	glCompileShader(shaderObj);
	glAttachShader(this->programObj, shaderObj);
}
void Shader::GetShaderAttributes() {
	this->vertexAttribute = glGetAttribLocation(this->programObj, "_vertices");
	this->uvAttribute = glGetAttribLocation(this->programObj, "_uvcoords");

	this->fontColorAttribute = glGetUniformLocation(this->programObj, "_fontcolor");
	this->modelAttribute = glGetUniformLocation(this->programObj, "_model");
	this->viewAttribute = glGetUniformLocation(this->programObj, "_view");
	this->projectionAttribute = glGetUniformLocation(this->programObj, "_projection");
}
void Shader::ApplyShader() {
	this->GetShaderAttributes();

	glLinkProgram(this->programObj);
	glUseProgram(this->programObj);
}