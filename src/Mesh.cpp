/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 19:25:06 by tchartie          #+#    #+#             */
/*   Updated: 2026/05/11 19:26:45 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mesh.hpp"

Mesh::Mesh(const std::vector<Vertex> &vertices) : _ebo(0), _indexed(false) {
	_setup(vertices, nullptr);
}

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices) : _ebo(0), _indexed(true) {
	_setup(vertices, &indices);
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);
	if (_indexed)
		glDeleteBuffers(1, &_ebo);
}

void	Mesh::_setup(const std::vector<Vertex> &vertices, const std::vector<unsigned int> *indices) {
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glBindVertexArray(_vao);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER,
		vertices.size() * sizeof(Vertex),
		vertices.data(),
		GL_STATIC_DRAW);

	if (indices) {
		glGenBuffers(1, &_ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size() * sizeof(unsigned int), indices->data(), GL_STATIC_DRAW);
		_count = indices->size();
	} else {
		_count = vertices.size();
	}

	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	// normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);

	// texCoord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texCoord));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void	Mesh::draw(const Shader &shader, const mat4 &model) const {
	shader.use();
	shader.setMat4("model", model);

	glBindVertexArray(_vao);
	if (_indexed)
		glDrawElements(GL_TRIANGLES, _count, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, _count);
	glBindVertexArray(0);
}
