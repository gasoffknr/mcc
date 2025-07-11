/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 04:48:02 by lfirmin           #+#    #+#             */
/*   Updated: 2025/07/09 04:48:02 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SHADER_HPP
# define SHADER_HPP

#include <glad/glad.h>           // GLAD EN PREMIER
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
    private:
        GLuint m_programID;
        std::string loadShaderFromFile(const std::string& path);
        void checkCompileErrors(GLuint shader, const std::string& type);

    public:
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        ~Shader();
        void use();

        void setFloat(const std::string& name, float value);
        void setInt(const std::string& name, int value);
        void setVec3(const std::string& name, const glm::vec3& value);
        void setMat4(const std::string& name, const glm::mat4& value);
};

#endif