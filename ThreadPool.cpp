#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t threadCount)
{
    for(size_t i = 0; i < threadCount; ++i)
    {
        workers_.emplace_back([this]{ workerLoop(); });
    }
}

void ThreadPool::workerLoop()
{
    while(true)
    {
        std::unique_ptr<std::function<void()>> task;
        {
            std::unique_lock<std::mutex> lock(mutex_);

            cv_.wait(lock, [this] { return stop_ || !tasks_.empty(); });

            if(stop_ && tasks_.empty()) { return; }

            task = std::move(tasks_.front());
            tasks_.pop();
        }

        (*task)();
    }
}

ThreadPool::~ThreadPool()
{
    stop_ = true;
    cv_.notify_all();

    for(auto& pool: workers_)
    {
        if(pool.joinable())
        {
            pool.join();
        }
    }
}

void ThreadPool::shutdown()
{
    stop_ = true;
    cv_.notify_all();

    for(auto& t: workers_)
    {
        if(t.joinable())
        {
            t.join();
        }
    }
}