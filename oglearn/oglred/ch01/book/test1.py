import sys
import ctypes
import numpy as np
import OpenGL.GL as gl
import OpenGL.GLUT as glut

class test1:
    def __init__(self):
        self.vertex_code = """
            #version 430 core
            layout(location = 0) in vec4 vPosition;
            void
            main() {
                gl_Position = vPosition;
            } """

        self.fragment_code = """
            #version 430 core
            out vec4 fColor;
            void
            main() {
                fColor = vec4(0.0, 0.0, 1.0, 1.0);
            } """

        self.vertex_code1 = """
            layout(location = 0) in vec2 position;
            void main()
            {
                gl_Position = vec4(position, 0.0, 1.0);
            } """

        self.fragment_code1 = """
            void main()
            {
                gl_FragColor = vec4(0.0, 0.0, 1.0, 1.0);
            } """

    def loadShaders(self):
        program  = gl.glCreateProgram()
        vertex   = gl.glCreateShader(gl.GL_VERTEX_SHADER)
        fragment = gl.glCreateShader(gl.GL_FRAGMENT_SHADER)
        gl.glShaderSource(vertex, self.vertex_code)
        gl.glShaderSource(fragment, self.fragment_code)
        gl.glCompileShader(vertex)
        gl.glCompileShader(fragment)
        gl.glGetError()
        gl.glAttachShader(program, vertex)
        gl.glAttachShader(program, fragment)
        gl.glLinkProgram(program)
        gl.glDetachShader(program, vertex)
        gl.glDetachShader(program, fragment)
        gl.glGetError()
        #gl.glUseProgram(program)

        return program

    def disp(self):
        gl.glClear(gl.GL_COLOR_BUFFER_BIT)
        #gl.glBindVertexArray(self.vaos)
        #gl.glDrawArrays(gl.GL_TRIANGLES, 0, 6)
        gl.glFlush()

    def init(self):
        verts = np.asarray([[-0.9, -0.9],[0.85, -0.9],[-0.9, 0.85],[0.9, -0.85],[0.9, 0.9],[-0.85, 0.9]], dtype=np.float32)

        self.vaos = gl.glGenVertexArrays(1)
        gl.glBindVertexArray(self.vaos)

        buffers = gl.glGenBuffers(1)
        gl.glBindBuffer(gl.GL_ARRAY_BUFFER, buffers)

        gl.glBufferData(gl.GL_ARRAY_BUFFER, verts.nbytes, verts, gl.GL_STATIC_DRAW)
        #gl.glGetError()

        program = self.loadShaders()
        gl.glVertexAttribPointer(0, 2, gl.GL_FLOAT, gl.GL_FALSE, 0, 0)
        gl.glEnableVertexAttribArray(0)
        if False:
            loc = gl.glGetAttribLocation(program, "position")
            gl.glEnableVertexAttribArray(loc)
            gl.glBindBuffer(gl.GL_ARRAY_BUFFER, buffers)
            gl.glVertexAttribPointer(loc, 2, gl.GL_FLOAT, gl.GL_FALSE, 0, 0)
            loc = gl.glGetUniformLocation(program, "scale")
            gl.glUniform1f(loc, 1.0)

    def init1(self):
        self.vaos = gl.glGenVertexArrays(1)

    def mainfunc(self):
        glut.glutInit()
        glut.glutInitDisplayMode(glut.GLUT_RGBA | glut.GLUT_3_2_CORE_PROFILE)
        glut.glutInitWindowSize(512, 512)
        #glut.glutInitContextVersion(4, 3)
        #glut.glutInitContextProfile(glut.GLUT_CORE_PROFILE)
        glut.glutCreateWindow('CH01_01')
        self.init()
        glut.glutDisplayFunc(self.disp)
        glut.glutMainLoop()

curobj = test1()
curobj.mainfunc()