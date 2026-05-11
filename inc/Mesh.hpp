/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 19:23:35 by tchartie          #+#    #+#             */
/*   Updated: 2026/05/11 19:40:02 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_HPP
# define MESH_HPP

# include "Shader.hpp"
# include "utils.hpp"

class	Shader;

struct	Vertex {
	vec3	position;
	vec3	normal;
	vec2	texCoord;
};

class	Mesh {
	public:
		Mesh(const std::vector<Vertex> &vertices);
		Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices);
		~Mesh();

		void			draw(const Shader &shader, const mat4 &model) const;

	private:
		unsigned int	_vao;
		unsigned int	_vbo;
		unsigned int	_ebo;
		unsigned int	_count;
		bool			_indexed;

		void			_setup(const std::vector<Vertex> &vertices, const std::vector<unsigned int> *indices);
};

#endif //MESH_HPP
