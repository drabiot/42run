/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:13:08 by tchartie          #+#    #+#             */
/*   Updated: 2026/01/23 16:45:28 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <string>
# include <fstream>
# include <sstream>
# include <iostream>
# include <vector>
# include <map>
# include <cctype>
# include <sys/stat.h>
# include <thread>
# include <chrono>
# include <sstream>
# include <algorithm> 
# include <cstring>

# include "glad.h"
# include "glfw3.h"
# include "ft_glm.hpp"

# include "color.hpp"

# define AND	<<
# define PRINT	std::cout AND
# define ERROR	std::cerr AND
# define NLINE	PRINT std::endl
# define ENDL	AND std::endl
# define CENDL	AND BASE_COLOR ENDL
# define TAB	"\t"

typedef std::string str;

# define cref(type) const type &
# define ref(type) type &

extern int	WD_WIDTH;
extern int	WD_HEIGHT;
extern str	WD_NAME;

void	initWindow(GLFWwindow **window);
void	initGlad();
void    opengErrorMsg(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);

#endif //UTILS_HPP
