#include "hzpch.h"

#include "Hazel/Core.h"
#include "Hazel/Renderer/Shader.h"

#include <glad/glad.h>

namespace Hazel
{
	Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertexShader);

			HZ_CORE_ERROR("{0}", infoLog.data());
			HZ_CORE_ASSERT(false, "Failed to compile vertex shader!");

			return;
		}

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);

			HZ_CORE_ERROR("{0}", infoLog.data());
			HZ_CORE_ASSERT(false, "Failed to compile fragment shader!");

			return;
		}

		m_ProgramId = glCreateProgram();

		glAttachShader(m_ProgramId, vertexShader);
		glAttachShader(m_ProgramId, fragmentShader);

		glLinkProgram(m_ProgramId);

		GLint isLinked = 0;
		glGetProgramiv(m_ProgramId, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_ProgramId, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_ProgramId, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(m_ProgramId);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			HZ_CORE_ERROR("{0}", infoLog.data());
			HZ_CORE_ASSERT(false, "Failed to link shader program!");

			return;
		}

		//may need to track these ids and delete in the dtor
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		glDetachShader(m_ProgramId, vertexShader);
		glDetachShader(m_ProgramId, fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_ProgramId);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_ProgramId);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}
}