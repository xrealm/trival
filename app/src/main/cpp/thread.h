//
// Created by Mao on 7/9/18.
//

#ifndef TRIVAL_THREAD_H
#define TRIVAL_THREAD_H

#include <pthread.h>
#include "util.h"

class Thread {
public:
    Thread();

    ~Thread();

    void start();

    void startAsync();

    int wait();

    void waitOnNotify();

    void notify();

    virtual void stop();

protected:
    bool isRunning;

    virtual void handleRun(void *ptr);

private:
    pthread_t thread;
    pthread_mutex_t lock;
    pthread_cond_t condition;

    void* startThread(void *ptr);
};

#endif //TRIVAL_THREAD_H
