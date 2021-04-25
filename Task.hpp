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


class Task
{
public:

    /**
     * @brief Constructor
     * @param Task id
     */
    Task(unsigned int id);

    /**
     * @brief Destructor
     */
    ~Task();

    /**
     * @brief Starts task if task is idle.
     */
    void start();

    /**
     * @brief Pauses task if task is running.
     */
    void pause();

    /**
     * @brief Aborts task. Thread will be ready for join.
     */
    void abort();

    /**
     * @brief Resumes task if task is paused.
     */
    void resume();

    /**
     * @brief Gets status of task.
     */
    TaskStatus getStatus() const;

    /**
     * @brief Sets id of task.
     * @param status New status
     */
    void setStatus(TaskStatus status);

    /**
     * @brief Gets the worker to execute the task.
     */
    std::unique_ptr<AnyWorker> getWorker();

    /**
     * @brief Sets the worker to execute the task.
     * @param status New worker
     */
    void setWorker(std::unique_ptr<AnyWorker> worker);

    /**
     * @brief Gets id of task.
     */
    unsigned int getId() const;

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

    std::unique_ptr<AnyWorker> m_worker;

    /// Thread state.
    std::atomic<TaskStatus> m_status;

    /// Thread ID.
    unsigned int m_id;
};

#endif /* TASK_HPP_INCLUDED */
