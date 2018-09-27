//
// Created by Federico Gianno on 27/09/2018.
//

#ifndef THREAD_SAFE_CLASS_ITEM_H
#define THREAD_SAFE_CLASS_ITEM_H

#include <mutex>
#include <queue>

using namespace std;

class Item {
private:
    bool valid;
    mutex mtx;
    condition_variable cv;
    priority_queue<int> pq;

public:
    Item();
    ~Item();
    bool pop(int &var);
    void push(int var);
    void invalidate();
};


#endif //THREAD_SAFE_CLASS_ITEM_H
