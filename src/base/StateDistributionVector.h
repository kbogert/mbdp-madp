/**\file StateDistributionVector.h
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
 * $Id: StateDistributionVector.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _STATEDISTRIBUTIONVECTOR_H_
#define _STATEDISTRIBUTIONVECTOR_H_ 1

/* the include directives */
#include "Globals.h"
#include "StateDistribution.h"


namespace {
    typedef std::vector<double> SDV;
}

/** \brief StateDistributionVector represents a probability
 * distribution over states as a vector of doubles. */
class StateDistributionVector : 
    public StateDistribution,
    public SDV
{
    private:    
    
    protected:
    
    public:
        // Constructor, destructor and copy assignment.
        /// (default) Constructor
        StateDistributionVector()
            :
                SDV()
        {};         

        /// Copy constructor.
        StateDistributionVector(const StateDistributionVector& a)
            :
                SDV(a)
        {};
        StateDistributionVector(const SDV& a)
            :
                SDV(a)
        {};
        /// Destructor.
        ~StateDistributionVector(){};
        /// Copy assignment operator
        StateDistributionVector& operator= (const StateDistributionVector& o)
        {
            if (this == &o) return *this;   // Gracefully handle self assignment
            this->SDV::operator=(o);
            return *this;
        }
        StateDistributionVector& operator= (const SDV& o)
        {
            if (this == &o) return *this;   // Gracefully handle self assignment
            this->SDV::operator=(o);
            return *this;
        }

        //operators:

        //data manipulation (set) functions:
        
        //get (data) functions:
        virtual double GetProbability( Index sI) const
        { return this->at(sI); }

        virtual std::vector<double> ToVectorOfDoubles() const
        { return *this; }
        
        /// Returns a pointer to a copy of this class.
        virtual StateDistributionVector* Clone() const
        { return new StateDistributionVector(*this); }

        virtual std::string SoftPrint() const
        { return SoftPrintVector( *((SDV*)this) ); }
};


#endif /* !_STATEDISTRIBUTIONVECTOR_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
