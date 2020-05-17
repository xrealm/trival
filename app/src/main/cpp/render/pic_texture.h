//
// Created by Mao on 25/7/18.
//

#ifndef GL3BOOK_PNG_TEXTURE_H
#define GL3BOOK_PNG_TEXTURE_H

#include <GLES3/gl3.h>
#include "../util.h"
#include "../shader.h"

//#define LOG_TAG = "PicTexture"


class PicTexture {
private:
    GLuint texture;

    int initTexture();

    bool checkGlError(const char* op);

public:
    PicTexture();

    virtual ~PicTexture();

    bool createTexture();

    bool bindTexture(GLint uniformSampler);

    void updateTexImage(char * pixel, int width, int height);

    void dealloc();
};

#endif //GL3BOOK_PNG_TEXTURE_H
