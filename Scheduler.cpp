#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>  // for std::sort
#include "Scheduler.h"

// Global mutex for synchronized output to std::cout
std::mutex coutMutex;

// Constructor: Initializes the scheduler with the specified number of threads
Scheduler::Scheduler(size_t numThreads) : stopFlag(false) {
    // Reserve space for threads and start each worker thread
    workers.reserve(numThreads);
    for (size_t i = 0; i < numThreads; ++i) {
        workers.emplace_back(&Scheduler::workerThread, this);
    }
}

// Destructor: Stops the scheduler and joins all worker threads
Scheduler::~Scheduler() {
    stop();
}

// Add a new task to the queue
void Scheduler::addTask(const Task& task) {
    {
        // Lock the queue and add the task
        std::lock_guard<std::mutex> lock(queueMutex);
        taskQueue.push_back(task);
        std::sort(taskQueue.begin(), taskQueue.end(), std::greater<Task>());
    }
    // Notify one waiting thread that a new task is available
    cv.notify_one();
}

// Adjust task priority
void Scheduler::modifyTaskPriority(int taskId, int newPriority) {
    std::lock_guard<std::mutex> lock(queueMutex);
    for (auto& task : taskQueue) {
        if (task.getId() == taskId) {
            task.setPriority(newPriority);  // Add setPriority method in Task class
            break;
        }
    }
    // Sort the queue based on updated priorities
    std::sort(taskQueue.begin(), taskQueue.end(), std::greater<Task>());
}

// Start processing tasks
void Scheduler::start() {
    stopFlag = false;
}

// Stop all processing and join all worker threads
void Scheduler::stop() {
    {
        // Set stop flag and notify all threads to exit
        std::lock_guard<std::mutex> lock(queueMutex);
        stopFlag = true;
    }
    cv.notify_all();

    // Join each thread
    for (auto& worker : workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

// Worker thread function to process tasks
void Scheduler::workerThread() {
    while (true) {
        Task task(0, 0, [] {}); // Placeholder for an empty task
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            // Wait until there is a task or stop flag is set
            cv.wait(lock, [this] { return !taskQueue.empty() || stopFlag; });

            if (stopFlag && taskQueue.empty()) {
                return; // Exit if stop is requested and no tasks are left
            }

            // Pop the highest priority task
            if (!taskQueue.empty()) {
                task = taskQueue.back();
                taskQueue.pop_back();
            }
        }

        {
            std::lock_guard<std::mutex> lock(coutMutex);
            std::cout << "Executing task " << task.getId()
                << " on thread " << std::this_thread::get_id() << std::endl;
        }

        // Execute the task outside the lock
        task.execute();
    }
}


// Update Task class to allow setting priority
void Task::setPriority(int priority) {
    this->priority = priority;
}

void Scheduler::printStatus() {
    std::lock_guard<std::mutex> lock(queueMutex);
    std::cout << "Scheduler Status: " << std::endl;
    std::cout << "Tasks in Queue: " << taskQueue.size() << std::endl;
    std::cout << "Active Threads: " << workers.size() << std::endl;

    for (const auto& task : taskQueue) {
        std::cout << "Task ID: " << task.getId()
            << ", Priority: " << task.getPriority()
            << ", Ready to Execute: " << (task.isReady() ? "Yes" : "No") << std::endl;
    }
}