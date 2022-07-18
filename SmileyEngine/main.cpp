#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include "main.h"
#include <stb/stb_image.h>

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

  // Vertices coordinates
  GLfloat vertices[] =
  { //     COORDINATES     /        COLORS      /   TexCoord  //
    -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
    -0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
     0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
     0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
  };

  // Indices for vertices order
  GLuint indices[] =
  {
    0, 2, 1, // Upper triangle
    0, 3, 2 // Lower triangle
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

  vertexArrayObject.LinkAttrib(vertexBuffer, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
  vertexArrayObject.LinkAttrib(vertexBuffer, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  vertexArrayObject.LinkAttrib(vertexBuffer, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

  vertexArrayObject.Unbind();
  vertexBuffer.Unbind();
  elementBuffer.Unbind();

  GLuint idOfScaleUniformVariable = glGetUniformLocation(shader.GetHandle(), "scale");

  // Load Texture
  int widthImg, heightImg, numColorChannels;
  // Load Image Data in cpu memory
  stbi_set_flip_vertically_on_load(true);
  unsigned char* imgBytes = stbi_load("pop_cat.png", &widthImg, &heightImg, &numColorChannels, 0);

  GLuint texture;
  // Create a texture in gpu memory
  glGenTextures(1, &texture);
  // OpenGl has 16 Texture-Slots that we can use
  // Here we tell OpenGL to activate the Texture-Slot with index 0
  glActiveTexture(GL_TEXTURE0);
  // Bind the texture for the following calls
  glBindTexture(GL_TEXTURE_2D, texture);

  // Settings for how the gpu should work with the texture
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  // load the texture data from cpu to gpu
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgBytes);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(imgBytes);
  glBindTexture(GL_TEXTURE_2D, 0);

  GLuint idOfTexUniform = glGetUniformLocation(shader.GetHandle(), "tex0");
  shader.Activate();
  glUniform1i(idOfTexUniform, 0);

  // Main Loop
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.Activate();
    glUniform1f(idOfScaleUniformVariable, 1.0f);
    glBindTexture(GL_TEXTURE_2D, texture);

    vertexArrayObject.Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);

  }

  // Shutdown  

  vertexArrayObject.Delete();
  vertexBuffer.Delete();
  elementBuffer.Delete();

  glDeleteTextures(1, &texture);

  shader.Delete();

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;

}

