/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:41:16 by tchartie          #+#    #+#             */
/*   Updated: 2026/01/23 16:45:13 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

void	initWindow(GLFWwindow **window) {
	//Initialize GLFW
	glfwInit();
	
	//Tell GLFW that we use version 3.3 of OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
		
	//Tell GLFW that we are using CORE profile so we only have modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	//Create a GLFW window object & protect it
	*window = glfwCreateWindow(WD_WIDTH, WD_HEIGHT, (str(WD_NAME) + ":").c_str(), NULL, NULL);
	
	if (!*window) {
		glfwTerminate();
		throw std::runtime_error(std::string("Failed to create GLFW window"));
	}

	// Introduce the window into the current context
	glfwMakeContextCurrent(*window);
}

void	initGlad() {
	//Load GLAD so it configures OpenGL
	gladLoadGL();
	
	// Specify the viewport of OpenGL in the Window
	glViewport(0, 0, WD_WIDTH, WD_HEIGHT);
	glDebugMessageCallback(opengErrorMsg, 0);
}

void    opengErrorMsg(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
	(void)length;
	(void)source;
	(void)id;
	(void)userParam;
	std::string severityColor;
	switch (severity){
		case GL_DEBUG_SEVERITY_LOW:
			severityColor = GREEN;
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			severityColor =  YELLOW;
			break;
		case GL_DEBUG_SEVERITY_HIGH:
			severityColor =  RED;
			break;
		default:
			return ; //these are notifications and not really important
			severityColor =  WHITE;
	}

	PRINT RED "Opengl Message: " << severityColor;

	switch (type) {
		case GL_DEBUG_TYPE_ERROR:
			PRINT "ERROR; ";
			break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			PRINT "DEPRECATED_BEHAVIOR; ";
			break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			PRINT "UNDEFINED_BEHAVIOR; ";
			break;
		case GL_DEBUG_TYPE_PORTABILITY:
			PRINT "PORTABILITY; ";
			break;
		case GL_DEBUG_TYPE_PERFORMANCE:
			PRINT "PERFORMANCE; ";
			break;
		case GL_DEBUG_TYPE_OTHER:
			PRINT "OTHER; ";
			break;
		default:
			PRINT "NO TYPE; ";
	}

	PRINT message CENDL;
}
