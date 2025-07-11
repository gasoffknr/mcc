/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.class.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:42:10 by lfirmin           #+#    #+#             */
/*   Updated: 2025/07/07 18:42:10 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Application.class.hpp"
#include <glm/glm.hpp>
#include <iostream>
#include "../renderer/Shader.class.hpp"

// Constructeur
Application::Application()
	: m_window(800, 600, "Minecraft Clone"),
	  m_running(true),
	  m_camera(glm::vec3(2.0f, 1.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -135.0f, -20.0f),
	  //                                                                                    ^ virgule
	  m_firstMouse(true), m_lastX(400.0f), m_lastY(300.0f) {
	std::cout << "Application initialized" << std::endl;
}

// Destructeur
Application::~Application() {
    std::cout << "Application shutdown" << std::endl;
}

// Boucle principale
int Application::run() {
    std::cout << "Starting application..." << std::endl;

    Shader ourShader("assets/shaders/basic.vertex.glsl", "assets/shaders/basic.fragment.glsl");

    // Triangle vertices (position x, y, z pour chaque sommet)
	float vertices[] = {
		// Face avant
		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		// Face arrière
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f
	};

	unsigned int indices[] = {
		// Face avant (z = 0.5)
		0, 1, 2,   2, 3, 0,
		// Face arrière (z = -0.5)
		4, 5, 6,   6, 7, 4,
		// Face gauche
		7, 3, 0,   0, 4, 7,
		// Face droite
		1, 5, 6,   6, 2, 1,
		// Face haut
		3, 2, 6,   6, 7, 3,
		// Face bas
		0, 1, 5,   5, 4, 0
	};

    // Créer VAO et VBO
	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// BIND VAO EN PREMIER
	glBindVertexArray(VAO);

	// Setup VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Setup EBO (APRÈS avoir bindé le VAO)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Setup attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


    while (m_running && !m_window.shouldClose())
    {
        m_window.pollEvents();
    	double xpos, ypos;
    	glfwGetCursorPos(m_window.getHandle(), &xpos, &ypos);

    	if (m_firstMouse) {
    		m_lastX = xpos;
    		m_lastY = ypos;
    		m_firstMouse = false;
    	}

    	float xoffset = xpos - m_lastX;
    	float yoffset = m_lastY - ypos; // Inversé car y va de bas en haut
    	m_lastX = xpos;
    	m_lastY = ypos;

    	m_camera.processMouseMovement(xoffset, yoffset);
    	if (glfwGetKey(m_window.getHandle(), GLFW_KEY_W) == GLFW_PRESS)
    		m_camera.processKeyboard(FORWARD, 0.016f);
    	if (glfwGetKey(m_window.getHandle(), GLFW_KEY_S) == GLFW_PRESS)
    		m_camera.processKeyboard(BACKWARD, 0.016f);
    	if (glfwGetKey(m_window.getHandle(), GLFW_KEY_A) == GLFW_PRESS)
    		m_camera.processKeyboard(LEFT, 0.016f);
    	if (glfwGetKey(m_window.getHandle(), GLFW_KEY_D) == GLFW_PRESS)
    		m_camera.processKeyboard(RIGHT, 0.016f);
        glClearColor(0.2f, 0.8f, 0.3f, 1.0f);  // Vert cette fois
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.use();
    	glm::mat4 model = glm::mat4(1.0f);
    	model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));  // Rotation  // Identité (pas de transformation)
    	glm::mat4 view = m_camera.getViewMatrix();
    	glm::mat4 projection = m_camera.getProjectionMatrix(800.0f / 600.0f);

    	// Envoyer au shader
    	ourShader.setMat4("model", model);
    	ourShader.setMat4("view", view);
    	ourShader.setMat4("projection", projection);
        glBindVertexArray(VAO);
    	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        m_window.swapBuffers();
    }

    return 0;
}

// Arrêt propre
void Application::shutdown() {
    m_running = false;
}