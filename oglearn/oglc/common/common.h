#ifndef __COMMON_H_
#define __COMMON_H_

static char *shaderLoadSource(const char *filePath);
static GLuint shaderCompileFromFile(GLenum type, const char *filePath);
GLuint LoadShaders(char* vsfl, char* fsfl);

#endif
