/**\file GeneralizedMAAStarPlannerForDecPOMDPDiscrete.cpp
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
 * $Id: GeneralizedMAAStarPlannerForDecPOMDPDiscrete.cpp 3604 2009-08-25 10:52:24Z mtjspaan $
 */

#include <float.h>
#include <limits.h>
#include "GeneralizedMAAStarPlannerForDecPOMDPDiscrete.h"

#include "QFunctionJAOHInterface.h"

#include "PartialJointPolicyPureVector.h"
#include "PartialJPDPValuePair.h"
#include "PolicyPoolPartialJPolValPair.h"

//#include "JointObservationHistoryTree.h"
//#include "JointBeliefInterface.h"
//#include "JointActionObservationHistoryTree.h"
//#include "BeliefIteratorGeneric.h"


using namespace std;

//Default constructor
GeneralizedMAAStarPlannerForDecPOMDPDiscrete::GeneralizedMAAStarPlannerForDecPOMDPDiscrete(
        const PlanningUnitMADPDiscreteParameters &params,
        size_t horizon, 
        DecPOMDPDiscreteInterface* p
        , int verboseness) 
:
    PlanningUnitDecPOMDPDiscrete(params, horizon, p)
    ,GeneralizedMAAStarPlanner(verboseness)
{
    _m_qHeuristic=0;
    _m_useSparseBeliefs=GetParams().GetUseSparseJointBeliefs();
}

GeneralizedMAAStarPlannerForDecPOMDPDiscrete::
GeneralizedMAAStarPlannerForDecPOMDPDiscrete(
    size_t horizon, 
    DecPOMDPDiscreteInterface* p) 
:
    PlanningUnitDecPOMDPDiscrete(horizon, p)
{
    _m_qHeuristic=0;
    _m_useSparseBeliefs=GetParams().GetUseSparseJointBeliefs();
}

/*
//Destructor
GeneralizedMAAStarPlannerForDecPOMDPDiscrete::
~GeneralizedMAAStarPlannerForDecPOMDPDiscrete()
{
}
*/
//Copy assignment operator
GeneralizedMAAStarPlannerForDecPOMDPDiscrete& GeneralizedMAAStarPlannerForDecPOMDPDiscrete::operator= (const GeneralizedMAAStarPlannerForDecPOMDPDiscrete& o)
{
    if (this == &o) return *this;   // Gracefully handle self assignment
    // Put the normal assignment duties here...
    throw("GeneralizedMAAStarPlannerForDecPOMDPDiscrete::operator= not implemented");

    return *this;
}

//this function extends a previous policy jpolPrevTs for ts-1 with the behavior specified by the policy of the BayesianGame for time step ts (jpolBG).
PartialJointPolicyDiscretePure* GeneralizedMAAStarPlannerForDecPOMDPDiscrete::ConstructExtendedJointPolicy(
        const PartialJointPolicyDiscretePure& jpolPrevTs, 
        const JointPolicyDiscretePure& jpolBG,
        const vector<size_t>& nrOHts, 
        const vector<Index>& firstOHtsI)
{
    //check policy types
    if(jpolPrevTs.GetIndexDomainCategory() != PolicyGlobals::OHIST_INDEX)
        throw E("GeneralizedMAAStarPlannerForDecPOMDPDiscrete::ConstructExtendedJointPolicy --- jpolPrevTs.GetIndexDomainCategory() != PolicyGlobals::OHIST_INDEX ");
    if(jpolBG.GetIndexDomainCategory() != PolicyGlobals::TYPE_INDEX)
        throw E("GeneralizedMAAStarPlannerForDecPOMDPDiscrete::ConstructExtendedJointPolicy --- jpolPrevTs.GetIndexDomainCategory() != PolicyGlobals::TYPE_INDEX ");
    //construct a policy for the DecPOMDP: 
    //a copy of jpolPrevTs with extended to this time step (ts) by 
    //jpolBG
    PartialJointPolicyDiscretePure* jpolTs = new 
        PartialJointPolicyPureVector(jpolPrevTs);
    jpolTs->SetDepth( jpolTs->GetDepth()+1 );
    for(Index agentI=0; agentI < GetNrAgents(); agentI++)
    {
        for(Index type = 0; type < nrOHts[agentI]; type++)
        {
            Index ohI = type + firstOHtsI[agentI];
            jpolTs->SetAction(agentI, ohI, 
                    jpolBG.GetActionIndex(agentI, type) );
        }         
    }
    return(jpolTs);
}


PartialJointPolicyDiscretePure* GeneralizedMAAStarPlannerForDecPOMDPDiscrete::
NewJPol() const
{ return new PartialJointPolicyPureVector(*this, OHIST_INDEX, 0.0); }

PartialPolicyPoolItemInterface*
GeneralizedMAAStarPlannerForDecPOMDPDiscrete::
NewPPI(PartialJointPolicyDiscretePure* jp, double v) const
{
    ///we know that jp is a PartialJointPolicyPureVector (see NewJPol above)
    //this can be used to have a more compact representation by doing:
    //  PartialJointPolicyPureVector* p = 
    //      static_cast<PartialJointPolicyPureVector*>(jp);
    //  ppi = new PartialJPPVIndexValPair(jp,v);

    PartialPolicyPoolItemInterface* ppi = new PartialJPDPValuePair(jp,v);
    //delete jp;
    return (ppi);
}

PartialPolicyPoolInterface*
GeneralizedMAAStarPlannerForDecPOMDPDiscrete::
NewPP() const
{
    return (new PolicyPoolPartialJPolValPair);
}
