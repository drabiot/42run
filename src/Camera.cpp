/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 14:03:52 by tchartie          #+#    #+#             */
/*   Updated: 2026/10/06 14:17:54 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Camera.hpp"

Camera::Camera(vec3 position) {
	this->Position = position;
}

void	Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane) {
	mat4	view = mat4(1.0f);
	mat4	projection = mat4(1.0f);

	view = lookAt(Position, Position + Orientation, Up);
	projection = perspective(radians(FOVdeg), static_cast<float>(WD_WIDTH) / static_cast<float>(WD_HEIGHT), nearPlane, farPlane);

	cameraMatrix = projection * view;
}

void	Camera::Matrix(Shader &shader, const char *uniform) {
	glUniformMatrix4fv(glGetUniformLocation(shader.id, uniform), 1, GL_FALSE, value_ptr(cameraMatrix));
}

void	Camera::Inputs(GLFWwindow *window) {
	//Handles Display inputs
	static bool	pauseKey = false;

	//Utility key input
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && !pauseKey) {
		PAUSE = !PAUSE;
		pauseKey = true;
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE && pauseKey)
		pauseKey = false;
}
