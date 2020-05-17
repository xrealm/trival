//
// Created by Mao on 7/9/18.
//

#include "thread.h"

Thread::Thread() {
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&condition, NULL);
}

Thread::~Thread() {

}

void Thread::start() {
    handleRun(NULL);
}

void Thread::startAsync() {
    pthread_create(&thread, NULL, startThread, this);
}



int Thread::wait() {
    if (!isRunning) {
        LOGI("runing is false");
        return 0;
    }
    void* status;
    int result = pthread_join(thread, &status);
    LOGI("pthread_join result is %d ", status);
    return  result;
}

void Thread::waitOnNotify() {
    pthread_mutex_lock(&lock);
    pthread_cond_wait(&condition, &lock);
    pthread_mutex_unlock(&lock);
}

void Thread::notify() {
    pthread_mutex_lock(&lock);
    pthread_cond_signal(&condition);
    pthread_mutex_unlock(&lock);
}

void Thread::stop() {

}

void Thread::handleRun(void *ptr) {

}

void* Thread::startThread(void *ptr) {
    LOGI("start thread");
    Thread* curThread = static_cast<Thread *>(ptr);
    curThread->isRunning = true;
    curThread->handleRun(ptr);
    curThread->isRunning = false;
}