# thread-pool
Thread pool in C++

More threads access at the same data structure (a class named Item in this example) and the concurrency is managed by condition variable, lock (lock_guard and unique_lock) and mutex used in ThreadPool class. 

In this way Item is a thread safe class and more threads (that will do some stuff) access to it.

# Class Item
#### Variables
- Boolean 'valid'
  - The constructor of the class set this variable as true
  - The destructor (or the method invalidate()) set this variable as false
  - This is usefull to understand if the class is still valid and so if the threads that are waiting to do some stuff can terminate or not
- Mutex
  - Mutual exclusion variable able to prevent race condition
  - It is the requirement that one thread of execution never enter its critical section at the same time that another concurrent thread of execution enters its own critical section
- Condition variable
  - It allows threads to have both mutual exclusion and the ability to wait (block) for a certain condition to become true
- Priority queue
  - This is the true data that you access
  - You can modify this data type and put another data type
  
#### Methods
- ```cpp public void push(int var)```
  1. Method requires a var (of type int but you can modify it as you want) that have to be pushed in the queue
  2. A lock guard is defined
     ```cpp   
     lock_guard<mutex> lck(mtx);
     ```
     In this way a thread access to the critial section only when the lock is released by another one 
  3. A check of valid is done
  4. The value is pushed on the priority queue
  5. Notify through condition variable that a value is inserted in the queue and so if there are at least one thread waiting for a value it can do its stuff
- ```cpp public bool pop(int &var)```
  1. A unique lock is defined
     ```cpp   
       unique_lock<mutex> lck(mtx);
      ```      
     Unlike lock guard the unique lock can be released when you want. Thanks to this if the queue is empty the thread can release the lock (in this way it allows other thread to acces to the data structure) and wait for a condition: i.e. a value is pushed in the priority queue
  2. Thread check if the queue is empty (and valid at the same time) 
     ```cpp   
      cv.wait(lck, [this](){return !(valid && pq.empty());});
      ```      
     When the condition becomes true the thread will take the lock and go on
  3. Pop the value from the top of the proprity queue
  4. 'var' will contain the poped variable and the method will return true
  5. If the method return false means that the class is not valid anymore
- ```cpp public void invalidate(void)```
  1. A lock guard is defined
  2. Queue is invalidate
  3. Notify all thread of the changes 
     ```cpp   
     cv.notify_all();
     ```
     If threads are in ```cpp cv.wait(...)``` the will wake up and will see that the class is invalid and will terminate
     
# Class ThreadPool
#### Variables
- A type Item
- nthreads
  - An int value that through thread::hardware_concurrency() will know the maximum number of concurrent threads that are supported
- Vector of threads
  - Usefull to remember all generated threads
  - Used also to terminate all threads
- Once flag
  - It allows to call a function only once
  
#### Methods
-  ```cpp public void startup(void)```
  1. It have to be called and the start of the program
  2. This method have to be called only once otherwise an exception is raised
  3. It generated 'nthreads' and it associates to each thread the funciton worker()
     ```cpp   
     threads.emplace_back(thread{&ThreadPool::worker, this});
     ```
-  ```cpp public void shutdown(void)```
  1. It have to be called and the end of the program
  2. This method have to be called only once otherwise an exception is raised
  3. It will invalidate the class and terminate all threads that are generated earlier
- ```cpp private void worker(void)```
  1. While the queue is valid the method will go on
  2. A value is popped from the priority queue
  3. Given this value the method do some stuff (in this case only a cout)
- ```cpp public void post_task(int var)```
  1. Method requires a var (of type int but you can modify it as you want) you want to push on the queue
