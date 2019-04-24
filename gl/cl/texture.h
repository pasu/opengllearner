#include "pch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>
#include<fstream>
#include <vector>
#include "shared.h"

using namespace std;

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

GLuint loadDDS(const char * imagepath);

GLuint genTexture();

class CL_Texture
{
public:
    enum
    {
        DEFAULT = 0,
        FLOAT = 1
    };
    // constructor / destructor
    CL_Texture(unsigned int width, unsigned int height, unsigned int type = DEFAULT);
    CL_Texture(char* fileName);
    // get / set
    unsigned int GetID() { return id; }
    // methods
    void Bind();
private:
    // data members
    GLuint id;
};
