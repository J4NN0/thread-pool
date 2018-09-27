#include <iostream>
#include <thread>

#include "ThreadPool.h"

int main()
{
    ThreadPool tp;

    tp.startup();

    //or also more thread can do this stuff, this is an easy example
    tp.post_task(2);

    tp.shutdown();

    return 0;
}
