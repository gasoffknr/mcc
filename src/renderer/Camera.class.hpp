/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 05:34:18 by lfirmin           #+#    #+#             */
/*   Updated: 2025/07/10 05:34:18 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
	private:
		glm::vec3 m_position;
		glm::vec3 m_front, m_up, m_right, m_worldUp;
		float m_yaw, m_pitch;
		float m_movementSpeed, m_mouseSensitivity, m_zoom;
		void updateCameraVectors();

	public:
		Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);
		~Camera();

		glm::mat4 getViewMatrix();
		glm::mat4 getProjectionMatrix(float aspect);
		void processKeyboard(int direction, float deltaTime);
		void processMouseMovement(float xoffset, float yoffset);
		glm::vec3 getPosition();
		glm::vec3 getFront();
};

#endif