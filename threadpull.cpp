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
            std::unique_lock<std::mutex> lk(pull->mut); //� ������� �� std::lock_guard ��������� ���������� ������ ��������� ���������� ���������
            pull->IsWorked.wait(lk,[pull]{return (!pull->work_queue.empty()) || pull->done;});
        }
    }
}

ThreadPull::ThreadPull():  done(false)
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

void ThreadPull::submit(Task f)
{
    work_queue.push(f);
    IsWorked.notify_all();
}

void ThreadPull::StartThreads()
{
    done = false;
    unsigned const thread_count=4;//std::thread::hardware_concurrency();
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
