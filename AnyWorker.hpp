/*
 * AnyWorker.hpp
 *
 *  Created on: Apr 23, 2021
 *      Author: sukran
 */

#ifndef ANYWORKER_HPP_INCLUDED
#define ANYWORKER_HPP_INCLUDED


#include <iostream>
#include <thread>
#include <functional>

using namespace std;

class AnyWorker
{
public:

    /**
     * @brief Destructor
     */
    virtual ~AnyWorker(void) {}

    /**
     * @brief To be implemented by derived classes in order to execute the tasks in parallel.
     */
    virtual void operator()() = 0;

    /**
     * @brief To be implemented by derived classes in order to be executed.
     */
    virtual void execute() = 0;
};


#endif /* ANYWORKER_HPP_INCLUDED */
