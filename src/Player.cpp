/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 14:17:02 by tchartie          #+#    #+#             */
/*   Updated: 2026/10/06 14:42:07 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.hpp"

Player::Player() : _pos(0.0f), _speed(3.0f) {}

void	Player::update(GLFWwindow *window, float dt) {
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		_pos.x -= _speed * dt;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		_pos.x += _speed * dt;
}

mat4	Player::getModelMatrix() const {
	return (translate(_pos));
}

vec3	Player::getPosition() const {
	return (_pos);
}
