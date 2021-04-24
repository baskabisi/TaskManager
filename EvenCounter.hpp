/*
 * TimeConsumingTaskV1.hpp
 *
 *  Created on: Apr 23, 2021
 *      Author: sukran
 */

#ifndef TIMECONSUMINGTASKV1_HPP_INCLUDED
#define TIMECONSUMINGTASKV1_HPP_INCLUDED

#include "AnyCounter.hpp"

class EvenCounter: public AnyCounter
{
public:

    EvenCounter();

    virtual ~EvenCounter(void) {}

    void operator()();

    void count();

private:

    unsigned int m_count;
};





#endif /* TIMECONSUMINGTASKV1_HPP_INCLUDED */
