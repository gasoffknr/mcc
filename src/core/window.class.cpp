/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:59:58 by lfirmin           #+#    #+#             */
/*   Updated: 2025/07/07 18:00:14 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <glad/glad.h>
#include "Window.class.hpp"
#include <iostream>

Window::Window(int width, int height, const std::string& title)
    : m_width(width), m_height(height), m_title(title), m_window(nullptr)
{
    // Initialiser GLFW (obligatoire avant toute autre fonction GLFW)
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }
    // Configuration du contexte OpenGL avant création fenêtre
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Créer la fenêtre avec les dimensions et titre passés en paramètre
    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
    if (!m_window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate(); // Nettoyer GLFW si échec
        return;
    }
    // Rendre ce contexte OpenGL actif pour ce thread
    glfwMakeContextCurrent(m_window);
    // Charger les fonctions OpenGL modernes via GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }
}

Window::~Window()
{
    if (m_window)
    {
        glfwDestroyWindow(m_window);   // Détruit la fenêtre
        m_window = nullptr;            // Évite les double-free
    }
    glfwTerminate();                   // Termine GLFW
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(m_window);  // retourner true/false
}

void Window::swapBuffers() {
    glfwSwapBuffers(m_window);  // swap les buffers
}

void Window::pollEvents() {
    glfwPollEvents();  // traiter les événements
}

GLFWwindow* Window::getHandle() {
    return m_window;  // retourner le pointeur
}