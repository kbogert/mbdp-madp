/**\file ActionObservationHistory.cpp
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
 * $Id: ActionObservationHistory.cpp 2945 2008-10-25 11:14:45Z mtjspaan $
 */

#include "ActionObservationHistory.h"
#include "Action.h"
#include "Observation.h"
#include "PlanningUnitMADPDiscrete.h"
#include "ActionHistory.h"
#include "ObservationHistoryTree.h"

using namespace std;

#define DEBUG_AOH 0

//Default constructor
ActionObservationHistory::ActionObservationHistory(PlanningUnitMADPDiscrete& pu, Index agentI) :
    Referrer<PlanningUnitMADPDiscrete>(pu),
    IndividualHistory(agentI)
{    
    SetLength(0);
    _m_pred = 0;
    _m_ahI = 0; //HARDCODED
    _m_ohI = 0; //HARDCODED
}
ActionObservationHistory::ActionObservationHistory(Index aI, Index oI, 
                ActionObservationHistory* pred) :
    Referrer<PlanningUnitMADPDiscrete>(pred->GetReferred()),
    IndividualHistory(pred->_m_agentI)
{
    SetLength(pred->GetLength() + 1);
    _m_pred = pred;
    _m_ahI = 
        GetReferred()->GetActionHistoryTree(_m_agentI, pred->_m_ahI) //=aht
        ->GetSuccessor(aI) //=aht'
        ->GetIndex(); //=ahI'
    _m_ohI = 
        GetReferred()->GetObservationHistoryTree(_m_agentI, pred->_m_ohI) //=oht
        ->GetSuccessor(oI) //=oht'
        ->GetIndex(); //=ohI'
}

string ActionObservationHistory::SoftPrint() const
{
    stringstream ss;
    if(_m_pred != 0)
    {
        if(_m_length >= 1)
            ss << _m_pred->SoftPrint();
        else
        {
            ss << "ObservationHistory:Print() - Warning:_m_pred != "<<
            "null, but lenght < 1 !"<<endl;
            throw E(ss);
        }
    }

    ActionHistory* ah = GetReferred()->GetActionHistoryTree(
            _m_agentI, _m_ahI) //=aht
        ->GetContainedElement(); //=ah
    if (!ah->IsEmpty()) // don't print the empty observation
    {
        ss << ", ";
        Index aI = ah->GetLastActionIndex(); // aI
        ss << GetReferred()->GetAction(_m_agentI, aI)->SoftPrintBrief();
    }
    else
        ss << "EMPTY_AH";

    ss << ", ";

    ObservationHistory* oh = GetReferred()->GetObservationHistoryTree(
            _m_agentI, _m_ohI) //=oht
        ->GetContainedElement(); //=oh
    if (!oh->ContainsEmptyOI()) // don't print the empty observation
    {
        ss << ", ";
        Index oI = oh->GetLastObservationIndex(); // oI
        ss << GetReferred()->GetObservation(_m_agentI, oI)->SoftPrintBrief();
    }
    else
        ss << "Oempty";

    return(ss.str());
}
