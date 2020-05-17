//
// Created by Mao on 21/8/18.
//

#include "preview_controller.h"

PreviewController::PreviewController() : msg(MSG_NONE), previewSurface(0), eglCore(0) {
    LOGI("PreviewController instance created.");
    pthread_mutex_init(&mLock, NULL);
    pthread_cond_init(&mCondition, NULL);
    render = new PreviewRender();
    width = 720;
    height = 720;
}

PreviewController::~PreviewController() {
    LOGI("PreviewController instance destroy.");
    pthread_mutex_destroy(&mLock);
    pthread_cond_destroy(&mCondition);
}

bool PreviewController::start() {
    LOGI("PreviewController start");
    pthread_create(&threadId, 0, threadStartCallback, this);
    return true;
}

void PreviewController::stop() {
    LOGI("PreviewController stop");
    pthread_mutex_lock(&mLock);
    msg = MSG_RENDER_LOOP_EXIT;
    pthread_cond_signal(&mCondition);
    pthread_mutex_unlock(&mLock);

    pthread_join(threadId, 0);
    LOGI("PreviewController render thread stop");
}

void PreviewController::setWindow(ANativeWindow *window) {
    LOGI("PreviewController setWindow");
    pthread_mutex_lock(&mLock);
    msg = MSG_WINDOW_SET;
    this->window = window;
    pthread_cond_signal(&mCondition);
    pthread_mutex_unlock(&mLock);
}

void PreviewController::resetSize(int width, int height) {
    LOGI("PreviewController resetSize w:%d, h:%d", width, height);
    pthread_mutex_lock(&mLock);
    this->width = width;
    this->height = height;
    render->resetRenderSize(0, 0, width, height);
    pthread_cond_signal(&mCondition);
    pthread_mutex_unlock(&mLock);
}

void *PreviewController::threadStartCallback(void *myself) {
    PreviewController *controller = static_cast<PreviewController *>(myself);
    controller->renderLoop();
    pthread_exit(0);
}

void PreviewController::renderLoop() {
    bool renderEable = true;
    LOGI("Render loop");
    while (renderEable) {
        pthread_mutex_lock(&mLock);
        switch (msg) {
            case MSG_WINDOW_SET:
                initialize();
                break;
            case MSG_RENDER_LOOP_EXIT:
                renderEable = false;
                destroy();
                break;
            default:
                break;
        }
        msg = MSG_NONE;
        if (eglCore) {
            eglCore->makeCurrent(previewSurface);
            this->drawFrame();
//            pthread_cond_wait(&mCondition, &mLock);
            usleep(100);
        }
        pthread_mutex_unlock(&mLock);
    }
    LOGI("Render exit");
}

bool PreviewController::initialize() {
    eglCore = new EGLCore();
    eglCore->init();
    previewSurface = eglCore->createWindowSurface(window);
    eglCore->makeCurrent(previewSurface);

    bool isInit = render->init(width, height, NULL);
    if (!isInit) {
        LOGI("render failed on initialized...");
        return false;
    }
    LOGI("initialize context success.");
    return true;
}

void PreviewController::updateTexImage() {

}

void PreviewController::drawFrame() {
    render->render();
    if (!eglCore->swapBuffers(previewSurface)) {
        LOGE("eglSwapBuffers error %d", eglGetError());
    }
}

void PreviewController::destroy() {
    LOGI("dealloc render..");
    if (render != NULL) {
        render->dealloc();
        delete render;
        render = NULL;
    }
    if (eglCore != NULL) {
        eglCore->releaseSurface(previewSurface);
        eglCore->release();
        delete eglCore;
        eglCore = NULL;
    }
}