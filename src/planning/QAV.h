/**\file QAV.h
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
 * $Id: QAV.h 2957 2008-10-31 15:45:54Z faolieho $
 */

/* Only include this header file once. */
#ifndef _QAV_H_
#define _QAV_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"

#include "QFunctionJointBelief.h"
#include "BeliefSet.h"
#include "ValueFunctionPOMDPDiscrete.h"
#include "AlphaVectorPlanning.h"
#include "PlanningUnitDecPOMDPDiscrete.h"
#include "QAVParameters.h"

/** \brief QAV implements a QFunctionJointBelief using a planner based
 * on alpha functions, for instance the Perseus planners. */
template<class P>
class QAV : public QFunctionJointBelief
{
private:    

    P *_m_p;

    void Initialize(){};
    void DeInitialize(){};

protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    QAV(const PlanningUnitDecPOMDPDiscrete& pu) :
        QFunctionForDecPOMDP(pu), //virtual base first
        QFunctionJointBelief(pu)
        { _m_p=new P(pu); }
    
    QAV(const PlanningUnitDecPOMDPDiscrete& pu,
        const QAVParameters &params) :
        QFunctionForDecPOMDP(pu), //virtual base first
        QFunctionJointBelief(pu)
        { _m_p=new P(pu,params); }

    QAV(const PlanningUnitDecPOMDPDiscrete& pu, const BeliefSet &B) :
        QFunctionForDecPOMDP(pu), //virtual base first
        QFunctionJointBelief(pu)
        {
            _m_p=new P(pu);
            _m_p->SetBeliefSet(B);
        }

    QAV(const PlanningUnitDecPOMDPDiscrete& pu, const BeliefSet &B,
        const QAVParameters &params) :
        QFunctionForDecPOMDP(pu), //virtual base first
        QFunctionJointBelief(pu)
        {
            _m_p=new P(pu,params);
            _m_p->SetBeliefSet(B);
        }

    QAV(const PlanningUnitDecPOMDPDiscrete& pu,
        const std::string &ValueFunctionFile) :
        QFunctionForDecPOMDP(pu), //virtual base first
        QFunctionJointBelief(pu)
        {
            _m_p=new P(pu);
            _m_p->SetValueFunction(ValueFunctionFile);
        }

    QAV(const PlanningUnitDecPOMDPDiscrete& pu,
        const std::string &ValueFunctionFile,
        const QAVParameters &params) :
        QFunctionForDecPOMDP(pu), //virtual base first
        QFunctionJointBelief(pu)
        {
            _m_p=new P(pu,params);
            _m_p->SetValueFunction(ValueFunctionFile);
        }

    /// Destructor.
    ~QAV()
        {
            delete _m_p;
        }

    
    void Compute()
        {
            _m_p->Plan();
        }

    double GetQ(const JointBeliefInterface &b, Index jaI) const
        {
            return(_m_p->GetQ(b,jaI));
        }

    double GetQ(const JointBeliefInterface &b, Index jaI, int &betaMaxI) const
        {
            return(_m_p->GetQ(b,jaI,betaMaxI));
        }

    double GetQ(const JointBeliefInterface &b, Index t, Index jaI) const
        {
            return(_m_p->GetQ(b,t,jaI));
        }

    double GetQ(const JointBeliefInterface &b, Index t, Index jaI,
                int &betaMaxI) const
        {
            return(_m_p->GetQ(b,t,jaI,betaMaxI));
        }

    P* GetPlanner()
        { return(_m_p); }
};

#endif /* !_QAV_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
