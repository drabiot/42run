/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:11:37 by tchartie          #+#    #+#             */
/*   Updated: 2026/01/23 16:55:57 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

int		WD_WIDTH = 800;
int		WD_HEIGHT = 800;
str		WD_NAME = "42run";

int	main(void) {
	GLFWwindow *window;
	
	initWindow(&window);
	initGlad();

	double			prevTime = 0.0;
	double			crntTime = 0.0;
	double			deltaTime;
	unsigned int	counter = 0;

	while(!glfwWindowShouldClose(window)) {
		crntTime = glfwGetTime();
		deltaTime = crntTime - prevTime;
		counter++;
		if (deltaTime >= 1.0 / 30.0) {
			str FPS	= std::to_string((1.0 / deltaTime) * counter);
			str	ms	= std::to_string((deltaTime / counter) * 1000);
			
			str	newTitle = WD_NAME + ":" + " FPS:" + FPS + " ms:" + ms;
			glfwSetWindowTitle(window, newTitle.c_str());
			prevTime = crntTime;
			counter = 0;
		}

		glfwPollEvents();
	}
	
	glfwDestroyWindow(window);
	glfwTerminate();

	return (0);
}
