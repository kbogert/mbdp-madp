/**\file PartialJointPolicy.h
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
 * $Id: PartialJointPolicy.h 3603 2009-08-25 10:38:25Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _PARTIALJOINTPOLICY_H_
#define _PARTIALJOINTPOLICY_H_ 1

/* the include directives */
#include "Globals.h"

/** \brief PartialJointPolicy represents a joint policy that is only
 * specified for t time steps instead of for every time step.
 *
 * I.e., it is specified for time steps 0 until t, instead of 0 until
 * horizon.
 */
class PartialJointPolicy 
{
    private:    
        ///Stores the past reward the partial policy achieves 
        double _m_pastReward;
    
    protected:
    
    public:
        // Constructor, destructor and copy assignment.
        /// (default) Constructor
        PartialJointPolicy(double r = 0.0)
            : _m_pastReward(r)
        {};

        /// Copy constructor.
        PartialJointPolicy(const PartialJointPolicy& a)
            : _m_pastReward(a._m_pastReward)
        {};
        /// Destructor.
        //~PartialJointPolicy();
        /// Copy assignment operator
        PartialJointPolicy& operator= (const PartialJointPolicy& o);

        //operators:

        //data manipulation (set) functions:
        
        //get (data) functions:        
        double GetPastReward() const
        { return _m_pastReward;}
        void SetPastReward(double r) 
        { _m_pastReward = r; }


};


#endif /* !_PARTIALJOINTPOLICY_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
