# Multithreaded-Task-Scheduler
A C++ project implementing a multithreaded task scheduler with priority-based scheduling. It uses a vector-based queue, dynamic priority adjustments based on CPU/memory usage, and thread-safe logging. Demonstrates C++ multithreading, priority management, and scheduling algorithms for efficient task handling.


## Features

- **Multithreading**: Utilizes multiple threads to execute tasks concurrently, enhancing efficiency and performance.
- **Priority-Based Scheduling**: Tasks are prioritized based on CPU and memory usage, allowing the scheduler to manage resources more effectively.
- **Real-Time Adjustments**: Allows dynamic adjustment of task priorities based on real-time metrics.
- **Thread-Safe Logging**: Provides synchronized output using mutexes, ensuring clean and orderly logging.
- **Resource Monitoring**: Tracks CPU time and memory utilization for each task to set priorities automatically.

## Data Structures Used

- **`std::vector<Task>`**: Used as a task queue, allowing dynamic reordering based on task priority.
- **Mutexes and Condition Variables**: Synchronize access to the task queue, preventing race conditions.
- **Atomic Flags**: Used to control the scheduler's start and stop mechanisms.
  
## Getting Started

### Prerequisites

- C++11 or later
- Visual Studio or any C++ IDE supporting multithreading
- CMake (optional, for cross-platform builds)

### Setup and Compilation

1. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/multithreaded-task-scheduler.git
   cd multithreaded-task-scheduler
   ```

2. **Open in IDE** or use CMake:
   - If using an IDE like Visual Studio, open the solution file directly.
   - To use CMake, run:
     ```bash
     mkdir build
     cd build
     cmake ..
     make
     ```

3. **Run the Executable:**
   ```bash
   ./multithreaded-task-scheduler
   ```

## File Structure

- `main.cpp`: Entry point of the application. Adds sample tasks, starts the scheduler, and adjusts priorities.
- `Scheduler.h` and `Scheduler.cpp`: Defines and implements the `Scheduler` class, which manages task scheduling and execution.
- `Task.h` and `Task.cpp`: Defines and implements the `Task` class, including priority settings and execution functionality.

## Usage

To use the scheduler, create `Task` objects with appropriate resource requirements, and add them to the `Scheduler`. The scheduler will dynamically adjust priorities and execute tasks based on available system resources.

Example:
```cpp
scheduler.addTask(Task(1, []() { sampleTask(1); }));
scheduler.start();
std::this_thread::sleep_for(std::chrono::seconds(3));
scheduler.stop();
```

## Future Enhancements

- **Task Dependencies**: Enable tasks to specify dependencies, so that certain tasks must complete before others begin.
- **Advanced Scheduling Policies**: Implement different algorithms like round-robin or weighted fair queuing.
- **Enhanced Monitoring**: Extend resource monitoring to include I/O utilization or network activity.
