//
// Created by Mao on 30/7/18.
//

#include "egl_core.h"

EGLCore::EGLCore() {
    pfneglPresentationTimeANDROID = 0;
    display = EGL_NO_DISPLAY;
    context = EGL_NO_CONTEXT;
}

EGLCore::~EGLCore() {

}

bool EGLCore::initWithSharedContext() {
    EGLContext shareContext = EglShareContext::getShareContext();
    if (shareContext == EGL_NO_CONTEXT) {
        return false;
    }
    return init(shareContext);
}

bool EGLCore::init() {
    return this->init(NULL);
}

bool EGLCore::init(EGLContext sharedContext) {
    EGLint numConfigs;
    EGLint width;
    EGLint height;

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

    if ((display = eglGetDisplay(EGL_DEFAULT_DISPLAY)) == EGL_NO_DISPLAY) {
        LOGE("eglGetDisplay return error %d", eglGetError());
        return false;
    }

    EGLint major, minor;
    if (!eglInitialize(display, &major, &minor)) {
        LOGE("eglInitialize return error %d", eglGetError());
        return false;
    }

    if (!eglChooseConfig(display, attribs, &config, 1, &numConfigs)) {
        LOGE("eglChooseConfig return error %d", eglGetError());
        release();
        return false;
    }

    EGLint eglContextAttributes[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
    if (!(context = eglCreateContext(display, config,
                                     NULL == sharedContext ? EGL_NO_CONTEXT : sharedContext,
                                     eglContextAttributes))) {
        LOGE("eglCreateContext return error %d", eglGetError());
        release();
        return false;
    }

    EGLint value[1];
    eglQueryContext(display, context, EGL_CONTEXT_CLIENT_VERSION, value);

    pfneglPresentationTimeANDROID = (PFNEGLPRESENTATIONTIMEANDROIDPROC)eglGetProcAddress("eglPresentationTimeANDROID");
    if (!pfneglPresentationTimeANDROID) {
        LOGE("eglPresentationTimeANDROID is not available!");
    }
    return true;
}

EGLSurface EGLCore::createWindowSurface(ANativeWindow *window) {
    EGLSurface surface = NULL;
    EGLint format;
    if (!eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format)) {
        LOGE("eglGetConfigAttrib return error %d", eglGetError());
        release();
        return surface;
    }

    ANativeWindow_setBuffersGeometry(window, 0, 0, format);
    if (!(surface = eglCreateWindowSurface(display, config, window, 0))) {
        LOGE("eglCreateWindowSurface error %d", eglGetError());
    }
    return surface;
}

EGLSurface EGLCore::createOffscreenSurface(int width, int height) {
    EGLSurface surface;
    EGLint  pbufferAttributes[] = {
            EGL_WIDTH, width, EGL_HEIGHT, height, EGL_NONE, EGL_NONE
    };
    if (!(surface = eglCreatePbufferSurface(display, config, pbufferAttributes))) {
        LOGE("eglCreatePbufferSurface error %d", eglGetError());
    }
    return surface;
}

int EGLCore::querySurface(EGLSurface surface, int what) {
    int value = -1;
    eglQuerySurface(display, surface, what, &value);
    return value;
}

bool EGLCore::makeCurrent(EGLSurface eglSurface) {
    return eglMakeCurrent(display, eglSurface, eglSurface, context);
}

void EGLCore::doneCurrent() {
    eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
}

bool EGLCore::swapBuffers(EGLSurface eglSurface) {
    return eglSwapBuffers(display, eglSurface);
}

int EGLCore::setPresentationTime(EGLSurface surface, khronos_stime_nanoseconds_t nsecs) {
    pfneglPresentationTimeANDROID(display, surface, nsecs);
    return 0;
}

void EGLCore::releaseSurface(EGLSurface eglSurface) {
    eglDestroySurface(display, eglSurface);
    eglSurface = EGL_NO_SURFACE;
}

void EGLCore::release() {
    LOGI("egl release..");
    eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroyContext(display, context);
    display = EGL_NO_DISPLAY;
    context = EGL_NO_CONTEXT;
}

EGLContext EGLCore::getContext() {
    return context;
}

EGLDisplay EGLCore::getDisplay() {
    return display;
}

EGLConfig EGLCore::getConfig() {
    return config;
}