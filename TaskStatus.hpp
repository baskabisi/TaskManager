/*
 * TaskStatus.hpp
 *
 *  Created on: Apr 24, 2021
 *      Author: sukran
 */

#ifndef TASKSTATUS_HPP_INCLUDED
#define TASKSTATUS_HPP_INCLUDED

#include <string>
#include <iostream>

enum class TaskStatus
{
    ///initial state before run
    IDLE,
    ///task is running
    RUNNING,
    ///task is paused
    PAUSED,
    ///task is aborted. can not be run again
    ABORTED,
    ///unknown state
    UNKNOWN
};

/**
 * This function converts TaskStatus to a string.
 *
 */
inline std::string
taskStatusToString(TaskStatus state)
{
    switch (state)
    {
        case TaskStatus::IDLE:
            return "IDLE";
        case TaskStatus::RUNNING:
            return "RUNNING";
        case TaskStatus::PAUSED:
            return "PAUSED";
        case TaskStatus::ABORTED:
            return "ABORTED";
    }
    return "UNKNOWN";
}

#endif /* TASKSTATUS_HPP_INCLUDED */
