/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 04:56:29 by lfirmin           #+#    #+#             */
/*   Updated: 2025/07/09 04:56:29 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.class.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

std::string Shader::loadShaderFromFile(const std::string& path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "ERROR: Could not open shader file: " << path << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}

void Shader::use()
{
    glUseProgram(m_programID);  // Active ce shader pour tous les prochains rendus
}

void Shader::setInt(const std::string& name, int value)
{
    GLint location = glGetUniformLocation(m_programID, name.c_str());    // Trouve la variable dans le shader
    glUniform1i(location, value);    // Envoie la valeur
}

void Shader::setFloat(const std::string& name, float value)
{
    GLint location = glGetUniformLocation(m_programID, name.c_str());
    glUniform1f(location, value);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value)
{
    GLint location = glGetUniformLocation(m_programID, name.c_str());
    glUniform3f(location, value.x, value.y, value.z);
}

void Shader::setMat4(const std::string& name, const glm::mat4& value)
{
    GLint location = glGetUniformLocation(m_programID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

std::string loadShaderFromFile(const std::string& path)
{
	std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "ERROR: Could not open shader file: " << path << std::endl;
        return "";
    }
	std::stringstream buffer;
	buffer << file.rdbuf();
    file.close();
	return buffer.str();
}

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string vertexCode = loadShaderFromFile(vertexPath);
    std::string fragmentCode = loadShaderFromFile(fragmentPath);

	//vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* vertexSource = vertexCode.c_str();
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	checkCompileErrors(vertexShader, "VERTEX");

    //fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentSource = fragmentCode.c_str();
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
   	glCompileShader(fragmentShader);
    checkCompileErrors(fragmentShader, "FRAGMENT");

	m_programID = glCreateProgram();
	//attach
	glAttachShader(m_programID, vertexShader);
	glAttachShader(m_programID, fragmentShader);
    //link
	glLinkProgram(m_programID);
	checkCompileErrors(m_programID, "PROGRAM");
    //clear shader
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    glDeleteProgram(m_programID);  // Libère le programme OpenGL
}

void Shader::checkCompileErrors(GLuint shader, const std::string& type) {
    GLint success;
    GLchar infoLog[1024];

    if (type == "PROGRAM")
    {
    	glGetProgramiv(shader, GL_LINK_STATUS, &success);
    	if (!success)
   		{
  	    	glGetProgramInfoLog(shader, 1024, NULL, infoLog);
 	    	std::cerr << "ERROR::PROGRAM_LINKING_ERROR\n" << infoLog << std::endl;
 	    }
	}
    else
    {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
          glGetShaderInfoLog(shader, 1024, NULL, infoLog);
          std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << std::endl;
        }
    }
}