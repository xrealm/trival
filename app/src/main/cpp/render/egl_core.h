//
// Created by Mao on 30/7/18.
//

#ifndef GL3BOOK_EGL_CORE_H
#define GL3BOOK_EGL_CORE_H

#include <android/native_window.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <KHR/khrplatform.h>
#include "./../util.h"
#include "egl_share_context.h"

class EGLCore {
public:
    EGLCore();

    virtual ~EGLCore();

    bool init();

    bool initWithSharedContext();

    bool init(EGLContext sharedContext);

    EGLSurface createWindowSurface(ANativeWindow *window);

    EGLSurface createOffscreenSurface(int width, int height);

    bool makeCurrent(EGLSurface eglSurface);

    void doneCurrent();

    bool swapBuffers(EGLSurface eglSurface);

    int querySurface(EGLSurface surface, int what);

    int setPresentationTime(EGLSurface surface, khronos_stime_nanoseconds_t nsecs);

    void releaseSurface(EGLSurface eglSurface);

    void release();

    EGLContext getContext();

    EGLDisplay getDisplay();

    EGLConfig getConfig();

private:

//    static EglShareContext* eglShareContext;
    EGLDisplay display;
    EGLConfig config;
    EGLContext context;
    PFNEGLPRESENTATIONTIMEANDROIDPROC pfneglPresentationTimeANDROID;
};

#endif //GL3BOOK_EGL_CORE_H
