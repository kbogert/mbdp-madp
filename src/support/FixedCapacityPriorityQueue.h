/**\file FixedCapacityPriorityQueue.h
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
 * $Id: FixedCapacityPriorityQueue.h 2962 2008-11-02 15:04:43Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _FIXEDCAPACITYPRIORITYQUEUE_H_
#define _FIXEDCAPACITYPRIORITYQUEUE_H_ 1

/* the include directives */
#include "Globals.h"
#include <list>

/** \brief FixedCapacityPriorityQueue is a class that represents 
 * a priority queue with a fixed size.
 *
 * -all overflowed items are returned, such that the user can delete them
 *
 * TODO: fill out...  */
template <class T>
class FixedCapacityPriorityQueue 
{
    private:    
        std::list <T> _m_l;
        size_t _m_capacity;
    
    protected:
    
    public:

        // Constructor, destructor and copy assignment.
        // 
        /// (default) Constructor
        FixedCapacityPriorityQueue(size_t capacity)
            : _m_capacity(capacity)
        {};
/* let's trust the compiler to deal with this correctly...?        
        /// Copy constructor.
        FixedCapacityPriorityQueue(const FixedCapacityPriorityQueue& a);
        /// Destructor.
        ~FixedCapacityPriorityQueue();
        /// Copy assignment operator
        FixedCapacityPriorityQueue& operator= (const FixedCapacityPriorityQueue& o);
*/
        //operators:

        //data manipulation (set) functions:
        /**\brief inserts a in the priority q. 
         *
         * returns true if the capacity overflows
         * in this case, overflown_T is set to the overflown value
         * (which can then be recovered or deleted by the user).
         */
        bool insert( T& a, T& overflown_T );
        
        //get (data) functions:
        bool empty() const   {return _m_l.empty();}
        T& top() { return _m_l.front(); } //highest priority (value) at the front
        void pop() { _m_l.pop_front(); }

        T& back() {return _m_l.back(); }

        size_t size() const {return _m_l.size();}
};

#define DEBUG_FCPQ 0
template <class T>
bool FixedCapacityPriorityQueue<T>::insert( T& a, T& overflown_T )
{
    bool overflow = ( _m_l.size() == _m_capacity);
    bool skip_insert = false;

    if(overflow) //check if we need to make space at the end
    {
        // overflown_Tp is the T* to which overflown_Tpp points
        // we set the former to point to the overflown element.
        //T* & overflown_Tp = *overflown_Tpp;

        T& last_in_queue = _m_l.back();
        std::less< T > theLessOp;
        if( theLessOp( last_in_queue,  a) )
        //if( last_in_queue <  a ) //doesn't work automatically...
        {
            //This does not work with (or need) pointers, 
            //this simply points to last position in queue !!!
            //overflown_Tp = &last_in_queue;             
            
            //rather copy the value of the stuff we will throw out!
            overflown_T = last_in_queue; 
            _m_l.pop_back();
        }
        else
        {
            overflown_T = a;
            skip_insert = true;
        }
    }

    if(!skip_insert)
    {
        //insert a at the appropriate place
        typename std::list<T>::iterator it = _m_l.begin();
        typename std::list<T>::iterator last = _m_l.end();
        bool not_positioned = true; //so long as it does not point to the correct pos.
        while(it != last && not_positioned)
        {
            if( a > *it)
                not_positioned = false;
            else
                it++;
        }
        _m_l.insert( it, a);
    }
#if 0 && DEBUG_FCPQ
    std::cout << "----AFTER POP AND INSERT\nthe overflown_Tp=" <<overflown_Tp << ", which means it points to..." <<std::endl ;
    if(overflown_Tp != NULL)
    {
        T& the_overflown_T = (*overflown_Tp);
        std::string typestr = " JPPVValPair* ";
        std::cout << "the_overflown_T [T="<< typestr <<
            "]=" << the_overflown_T << ", which points to..."<<std::endl;

        if(the_overflown_T != NULL)
            std::cout<< (*the_overflown_T).SoftPrintBrief() << std::endl;
        else
            std::cout << "nothing" <<std::endl;
    }
    else
        std::cout << " nothing." << std::endl;
    
    std::cout << "----" <<std::endl ;
#endif
    
    return(overflow);
}

#endif /* !_FIXEDCAPACITYPRIORITYQUEUE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
