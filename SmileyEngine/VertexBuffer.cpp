#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(GLfloat* vertices, GLsizeiptr size) {
  glGenBuffers(1, &_Handle);
  glBindBuffer(GL_ARRAY_BUFFER, _Handle);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VertexBuffer::Bind() {
  glBindBuffer(GL_ARRAY_BUFFER, _Handle);
}

void VertexBuffer::Unbind() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::Delete() {
  glDeleteBuffers(1, &_Handle);
}
