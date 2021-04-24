/*
 * OddCounter.cpp
 *
 *  Created on: Apr 23, 2021
 *      Author: sukran
 */

#include "OddCounter.hpp"

#include <iostream>
using namespace std;

OddCounter::OddCounter()
: m_current_number(1)
{
}

void
OddCounter::operator()()
{
    count();
}

void
OddCounter::count()
{
    //cout <<  endl << "Odd counter started counting..." <<  endl;
    while (1)
    {
        //cout << "Odd counter is counting: " << m_current_number << endl;
        m_current_number += 2;
    }
}
