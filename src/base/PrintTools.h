/**\file PrintTools.h
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
 * $Id: PrintTools.h 3853 2009-11-26 16:38:11Z mtjspaan $
 */

#ifndef _PRINTTOOLS_H_
#define _PRINTTOOLS_H_ 1

#include <vector>
#include <set>
#include <sstream>
#include <iomanip>

/// PrintTools contains functionality for printing vectors etc.
/** The SoftPrint*() functions returns strings, the Print*() print to
 * standard out. */
namespace PrintTools {

/**Prints a vector using cout - i.e. the data type can be written to cout using
 * << (operator<< must be defined for T).*/
template <class T>
static void PrintVectorCout(const T &v)
{
    std::cout << v;
}
    
template <class T>
static void PrintVectorCout(const std::vector<T> &v)
{
    std::cout << SoftPrintVector(v) << std::endl;
}

template <class T>
static std::string SoftPrintVector(const T &v)
{
    std::stringstream ss;
    ss << v;
    return(ss.str());
}
    
template <class T>
static std::string SoftPrintVector(const std::vector<T> &v)
{
    std::stringstream ss;
    typename std::vector<T>::const_iterator it =  v.begin();
    typename std::vector<T>::const_iterator last =  v.end();
    ss << "< ";
    while(it != last)
    {
        if(it != v.begin())
            ss << ", ";

        ss << SoftPrintVector(*it);        
        it++;
    }
    ss << " >";
    return(ss.str());
}

template <class T>
static void PrintCout(const T &v)
{
    std::cout << v;
}

template <class T>
static void PrintCout(const std::vector<T> &v)
{
    PrintVectorCout(v);
}

template <class T>
static void PrintCout(const std::set<T> &v)
{
    std::cout << SoftPrint(v);
}

template <class T>
static std::string SoftPrint(const T &v)
{
    std::stringstream ss;
    ss << v;
    return(ss.str());
}

template <class T>
static std::string SoftPrint(const std::vector<T> &v)
{
    return(SoftPrintVector(v));
}

template <class T>
static std::string SoftPrint(const std::set<T> &v)
{
    std::stringstream ss;
    typename std::set<T>::const_iterator it =  v.begin();
    typename std::set<T>::const_iterator last =  v.end();
    ss << "< ";
    while(it != last)
    {
        if(it != v.begin())
            ss << ", ";

        ss << SoftPrint(*it);
        it++;
    }
    ss << " >";
    return(ss.str());
}

template <class T>
static void PrintProgress(T prefix, LIndex i,
                   LIndex nr, size_t interval)
{
    if(i % interval == 0&& i > interval)
    {
        std::cout << prefix << " "<< i << " of " << nr << " - "
                  << std::setprecision(4)
                  << ((double) i / nr) * 100
                  << "%" << std::endl;
    }
}

}

#endif /* !_PRINTTOOLS_H_ */
