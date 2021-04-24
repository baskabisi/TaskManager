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

    virtual void operator()() = 0;
};


#endif /* ANYWORKER_HPP_INCLUDED */
