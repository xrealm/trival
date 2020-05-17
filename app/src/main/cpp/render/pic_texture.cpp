//
// Created by Mao on 25/7/18.
//

#include "pic_texture.h"

PicTexture::PicTexture() {

}

PicTexture::~PicTexture() {

}

bool PicTexture::createTexture() {
    LOGI("PicTexture::createTexture");
    int texture = 0;
    int ret = initTexture();
    if (ret < 0) {
        LOGE("init texture failed");
        this->dealloc();
        return false;
    }
    return true;
}

int PicTexture::initTexture() {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    return 1;
}

bool PicTexture::bindTexture(GLint uniformSampler) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, uniformSampler);
    if (checkGlError("glBindTexture")) {
        return false;
    }
    glUniform1i(uniformSampler, 0);
    return true;
}

void PicTexture::updateTexImage(char *pixels, int width, int height) {
    if (pixels) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        if (checkGlError("glbindTexture")) {
            return;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                     pixels);
    }
}

bool PicTexture::checkGlError(const char *op) {
    GLint error;
    for (error = glGetError(); error; error = glGetError()) {
        LOGI("error::after %s() glError (0x%x\n", op, error);
        return true;
    }
    return false;
}

void PicTexture::dealloc() {
    LOGI("PicTexture::dealloc");
    if (texture) {
        glDeleteTextures(1, &texture);
    }
}