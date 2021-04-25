/*
 * Task.cpp
 *
 *  Created on: Apr 24, 2021
 *      Author: sukran
 */

#include "Task.hpp"
#include "EvenCounter.hpp"
#include "OddCounter.hpp"


Task::Task(unsigned int id)
: m_status(TaskStatus::IDLE),
  m_id(id)
{
}

Task::~Task()
{
    m_status = TaskStatus::ABORTED;
    m_state_changed.notify_one();
    if (m_thread.joinable())
    {
        m_thread.join();
    }
}

void
Task::start()
{
    if (m_status == TaskStatus::IDLE)
    {
        m_status = TaskStatus::RUNNING;

        m_thread = std::thread{std::bind(&Task::internalTask, this)};

        m_state_changed.notify_one();
    }
}

void
Task::abort()
{
    m_status = TaskStatus::ABORTED;
    m_state_changed.notify_one();
}

void
Task::pause()
{
    if (m_status == TaskStatus::RUNNING)
    {
        m_status = TaskStatus::PAUSED;
    }
}

void
Task::resume()
{
    if (m_status == TaskStatus::PAUSED)
    {
        m_status = TaskStatus::RUNNING;
        m_state_changed.notify_one();
    }
}

TaskStatus
Task::getStatus() const
{
    return m_status;
}

void
Task::setStatus(TaskStatus status)
{
    m_status = status;
}

std::unique_ptr<AnyWorker>
Task::getWorker()
{
    return std::move(m_worker);
}

void
Task::setWorker(std::unique_ptr<AnyWorker> worker)
{
    m_worker = std::move(worker);
}

unsigned int
Task::getId() const
{
    return m_id;
}

void
Task::internalTask()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    do
    {
        while (m_status == TaskStatus::PAUSED || m_status == TaskStatus::IDLE)
        {
            m_state_changed.wait(lock);
        }
        while (m_status == TaskStatus::RUNNING && m_worker != nullptr)
        {
            m_worker->execute();
        }

    } while (m_status != TaskStatus::ABORTED);
}

