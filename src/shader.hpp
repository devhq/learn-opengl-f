#ifndef SHADER_H
#define SHADER_H

#include <string>

class Shader
{
public:
	unsigned int id;
	int success;
	char infoLog[1024];

	Shader(const char* vertex_shader_file_path, const char* fragment_shader_file_path);

	void useProgram();
};

#endif