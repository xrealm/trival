//
// Created by Mao on 6/9/18.
//

#ifndef GL3BOOK_EGL_SHARE_CONTEXT_H
#define GL3BOOK_EGL_SHARE_CONTEXT_H

#include "egl_core.h"

class EglShareContext {
public:
    ~EglShareContext();

    static EGLContext getShareContext() {
        if (instance->shareDisplay == EGL_NO_DISPLAY) {
            instance->init();
        }
        return instance->shareContext;
    }
protected:
    EglShareContext();

    void init();

private:
    static EglShareContext* instance;
    EGLContext shareContext;
    EGLDisplay shareDisplay;
};

#endif //GL3BOOK_EGL_SHARE_CONTEXT_H
