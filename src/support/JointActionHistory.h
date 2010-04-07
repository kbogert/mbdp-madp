/**\file JointActionHistory.h
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
 * $Id: JointActionHistory.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _JOINTACTIONHISTORY_H_
#define _JOINTACTIONHISTORY_H_ 1

/* the include directives */
#include <iostream>
#include <vector>

#include "Globals.h"
#include "Referrer.h"
#include "TreeNode.h"
#include "JointHistory.h"

//#include "PlanningUnitMADPDiscrete.h"
class PlanningUnitMADPDiscrete; //forward declaration to avoid including each other

/// JointActionHistory represents a joint action history.
/** 
 * This consists of a joint action history index, the last joint
 * action (index) a pointer to the predecessor JOH.  and a vector of
 * indexes to the individual action histories.  */
class JointActionHistory : public Referrer<PlanningUnitMADPDiscrete>,
    public JointHistory
{
    private:
        
        ///The last joint action (index).
        Index _m_jointActionI;
        /**True if the last joint action (index) is empty (i.e., there is 
         * no last joint action.)  This is true for a action history at 
         * time step 0.
         */
        bool _m_isEmpty;
        /**The predecessor joint belief. Together with the last joint 
         * action(_m_jointActionI) this gives a full description of 
         * this joint action history.*/    
        JointActionHistory* _m_pred;
        /**A vector of ints which are the indices of individual 
         * ActionHistories this gives an alternate description of the 
         * current JointAction History. */
        std::vector<Index> _m_individualActionHistories;

    
    protected:
    
    public:
        // Constructor, destructor and copy assignment.
        /**Constructor - creates a new initial (=empty) JointActionHistory.
         * This method relies on the fact that the empty individual
         * action histories are indexed 0. */
        JointActionHistory(PlanningUnitMADPDiscrete& pu);
        /**Creates a initial action history specifying obsI as the
          * action at time step t=0 (o^t=0) */
        JointActionHistory(PlanningUnitMADPDiscrete& pu, Index jObsI);
        /**Creates a action history specifying jObsI for the last joint
          * action and pred as the preceeding JointActionHistory.*/
        JointActionHistory(Index jObsI, JointActionHistory * pred);
        /// Copy constructor.
        JointActionHistory(const JointActionHistory& a);
        /// Destructor.
        ~JointActionHistory();

        //operators:

        //data manipulation (set) functions:
        
        //get (data) functions:
        ///Returns the indices of the indiv. action histories.
        const std::vector<Index>& GetIndividualActionHistoryIndices() const;
        //other
        /// Returns a pointer to a copy of this class.
        virtual JointActionHistory* Clone() const
        { return new JointActionHistory(*this); }

        ///SoftPrints the joint observation history.
        std::string SoftPrint() const;
        ///Prints the joint observation history.
        void Print() const { std::cout << SoftPrint(); }

};

#endif /* !_JOINTACTIONHISTORY_H_ */


// Local Variables: ***
// mode:c++ ***
// End: ***
