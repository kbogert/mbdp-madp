/**\file JointActionObservationHistory.h
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
 * $Id: JointActionObservationHistory.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _JOINTACTIONOBSERVATIONHISTORY_H_
#define _JOINTACTIONOBSERVATIONHISTORY_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "Referrer.h"
#include "JointHistory.h"

//forward declation:
class PlanningUnitMADPDiscrete;

/// JointActionObservationHistory represents a joint action observation history.
class JointActionObservationHistory  : public Referrer<PlanningUnitMADPDiscrete>,
    public JointHistory
{
    private:    
        
        ///The last joint action (index).
        Index _m_jaI;
        ///The last joint observation (index).
        Index _m_joI;

        /**The predecessor together with the last joint actionObservation
         * (_m_actionObservationI) this gives a full description of 
         * this joint actionObservation history.*/   
        JointActionObservationHistory* _m_pred;
        
        /**A vector of Indices which are the indices of individual 
         * ActionObservationHistories this gives an alternate description of the
         * current JointActionObservation History. */
        std::vector<Index> _m_individualActionObservationHistories;

        void GetJointActionObservationHistoryVectorsRecursive(
            std::vector<Index> &jaIs, std::vector<Index> &joIs);

    protected:
    
    public:
        // Constructor, destructor and copy assignment.
        /** \brief (default) Constructor - creates a new initial
         * (=empty) JointActionObservationHistory. */
        JointActionObservationHistory(PlanningUnitMADPDiscrete& pu);
        /** \brief Creates the joint action-obs. history resulting
         * from joint action jaI and obs. joI after
         * JointActionObservationHistory pred.*/
        JointActionObservationHistory(Index jaI, Index joI, 
                JointActionObservationHistory* pred);

        //operators:

        //data manipulation (set) functions:


        //get (data) functions:      
        ///Returns the indices of the indiv. action observation histories.
        const std::vector<Index>& GetIndividualActionObservationHistoryIndices()
            const
        {return _m_individualActionObservationHistories;}
        
        //other
        ///SoftPrints the history.
        std::string SoftPrint() const;
        ///SoftPrints the history in terms of joint action/observation indices.
        std::string SoftPrintJointIndices() const;
        ///Prints the history.
        void Print() const {std::cout << SoftPrint(); }
       
        /** \brief Get vectors of joint action and observation indices
         * stored by this history. */
        void GetJointActionObservationHistoryVectors(
            std::vector<Index> &jaIs, std::vector<Index> &joIs);

        ///Gets the last joint action index. 
        Index GetJointActionIndex() const
            {return _m_jaI;}
        ///Gets the last joint observation index.
        Index GetJointObservationIndex() const
            {return _m_joI;}

        /// Returns a pointer to a copy of this class.
        virtual JointActionObservationHistory* Clone() const
        { return new JointActionObservationHistory(*this); }


};


#endif /* !_JOINTACTIONOBSERVATIONHISTORY_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
