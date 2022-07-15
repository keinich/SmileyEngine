#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject() {
  glGenVertexArrays(1, &_Handle);
}

void VertexArrayObject::LinkVertexBuffer(VertexBuffer vertexBuffer, GLuint layout) {
  vertexBuffer.Bind();
  glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(layout);
  vertexBuffer.Unbind();
}

void VertexArrayObject::Bind() {
  glBindVertexArray(_Handle);
}

void VertexArrayObject::Unbind() {
  glBindVertexArray(0);
}

void VertexArrayObject::Delete() {
  glDeleteVertexArrays(1, &_Handle);
}
