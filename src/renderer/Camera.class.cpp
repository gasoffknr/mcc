/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 05:46:56 by lfirmin           #+#    #+#             */
/*   Updated: 2025/07/10 05:46:56 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Camera.class.hpp"

#include <algorithm>

// Valeurs par défaut
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
	: m_position(position), m_worldUp(up), m_yaw(yaw), m_pitch(pitch)
{
	m_movementSpeed = SPEED;
	m_mouseSensitivity = SENSITIVITY;
	m_zoom = ZOOM;

	updateCameraVectors();
}

void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

	m_front = glm::normalize(front);
 	m_right = glm::normalize(glm::cross(m_front, m_worldUp));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 Camera::getProjectionMatrix(float aspect)
{
	return glm::perspective(glm::radians(m_zoom), aspect, 0.1f, 100.0f);
}

void Camera::processKeyboard(int direction, float deltaTime)
{
	float velocity = m_movementSpeed * deltaTime;

	if (direction == FORWARD)
		m_position += m_front * velocity;
	if (direction == BACKWARD)
		m_position -= m_front * velocity;
	if (direction == LEFT)
		m_position -= m_right * velocity;
	if (direction == RIGHT)
		m_position += m_right * velocity;
}

void Camera::processMouseMovement(float xoffset, float yoffset)
{
	xoffset *= m_mouseSensitivity;
	yoffset *= m_mouseSensitivity;

	m_yaw += xoffset;
	m_pitch += yoffset;

	if (m_pitch > 89.0f)
		m_pitch = 89.0f;
	if (m_pitch < -89.0f)
		m_pitch = -89.0f;

	updateCameraVectors();
}

glm::vec3 Camera::getPosition()
{
	return m_position;
}

glm::vec3 Camera::getFront()
{
	return m_front;
}

Camera::~Camera() {
}