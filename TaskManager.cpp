/*
 * TaskManager.cpp
 *
 *  Created on: Apr 23, 2021
 *      Author: sukran
 */

#include "TaskManager.hpp"

#include "AnyWorker.hpp"
#include "EvenCounter.hpp"
#include "OddCounter.hpp"


const std::string command_status("status");
const std::string command_start("start");
const std::string command_abort("abort");
const std::string command_pause("pause");
const std::string command_resume("resume");
const std::string command_quit("quit");

TaskManager::TaskManager()
: m_number_of_tasks(0),
  m_next_task(count_even)
{
}

bool
TaskManager::setNumberOfTasks(unsigned int number_of_tasks)
{
    if (number_of_tasks <= getMaxNumberOfTasks())
    {
        m_number_of_tasks = number_of_tasks;
        return true;
    }

    return false;
}

unsigned int
TaskManager::getMaxNumberOfTasks() const
{
    return MAX_NUM_JOBS;
}

bool
TaskManager::registerTasks()
{
    for (unsigned int i = 0; i < m_number_of_tasks; i++ )
    {
        taskInfo task;
        task.status = idle;
        task.type = getNextTaskVersion();

        m_tasks.insert(std::pair<unsigned int, taskInfo>(i , task));
    }

    return false;
}

bool
TaskManager::executeCommand(const std::string& command)
{

    if (command.compare(command_quit) == 0)
    {
        quit();
        cout << "See you next time!" << endl;
        return false;
    }
    else if (command.compare(command_status) == 0)
    {
        for (auto& item: m_tasks)
        {
            cout << "Job id: " << item.first << " | Job type: " << getType(item.second.type) << " | Status: " << getStatus(item.second.status) << endl;
        }
    }
    else
    {
        unsigned int id = 0;
        cin >> id;

        if (!cin)
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << "Try again with a valid job id!" << endl;
        }
        else
        {
            if (id < m_number_of_tasks)
            {
                if (command.compare(command_start) == 0)
                {
                    cout << "Trying to start job #" << id <<  endl;
                    startTask(id);
                }
                else if (command.compare(command_abort) == 0)
                {
                    cout << "Trying to abort job #" << id <<  endl;
                    abortTask(id);
                }
                else if (command.compare(command_pause) == 0)
                {
                    cout << "Trying to pause job #" << id <<  endl;
                    pauseTask(id);
                }
                else if (command.compare(command_resume) == 0)
                {
                    cout << "Trying to resume job #" << id <<  endl;
                    resumeTask(id);
                }
                else
                {
                    cout << endl << "Try again, '" << command << "' is not a valid command!" << endl;

                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
            else
            {
                cout << "Try again, " << id << " is not valid job id!" << endl;
            }
        }
    }

    return true;
}

enum taskType
TaskManager::getNextTaskVersion()
{
    if (m_next_task == count_even)
    {
        m_next_task = count_odd;
    }
    else if (m_next_task == count_odd)
    {
        m_next_task = count_even;
    }

    return m_next_task;
}

const std::string
TaskManager::getStatus(enum taskStatus status) const
{
    const std::string status_idle("Idle");
    const std::string status_running("Running");
    const std::string status_paused("Paused");
    const std::string status_aborted("Aborted");

    switch (status)
    {
        case running:
            return status_running;
        case paused:
            return status_paused;
        case aborted:
            return status_aborted;
        case idle:
        default:
            return status_idle;
    }
}

const std::string
TaskManager::getType(enum taskType type) const
{
    const std::string even_counter("Even Counter");
    const std::string odd_counter("Odd Counter");

    switch (type)
    {
        case count_even:
            return even_counter;
        case count_odd:
            return odd_counter;
    }
}

bool
TaskManager::checkCommand(const std::string command) const
{
    bool valid_command = false;

    if (((command.compare(command_status) == 0)) ||
        ((command.compare(command_start) == 0))  ||
        ((command.compare(command_abort) == 0))  ||
        ((command.compare(command_pause) == 0))  ||
        ((command.compare(command_resume) == 0))  ||
        ((command.compare(command_quit) == 0)))
    {
        valid_command = true;
    }

    return valid_command;
}

bool
TaskManager::startTask(unsigned int id)
{
    auto it = m_tasks.find(id);
    if (it != m_tasks.end())
    {
        if (it->second.status == idle)
        {
            if (it->second.type == count_even)
            {
                m_workers.insert(std::pair<unsigned int, std::thread>(it->first, std::thread((EvenCounter()))));
            }
            else if (it->second.type == count_odd)
            {
                m_workers.insert(std::pair<unsigned int, std::thread>(it->first, std::thread((OddCounter()))));
            }
            it->second.status = running;
        }
        else
        {
            cout << "Job #" << id << " is not idle." <<  endl;
        }
    }

    return false;
}

bool
TaskManager::abortTask(unsigned int id)
{
    auto it = m_tasks.find(id);
    if (it != m_tasks.end())
    {
        if (it->second.status != aborted)
        {
            it->second.status = aborted;
            auto it = m_workers.find(id);
            if (it != m_workers.end())
            {
                // abort thread
            }
            cout << "Job #" << id << " aborted." <<  endl;
        }
        else
        {
            cout << "Job #" << id << " is already aborted." <<  endl;
        }
    }

    return false;
}

bool
TaskManager::pauseTask(unsigned int id)
{
    auto it = m_tasks.find(id);
    if (it != m_tasks.end())
    {
        if (it->second.status == running)
        {
            it->second.status = paused;
            cout << "Job #" << id << " paused." <<  endl;
        }
        else
        {
            cout << "Job #" << id << " was not running." <<  endl;
        }
    }

    return false;
}

bool
TaskManager::resumeTask(unsigned int id)
{
    auto it = m_tasks.find(id);
    if (it != m_tasks.end())
    {
        if (it->second.status == paused)
        {
            it->second.status = running;
            cout << "Job #" << id << " resumed." <<  endl;
        }
        else
        {
            cout << "Job #" << id << " was not paused." <<  endl;
        }
    }

    return false;
}

bool
TaskManager::quit()
{
    cout << "Aborting all tasks and leaving." <<  endl;
    return false;
}
