#include "ElementBuffer.h"

ElementBuffer::ElementBuffer(GLuint* indices, GLsizeiptr size) {
  glGenBuffers(1, &_Handle);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _Handle);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void ElementBuffer::Bind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _Handle);
}

void ElementBuffer::Unbind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ElementBuffer::Delete() {
  glDeleteBuffers(1, &_Handle);
}
