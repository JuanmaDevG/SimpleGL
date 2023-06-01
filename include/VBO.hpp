#pragma once

#include <iostream>
#include <cstdint>
#include <cstring>

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <glew.h>

class VertexArray;

class VertexBuffer
{
    friend class VertexArray;
    friend std::ostream& operator<<(std::ostream& os, const VertexBuffer& VBO);
public:
    VertexBuffer(const float* data, const size_t float_count, const uint8_t* f_per_vert, const uint8_t attrib_ptr_count);
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