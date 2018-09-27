//
// Created by Federico Gianno on 27/09/2018.
//

#include "Item.h"

Item::Item()
{
    valid = true;
}

Item::~Item()
{
    valid = false;
}

void Item::push(int var)
{
    lock_guard<mutex> lck(mtx);

    if(!valid){
        return;
    }

    pq.push(var);

    cv.notify_one();
}

bool Item::pop(int &var)
{
    unique_lock<mutex> lck(mtx);

    cv.wait(lck, [this](){return !(valid && pq.empty());});

    if(!valid)
        return false;

    var = pq.top();
    pq.pop();

    lck.unlock();

    return true;
}

void Item::invalidate()
{
    lock_guard<mutex> lck(mtx);

    valid = false;

    cv.notify_all();
}