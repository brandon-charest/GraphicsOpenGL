#pragma once
#include <string>
#include <GL/glew.h>
class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();

	// const prevents strings from ever being changed
	void compileShaders(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath);
	void linkShaders();

	void addAttribute(const std::string &attributeName);
	void use();
	void unuse();
private:
	GLuint _programID;
	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
	int _numAttributes;

	void compileShader(const std::string &filePath, GLuint id);
};

