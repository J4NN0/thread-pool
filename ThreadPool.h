//
// Created by Federico Gianno on 27/09/2018.
//

#ifndef THREAD_SAFE_CLASS_THREADPOOL_H
#define THREAD_SAFE_CLASS_THREADPOOL_H

#include <thread>
#include <vector>

#include "Item.h"

using namespace std;

class ThreadPool {
private:
    Item i;
    int nthreads = thread::hardware_concurrency(); //number of concurrent threads that are supported
    vector<thread> threads;
    once_flag on, off;

    void worker();

public:
    void startup();
    void shutdown();
    void post_task(int var);
};


#endif //THREAD_SAFE_CLASS_THREADPOOL_H
