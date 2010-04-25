/**\file JointActionObservationHistory.cpp
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
 * $Id: JointActionObservationHistory.cpp 2945 2008-10-25 11:14:45Z mtjspaan $
 */

#include "JointActionObservationHistory.h"
#include "JointAction.h"
#include "JointObservation.h"
#include "PlanningUnitMADPDiscrete.h"
#include "JointActionObservationHistoryTree.h"
#include "ActionObservationHistoryTree.h"
#include "IndexTools.h"

using namespace std;

#define DEBUG_JAOH 0

//Default constructor
JointActionObservationHistory::JointActionObservationHistory(PlanningUnitMADPDiscrete& pu) :
     Referrer<PlanningUnitMADPDiscrete>(pu)
{    
    SetLength(0);
    _m_pred = 0;
    _m_jaI = 0; //HARDCODED
    _m_joI = 0; 
    Index individualInitialAOHIndex = 0;//HARDCODED 
    _m_individualActionObservationHistories = vector<Index>(
            GetReferred()->GetNrAgents(), individualInitialAOHIndex);

}
JointActionObservationHistory::JointActionObservationHistory(Index jaI, Index 
        joI, JointActionObservationHistory* pred) :
    Referrer<PlanningUnitMADPDiscrete>(pred->GetReferred())
{
    SetLength(pred->GetLength() + 1);
    _m_pred = pred;
    
    _m_jaI = jaI;
    _m_joI = joI; 

    //calculate the new individual ActionObservationHistory indices...
    vector<Index> iA = GetReferred()->JointToIndividualActionIndices(jaI);
    vector<Index> iO = GetReferred()->JointToIndividualObservationIndices(joI);
    vector<Index> pred_iAOH= pred->GetIndividualActionObservationHistoryIndices();
    for(Index agentI = 0; agentI < GetReferred()->GetNrAgents(); agentI++)
    {
        Index next_indivIndex = 
            GetReferred() //=PlanningUnitMADPDiscrete
            -> GetSuccessorAOHI(agentI, 
                    pred_iAOH[agentI], iA[agentI], iO[agentI] ) ;
        //Index next_indivIndex = 
            //GetReferred() //=PlanningUnitMADPDiscrete
            //->GetActionObservationHistoryTree(agentI, pred_iAOH[agentI])//=aoht
            //->GetSuccessor( iA[agentI], iO[agentI] ) //=aoht'
            //->GetIndex(); //=aohI'
        _m_individualActionObservationHistories.push_back(next_indivIndex);
    }
            
}

string JointActionObservationHistory::SoftPrint() const
{
    stringstream ss;
    if(_m_pred != 0)
    {
        if(_m_length >= 1)
        {
            ss << _m_pred->SoftPrint();
            ss << ", ";
        }
        else
        {
            ss << "JointActionObservationHistory:Print() -Warning:_m_pred != "
                << "null, but lenght <= 1 !"<<endl;
            throw E(ss);
        }
    }

    if (_m_length >= 1) 
    {
        ss << "< ";    
        ss << GetReferred()->GetJointAction(_m_jaI)->SoftPrintBrief();
        ss << ", ";    
        ss << GetReferred()->GetJointObservation(_m_joI)->SoftPrintBrief();
        ss << " >";    
    }
    else
        ss << "<EMPTY>";


    return(ss.str());

}

string JointActionObservationHistory::SoftPrintJointIndices() const
{
    stringstream ss;
    if(_m_pred != 0)
    {
        if(_m_length >= 1)
        {
            ss << _m_pred->SoftPrintJointIndices();
            ss << ", ";
        }
        else
        {
            ss << "JointActionObservationHistory:Print() -Warning:_m_pred != "
                << "null, but lenght <= 1 !"<<endl;
            throw E(ss);
        }
    }

    if (_m_length >= 1) 
    {
        ss << "jaoI=" <<
            IndexTools::ActionAndObservation_to_ActionObservationIndex(
            _m_jaI, _m_joI, 
            GetReferred()->GetNrJointActions(), 
            GetReferred()->GetNrJointObservations() );
        ss << "(jaI=";    
        ss << _m_jaI;
        ss << ",joI=";    
        ss << _m_joI;
        ss << ")";    
    }
    else
        ss << "<>";


    return(ss.str());

}

void 
JointActionObservationHistory::GetJointActionObservationHistoryVectors(
//    JointActionObservationHistory *joah,
    vector<Index> &jaIs, vector<Index> &joIs)
{
    vector<Index> jaIsReversed;
    vector<Index> joIsReversed;

    GetJointActionObservationHistoryVectorsRecursive( jaIsReversed,
            joIsReversed);

    // reverse both vectors
    for(vector<Index>::reverse_iterator it=jaIsReversed.rbegin();
        it!=jaIsReversed.rend(); ++it)
        jaIs.push_back(*it);

    for(vector<Index>::reverse_iterator it=joIsReversed.rbegin();
        it!=joIsReversed.rend(); ++it)
        joIs.push_back(*it);

#if DEBUG_JAOH
    cout << SoftPrint() << " " << SoftPrintVector(jaIsReversed) << " "
         << SoftPrintVector(joIsReversed) << endl;
#endif
}

void 
JointActionObservationHistory::GetJointActionObservationHistoryVectorsRecursive(
    vector<Index> &jaIs, vector<Index> &joIs)
{
    if(_m_length >= 1) // for t=0, length=0 (and we don't want to include the
        //_m_jaI, _m_joI for that stage (they are def'd to be 0) )
    {
        jaIs.push_back(_m_jaI);
        joIs.push_back(_m_joI);
    }
    if(_m_pred!=NULL)
        _m_pred->GetJointActionObservationHistoryVectorsRecursive(jaIs,joIs);
}

/* old - this seems strange...
void 
JointActionObservationHistory::GetJointActionObservationHistoryVectors(
    JointActionObservationHistory *joah,
    vector<Index> &jaIs, vector<Index> &joIs)
{
    vector<Index> jaIsReversed;
    vector<Index> joIsReversed;

    GetJointActionObservationHistoryVectorsRecursive(joah,
                                                     jaIsReversed,
                                                     joIsReversed);

    // reverse both vectors
    for(vector<Index>::reverse_iterator it=jaIsReversed.rbegin();
        it!=jaIsReversed.rend(); ++it)
        jaIs.push_back(*it);

    for(vector<Index>::reverse_iterator it=joIsReversed.rbegin();
        it!=joIsReversed.rend(); ++it)
        joIs.push_back(*it);

}

void 
JointActionObservationHistory::GetJointActionObservationHistoryVectorsRecursive(
    JointActionObservationHistory *joah,
    vector<Index> &jaIs, vector<Index> &joIs)
{
    if(joah->_m_length > 1)
    {
        jaIs.push_back(joah->_m_jaI);
        joIs.push_back(joah->_m_joI);
    }
    if(joah->_m_pred!=NULL)
        GetJointActionObservationHistoryVectorsRecursive(joah->_m_pred,
                                                         jaIs,joIs);
}

*/
