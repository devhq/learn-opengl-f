#include "shader.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>

Shader::Shader(const char* vertex_shader_file_path, const char* fragment_shader_file_path)
{
    std::ifstream   v_file, f_file;
    std::string     v_str, f_str;

    v_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        v_file.open(vertex_shader_file_path);
        std::stringstream v_ss;
        v_ss << v_file.rdbuf();
        v_file.close();
        v_str = v_ss.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "Error: Failed to read vertex shader" << std::endl;
    }

    f_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        f_file.open(fragment_shader_file_path);
        std::stringstream f_ss;
        f_ss << f_file.rdbuf();
        f_file.close();
        f_str = f_ss.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "Error: Failed to read fragment shader file" << std::endl;
    }

    const char* v_code = v_str.c_str();
    const char* f_code = f_str.c_str();

    unsigned int v_shader;
    v_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(v_shader, 1, &v_code, NULL);
    glCompileShader(v_shader);
    success = 0;
    infoLog[0] = '\0';
    glGetShaderiv(v_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(v_shader, 1024, NULL, infoLog);
        std::cout << "Error: Vertex shader compilation failed\n" << infoLog << std::endl;
    }

    unsigned int f_shader;
    f_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(f_shader, 1, &f_code, NULL);
    glCompileShader(f_shader);
    success = 0;
    infoLog[0] = '\0';
    glGetShaderiv(f_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(f_shader, 1024, NULL, infoLog);
        std::cout << "Error: Fragment shader compilation failed\n" << infoLog << std::endl;
    }

    id = glCreateProgram();
    glAttachShader(id, v_shader);
    glAttachShader(id, f_shader);
    glLinkProgram(id);
    success = 0;
    infoLog[0] = '\0';
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(id, 1024, NULL, infoLog);
        std::cout << "Error: Program linking failed\n" << infoLog << std::endl;
    }

    glDeleteShader(v_shader);
    glDeleteShader(f_shader);
}

void Shader::useProgram()
{
    glUseProgram(id);
}