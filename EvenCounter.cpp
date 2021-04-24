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
: m_count(0)
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
    cout << "Starting to count even numbers..." <<  endl;
    while (1)
    {
        //cout << "Counting even numbers: " << m_count << endl;
        m_count += 2;
    }
}
