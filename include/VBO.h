#pragma once

#include <iostream>
#include <cstdint>
#include <cstring>
#include <glew.h>

class VertexBuffer
{
    friend std::ostream& operator<<(std::ostream& os, const VertexBuffer& VBO);
public:
    VertexBuffer(const float* data, const size_t n_floats, const uint8_t* f_per_vert, const uint8_t attrib_ptrs);
    ~VertexBuffer();

    inline void Bind() const;
    inline void Unbind() const;
private:
    uint32_t id;
    float* data;
    size_t n_floats;
    uint8_t* f_per_vert;
    uint8_t n_attrib_ptrs;
};