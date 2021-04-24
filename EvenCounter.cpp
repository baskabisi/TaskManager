/*
 * TimeConsumingTaskV1.cpp
 *
 *  Created on: Apr 23, 2021
 *      Author: sukran
 */

#include "EvenCounter.hpp"

#include <iostream>
using namespace std;

EvenCounter::EvenCounter()
: m_current_number(0)
{
}

void
EvenCounter::operator()()
{
    count();
}

void
EvenCounter::count()
{
    //cout <<  endl << "Even counter started counting..." <<  endl;
    while (1)
    {
        //cout << "Even counter is counting: " << m_current_number << endl;
        m_current_number += 2;
    }
}
