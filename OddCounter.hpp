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

    OddCounter();

    virtual ~OddCounter(void) {}

    void count();

private:

    unsigned int m_count;

};


#endif /* ODDCOUNTER_HPP_INCLUDED */


