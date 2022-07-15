#include "Shader.h"

#include <iostream>
#include <fstream>
#include <string>

std::string readFile(const char* filePath) {
  std::string content;
  std::ifstream fileStream(filePath, std::ios::in);

  if (!fileStream.is_open()) {
    std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
    return "";
  }

  std::string line = "";
  while (!fileStream.eof()) {
    std::getline(fileStream, line);
    content.append(line + "\n");
  }

  fileStream.close();
  return content;
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {
  // Create Shaders and Gfx Program
  std::string vertexShaderStr = readFile(vertexFile);
  const char* vertexShaderSource = vertexShaderStr.c_str();
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  std::string fragmetShaderStr = readFile(fragmentFile);
  const char* fragmetShaderSource = fragmetShaderStr.c_str();
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmetShaderSource, NULL);
  glCompileShader(fragmentShader);

  _Handle = glCreateProgram();
  glAttachShader(_Handle, vertexShader);
  glAttachShader(_Handle, fragmentShader);

  // Tell the Gfx-Card to use this program
  glLinkProgram(_Handle);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void Shader::Activate() {
  glUseProgram(_Handle);
}

void Shader::Delete() {
  glDeleteProgram(_Handle);
}
