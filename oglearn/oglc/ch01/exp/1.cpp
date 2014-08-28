#include <iostream>
using namespace std;

#include <OpenGL/gl3.h>
# define __gl_h_
#include <GLUT/glut.h>
#include "common.h"

#define Triangles 0
#define NumVAOs 1
# define NumBuffers 2
GLuint  VAOs[NumVAOs];
GLuint  Buffers[NumBuffers];
const GLuint NumVertices = 6;


void init(void) {
  GLuint vpos, fpos;
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
  GLfloat  colors[NumVertices][4] = {
    { 1, 0, 0, 1 },  // Triangle 1
    {  0, 1, 0, 1 },
    {  0, 0, 1, 1 },
    { 1, 0, 0, 1 },  // Triangle 2
    {  0, 1, 0, 1 },
    {  0, 0, 1, 1 },
  };

  glGenBuffers(NumBuffers, Buffers); 
  glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]); 
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

  GLuint program = LoadShaders("../oglred/oglearn/oglc/ch01/shaders/vert1.glsl", "../oglred/oglearn/oglc/ch01/shaders/frag1.glsl");
  glUseProgram(program);

  vpos = glGetAttribLocation(program, "position");
  glVertexAttribPointer(vpos, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vpos);

  glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]); 
  glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_DYNAMIC_DRAW);
  fpos = glGetAttribLocation(program, "color");
  glVertexAttribPointer(fpos, 4, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(fpos);

}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);
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
