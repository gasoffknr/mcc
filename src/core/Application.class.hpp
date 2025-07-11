/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.class.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:42:22 by lfirmin           #+#    #+#             */
/*   Updated: 2025/07/07 18:42:22 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Window.class.hpp"
#include "../renderer/Camera.class.hpp"

class Application
{
private:
    Window m_window;                    // Notre fenêtre encapsulée
    bool m_running;                     // État de l'application
    Camera m_camera;
    bool m_firstMouse;
    float m_lastX, m_lastY;

public:
    Application();                      // Constructeur : initialise tout
    ~Application();                     // Destructeur : cleanup

    int run();                         // Boucle principale + logique de jeu
    void shutdown();                   // Arrêt propre de l'application

    Application(const Application&) = delete;            // Pas de copie
    Application& operator=(const Application&) = delete; // Pas d'assignation
};

#endif