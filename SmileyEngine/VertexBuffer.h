#pragma once

#include <glad/glad.h>

class VertexBuffer {

public:

  VertexBuffer(GLfloat* vertices, GLsizeiptr size);

  GLuint GetHandle() { return _Handle; }

  void Bind();
  void Unbind();
  void Delete();

private:

  GLuint _Handle;

};