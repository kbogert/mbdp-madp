/**\file ObservationHistory.h
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
 * $Id: ObservationHistory.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _OBSERVATIONHISTORY_H_
#define _OBSERVATIONHISTORY_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "Referrer.h"
#include "E.h"
#include "IndividualHistory.h"

class PlanningUnitMADPDiscrete; //forward declaration to avoid including each other



/// ObservationHistory represents an action history of a single agent.
/** 
 * It does so by storing an index and a pointer to a preceeding
 * observation history.
 */
class ObservationHistory  : public Referrer<PlanningUnitMADPDiscrete>,
    public IndividualHistory
{
    private:
        
        ///The last observation (index).
        Index _m_observationI;

        /**True if the last observation (index) is empty (i.e., there is 
         * no last observation.) This is particularly true for a 
         * observation history at time step t=0 in a MADP that does not issue 
         * an initial observation. (this behavior is defined in 
         * MADPComponentDiscreteObservations)*/
        bool _m_containsEmptyOI;
        /**The predecessor observation hist. Together with the last joint 
         * observation(_m_observationI) this gives a full description of 
         * this observation history.*/   
        ObservationHistory* _m_pred;
    protected:
    
    public:
        // Constructor, destructor and copy assignment.
        /**(default) Constructor - creates a new initial (=empty)
         * ObservationHistory for agent agentI*/
        ObservationHistory(PlanningUnitMADPDiscrete& pu, Index agentI);
        /**Creates a initial observation history specifying obsI as the
         * observation at time step t=0 (o^t=0) */
        ObservationHistory(PlanningUnitMADPDiscrete& pu, Index agentI, 
                Index obsI);
        /**Creates a observation history specifying obsI for the last 
         * observation and pred as the preceeding ObservationHistory.*/
        ObservationHistory(Index obsI, ObservationHistory* pred);
        /// Copy constructor.
        //ObservationHistory(const ObservationHistory& a);
        /// Destructor.
        ~ObservationHistory();

        //operators:

        //data manipulation (set) functions:
        
        //get (data) functions:
        /// Check whether this history contains an empty observation.
        bool ContainsEmptyOI() const
            {return _m_containsEmptyOI;}
        ///Return a reference to the Observation history that precedes this.
        const ObservationHistory* GetPredecessor() const
            {return _m_pred;}
        ///Returns the index of the last observation.
        Index GetLastObservationIndex() const
            { return _m_observationI; }

        //other
        /// Returns a pointer to a copy of this class.
        virtual ObservationHistory* Clone() const
        { return new ObservationHistory(*this); }

        /// Prints a description of *this* to a string.
        std::string SoftPrint() const; 
        ///Print *this* to cout.
        void Print() const
        { std::cout << SoftPrint();}
};


#endif /* !_OBSERVATIONHISTORY_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
