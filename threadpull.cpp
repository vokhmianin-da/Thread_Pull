#include "threadpull.h"

void ThreadPull::worker_thread(ThreadPull *pull)
{
    while(!pull->done)
    {
        Task task;
        if(pull->work_queue.try_pop(task))
        {
            QString str = pull->codec->toUnicode("����������� ��������� ����� %1").arg(task.getVal());
            emit pull->MessageSender.SendMessage(str);
            task();
            str = pull->codec->toUnicode("��������� ����� %1 ����� %2. �������� �����: %3").arg(task.getVal()).arg(task.getResult()).arg(pull->GetTasks());
            emit pull->MessageSender.SendMessage(str);
        }
        else
        {
//            std::this_thread::yield();
            std::unique_lock<std::mutex> lk(pull->mut); //� ������� �� std::lock_guard ��������� ���������� ������ ��������� ���������� ���������
            pull->IsWorked.wait(lk,[pull]{return (!pull->work_queue.empty()) || pull->done;});
        }
    }
}

ThreadPull::ThreadPull():  done(true), ThreadQuantity(1)
{
#ifndef __unix__
    codec = QTextCodec::codecForName("CP1251");
#else
    codec = QTextCodec::codecForName("UTF-8");
#endif
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
    QString str = codec->toUnicode("��������� ������ ���������� ���������� ����� %1").arg(f.getVal());
    emit MessageSender.SendMessage(str);
}
#include <QString>
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
        QString str = codec->toUnicode("�������� %1 ������� ����").arg(thread_count);
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
    QString str = codec->toUnicode("��� ������� ����������");
    emit MessageSender.SendMessage(str);
}
