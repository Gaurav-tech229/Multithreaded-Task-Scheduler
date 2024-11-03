#include "Scheduler.h"
#include "Task.h"
#include <iostream>
#include <thread>
#include <chrono>

void sampleTask(int id) {
    std::cout << "Task " << id << " executed on thread " << std::this_thread::get_id() << std::endl;
}

int main() {
    // Initialize scheduler with 3 threads
    Scheduler scheduler(3);

    // Add sample tasks with different priorities
    scheduler.addTask(Task(1, 1, []() { sampleTask(1); }));
    scheduler.addTask(Task(2, 3, []() { sampleTask(2); }));
    scheduler.addTask(Task(3, 2, []() { sampleTask(3); }));
    scheduler.addTask(Task(4, 5, []() { sampleTask(4); }));

    // Start the scheduler and let it run for a short duration
    scheduler.start();

    // Modify priority of an existing task
    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    scheduler.modifyTaskPriority(3, 5);  // Task 3 gets highest priority

    // Check scheduler status
    std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Short delay to allow for task execution
    scheduler.printStatus();

    std::this_thread::sleep_for(std::chrono::seconds(3));

    // Stop the scheduler
    scheduler.stop();
    return 0;
}
