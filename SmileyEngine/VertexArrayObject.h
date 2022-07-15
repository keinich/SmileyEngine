#pragma once

#include <glad/glad.h>

#include "VertexBuffer.h"

class VertexArrayObject {

public:

  VertexArrayObject();

  void LinkVertexBuffer(VertexBuffer vertexBuffer, GLuint layout);

  void Bind();
  void Unbind();
  void Delete();

private:

  GLuint _Handle;

};