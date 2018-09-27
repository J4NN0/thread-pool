//
// Created by Federico Gianno on 27/09/2018.
//

#include <iostream>

#include "ThreadPool.h"

void ThreadPool::startup()
{
    try {
        call_once(on, [this](){
            for(int i=0; i<nthreads; i++)
                threads.emplace_back(thread{&ThreadPool::worker, this});
        });
    }
    catch(int e) {
        cout << "startup() just called once. Exception: " << e << endl;
    }
}

void ThreadPool::shutdown()
{
    try {
        call_once(off, [this](){
            i.invalidate();

            for (auto& th : threads)
                th.join();
        });
    }
    catch(int e) {
        cout << "shutdown() just called once. Exception: " << e << endl;
    }
}

void ThreadPool::worker()
{
    bool keeprunning = true;
    int var;

    while(keeprunning){
        keeprunning = i.pop(var); //pop value and put it in var, if queue is invalid then keeprunning will be set to false
        if(keeprunning){
            //do stuff
            cout << "Pop value: " << var << endl;
        }
    }
}

void ThreadPool::post_task(int var)
{
    i.push(var);
}