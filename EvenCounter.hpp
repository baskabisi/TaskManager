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

    /**
     * @brief Constructor
     */
    EvenCounter();

    /**
     * @brief Destructor
     */
    virtual ~EvenCounter(void) {}

    /**
     * @brief Implemented in order to execute the counting task in parallel.
     */
    void operator()();

    /**
     * @brief Counts even numbers
     */
    void count();

private:

    long long m_current_number;
};


#endif /* TIMECONSUMINGTASKV1_HPP_INCLUDED */
