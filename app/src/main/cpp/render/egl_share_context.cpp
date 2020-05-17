//
// Created by Mao on 6/9/18.
//

#include "egl_share_context.h"

EglShareContext* EglShareContext::instance = new EglShareContext();

EglShareContext::EglShareContext() {
    init();
}

EglShareContext::~EglShareContext() {

}

void EglShareContext::init() {
    shareContext = EGL_NO_CONTEXT;
    EGLint  numConfigs;
    EGLConfig config;
    const EGLint attribs[] = {
            EGL_BUFFER_SIZE, 32,
            EGL_RED_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_ALPHA_SIZE, 8,
            EGL_DEPTH_SIZE, 16,
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT_KHR,
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_NONE
    };

    if ((shareContext = eglGetDisplay(EGL_DEFAULT_DISPLAY)) == EGL_NO_DISPLAY) {
        LOGE("eglGetDisplay error %d", eglGetError());
        return;
    }

    if (!eglInitialize(shareDisplay, 0, 0)) {
        LOGE("eglInitialize error %d", eglGetError());
        return;
    }

    if (!eglChooseConfig(shareDisplay, attribs, &config, 1, &numConfigs)) {
        LOGE("eglChooseConfig error %d", eglGetError());
        return;
    }
    EGLint eglContextAttributes[] = {
            EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE
    };

    if (!(shareContext = eglCreateContext(shareDisplay, config,
                                          NULL == shareContext ? EGL_NO_CONTEXT : shareContext,
                                          eglContextAttributes))) {
        LOGE("eglCreateContext error %d", eglGetError());
        return;
    }
}
