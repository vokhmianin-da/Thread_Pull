#include "threadpull.h"

void ThreadPull::worker_thread(ThreadPull *pull)
{
    while(!pull->done)
    {
        Task task;
        if(pull->work_queue.try_pop(task))
        {
            task();
        }
        else
        {
//            std::this_thread::yield();
            std::unique_lock<std::mutex> lk(pull->mut); //в отличие от std::lock_guard позволяет ожидающему потоку захватить управление мьютексом
            pull->IsWorked.wait(lk,[pull]{return (!pull->work_queue.empty()) || pull->done;});
        }
    }
}

ThreadPull::ThreadPull():  done(true), ThreadQuantity(1)
{

}

ThreadPull::~ThreadPull()
{
    done=true;
    IsWorked.notify_all();
    for(unsigned i=0;i<threads.size();++i)
    {
        if(threads[i].joinable())
        threads[i].join();
    }
}

bool ThreadPull::SetThreadQuantity(unsigned int x)
{
    if(done && x > 0 && x <= std::thread::hardware_concurrency())
    {
        ThreadQuantity = x;
        return true;
    }

    return false;
}

int ThreadPull::GetTasks()
{
    return work_queue.getSize();
}

void ThreadPull::submit(Task f)
{
    work_queue.push(f);
    IsWorked.notify_all();
}

void ThreadPull::StartThreads()
{
    done = false;
//    unsigned const thread_count=4;//std::thread::hardware_concurrency();
    unsigned int thread_count = ThreadQuantity;
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
    IsWorked.notify_all();
    for(unsigned i=0;i<threads.size();++i)
    {
        if(threads[i].joinable())
        threads[i].join();
    }
    threads.clear();
}
