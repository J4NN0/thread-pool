# thread-pool
Thread pool in c++

More threads access at the same data structure (a class named Item in this example) and the concurrency is managed by condition variable, lock (lock_guard and unique_lock) and mutex used in ThreadPool class. 

In this way Item is a thread safe class and more threads (that will do some stuff) access to it.
