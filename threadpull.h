#ifndef THREADPULL_H
#define THREADPULL_H

#include <thread>
#include <vector>
#include <atomic>
#include <queue>
#include "thread_safe_queue.h"
#include <functional>

struct join_threads
{
    join_threads(std::vector<std::thread>&)
    {}
};

class ThreadPull
{
    std::atomic_bool done;
    thread_safe_queue<std::function<void()> > work_queue;
    std::vector<std::thread> threads;
    join_threads joiner;

    static void worker_thread(ThreadPull *pull);
public:
    ThreadPull();
     ~ThreadPull();

    void submit(void f());
};

#endif // THREADPULL_H
