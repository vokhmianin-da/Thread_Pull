#include "threadpull.h"

void ThreadPull::worker_thread(ThreadPull *pull)
{
    while(!pull->done)
    {
        Task task;
        if(pull->work_queue.try_pop(task))
        {
            QString str = QString("Вычисляется факториал числа %1").arg(task.getVal());
            emit pull->MessageSender.SendMessage(str);
            task();
            str = QString("Факториал числа %1 равен %2").arg(task.getVal()).arg(task.getResult());
            emit pull->MessageSender.SendMessage(str);
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
    QString str = QString("Добавлена задача вычисления факториала числа %1").arg(f.getVal());
    emit MessageSender.SendMessage(str);
}

void ThreadPull::StartThreads()
{
    if(!done) return;
    done = false;
    unsigned int thread_count = ThreadQuantity;
    try
    {
        for(unsigned i=0;i<thread_count;++i)
        {
            threads.push_back(
                        std::thread(worker_thread,this));
        }
        QString str = QString("Запущено %1 потоков пула").arg(thread_count);
        emit MessageSender.SendMessage(str);
    }
    catch(...)
    {
        done=true;
        throw;
    }
}

void ThreadPull::StopThreads()
{
    if(done) return;
    done = true;
    IsWorked.notify_all();
    for(unsigned i=0;i<threads.size();++i)
    {
        if(threads[i].joinable())
        threads[i].join();
    }
    threads.clear();
    work_queue.clear(); //по заданию нужно удалить оставшиеся в очереди задачи
    QString str = "Пул потоков остановлен";
    emit MessageSender.SendMessage(str);
}
