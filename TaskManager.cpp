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
#include "TaskStatus.hpp"


const std::string command_status("status");
const std::string command_start("start");
const std::string command_abort("abort");
const std::string command_pause("pause");
const std::string command_resume("resume");
const std::string command_quit("quit");

TaskManager::TaskManager()
: m_number_of_tasks(),
  m_next_task(count_even)
{
}

TaskManager::~TaskManager()
{
    m_tasks.clear();
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
        auto ret = std::make_unique<Task>(i);
        m_tasks.push_back(std::move(ret));
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
            cout << "Job id: " << item->id() << " | Job type: " << getType(item->type()) << " | Status: " << getStatus(item->status()) << endl;
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

const std::string
TaskManager::getStatus(enum TaskStatus status) const
{
    const std::string status_idle("Idle");
    const std::string status_running("Running");
    const std::string status_paused("Paused");
    const std::string status_aborted("Aborted");
    const std::string status_unknown("Unknown");

    switch (status)
    {
        case TaskStatus::RUNNING:
            return status_running;
        case TaskStatus::PAUSED:
            return status_paused;
        case TaskStatus::ABORTED:
            return status_aborted;
        case TaskStatus::IDLE:
            return status_idle;
        case TaskStatus::UNKNOWN:
        default:
            return status_unknown;
    }
}

const std::string
TaskManager::getType(enum TaskType type) const
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
    if ((m_tasks.size() > id) &&
        (m_tasks[id]->status() == TaskStatus::IDLE))
    {
        m_tasks[id]->start();
    }
    else
    {
        cout << "Job #" << id << " is not idle." <<  endl;
    }

    return false;
}

bool
TaskManager::abortTask(unsigned int id)
{
    if ((m_tasks.size() > id) &&
        (m_tasks[id]->status() != TaskStatus::ABORTED))
    {
        m_tasks[id]->abort();
        cout << "Job #" << id << " aborted." <<  endl;
    }
    else
    {
        cout << "Job #" << id << " is already aborted." <<  endl;
    }

    return false;
}

bool
TaskManager::pauseTask(unsigned int id)
{
    if ((m_tasks.size() > id) &&
        (m_tasks[id]->status() == TaskStatus::RUNNING))
    {
        m_tasks[id]->pause();

        cout << "Job #" << id << " paused." <<  endl;
    }
    else
    {
        cout << "Job #" << id << " was not running." <<  endl;
    }

    return false;
}

bool
TaskManager::resumeTask(unsigned int id)
{
    if ((m_tasks.size() > id) &&
        (m_tasks[id]->status() == TaskStatus::PAUSED))
    {
        m_tasks[id]->resume();
        cout << "Job #" << id << " resumed." <<  endl;
    }
    else
    {
        cout << "Job #" << id << " was not paused." <<  endl;
    }

    return false;
}

bool
TaskManager::quit()
{
    cout << "Aborting all tasks and leaving." <<  endl;
    return false;
}
