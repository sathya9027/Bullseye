#pragma once
class Shader
{
private:

public:
	Shader();
	~Shader();
	GLuint programObj;
	GLuint fontColorAttribute;
	GLuint vertexAttribute, uvAttribute, modelAttribute, viewAttribute, projectionAttribute;
	string ReadShaderFile(const char* filename);
	void ShaderInit();
	void ProcessShaderFile(const char* filename, GLenum shaderType);
	void GetShaderAttributes();
	void ApplyShader();
};