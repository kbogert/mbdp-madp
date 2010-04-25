/**\file Referrer.h
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
 * $Id: Referrer.h 2116 2008-01-16 23:11:49Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _REFERRER_H_
#define _REFERRER_H_ 1

/* the include directives */
#include <iostream>



/// Referrer is a template class that represents objects that refer another.
/** I.e. it containt a pointer to type T  */
template <class T>
class Referrer 
{
    private:
        T* _m_referred;
    
    protected:
    
    public:
        // Constructor, destructor and copy assignment.
        //    Referrer() {_m_referred = 0;}
        /// (default) Constructor
        Referrer(T* t_p = 0) : _m_referred(t_p){};
        ///Alternative constructor.
        Referrer(T& t) : _m_referred(&t) {};
        /// Copy constructor.
        Referrer(const Referrer& a) : _m_referred(a._m_referred){};
        /// Destructor.
        virtual ~Referrer(){};

        //operators:

        //data manipulation (set) functions:
        ///Change the referred thing...
        void SetReferred(T* t_p)  { _m_referred = t_p; }

        
        //get (data) functions:
        ///Return the referred thing...
        T* GetReferred() const { return(_m_referred); }
};


#endif /* !_REFERRER_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
