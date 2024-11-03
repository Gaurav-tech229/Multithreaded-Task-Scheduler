#pragma once

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Task.h"
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>

class Scheduler {
public:
    // Constructor and Destructor
    Scheduler(size_t numThreads);
    ~Scheduler();

    // Public API
    void addTask(const Task& task);
    void start();
    void stop();

    void modifyTaskPriority(int taskId, int newPriority);

    void printStatus();
private:
    // Internal method for worker threads to process tasks
    void workerThread();

    // Task priority queue and associated synchronization primitives
    std::vector<Task> taskQueue;
    std::vector<std::thread> workers;
    std::mutex queueMutex;
    std::condition_variable cv;
    std::atomic<bool> stopFlag;
};

#endif // SCHEDULER_H
