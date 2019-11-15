#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
	// constructor reads and builds the shader
	Shader();
	// use/activate the shader
	uint use();
	void stop();
	// utility uniform functions
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;

	void setMat4(const std::string & name, const mat4x4 & mat) const;

public:
	unsigned int ID;
private:
	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 vertices;\n"
		"layout (location = 1) in vec3 Normal;\n"
		"layout (location = 2) in vec2 TexCoords;\n"
		"layout (location = 3) in vec4 Colors;\n"
		"out vec4 ourColor;\n"
		"out vec2 TexCoord;\n"
		"uniform mat4x4 view;\n"
		"uniform mat4x4 projection;\n"
		"uniform mat4x4 model;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = projection * view * model * vec4(vertices, 1.0);\n"
		"   TexCoord = vec2(TexCoords.x, TexCoords.y);\n"
		"   ourColor = Colors;\n"
		"}\0";

	const char *fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec4 ourColor;\n"
		"in vec2 TexCoord;\n"
		"uniform bool render;\n"
		"uniform sampler2D Diffuse_Map1;\n"
		"void main()\n"
		"{\n"
			"if (render == true) { FragColor = texture(Diffuse_Map1, TexCoord) * vec4(1.0,1.0,1.0,1.0); }\n"
			"if (render == false){ FragColor =  ourColor;  }\n"
		"}\0";
};

#endif