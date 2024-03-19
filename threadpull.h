#ifndef THREADPULL_H
#define THREADPULL_H

#include <thread>
#include <vector>
#include <atomic>
#include <queue>
#include "thread_safe_queue.h"
#include <functional>
#include <condition_variable>
#include <mutex>
#include "task.h"
#include "pullmessages.h"


class ThreadPull
{
    std::atomic_bool done;
    thread_safe_queue<Task> work_queue;
    std::vector<std::thread> threads;
    std::condition_variable IsWorked;
    std::mutex mut;

    unsigned int ThreadQuantity;

    static void worker_thread(ThreadPull *pull);

public:
    ThreadPull();
     ~ThreadPull();

    bool SetThreadQuantity(unsigned int x);
    bool IsDone()
    {
        return done;
    }
    int GetTasks();
    void submit(Task f);
    void StartThreads();
    void StopThreads();

    PullMessages MessageSender;
};

#endif // THREADPULL_H
