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

    virtual ~AnyWorker(void) {}
    void executeInBackground() { join(); m_worker_thread = std::thread(&AnyWorker::execute, std::ref(*this)); }

protected:

    virtual void execute() = 0;

private:

    void join() { if (m_worker_thread.joinable()) m_worker_thread.join(); }
    std::thread m_worker_thread;
};


#endif /* ANYWORKER_HPP_INCLUDED */
