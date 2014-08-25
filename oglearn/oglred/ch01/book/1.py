import sys
import ctypes
import numpy as np
import OpenGL.GL as gl
import OpenGL.GLUT as glut

vertex_code = """
    uniform float scale;
    attribute vec4 color;
    attribute vec2 position;
    varying vec4 v_color;
    void main()
    {
        gl_Position = vec4(position, 0.0, 1.0);
        v_color = color;
    } """

fragment_code = """
    varying vec4 v_color;
    void main()
    {
        gl_FragColor = vec4(255, 0, 0, 1);
    } """


def loadShaders():
    global vertex_code
    global fragment_code

    program  = gl.glCreateProgram()
    vertex   = gl.glCreateShader(gl.GL_VERTEX_SHADER)
    fragment = gl.glCreateShader(gl.GL_FRAGMENT_SHADER)
    gl.glShaderSource(vertex, vertex_code)
    gl.glShaderSource(fragment, fragment_code)
    gl.glCompileShader(vertex)
    gl.glCompileShader(fragment)
    gl.glAttachShader(program, vertex)
    gl.glAttachShader(program, fragment)
    gl.glLinkProgram(program)
    gl.glDetachShader(program, vertex)
    gl.glDetachShader(program, fragment)
    gl.glUseProgram(program)

    return program

def disp():
    gl.glClear(gl.GL_COLOR_BUFFER_BIT)
    #gl.glBindVertexArray(vaos[0])
    gl.glDrawArrays(gl.GL_TRIANGLES, 0, 6)
    gl.glFlush()

def init1():
    verts = np.asarray([[-0.9, -0.9],[0.85, -0.9],[-0.9, 0.85],[0.9, -0.85],[0.9, 0.9],[-0.85, 0.9]], dtype=np.float32)

    buffers = gl.glGenBuffers(1)
    gl.glBindBuffer(gl.GL_ARRAY_BUFFER, buffers)
    gl.glBufferData(gl.GL_ARRAY_BUFFER, verts.nbytes, verts, gl.GL_DYNAMIC_DRAW)
    program = loadShaders()

    loc = gl.glGetAttribLocation(program, "position")
    gl.glEnableVertexAttribArray(loc)
    gl.glBindBuffer(gl.GL_ARRAY_BUFFER, buffers)
    gl.glVertexAttribPointer(loc, 2, gl.GL_FLOAT, gl.GL_FALSE, 0, 0)
    loc = gl.glGetUniformLocation(program, "scale")
    gl.glUniform1f(loc, 1.0)

def init():
    vaos = gl.glGenVertexArrays(1)

glut.glutInit()
glut.glutInitDisplayMode(glut.GLUT_3_2_CORE_PROFILE | glut.GLUT_RGBA)
glut.glutInitWindowSize(512, 512)
#glut.glutInitContextVersion(4, 3)
#glut.glutInitContextProfile(glut.GLUT_CORE_PROFILE)
glut.glutCreateWindow('CH01_01')
init()
glut.glutDisplayFunc(disp)
glut.glutMainLoop()