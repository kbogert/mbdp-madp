/**\file TimedAlgorithm.cpp
 *
 * Authors:
 * Frans Oliehoek <faolieho@science.uva.nl>
 * Matthijs Spaan <mtjspaan@isr.ist.utl.pt>
 *
 * Copyright 2008 Universiteit van Amsterdam, Instituto Superior Tecnico
 *
 * This file is part of MultiAgentDecisionProcess.
 *
 * MultiAgentDecisionProcess is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * MultiAgentDecisionProcess is distributed in the hope that it will
 * be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MultiAgentDecisionProcess.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * $Id: TimedAlgorithm.cpp 4016 2010-03-11 16:56:02Z mtjspaan $
 */

#include "TimedAlgorithm.h"
#include <fstream>

using namespace std;

//Default constructor
TimedAlgorithm::TimedAlgorithm()
{
    _m_timer=new Timing();
}
//Destructor
TimedAlgorithm::~TimedAlgorithm()
{
    delete _m_timer;
}

void TimedAlgorithm::StartTimer(const string & id) const
{
    _m_timer->Start(id);
}

void TimedAlgorithm::StopTimer(const string & id) const
{
    _m_timer->Stop(id);
}

void TimedAlgorithm::PrintTimers() const
{
    _m_timer->Print();
}

void TimedAlgorithm::SaveTimers(const string & filename) const
{
    _m_timer->Save(filename);
}

void TimedAlgorithm::SaveTimers(ofstream &of) const
{
    _m_timer->Save(of);
}

void TimedAlgorithm::LoadTimers(const string & filename)
{
    _m_timer->Load(filename);
}

void TimedAlgorithm::PrintTimersSummary() const
{ 
    _m_timer->PrintSummary();
}

void TimedAlgorithm::AddTimedEvent(const string & id, clock_t duration)
{
    _m_timer->AddEvent(id,duration);
}

vector<double> TimedAlgorithm::GetTimedEventDurations(const string & id)
{
    return(_m_timer->GetEventDurations(id));
}
