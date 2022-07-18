#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject() {
  glGenVertexArrays(1, &_Handle);
}

void VertexArrayObject::LinkAttrib(
  VertexBuffer vertexBuffer, 
  GLuint layout,
  GLuint numComponents,
  GLenum type,
  GLsizeiptr stride,
  void* offset
) {
  vertexBuffer.Bind();
  glVertexAttribPointer(layout, numComponents, GL_FLOAT, GL_FALSE, stride, offset);
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
