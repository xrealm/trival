//
// Created by Mao on 21/8/18.
//

#ifndef GL3BOOK_PREVIEW_CONTROLLER_H
#define GL3BOOK_PREVIEW_CONTROLLER_H

#include <unistd.h>
#include <android/native_window.h>
#include "preview_render.h"
#include "egl_core.h"
#include "../util.h"

class PreviewController {
public:
    PreviewController();
    virtual ~PreviewController();

    bool start();

    void stop();

    void setWindow(ANativeWindow *window);

    void resetSize(int width, int height);

private:
    PreviewRender *render;
    PicTexture *picTexture;

    int width;
    int height;
    enum RenderThreadMessage {
        MSG_NONE=0,
        MSG_WINDOW_SET = 1,
        MSG_RENDER_LOOP_EXIT
    };

    pthread_t threadId;
    pthread_mutex_t mLock;
    pthread_cond_t mCondition;
    enum RenderThreadMessage msg;
    ANativeWindow *window;
    EGLCore *eglCore;
    EGLSurface previewSurface;

    static void *threadStartCallback(void *myself);

    void renderLoop();

    bool initialize();

    void updateTexImage();

    void drawFrame();

    void destroy();
};

#endif //GL3BOOK_PREVIEW_CONTROLLER_H
