#include "VBO.h"

VertexBuffer::VertexBuffer(const float* data, const size_t n_floats, const uint8_t* f_per_vert, const uint8_t n_attrib_ptrs)
{
    this->n_attrib_ptrs = n_attrib_ptrs;
    this->f_per_vert[n_attrib_ptrs];
    memcpy(this->f_per_vert, f_per_vert, (size_t)n_attrib_ptrs);

    this->n_floats = n_floats;
    this->data[n_floats];
    memcpy(this->data, data, n_floats * sizeof(float));

    glGenBuffers(1, &id);
    Bind();
    glBufferData(GL_ARRAY_BUFFER, n_floats * sizeof(float), data, GL_STATIC_DRAW);
    Unbind();
}


inline void VertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, id); }

inline void VertexBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }