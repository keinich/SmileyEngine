#pragma once

#include <glad/glad.h>

#include "VertexBuffer.h"

class VertexArrayObject {

public:

  VertexArrayObject();

  void LinkAttrib(
    VertexBuffer vertexBuffer,
    GLuint layout,
    GLuint numComponents,
    GLenum type,
    GLsizeiptr stride,
    void* offset
  );

  void Bind();
  void Unbind();
  void Delete();

private:

  GLuint _Handle;

};