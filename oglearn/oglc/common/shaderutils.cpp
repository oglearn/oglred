#include <iostream>
using namespace std;

#include <OpenGL/gl3.h>
# define __gl_h_
#include <GLUT/glut.h>
#include "common.h"

static char *shaderLoadSource(const char *filePath)
{
	const size_t blockSize = 512;
	FILE *fp;
	char buf[blockSize];
	char *source = NULL;
	size_t tmp, sourceLength = 0;

	/* open file */
	fp = fopen(filePath, "r");
	if(!fp) {
		fprintf(stderr, "shaderLoadSource(): Unable to open %s for reading\n", filePath);
		return NULL;
	}

	/* read the entire file into a string */
	while((tmp = fread(buf, 1, blockSize, fp)) > 0) {
	  char *newSource = (char*)malloc(sourceLength + tmp + 1);
		if(!newSource) {
			fprintf(stderr, "shaderLoadSource(): malloc failed\n");
			if(source)
				free(source);
			return NULL;
		}

		if(source) {
			memcpy(newSource, source, sourceLength);
			free(source);
		}
		memcpy(newSource + sourceLength, buf, tmp);

		source = newSource;
		sourceLength += tmp;
	}

	/* close the file and null terminate the string */
	fclose(fp);
	if(source)
		source[sourceLength] = '\0';

	return source;
}

static GLuint shaderCompileFromFile(GLenum type, const char *filePath)
{
    char *source;
    GLuint shader;
    GLint length, result;

    /* get shader source */
    source = shaderLoadSource(filePath);
    if(!source)
        return 0;

    /* create shader object, set the source, and compile */
    shader = glCreateShader(type);
    length = strlen(source);
    glShaderSource(shader, 1, (const char **)&source, &length);
    glCompileShader(shader);
    free(source);

    /* make sure the compilation was successful */
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE) {
        char *log;

        /* get the shader info log */
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        log = (char*)malloc(length);
        glGetShaderInfoLog(shader, length, &result, log);

        /* print an error message and the info log */
        fprintf(stderr, "shaderCompileFromFile(): Unable to compile %s: %s\n", filePath, log);
        free(log);

        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

GLuint LoadShaders(char* vsfl, char* fsfl)
{
  GLuint program = glCreateProgram();

  GLuint vertex = shaderCompileFromFile(GL_VERTEX_SHADER, vsfl);
  GLuint fragment = shaderCompileFromFile(GL_FRAGMENT_SHADER, fsfl);

  glAttachShader(program, vertex);
  glAttachShader(program, fragment);

  glLinkProgram(program);
  glDetachShader(program, vertex);
  glDetachShader(program, fragment);
  
  return program;
}
