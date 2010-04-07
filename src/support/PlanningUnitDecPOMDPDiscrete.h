/**\file PlanningUnitDecPOMDPDiscrete.h
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
 * $Id: PlanningUnitDecPOMDPDiscrete.h 3604 2009-08-25 10:52:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _PLANNINGUNITDECPOMDPDISCRETE_H_
#define _PLANNINGUNITDECPOMDPDISCRETE_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "Referrer.h"
#include "PlanningUnitMADPDiscrete.h"
#include "DecPOMDPDiscreteInterface.h"

class JointPolicyPureVector;

/** \brief PlanningUnitDecPOMDPDiscrete represents a planning unit for
 * discrete Dec-POMDPs. */
class PlanningUnitDecPOMDPDiscrete : 
    public Referrer<DecPOMDPDiscreteInterface>,
    public PlanningUnitMADPDiscrete 
{
    private:    

    protected:
    
       /// Runs some consistency tests.
       bool SanityCheck() const;
    
    public:
        // Constructor, destructor and copy assignment.
        ///the (default) Constructor. 
        PlanningUnitDecPOMDPDiscrete(
                const PlanningUnitMADPDiscreteParameters &params,
                size_t horizon=3,
                DecPOMDPDiscreteInterface* p=0
            );
        PlanningUnitDecPOMDPDiscrete(
                size_t horizon=3,
                DecPOMDPDiscreteInterface* p=0
            );

        //operators:

        //data manipulation (set) functions:

        /// Tell which SetReferred to use by default.
        void SetReferred(DecPOMDPDiscreteInterface* p) 
        {Referrer<DecPOMDPDiscreteInterface>::SetReferred(p);}
        ///Set the problem (DecPOMDPDiscreteInterface) using a pointer.
        void SetProblem(DecPOMDPDiscreteInterface* p);

        //get (data) functions:

        /// Returns the DecPOMDPDiscreteInterface pointer.
        /** Tell which GetReferred to use by default... (nl. the
         * Referrer<DecPOMDPDiscreteInterface>::GetReferred(), not the
         * PlanningUnitMADPDiscrete::GetReferred(). */
        DecPOMDPDiscreteInterface* GetReferred() const
        {return(Referrer<DecPOMDPDiscreteInterface>::GetReferred() );}

        /// Return the reward for state, joint action indices 
        double GetReward(Index sI, Index jaI) const
            { return(GetReferred()->GetReward(sI, jaI)); }
        
        ///Returns the discount parameter.
        double GetDiscount() const 
            {return GetReferred()->GetDiscount();}

        /// Returns the expected reward of the best found joint policy.
        virtual double GetExpectedReward() const = 0;
        /// Returns the expected reward of the best found joint policy.
        virtual JointPolicyPureVector* GetJointPolicyPureVector(void)
        {throw E("PlanningUnitDecPOMDPDiscrete::GetJointPolicyPureVector - Error this function should be overriden by the derived PU!");}

};


#endif /* !_PLANNINGUNITDECPOMDPDISCRETE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
