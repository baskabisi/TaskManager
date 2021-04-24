/*
 * AnyTimeConsumingTask.hpp
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

    virtual ~AnyCounter(void) {}

    virtual void operator()(){count();};

    virtual void count() = 0;

};


#endif /* ANYCOUNTER_HPP_INCLUDED */
