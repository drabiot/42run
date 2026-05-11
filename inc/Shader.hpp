/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 19:13:49 by tchartie          #+#    #+#             */
/*   Updated: 2026/05/11 19:30:52 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_HPP
# define SHADER_HPP

# include "utils.hpp"

class	Shader {
	public:
		unsigned int    id;
		Shader();
		Shader(const char *vertPath, const char *fragPath);
		~Shader();

		void			use() const;

		void			setInt(const str &name, int value) const;
		void			setFloat(const str &name, float value) const;
		void			setVec3(const str &name, const vec3 &v) const;
		void			setVec4(const str &name, const vec4 &v) const;
		void			setMat4(const str &name, const mat4 &m) const;

	private:
		unsigned int	_compile(const char *path, GLenum type) const;
		void			_checkLink() const;
};

#endif //SHADER_HPP
