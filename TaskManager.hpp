/*
 * TaskManager.hpp
 *
 *  Created on: Apr 23, 2021
 *      Author: sukran
 */

#ifndef TASKMANAGER_HPP_INCLUDED
#define TASKMANAGER_HPP_INCLUDED

#include "AnyWorker.hpp"
#include "Task.hpp"
#include "TaskStatus.hpp"

#include <iostream>
#include <cstdlib>
#include <thread>
#include <vector>
#include <map>
#include <memory>
#include <functional>


using namespace std;

#define MAX_NUM_JOBS 100 //std::thread::hardware_concurrency()


class TaskManager
{
public:

    /**
     * @brief Constructor
     */
    TaskManager();

    /**
     * @brief Destructor
     */
    ~TaskManager();

    /**
     * @brief Sets number of tasks to be managed.
     * @see getMaxNumberOfTasks()
     */
    bool setNumberOfTasks(unsigned int number_of_tasks);

    /**
     * @brief Gets the max number of tasks
     */
    unsigned int getMaxNumberOfTasks() const;

    /**
     * @brief Creates tasks and assign jobs
     */
    bool registerTasks();

    /**
     * @brief Checks if provided command is valid
     * @param command Command to be checked
     */
    bool checkCommand(const std::string command) const;

    /**
     * @brief Executes commands provided
     * @see checkCommand()
     * @param command Command to be executed
     */
    bool executeCommand(const std::string& command);

private:

    TaskManager(TaskManager const &) = delete;
    TaskManager& operator =(const TaskManager&) = delete;

    //enum taskType getNextTaskVersion();
    const std::string getStatus(enum TaskStatus status) const;
    const std::string getType(enum TaskType type) const;

    // Commands
    bool startTask(unsigned int id);
    bool abortTask(unsigned int id);
    bool pauseTask(unsigned int id);
    bool resumeTask(unsigned int id);
    bool quit();

    unsigned int m_number_of_tasks;

    std::vector<std::unique_ptr<Task>> m_tasks;

    enum TaskType m_next_task;
};


#endif /* TASKMANAGER_HPP_INCLUDED */
