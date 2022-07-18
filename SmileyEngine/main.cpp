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
  GLfloat vertices[] =
  { //               COORDINATES                  /     COLORS           //
    -0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.9f,  0.02f, // Lower left corner
     0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower right corner
     0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     1.0f, 0.6f,  0.32f, // Upper corner
    -0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner left
     0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner right
     0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.92f  // Inner down
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

  vertexArrayObject.LinkAttrib(vertexBuffer, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
  vertexArrayObject.LinkAttrib(vertexBuffer, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

  vertexArrayObject.Unbind();
  vertexBuffer.Unbind();
  elementBuffer.Unbind();

  GLuint idOfScaleUniformVariable = glGetUniformLocation(shader.GetHandle(), "scale");

  // Main Loop
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.Activate();
    glUniform1f(idOfScaleUniformVariable, 0.5f);

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

