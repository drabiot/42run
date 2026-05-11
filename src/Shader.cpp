/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 19:13:56 by tchartie          #+#    #+#             */
/*   Updated: 2026/05/11 19:20:19 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Shader.hpp"

static str	_readFile(const char *path) {
	std::ifstream	in(path, std::ios::binary);

	if (!in)
		throw std::runtime_error(str("Failed to open shader: ") + path);

	str contents;
	in.seekg(0, std::ios::end);
	contents.resize(in.tellg());
	in.seekg(0, std::ios::beg);
	in.read(&contents[0], contents.size());
	return (contents);
}

unsigned int	Shader::_compile(const char *path, GLenum type) const {
	str				src = _readFile(path);
	const char		*cstr = src.c_str();
	unsigned int	shader = glCreateShader(type);
	int				ok;
	char			log[1024];

	glShaderSource(shader, 1, &cstr, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
	if (!ok) {
		glGetShaderInfoLog(shader, 1024, NULL, log);
		glDeleteShader(shader);
		throw std::runtime_error(
			str(RED "Shader compile error (") + path + "):\n" + log + BASE_COLOR
		);
	}
	return (shader);
}

void	Shader::_checkLink() const {
	int	 	ok;
	char	log[1024];

	glGetProgramiv(id, GL_LINK_STATUS, &ok);
	if (!ok) {
		glGetProgramInfoLog(id, 1024, NULL, log);
		throw std::runtime_error(
			str(RED "Shader link error:\n") + log + BASE_COLOR
		);
	}
}

Shader::Shader() : id(0) {}

Shader::Shader(const char *vertPath, const char *fragPath) {
	unsigned int	vert = _compile(vertPath, GL_VERTEX_SHADER);
	unsigned int	frag = _compile(fragPath, GL_FRAGMENT_SHADER);

	id = glCreateProgram();
	glAttachShader(id, vert);
	glAttachShader(id, frag);
	glLinkProgram(id);

	glDeleteShader(vert);
	glDeleteShader(frag);

	_checkLink();
}

Shader::~Shader() {
	if (id)
		glDeleteProgram(id);
}

void	Shader::use() const {
	glUseProgram(id);
}

void	Shader::setInt(const str &name, int value) const {
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void	Shader::setFloat(const str &name, float value) const {
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void	Shader::setVec3(const str &name, const vec3 &v) const {
	glUniform3f(glGetUniformLocation(id, name.c_str()), v.x, v.y, v.z);
}

void	Shader::setVec4(const str &name, const vec4 &v) const {
	glUniform4f(glGetUniformLocation(id, name.c_str()), v.x, v.y, v.z, v.w);
}

void	Shader::setMat4(const str &name, const mat4 &m) const {
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, value_ptr(m));
}
