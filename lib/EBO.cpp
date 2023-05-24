#include "EBO.hpp"


ElementBuffer::ElementBuffer(const uint32_t* data, const uint32_t idx_count) : idx_count(idx_count)
{
    glGenBuffers(1, &id);
    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, idx_count * sizeof(uint32_t), data, GL_STATIC_DRAW);
    Unbind();
}

ElementBuffer::~ElementBuffer()
{
    glDeleteBuffers(1, &id);
    idx_count = 0ui32;
}

inline void ElementBuffer::Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id); }

inline void ElementBuffer::Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }


std::ostream& operator<<(std::ostream& s, const ElementBuffer& EBO)
{
    s << "Element Buffer [" << EBO.id << "] indexing " << EBO.idx_count << " vertices";
}