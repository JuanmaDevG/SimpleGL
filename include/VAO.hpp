#pragma once

#include "VBO.hpp"
#include "EBO.hpp"


class VertexArray
{
    friend std::ostream& operator<<(std::ostream& os, const VertexArray& VAO);
public:
    VertexArray(VertexBuffer* VBO, ElementBuffer* EBO);

    //NOTE: destructor does not free VBO and EBO memory, just dettach
    ~VertexArray();

    inline void Bind() const;
    inline void Unbind() const;
private:
    uint32_t id;
    VertexBuffer* VBO;
    ElementBuffer* EBO;
};