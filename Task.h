#pragma once

#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <chrono>
#include <functional>

class Task {
public:
    // Task constructor
    //Task(int id, int priority, std::function<void()> func);
    Task(int id, int priority, std::function<void()> func, int delay = 0);
    bool isReady() const;

    // Getter functions
    int getId() const;
    int getPriority() const;
    std::chrono::time_point<std::chrono::high_resolution_clock> getCreationTime() const;

    // Execute the task function
    void execute() const;

    // Comparison operator for priority queue sorting
    bool operator>(const Task& other) const;

    void setPriority(int priority);

private:
    int id;   // Task identifier
    int priority;   // Task priority (higher value = higher priority)
    std::function<void()> func;   // Function to be executed by task
    std::chrono::time_point<std::chrono::high_resolution_clock> creationTime; // Timestamp for when the task is created
    int delay;  // Delay in milliseconds before task execution
};

#endif // TASK_H
