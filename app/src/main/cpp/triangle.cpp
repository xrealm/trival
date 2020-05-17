#include <jni.h>
#include <string>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include "render/preview_controller.h"
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavfilter/avfilter.h"
}



extern "C" JNIEXPORT jstring JNICALL
Java_com_master_trival_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from M";
    return env->NewStringUTF(hello.c_str());
}

ANativeWindow *window;
PreviewController *controller;

/*
 * Class:     com_mao_gl3book_PlayRender
 * Method:    init
 * Signature: ()V
 */
extern "C" JNIEXPORT void JNICALL Java_com_master_trival_PlayRender_init
        (JNIEnv *env, jobject jobj) {
    controller = new PreviewController();
    controller->start();

}

extern "C" JNIEXPORT void JNICALL Java_com_master_trival_PlayRender_setSurface
        (JNIEnv *env, jobject jobj, jobject surface) {
    if (surface != NULL && controller != NULL) {
        window = ANativeWindow_fromSurface(env, surface);
        LOGI("new window %p", window);
        controller->setWindow(window);
    } else {
        LOGI("release window %p", window);
        ANativeWindow_release(window);
        window = 0;
    }
}

/*
 * Class:     com_mao_gl3book_PlayRender
 * Method:    resetSize
 * Signature: (II)V
 */
extern "C" JNIEXPORT void JNICALL Java_com_master_trival_PlayRender_resetSize
        (JNIEnv *env, jobject jobj, jint width, jint height) {
    if (controller != NULL) {
        controller->resetSize(width, height);
    }
}

/*
 * Class:     com_mao_gl3book_PlayRender
 * Method:    stop
 * Signature: ()V
 */
extern "C" JNIEXPORT void JNICALL Java_com_master_trival_PlayRender_stop
        (JNIEnv *env, jobject jobj) {
    if (NULL != controller) {
        controller->stop();
        delete controller;
        controller = NULL;
    }
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_master_trival_MainActivity_avcodecinfo(JNIEnv *env, jclass type) {
    char info[40000] = { 0 };

    // 注册所有组件
    av_register_all();

    AVCodec *c_temp = av_codec_next(NULL);

    while(c_temp!=NULL){
        if (c_temp->decode!=NULL){
            sprintf(info, "%s[Dec]", info);
        }
        else{
            sprintf(info, "%s[Enc]", info);
        }
        switch (c_temp->type){
            case AVMEDIA_TYPE_VIDEO:
                sprintf(info, "%s[Video]", info);
                break;
            case AVMEDIA_TYPE_AUDIO:
                sprintf(info, "%s[Audio]", info);
                break;
            default:
                sprintf(info, "%s[Other]", info);
                break;
        }
        sprintf(info, "%s[%10s]\n", info, c_temp->name);


        c_temp=c_temp->next;
    }
    return env->NewStringUTF(info);
}