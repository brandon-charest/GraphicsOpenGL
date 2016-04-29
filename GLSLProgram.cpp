#include "GLSLProgram.h"
#include "Errors.h"
#include <fstream>
#include <vector>

/* Initialization list used below
** good programming practice?
** initializes private variables to 0*/

GLSLProgram::GLSLProgram() : _programID(0), _vertexShaderID(0), _fragmentShaderID(0), _numAttributes(0)
{
}


GLSLProgram::~GLSLProgram()
{
}

//Code altered from OpenGL wiki on how to open shader files and compile them
void GLSLProgram::compileShaders(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath)
{
	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaderID == 0) {
		fatalError("Vertex shader failed to be created!");
	}


	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragmentShaderID == 0) {
		fatalError("Fragment shader failed to be created!");
	}

	compileShader(vertexShaderFilePath, _vertexShaderID);
	compileShader(fragmentShaderFilePath, _fragmentShaderID);
}

//Link shaders from OpenGL wiki
void GLSLProgram::linkShaders()
{
	//Vertex and fragment shaders are successfully compiled.
	//Now time to link them together into a program.
	//Get a program object.
	_programID = glCreateProgram();

	//Attach our shaders to our program
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);

	//Link our program
	glLinkProgram(_programID);

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

		//We don't need the program anymore.
		glDeleteProgram(_programID);
		//Don't leak shaders either.
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);

		std::printf("%s\n", &(errorLog[0]));
		fatalError("shader failed to link!");
	}

	//Always detach shaders after a successful link.
	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
}

void GLSLProgram::addAttribute(const std::string & attributeName)
{
	glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
}

void GLSLProgram::use()
{
	glUseProgram(_programID);
	for (int i = 0; i < _numAttributes; i++) {
		glEnableVertexAttribArray(i);
	}
}

void GLSLProgram::unuse()
{
	glUseProgram(0);
	for (int i = 0; i < _numAttributes; i++) {
		glDisableVertexAttribArray(i);
	}
}

void GLSLProgram::compileShader(const std::string & filePath, GLuint id)
{
	glCreateProgram();

	std::ifstream shaderFile(filePath);
	if (shaderFile.fail()) {
		perror(filePath.c_str());
		fatalError("Failed to open " + filePath);
	}

	std::string fileContents = "";
	std::string line;
	while (std::getline(shaderFile, line)) {
		fileContents += line + "\n";
	}
	shaderFile.close();

	const char *contentsPointer = fileContents.c_str();
	glShaderSource(id, 1, &contentsPointer, nullptr);

	glCompileShader(id);

	//error checking from OpenGL wiki
	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE) {

		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		//maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);

		glDeleteShader(id);

		std::printf("%s\n", &(errorLog[0]));
		fatalError("shader" + filePath + "failed to complie");
	}
}
