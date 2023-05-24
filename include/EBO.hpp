#pragma once

#include <iostream>
#include <cstdint>
#include <glew.h>

class VertexArray;

class ElementBuffer
{
    friend class vertexArray;
    friend std::ostream& operator<<(std::ostream& os, const ElementBuffer&);
public:
    ElementBuffer(const uint32_t* data, const uint32_t index_count);
    ~ElementBuffer();

    inline void Bind() const;
    inline void Unbind() const;
private:
    uint32_t id;
    uint32_t idx_count;
};