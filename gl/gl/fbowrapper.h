#include <glad/glad.h>
#include <GLFW/glfw3.h>

class fboWrapper {
public:
    GLuint _framebufferName, _renderedTexture, _depthrenderbuffer;
    void init(int nWidth, int nHeight)
    {
        glGenFramebuffers(1, &_framebufferName);
        glBindFramebuffer(GL_FRAMEBUFFER, _framebufferName);

        glGenTextures(1, &_renderedTexture);
        glBindTexture(GL_TEXTURE_2D, _renderedTexture);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, nWidth, nHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, _renderedTexture, 0);

        glGenRenderbuffers(1, &_depthrenderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER,_depthrenderbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, nWidth, nHeight);
        
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthrenderbuffer);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
};