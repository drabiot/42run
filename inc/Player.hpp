/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 14:16:32 by tchartie          #+#    #+#             */
/*   Updated: 2026/10/06 14:40:25 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "utils.hpp"

class Player {
	public:
		Player();

		void	update(GLFWwindow *window, float dt);
		mat4	getModelMatrix() const;
		vec3	getPosition() const;

	private:
		vec3	_pos;
		float	_speed;
};

#endif //PLAYER_HPP
