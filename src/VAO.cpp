#include "VAO.hpp"

VertexArray::VertexArray(VertexBuffer* VBO, ElementBuffer* EBO)
: VBO(VBO), EBO(EBO)
{
    glGenVertexArrays(1, &id);
    Bind();
    this->VBO->Bind();
    this->EBO->Bind();

    size_t offset = 0ui64, stride;
    for(uint8_t index = 0; index < VBO->n_attrib_ptrs; index++, offset += stride)
    {
        stride = (size_t)VBO->f_per_vert[index] * sizeof(float);
        glVertexAttribPointer(
            index, 
            (int)VBO->f_per_vert[index], 
            GL_FLOAT, false,
            stride,
            (void*)offset
        );
        glEnableVertexAttribArray(index);
    }
    Unbind();
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &id);
    VBO = nullptr;
    EBO = nullptr;
}

inline void VertexArray::Bind() const
{
    glBindVertexArray(id);
    EBO->Bind();
}

inline void VertexArray::Unbind() const 
{ 
    glBindVertexArray(0);
    EBO->Unbind(); 
}


std::ostream& operator<<(std::ostream& s, const VertexArray& VAO)
{
    s 
        << "Vertex Array [" << VAO.id << "] with\n\t"
        << (*VAO.VBO) << "\n\t"
        << (*VAO.EBO) << '\n';
    return s;
}