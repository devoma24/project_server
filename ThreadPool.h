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

    void submit(std::function<void()> task);

    private:
    void workerLoop();

    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;

    std::mutex mutex_;
    std::condition_variable cv_;
    std::atomic<bool> stop_ {false};
};