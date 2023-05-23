#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <glew.h>

class Shader
{
    friend std::ostream& operator<<(std::ostream& s, const Shader&);
public:
    Shader(const std::string& v_shader_path, const std::string& f_shader_path);
    ~Shader();

    inline void Use() const;
    inline void Not_use() const;
private:
    uint32_t program;
    uint32_t v_shader, f_shader;

    inline void _self_free();
    uint32_t _create_shader(GLenum type, const std::string& sh_path) const;
};