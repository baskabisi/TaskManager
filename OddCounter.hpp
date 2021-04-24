/*
 * OddCounter.hpp
 *
 *  Created on: Apr 23, 2021
 *      Author: sukran
 */


#ifndef ODDCOUNTER_HPP_INCLUDED
#define ODDCOUNTER_HPP_INCLUDED

#include "AnyCounter.hpp"

class OddCounter: public AnyCounter
{
public:

    /**
     * @brief Constructor
     */
    OddCounter();

    /**
     * @brief Destructor
     */
    virtual ~OddCounter(void) {}

    /**
     * @brief Implemented in order to execute the counting task in parallel.
     */
    void operator()();

    /**
     * @brief Counts odd numbers
     */
    void count();

private:

    long long m_current_number;
};


#endif /* ODDCOUNTER_HPP_INCLUDED */


