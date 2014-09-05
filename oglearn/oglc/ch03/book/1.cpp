#include <iostream>
using namespace std;

#include <OpenGL/gl3.h>
# define __gl_h_
#include <GLUT/glut.h>
#include "common.h"
#include "vmath.h"

using namespace vmath;

float aspect;
GLuint render_prog;
GLuint vao[1];
GLuint vbo[1];
GLuint ebo[1];

GLint render_model_matrix_loc;
GLint render_view_matrix_loc;
GLint render_projection_matrix_loc;
GLuint program;

void init(void) {
  GLuint vpos, fpos;
  program = LoadShaders("../oglred/oglearn/oglc/ch03/shaders/vert.glsl", "../oglred/oglearn/oglc/ch03/shaders/frag.glsl");
  glUseProgram(program);


  // "model_matrix" is actually an array of 4 matrices
  render_model_matrix_loc = glGetUniformLocation(program, "model_matrix");
  render_view_matrix_loc = glGetUniformLocation(program, "view_matrix");
  render_projection_matrix_loc = glGetUniformLocation(program, "projection_matrix");

  // A single triangle
  static const GLfloat vertex_positions[] =
  {
    -1.0f, -1.0f,  10.0f, 1.0f,
    1.0f, -1.0f,  10.0f, 1.0f,
    -1.0f,  1.0f,  10.0f, 1.0f,
    -1.0f, -1.0f,  10.0f, 1.0f,
  };

  // Color for each vertex
  static const GLfloat vertex_colors[] =
  {
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f
  };

  // Indices for the triangle strips
  static const GLushort vertex_indices[] =
  {
    0, 1, 2
  };

  // Set up the element array buffer
  glGenBuffers(1, ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indices), vertex_indices, GL_STATIC_DRAW);

  // Set up the vertex attributes
  glGenVertexArrays(1, vao);
  glBindVertexArray(vao[0]);

  fpos = glGetAttribLocation(program, "color");
  vpos = glGetAttribLocation(program, "position");

  glGenBuffers(1, vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions) + sizeof(vertex_colors), NULL, GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex_positions), vertex_positions);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertex_positions), sizeof(vertex_colors), vertex_colors);
  
  glVertexAttribPointer(vpos, 4, GL_FLOAT, GL_FALSE, 0, NULL);
  glVertexAttribPointer(fpos, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)sizeof(vertex_positions));
  glEnableVertexAttribArray(vpos);
  glEnableVertexAttribArray(fpos);
  
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  
}

void display(void) {
  bool auto_redraw = false;
  static float q = 0.0f;
  static const vmath::vec3 X(1.0f, 0.0f, 0.0f);
  static const vmath::vec3 Y(0.0f, 1.0f, 0.0f);
  static const vmath::vec3 Z(0.0f, 0.0f, 1.0f);

  mat4 model_matrix;

  // Setup
  glEnable(GL_CULL_FACE);
  glDisable(GL_DEPTH_TEST);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Activate simple shading program
  glUseProgram(program);
  mat4 view_matrix(vmath::scale(1.0f, 1.0f, -1.0f));
  glUniformMatrix4fv(render_view_matrix_loc, 1, GL_FALSE, view_matrix);

  /*
    1 0 0          0
    0 1 0          0
    0 0 -501/499  -1
    0 0 1000/499   0

    -1 -1 0 1 -> -1 -1 1000/499 0
    -1 -1 1 1 -> -1 -1 1 -1
   */
  // Set up the model and projection matrix
  float side = 1.0f;
  vmath::mat4 projection_matrix(vmath::frustum(-side, side, -side, side, 1.0f, 500.0f));
  glUniformMatrix4fv(render_projection_matrix_loc, 1, GL_FALSE, projection_matrix);

  // Set up for a glDrawElements call
  glBindVertexArray(vao[0]);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);

  // Draw Arrays...
  model_matrix = vmath::translate(-3.0f, 0.0f, -5.0f);
  glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, model_matrix);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  
  // DrawElements
  model_matrix = vmath::translate(-1.0f, 0.0f, -5.0f);
  glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, model_matrix);
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL);

  // DrawElementsBaseVertex
  model_matrix = vmath::translate(1.0f, 0.0f, -5.0f);
  glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, model_matrix);
  glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL, 1);

  // DrawArraysInstanced
  model_matrix = vmath::translate(3.0f, 0.0f, -5.0f);
  glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, model_matrix);
  glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 1);
  
  glutSwapBuffers();
  if (auto_redraw)
  {
    glutPostRedisplay();
  }

}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutInitWindowSize(512, 512);
  glutCreateWindow(argv[0]);
  init();
  glutDisplayFunc(display);
  glutMainLoop();
}
