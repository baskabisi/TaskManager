/*
 * OddCounter.cpp
 *
 *  Created on: Apr 23, 2021
 *      Author: sukran
 */

#include "OddCounter.hpp"

#include <iostream>
using namespace std;

OddCounter::OddCounter(unsigned int id)
: m_current_number(1),
  m_id(id),
  m_type(count_odd)
{
}

void
OddCounter::operator()()
{
    count();
}

TaskType
OddCounter::getTaskType()
{
    return m_type;
}

void
OddCounter::count()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));

    cout << endl << "    Job #" << m_id << "| Odd counter is counting: " << m_current_number << endl;
    m_current_number += 2;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
