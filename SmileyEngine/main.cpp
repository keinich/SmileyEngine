#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include "main.h"

#include "Shader.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "VertexArrayObject.h"

int main() {

  // Init GLFW
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Define our vertices to render
  GLfloat vertices[] = {
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
    0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
    -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
    0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
    0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
  };

  // Indices for vertices order
  GLuint indices[] = {
    0, 3, 5, // Lower left triangle
    3, 2, 4, // Lower right triangle
    5, 4, 1 // Upper triangle
  };

  // Create Window in GLFW
  GLFWwindow* window = glfwCreateWindow(800, 600, "Smiley Engine", NULL, NULL);
  glfwMakeContextCurrent(window);

  // Init Glad
  gladLoadGL();

  // OPEN GL Code
  glViewport(0, 0, 800, 600);

 
  Shader shader("BasicVertexShader.glsl", "BasicFragmentShader.glsl"); 
  
  VertexArrayObject vertexArrayObject;
  vertexArrayObject.Bind();

  VertexBuffer vertexBuffer(vertices, sizeof(vertices));
  ElementBuffer elementBuffer(indices, sizeof(indices));

  vertexArrayObject.LinkVertexBuffer(vertexBuffer, 0);

  vertexArrayObject.Unbind();
  vertexBuffer.Unbind();
  elementBuffer.Unbind();

  // Main Loop
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
  
    shader.Activate();

    vertexArrayObject.Bind();
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);

  }

  // Shutdown  

  vertexArrayObject.Delete();
  vertexBuffer.Delete();
  elementBuffer.Delete();
  shader.Delete();

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;

}

