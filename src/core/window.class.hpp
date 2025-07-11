/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 08:26:45 by lfirmin           #+#    #+#             */
/*   Updated: 2025/07/07 08:33:43 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Window {
  private:

    GLFWwindow* m_window;                                     // Handle vers la fenêtre GLFW
    int m_width, m_height;                                    // Dimensions de la fenêtre en px
    std::string m_title;                                      // Titre affiché dans la barre de titre
  public:

    Window(int width, int height, const std::string& title);  // Constructeur : crée la fenêtre GLFW + contexte OpenGL
    ~Window();                                                // Destructeur : nettoie GLFW proprement

    bool shouldClose();                                       // Retourne true si l'utilisateur veut fermer (croix rouge)
    void swapBuffers();                                       // Échange front/back buffer (affiche ce qu'on a rendu)
    void pollEvents();                                        // Traite les événements (clavier, souris, fermeture)
    GLFWwindow* getHandle();                                  // Donne accès au pointeur GLFW (pour d'autres classes)
    Window(const Window&) = delete;                           // Interdit la copie (une seule fenêtre)
    Window& operator=(const Window&) = delete;                // Interdit l'assignation
};

#endif