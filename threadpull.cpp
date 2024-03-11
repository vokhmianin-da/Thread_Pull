#include "threadpull.h"

void ThreadPull::worker_thread(ThreadPull *pull)
{
    while(!pull->done)
    {
        std::function<void()> task;
        if(pull->work_queue.try_pop(task))
        {
            task();
        }
        else
        {
            std::this_thread::yield();
        }
    }
}

ThreadPull::ThreadPull():  done(false)
{

}

ThreadPull::~ThreadPull()
{
    done=true;
    for(unsigned i=0;i<threads.size();++i)
    {
        if(threads[i].joinable())
        threads[i].join();
    }
}

void ThreadPull::submit(void f())
{
    work_queue.push(f);
}

void ThreadPull::StartThreads()
{
    done = false;
    unsigned const thread_count=std::thread::hardware_concurrency();
    try
    {
        for(unsigned i=0;i<thread_count;++i)
        {
            threads.push_back(
                        std::thread(worker_thread,this));
        }
    }
    catch(...)
    {
        done=true;
        throw;
    }
}

void ThreadPull::StopThreads()
{
    done = true;
    for(unsigned i=0;i<threads.size();++i)
    {
        if(threads[i].joinable())
        threads[i].join();
    }
    threads.clear();
}
