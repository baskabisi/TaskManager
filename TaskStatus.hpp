/*
 * TaskStatus.hpp
 *
 *  Created on: Apr 24, 2021
 *      Author: sukran
 */

#ifndef TASKSTATUS_HPP_INCLUDED
#define TASKSTATUS_HPP_INCLUDED


#include <iostream>

enum class TaskStatus
{
    // Initial status before run
    IDLE,
    // Task is running
    RUNNING,
    // Task is paused
    PAUSED,
    // Task is aborted. can not be run again
    ABORTED,
    // Unknown status
    UNKNOWN
};

/**
 * This function converts TaskStatus to a string.
 *
 */
inline const std::string
taskStatusToString(TaskStatus status)
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

#endif /* TASKSTATUS_HPP_INCLUDED */
