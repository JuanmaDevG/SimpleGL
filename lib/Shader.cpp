#include "Shader.h"

/*
    PUBLIC FUNCTIONS
*/

//
Shader::Shader(const std::string& v_shader_path, const std::string& f_shader_path)
{
    v_shader = _create_shader(GL_VERTEX_SHADER, v_shader_path);
    f_shader = _create_shader(GL_FRAGMENT_SHADER, f_shader_path);

    program = glCreateProgram();
    glAttachShader(program, v_shader);
    glAttachShader(program, f_shader);
    glLinkProgram(program);

    {
        int success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if(!success)
        {
            int length;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
            char* infoLog = (char*)alloca(length * sizeof(char));
            glGetProgramInfoLog(program, length, nullptr, infoLog);
            std::cout << "ERROR: could not link shader, will delete. " << infoLog << std::endl;
            _self_free();
        }
    }
    
}


inline void Shader::_self_free()
{
    //Luego...
}

inline void Shader::Use() const { glUseProgram(program); }

inline void Shader::Not_use() const { glUseProgram(0); }