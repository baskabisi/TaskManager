/*
 * TaskManager.hpp
 *
 *  Created on: Apr 23, 2021
 *      Author: sukran
 */

#ifndef TASKMANAGER_HPP_INCLUDED
#define TASKMANAGER_HPP_INCLUDED


#include <iostream>
#include <cstdlib>
#include <thread>
#include <vector>
#include <map>
#include <memory>
#include <functional>

#include "AnyWorker.hpp"

using namespace std;

#define MAX_NUM_JOBS 100 // Consider setting this value according to sth meaningful


enum taskStatus
{
    idle,
    running,
    paused,
    aborted
};

enum taskVersion
{
    task_version_1,
    task_version_2
};

struct taskInfo
{
    taskStatus status;
    //std::thread::id thread_id;
    //std::function<void()> func;
    //std::thread task_thread;
    //AnyWorker* worker;
    taskVersion version;
};

class TaskManager
{
public:
    TaskManager();

    bool setNumberOfTasks(unsigned int number_of_tasks);
    unsigned int getMaxNumberOfTasks() const;
    bool registerTasks();
    bool executeCommand(const std::string& command);

private:
    void threadFunction(int version);
    enum taskVersion getNextTaskVersion();
    const std::string getStatus(enum taskStatus status) const;
    bool checkCommand() const;

    // Commands
    bool startTask(unsigned int id);
    bool abortTask(unsigned int id);
    bool pauseTask(unsigned int id);
    bool resumeTask(unsigned int id);
    bool quit();

    unsigned int m_number_of_tasks;
    std::map<unsigned int, taskInfo> m_tasks;
    std::map<unsigned int, std::thread> m_workers;
    enum taskVersion m_next_task;
};


#endif /* TASKMANAGER_HPP_INCLUDED */
