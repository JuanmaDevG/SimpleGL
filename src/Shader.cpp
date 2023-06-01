#include "Shader.hpp"

/*
    PUBLIC FUNCTIONS
*/

//
Shader::Shader(const std::string& v_shader_path, const std::string& f_shader_path) : program(0)
{
    v_shader = _create_shader(GL_VERTEX_SHADER, v_shader_path);
    f_shader = _create_shader(GL_FRAGMENT_SHADER, f_shader_path);
    
    if(!(v_shader && f_shader)) return;

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
            std::cerr << "ERROR: cannot link program, will empty.\n" << infoLog << std::endl;
            _self_free();
            return;
        }
    }
    glValidateProgram(program);
}


Shader::~Shader() { _self_free(); }


inline void Shader::_self_free()
{
    glDeleteProgram(program);
    glDeleteShader(v_shader);
    glDeleteShader(f_shader);
    program = v_shader = v_shader = 0;
}


uint32_t Shader::_create_shader(GLenum type, const std::string& sh_path) const
{
    uint32_t shader = glCreateShader(type);

    std::ifstream file(sh_path, std::ios::in);
    if(!file.is_open()) return 0ui32;

    //Extra parentheses for the compiler to interpret the code as an object, and not as a function
    std::string src((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    const char* src_ptr = src.c_str();

    glShaderSource(shader, 1, &src_ptr, nullptr);
    glCompileShader(shader);
    
    {
        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            int length;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
            char* infoLog = (char*)alloca(length * sizeof(char));

            std::cerr 
                << "Error: cannot compile "
                << (type == GL_VERTEX_SHADER ? "vertex" : (type == GL_FRAGMENT_SHADER ? "fragment" : "geometry"))
                << " shader and will self destroy.\n"
                << infoLog << std::endl;
            glDeleteShader(shader);
            return 0;
        }
    }
    return shader;
}

inline void Shader::Use() const { glUseProgram(program); }

inline void Shader::Not_use() const { glUseProgram(0); }


/*
    Operator overloads
*/

//
std::ostream& operator<<(std::ostream& s, const Shader& prog)
{
    s << "Shader Program [" << prog.program << "] (v_shader: " << prog.v_shader << ") (frag_shader: " << prog.f_shader << ")";
    return s;
}