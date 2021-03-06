/*
 * EvenCounter.cpp
 *
 *  Created on: Apr 23, 2021
 *      Author: sukran
 */

#include "EvenCounter.hpp"

#include <thread>
#include <iostream>
using namespace std;

EvenCounter::EvenCounter(unsigned int id)
: m_current_number(0),
  m_id(id),
  m_type(count_even)
{
}

void
EvenCounter::operator()()
{
    count();
}

TaskType
EvenCounter::getTaskType() const
{
    return m_type;
}

void
EvenCounter::count()
{
    cout << endl << "    Job #" << m_id << "| Even counter is counting: " << m_current_number << endl;
    m_current_number += 2;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}
