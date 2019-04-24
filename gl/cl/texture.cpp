#include "pch.h"
#include "texture.h"
#include "FreeImage/FreeImage.h"

GLuint loadDDS(const char * imagepath)
{

    unsigned char header[124];

    FILE *fp;

    /* try to open the file */
    fp = fopen(imagepath, "rb");
    if (fp == NULL) {
        printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath); getchar();
        return 0;
    }

    /* verify the type of file */
    char filecode[4];
    fread(filecode, 1, 4, fp);
    if (strncmp(filecode, "DDS ", 4) != 0) {
        fclose(fp);
        return 0;
    }

    /* get the surface desc */
    fread(&header, 124, 1, fp);

    unsigned int height = *(unsigned int*)&(header[8]);
    unsigned int width = *(unsigned int*)&(header[12]);
    unsigned int linearSize = *(unsigned int*)&(header[16]);
    unsigned int mipMapCount = *(unsigned int*)&(header[24]);
    unsigned int fourCC = *(unsigned int*)&(header[80]);


    unsigned char * buffer;
    unsigned int bufsize;
    /* how big is it going to be including all mipmaps? */
    bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
    fread(buffer, 1, bufsize, fp);
    /* close the file pointer */
    fclose(fp);

    unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
    unsigned int format;
    switch (fourCC)
    {
    case FOURCC_DXT1:
        format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
        break;
    case FOURCC_DXT3:
        format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
        break;
    case FOURCC_DXT5:
        format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
        break;
    default:
        free(buffer);
        return 0;
    }

    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;

    /* load the mipmaps */
    for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
    {
        unsigned int size = ((width + 3) / 4)*((height + 3) / 4)*blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
            0, size, buffer + offset);

        offset += size;
        width /= 2;
        height /= 2;

        // Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
        if (width < 1) width = 1;
        if (height < 1) height = 1;

    }

    free(buffer);

    return textureID;
}

void CheckGL()
{
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        char t[1024];
        sprintf(t, "error %i (%x)\n", error, error);
        if (error == 0x500) strcat(t, "INVALID ENUM");
        else if (error == 0x502) strcat(t, "INVALID OPERATION");
        else if (error == 0x501) strcat(t, "INVALID VALUE");
        else if (error == 0x506) strcat(t, "INVALID FRAMEBUFFER OPERATION");
        else strcat(t, "UNKNOWN ERROR");
        FATALERROR("OpenGL error");
    }
}

CL_Texture::CL_Texture(unsigned int width, unsigned int height, unsigned int type)
{
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    if (type == DEFAULT)
    {
        // regular texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    }
    else /* type == FLOAT */
    {
        // texture to be used with OpenCL code
        float* data = new float[width * height * 4];
        memset(data, 0, width * height * 16);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGB, GL_FLOAT, data);
    }
    CheckGL();
}

GLuint genTexture() {
    // We create a single float channel 512^2 texture
    GLuint texHandle;
    glGenTextures(1, &texHandle);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texHandle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, SCRWIDTH, SCRHEIGHT, 0, GL_RGB, GL_FLOAT, NULL);

    // Because we're also using this tex as an image (in order to write to it),
    // we bind it to an image unit as well
    glBindImageTexture(0, texHandle, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
    return texHandle;
}

// Texture constructor
// Loads an image using FreeImage and creates an OpenGL texture for it.
// ----------------------------------------------------------------------------
CL_Texture::CL_Texture(char* fileName)
{
    GLuint textureType = GL_TEXTURE_2D;
    glGenTextures(1, &id);
    glBindTexture(textureType, id);
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
    fif = FreeImage_GetFileType(fileName, 0);
    if (fif == FIF_UNKNOWN) fif = FreeImage_GetFIFFromFilename(fileName);
    FIBITMAP* tmp = FreeImage_Load(fif, fileName);
    if (!tmp) ERRORMESSAGE(fileName, "File not found");
    FIBITMAP* dib = FreeImage_ConvertTo24Bits(tmp);
    FreeImage_Unload(tmp);
    unsigned int width = FreeImage_GetWidth(dib);
    unsigned int height = FreeImage_GetHeight(dib);
    unsigned int* data = new unsigned int[width * height];
    unsigned char* line = new unsigned char[width * 3];
    for (unsigned int y = 0; y < height; y++)
    {
        memcpy(line, FreeImage_GetScanLine(dib, height - 1 - y), width * 3);
        for (unsigned int x = 0; x < width; x++) data[y * width + x] = (line[x * 3 + 2] << 16) + (line[x * 3 + 1] << 8) + line[x * 3 + 0];
    }
    FreeImage_Unload(dib);
    glTexImage2D(textureType, 0, GL_RGBA8, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
    delete data;
    glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(textureType);
}

// Bind method
// Binds the texture for rendering.
// ----------------------------------------------------------------------------
void CL_Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, id);
}