/*
 * TaskManager.cpp
 *
 *  Created on: Apr 23, 2021
 *      Author: sukran
 */

#include "TaskManager.hpp"
/*
#include "AnyWorker.hpp"
#include "EvenCounter.hpp"
#include "OddCounter.hpp"
*/

class EvenCounter
{
public:
    void operator()()
    {
        int count = 0;
        cout << "Starting to count even numbers..." <<  endl;
        while (1)
        {
            //cout << "Counting even numbers: " << count << endl;
            count += 2;
        }
    }
};

class OddCounter
{
public:
    void operator()()
    {
        int count = 1;
        cout << "Starting to count odd numbers..." <<  endl;
        while (1)
        {
            //cout << "Counting odd numbers: " << count << endl;
            count += 2;
        }
    }
};



TaskManager::TaskManager()
: m_number_of_tasks(0),
  m_next_task(task_version_1)
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
        if (getNextTaskVersion() == task_version_1)
        {
/*
            std::function<void()> func_v1 = []() {
                                //Do Some Important Work
                                // .....
                                //Print Thread ID
                                std::cout << "1 From Thread ID : "<<std::this_thread::get_id() << "\n";
                                };

            std::thread task_v1((Thread1()));
            task_v1.join();
            task.task_thread = std::move(task_v1);

            //task.func = std::function<std::bind(&TimeConsumingTaskV1::execute)()>;
            task.thread_id = task_v1.get_id();
            */
            //task.worker = new EvenCounter();
        }
        else if (getNextTaskVersion() == task_version_2)
        {
/*
            std::function<void()> func_v2 = []() {
                                //Do Some Important Work
                                // .....
                                //Print Thread ID
                                std::cout << "2 From Thread ID : "<<std::this_thread::get_id() << "\n";
                                };
            std::thread task_v2((Thread2()));
            task_v2.join();
            task.task_thread = std::move(task_v2);

            //task.func = std::function<std::bind(&TimeConsumingTaskV2::execute)()>;
            task.thread_id = task_v2.get_id();
            */

            //task.worker = new OddCounter();
        }

        task.version = getNextTaskVersion();
        m_tasks.insert(std::pair<unsigned int, taskInfo>(i , task));

        //m_tasks.insert(std::pair<unsigned int, taskInfo>(i, task));
    }

    return false;
}

bool
TaskManager::executeCommand(const std::string& command)
{
    const std::string command_status("status");
    const std::string command_start("start");
    const std::string command_abort("abort");
    const std::string command_pause("pause");
    const std::string command_resume("resume");
    const std::string command_quit("quit");

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
            cout << "Job id: " << item.first << " status: " << getStatus(item.second.status) <<  endl;
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

/*
void
TaskManager::threadFunction(int version)
{
    int count = 0;
    if (version == 0)
    {
        cout << "Starting to count even numbers..." <<  endl;
        //while (1)
        {
            cout << "Counting even numbers: " << count << endl;
            count += 2;
        }
    }
    else
    {
        count = 1;
        cout << "Starting to count odd numbers..." <<  endl;
        //while (1)
        {
            cout << "Counting odd numbers: " << count << endl;
            count += 2;
        }
    }
}
*/

bool
TaskManager::startTask(unsigned int id)
{
    auto it = m_tasks.find(id);
    if (it != m_tasks.end())
    {
        if (it->second.status == idle)
        {
            /*
            AnyWorker* worker = it->second.worker;
            if (worker)
            {
                worker->executeInBackground();
            }
            */
            if (it->second.version == task_version_1)
            {
                std::thread worker((EvenCounter()));
                worker.join();
            }
            else if (it->second.version == task_version_2)
            {
                std::thread worker((OddCounter()));
                worker.join();
            }
            it->second.status = running;
            //cout << "Job #" << id << " started. Thread id: " <<  worker_thread.get_id() << endl;
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

enum taskVersion
TaskManager::getNextTaskVersion()
{
    if (m_next_task == task_version_1)
    {
        m_next_task = task_version_2;
    }
    else if (m_next_task == task_version_2)
    {
        m_next_task = task_version_1;
    }

    return m_next_task;
}
