/*
 * Task.hpp
 *
 *  Created on: Apr 24, 2021
 *      Author: sukran
 */

#ifndef TASK_HPP_INCLUDED
#define TASK_HPP_INCLUDED

#include "TaskStatus.hpp"
#include "AnyCounter.hpp"

#include <atomic>
#include <condition_variable>
#include <functional>
#include <thread>

enum TaskType
{
    count_even,
    count_odd
};

class Task
{
public:

    Task(unsigned int id);

    ~Task();

    /**
     * Get status of task.
     */
    TaskStatus status();

    /**
     * Start task if task is idle.
     */
    void start();

    /**
     * Pause task if task is running.
     */
    void pause();

    /**
     * Abort task. Thread will be ready for join.
     */
    void abort();

    /**
     * Resume task if task is paused.
     */
    void resume();

    /**
     * Get status of task.
     */
    TaskType type();

    /**
     * Get id of task.
     */
    unsigned int id();

private:
    /**
     * method for running thread.
     */
    void internalTask();

    std::thread m_thread;

    /// Mutex for thread loop.
    std::mutex m_mutex;

    /// Condition variable to wake up thread from pause or idle states.
    std::condition_variable m_state_changed;

    /// Thread ID.
    unsigned int m_id;

    /// Thread state.
    std::atomic<TaskStatus> m_status;

    std::unique_ptr<AnyWorker> m_worker;

    TaskType m_type;
};

#endif /* TASK_HPP_INCLUDED */
