#pragma once

#include <glad/glad.h>

class Shader {

public:

  Shader(const char* vertexFile, const char* fragmentFile);

  GLuint GetHandle() { return _Handle; }

  void Activate();
  void Delete();

private:

  GLuint _Handle;

};