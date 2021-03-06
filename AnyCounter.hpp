/*
 * AnyCounter.hpp
 *
 *  Created on: Apr 23, 2021
 *      Author: sukran
 */

#ifndef ANYCOUNTER_HPP_INCLUDED
#define ANYCOUNTER_HPP_INCLUDED

#include "AnyWorker.hpp"

class AnyCounter: public AnyWorker
{
public:

    /**
     * @brief Destructor
     */
    virtual ~AnyCounter(void) {}

    /**
     * @brief To be implemented by derived classes in order to execute the tasks in parallel.
     */
    virtual void operator()(){count();};

    /**
     * @brief Returns task type
     */
    virtual TaskType getTaskType() const = 0;

    /**
     * @brief Implemented in order to execute the counting task in parallel.
     */
    void execute(){count();};

    /**
     * @brief To be implemented by derived classes in order to perform a count task.
     */
    virtual void count() = 0;

};

#endif /* ANYCOUNTER_HPP_INCLUDED */
