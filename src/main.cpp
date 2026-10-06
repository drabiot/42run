/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:11:37 by tchartie          #+#    #+#             */
/*   Updated: 2026/10/06 14:44:56 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include "Player.hpp"
#include "Camera.hpp"

int		WD_WIDTH = 800;
int		WD_HEIGHT = 800;
bool	PAUSE = false;
str		WD_NAME = "42run";

int	main(void) {
	GLFWwindow *window;
	
	initWindow(&window);
	initGlad();

	{
		double				prevTime = 0.0;
		double				crntTime = 0.0;
		double				deltaTime;
		unsigned int		counter = 0;
		double				lastFrame = 0.0;

		std::vector<Vertex>	cubeVertices = makeCube();
		Mesh				cubeMesh(cubeVertices);
		Shader				shader("shader/basic.vert","shader/basic.frag");
		Player				player;

		while(!glfwWindowShouldClose(window)) {
			//Create FPS counter
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

			float dt = static_cast<float>(crntTime - lastFrame);
			lastFrame = crntTime;
			player.update(window, dt);

			//Start Render
			glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			shader.use();

			mat4 view = lookAt(vec3(0.0f, 0.0f, 3.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
			mat4 proj = perspective(radians(45.0f), (float)WD_WIDTH / (float)WD_HEIGHT, 0.1f, 100.0f);
			mat4 model = player.getModelMatrix();
			
			shader.setMat4("proj", proj);
			shader.setMat4("view", view);
			shader.setMat4("model", model);

			//Link cube model to player pos
			cubeMesh.draw(shader, model);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
	
	glfwDestroyWindow(window);
	glfwTerminate();
	return (0);
}
