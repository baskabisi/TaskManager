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
: m_count(1)
{
}

void
OddCounter::count()
{
    cout << "Starting to count odd numbers..." <<  endl;
    while (1)
    {
        cout << "Counting odd numbers: " << m_count << endl;
        m_count += 2;
    }
}


