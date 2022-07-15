#pragma once

#include <glad/glad.h>

class ElementBuffer {

public:

  ElementBuffer(GLuint* indices, GLsizeiptr size);

  GLuint GetHandle() { return _Handle; }

  void Bind();
  void Unbind();
  void Delete();

private:

  GLuint _Handle;

};