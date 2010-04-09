/**\file SimulationDecPOMDPDiscrete.cpp
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
 * $Id: SimulationDecPOMDPDiscrete.cpp 3638 2009-08-31 12:49:23Z mtjspaan $
 */

#include "SimulationDecPOMDPDiscrete.h"
#include "JointPolicyDiscrete.h"
#include "AgentLocalObservations.h"
#include "AgentSharedObservations.h"
#include "AgentDelayedSharedObservations.h"
#include "AgentFullyObservable.h"

#include "JointObservationHistoryTree.h"
#include "JointObservation.h"
#include "JointAction.h"

using namespace std;

SimulationDecPOMDPDiscrete::
SimulationDecPOMDPDiscrete(const PlanningUnitDecPOMDPDiscrete &pu, 
                           int nrRuns, int seed) : 
    Simulation(nrRuns, seed),
    _m_pu(&pu),
    _m_saveIntermediateResults(false)
{
    Initialize();
}

SimulationDecPOMDPDiscrete::
SimulationDecPOMDPDiscrete(const PlanningUnitDecPOMDPDiscrete &pu, 
                           const ArgumentHandlers::Arguments &args) : 
    Simulation(args.nrRuns, args.randomSeed),
    _m_pu(&pu),
    _m_saveIntermediateResults(false)
{
    if(args.verbose >= 4)
        SetVerbose(true);
    Initialize();
}

//Destructor
SimulationDecPOMDPDiscrete::~SimulationDecPOMDPDiscrete()
{
}

/* from http://www.mega-nerd.com/FPcast/ */
	__inline long int 
	lrint (double flt) 
	{	int intgr;

		_asm
		{	fld flt
			fistp intgr
			} ;
			
		return intgr ;
	} 

void SimulationDecPOMDPDiscrete::Initialize()
{
    if(_m_pu->GetHorizon()==MAXHORIZON)
    {
        // figure out until what horizon we should sample to get a
        // maximum error smaller than 1-e6
        double maxAbsReward=0;
        for(Index s=0;s!=_m_pu->GetNrStates();++s)
            for(Index ja=0;ja!=_m_pu->GetNrJointActions();++ja)
                if(abs(_m_pu->GetReward(s,ja))>maxAbsReward)
                    maxAbsReward=abs(_m_pu->GetReward(s,ja));
        
        _m_horizon=lrint(ceil((log(1e-6/maxAbsReward)/
                               log(_m_pu->GetDiscount()))));
        if(GetVerbose())
            cout << "Set horizon to " << _m_horizon << " (g "
                 << _m_pu->GetDiscount() << " max|R| " << maxAbsReward
                 << ")" << endl;
    }
    else
        _m_horizon=_m_pu->GetHorizon();

    if(GetVerbose())
        cout << "Simulation::RunSimulations horizon " << _m_horizon
             << " nrRuns " << GetNrRuns() << " seed " 
             << GetRandomSeed() << endl;
    
    if(GetRandomSeed()!=illegalRandomSeed)
    {
        // Seed the random number generator
        srand(GetRandomSeed());
    }
}

void SimulationDecPOMDPDiscrete::SaveIntermediateResults(string filename)
{
    _m_saveIntermediateResults=true;
    _m_intermediateResultsFilename=filename;
}

SimulationResult
SimulationDecPOMDPDiscrete::RunSimulations(const JointPolicyDiscrete *jp) const
{
    SimulationResult result(_m_horizon,GetRandomSeed(),GetNrRuns());
#if 0
    if(GetVerbose())
        jp->Print();

#endif
    // Run the simulations
    int i;
    for(i=0;i<GetNrRuns();i++)
    {
        double res = RunSimulation(jp);
        if(GetVerbose())
            cout << "Run ended r="<<res<<endl;
        result.AddReward(res);
    }

    return(result);
}

double
SimulationDecPOMDPDiscrete::RunSimulation(const JointPolicyDiscrete *jp) const
{
    Index jaI,sI,joI;
    double r,sumR=0;
    Index johI = INITIAL_JOHI;

    sI = _m_pu->GetReferred()->SampleInitialState();

    if(GetVerbose())
        cout << "Simulation::RunSimulation " << endl
             << "Simulation::RunSimulation set initial state to " 
             << sI << endl;

    for(unsigned int t=0;t<_m_horizon;t++)
    {	
        jaI = jp->SampleJointAction(johI);

        Step(jaI, t, sI, joI, r, sumR);
        
        /* action taken at ts=0,...,hor-1 - therefore only observation
         * histories at ts=0,...,hor-2 have successors.*/
        if(t < _m_horizon-1) 
            johI = _m_pu->GetSuccessorJOHI(johI, joI);
    }

    return(sumR);
}

void SimulationDecPOMDPDiscrete::Step(Index jaI, unsigned int t, Index &sI,
                                      Index &joI, double &r,
                                      double &sumR) const
{
    Index sI_suc=_m_pu->GetReferred()->SampleSuccessorState(sI,jaI);

    joI=_m_pu->GetReferred()->SampleJointObservation(jaI,sI_suc);
    r = _m_pu->GetReferred()->GetReward(sI,jaI);
        
    // calc. the discounted reward
    sumR+=r*pow(_m_pu->GetDiscount(),static_cast<double>(t));
    
    if(GetVerbose())
        cout << "Simulation::RunSimulation ("
             << sI << "," << jaI << "," << sI_suc << ") ("
             << (_m_pu->GetReferred()->GetState(sI)->SoftPrintBrief())
             << ","
             << (_m_pu->GetJointAction(jaI))->SoftPrintBrief()
             << ","
             << (_m_pu->GetReferred()->GetState(sI_suc)->SoftPrintBrief())
             << ") (p " 
             << _m_pu->GetReferred()->GetTransitionProbability(sI,jaI,sI_suc) 
             << ") jo " << joI << " "
             << (_m_pu->GetJointObservation(joI))->SoftPrintBrief()
             << " (p " 
             << _m_pu->GetReferred()->GetObservationProbability(jaI,sI_suc,joI)
             << ") r " << r << " sumR " << sumR << endl;

    sI = sI_suc;
}

Index SimulationDecPOMDPDiscrete::
GetAction(const vector<AgentLocalObservations*> &agents, Index i,
          Index jaI, Index joI, double r, Index prevJoI, Index sI) const
{
    if(joI==INT_MAX) //first stage: there is no joI
        return(agents[i]->Act(INT_MAX));
    else
    {
        vector<Index> oIs=_m_pu->JointToIndividualObservationIndices(joI);
        return(agents[i]->Act(oIs[i]));
    }
}

Index SimulationDecPOMDPDiscrete::
GetAction(const vector<AgentSharedObservations*> &agents, Index i,
          Index jaI, Index joI, double r, Index prevJoI, Index sI) const
{
    return(agents[i]->Act(joI));
}

Index SimulationDecPOMDPDiscrete::
GetAction(const vector<AgentDelayedSharedObservations*> &agents,
          Index i, Index jaI, Index joI, double r, Index prevJoI,
          Index sI) const
{
    if(joI==INT_MAX) //first stage: there is no joI
        return(agents[i]->Act(INT_MAX,prevJoI));
    else
    {
        vector<Index> oIs=_m_pu->JointToIndividualObservationIndices(joI);
        return(agents[i]->Act(oIs[i],prevJoI));
    }
}

Index SimulationDecPOMDPDiscrete::
GetAction(const vector<AgentFullyObservable*> &agents,
          Index i, Index jaI, Index joI, double r, Index prevJoI,
          Index sI) const
{
    return(agents[i]->Act(sI,joI,r));
}
