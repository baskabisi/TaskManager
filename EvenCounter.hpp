/*
 * EvenCounter.hpp
 *
 *  Created on: Apr 23, 2021
 *      Author: sukran
 */

#ifndef EVENCOUNTER_HPP_INCLUDED
#define EVENCOUNTER_HPP_INCLUDED

#include "AnyCounter.hpp"

class EvenCounter: public AnyCounter
{
public:

    /**
     * @brief Constructor
     */
    EvenCounter(unsigned int id);

    /**
     * @brief Destructor
     */
    virtual ~EvenCounter(void) {}

    /**
     * @brief Implemented in order to execute the counting task in parallel.
     */
    void operator()();

    /**
     * @brief Returns task type
     */
    TaskType getTaskType() const;

    /**
     * @brief Counts even numbers
     */
    void count();

private:

    TaskType m_type;
    long long m_current_number;
    unsigned int m_id;
};

#endif /* EVENCOUNTER_HPP_INCLUDED */
