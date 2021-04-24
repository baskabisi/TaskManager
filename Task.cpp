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
  m_id(id),
  m_type(count_even)
{
    if (m_id % 2 == 0)
    {
        m_worker = std::make_unique<EvenCounter>(m_id);
        m_type = count_even;
    }
    else
    {
        m_worker = std::make_unique<OddCounter>(m_id);
        m_type = count_odd;
    }
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
    cout << "Job #" << m_id << " aborted." <<  endl;
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
Task::status()
{
    return m_status;
}

TaskType
Task::type()
{
    return m_type;
}

unsigned int
Task::id()
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

