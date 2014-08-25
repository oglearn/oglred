#include <iostream>
using namespace std;

#include <OpenGL/gl3.h>
# define __gl_h_
#include <GLUT/glut.h>
#include "common.h"

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers }; enum Attrib_IDs { vPosition = 0 };
GLuint  VAOs[NumVAOs];
GLuint  Buffers[NumBuffers];
const GLuint NumVertices = 6;


void init(void) {
  glGenVertexArrays(NumVAOs, VAOs);
  glBindVertexArray(VAOs[Triangles]);
  GLfloat  vertices[NumVertices][2] = {
    { -0.90, -0.90 },  // Triangle 1
    {  0.85, -0.90 },
    { -0.90,  0.85 },
    {  0.90, -0.85 },  // Triangle 2
    {  0.90,  0.90 },
    { -0.85,  0.90 }
  };
  glGenBuffers(NumBuffers, Buffers); 
  glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]); 
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  GLuint program = LoadShaders("../oglred/oglearn/oglc/ch01/shaders/vert.glsl", "../oglred/oglearn/oglc/ch01/shaders/frag.glsl");
  glUseProgram(program);
  glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vPosition);
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glBindVertexArray(VAOs[Triangles]);
  glDrawArrays(GL_TRIANGLES, 0, NumVertices);
  glFlush(); 
}

int main(int argc, char** argv) {

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutInitWindowSize(512, 512);
  glutCreateWindow(argv[0]);
  init();
  glutDisplayFunc(display);
  glutMainLoop();
}
