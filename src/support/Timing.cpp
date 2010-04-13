/**\file Timing.cpp
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
 * $Id: Timing.cpp 4016 2010-03-11 16:56:02Z mtjspaan $
 */

#include "Timing.h"
#include <fstream>
#include <sys/times.h>
#include <limits.h>

using namespace std;

//Default constructor
Timing::Timing()
{
    _m_timeAtInitialization=GetCpuTime();
}

//Destructor
Timing::~Timing()
{
}

void Timing::Start(const string & id)
{
    Times newTimer;
    newTimer.start=GetCpuTime();
    newTimer.end=0;
    newTimer.hasEnded=false;
    _m_timesMap[id].push_back(newTimer);
}

void Timing::Stop(const string & id, clock_t endTime)
{
    map <string, vector<Times> >::iterator it=_m_timesMap.find(id);
    if(it==_m_timesMap.end())
    {
        stringstream ss;
        ss << "Timing::Stop Could not stop timing event called \""
           << id << "\", no such event ever started";
        throw(E(ss.str()));
    }
    else
    {
        it->second.size();
        it->second.back().end=endTime;
        it->second.back().hasEnded=true;
    }
}

void Timing::Stop(const string & id)
{
    Stop(id,GetCpuTime());
}

void Timing::Print() const
{
    map<string, vector<Times> >::const_iterator i;
    for(i=_m_timesMap.begin(); i!=_m_timesMap.end(); ++i)
    {
        const vector<Times> &times=i->second;
        const string &id=i->first;
        for(vector<Times>::const_iterator j=times.begin();
            j!=times.end();++j)
        {
            cout << id << ": ";
            if(j->hasEnded)
            {
                cout << j->end - j->start
                     << "   start "
                     << j->start << " end "
                     << j->end << endl;
            }
            else
                cout << "still running, started at " << j->start
                     << endl;
        }
    }
}

void Timing::PrintSummary() const
{
    map<string, vector<Times> >::const_iterator i;
    for(i=_m_timesMap.begin(); i!=_m_timesMap.end(); ++i)
    {
        const vector<Times> &times=i->second;
        const string &id=i->first;
        clock_t total=0,maxTime=0,minTime=INT_MAX,current;
        int nrSamples=0;
        for(vector<Times>::const_iterator j=times.begin();
            j!=times.end();++j)
        {
            if(j->hasEnded)
            {
                current=j->end - j->start;
                total+=current;
                if(current>maxTime)
                    maxTime=current;
                if(current<minTime)
                    minTime=current;

                nrSamples++;
            }
        }

        cout << id << ": ";
        if(nrSamples>0)            
            cout << ClockToSeconds(total)
                 << " s in " << nrSamples << " measurements"
                 << ", max " << ClockToSeconds(maxTime)
                 << ", min " << ClockToSeconds(minTime)
                 << endl;
        else if((times.size()-nrSamples)>0)     // this will only
                                                // print the correct
                                                // "still running"
                                                // time if called from
                                                // the same process
            cout << (times.size()-nrSamples) << " still running, spent "
                 << (ClockToSeconds(GetCpuTime()) - 
                     ClockToSeconds(i->second[0].start)) << endl;
    }
}

void Timing::Save(const string & filename) const
{
    ofstream fp(filename.c_str());
    if(!fp)
    {
        stringstream ss;
        ss << "Timing::Save: failed to open file " << filename;
        throw(E(ss.str()));
    }

    Save(fp);
}

void Timing::Save(ofstream &of) const
{
    of << _m_timeAtInitialization << endl;

    map<string, vector<Times> >::const_iterator i;
    for(i=_m_timesMap.begin(); i!=_m_timesMap.end(); ++i)
    {
        const vector<Times> &times=i->second;
        const string &id=i->first;

        for(vector<Times>::const_iterator j=times.begin();
            j!=times.end();++j)
        {
            if(j->hasEnded)
                of << id << " " << j->start << " " << j->end << endl;
        }
    }
}

void Timing::Load(const string & filename)
{
    const int bufsize=65536;
    char buffer[bufsize];
    bool first=true;

    ifstream fp(filename.c_str());
    if(!fp)
        cerr << "Timing::Load: failed to open file " << filename << endl;

    _m_timesMap.clear();

    while(!fp.getline(buffer,bufsize).eof())
    {
        {
            string identification;
            clock_t start,end;
            Times times;

            istringstream is(buffer);
            if(first)
            {
                first=false;
                is >> start;
                _m_timeAtInitialization=start;
            }
            else
            {
                is >> identification;
                is >> start;
                is >> end;
                times.start=start;
                times.end=end;
                _m_timesMap[identification].push_back(times);
            }
        }
    }
}

clock_t Timing::GetCpuTime() const
{
    struct tms timeStruct;
    times(&timeStruct);
    return(timeStruct.tms_utime + timeStruct.tms_stime);
}

double Timing::ClockToSeconds(clock_t clockTicks) const
{
    return(static_cast<double>(clockTicks) / CLOCKS_PER_SEC);
}

void Timing::AddEvent(const string & id, clock_t duration)
{
    Start(id);
    Stop(id,GetCpuTime()+duration);
}

vector<double> Timing::GetEventDurations(const string & id)
{
    vector<double> durations;

    map <string, vector<Times> >::iterator it=_m_timesMap.find(id);
    if(it==_m_timesMap.end())
    {
        stringstream ss;
        ss << "Timing::GetEventDurations No events called \""
           << id << "\" have been stored";
        throw(E(ss.str()));
    }
    else
    {
        const vector<Times> &times=it->second;
        for(vector<Times>::const_iterator j=times.begin();
            j!=times.end();++j)
        {
            if(j->hasEnded)
                durations.push_back(ClockToSeconds(j->end - j->start));
        }
    }
    return(durations);
}
