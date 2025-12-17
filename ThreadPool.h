#pragma once
#include <iostream>
#include <functional>
#include <thread>
#include <condition_variable>
#include <atomic>
#include <mutex>
#include <queue>
#include <vector>

class ThreadPool
{
    public:
    explicit ThreadPool(std::size_t treadCount);
    ~ThreadPool();

    template<typename F>
    void submit(F&& f)
{
    auto task = std::make_unique<std::function<void()>>(std::forward<F>(f));
    {
        std::lock_guard<std::mutex> lock(mutex_);
        tasks_.push(std::move(task));
    }
    cv_.notify_one();
}

    private:
    void workerLoop();

    std::vector<std::thread> workers_;
    //std::queue<std::function<void()>> tasks_;
    std::queue<std::unique_ptr<std::function<void()>>> tasks_;

    std::mutex mutex_;
    std::condition_variable cv_;
    std::atomic<bool> stop_ {false};
};