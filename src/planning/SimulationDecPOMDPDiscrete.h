/**\file SimulationDecPOMDPDiscrete.h
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
 * $Id: SimulationDecPOMDPDiscrete.h 3638 2009-08-31 12:49:23Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _SIMULATIONDECPOMDPDISCRETE_H_
#define _SIMULATIONDECPOMDPDISCRETE_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"

#include "Simulation.h"
#include "SimulationResult.h"
#include "PlanningUnitDecPOMDPDiscrete.h"
#include "argumentHandlers.h"
#include "State.h"

class JointPolicyDiscrete;
class AgentLocalObservations;
class AgentSharedObservations;
class AgentDelayedSharedObservations;
class AgentFullyObservable;

/**\brief SimulationDecPOMDPDiscrete simulates policies in
 * DecPOMDPDiscrete's.  */
class SimulationDecPOMDPDiscrete : public Simulation
{
private:    
    
    /// Pointer to the planning unit that generated the policy.
    const PlanningUnitDecPOMDPDiscrete* _m_pu;
    
    bool _m_saveIntermediateResults;

    std::string _m_intermediateResultsFilename;

    Index GetAction(const std::vector<AgentLocalObservations*> &agents, Index i,
                     Index jaI, Index joI, double r, Index prevJoI,
                     Index sI) const;

    Index GetAction(const std::vector<AgentSharedObservations*> &agents, Index i,
                     Index jaI, Index joI, double r, Index prevJoI,
                     Index sI) const;

    Index GetAction(const std::vector<AgentDelayedSharedObservations*> &agents,
                     Index i, Index jaI, Index joI, double r, Index prevJoI,
                     Index sI) const;

     Index GetAction(const std::vector<AgentFullyObservable*> &agents, Index i,
                     Index jaI, Index joI, double r, Index prevJoI,
                     Index sI) const;

    void Initialize();

    /// Perform one step of the simulation.
    void Step(Index jaI, unsigned int t, Index &sI,  Index &joI,
              double &r, double &sumR) const;

    /// Simulate a run of a discrete joint policy.
    double RunSimulation(const JointPolicyDiscrete* jp) const;

protected:
    
    size_t _m_horizon;

public:
    // Constructor, destructor and copy assignment.

    /// Constructor specifying the number of runs and the random seed.
    SimulationDecPOMDPDiscrete(const PlanningUnitDecPOMDPDiscrete &pu,
                               int nrRuns, int seed=illegalRandomSeed);

    /// Constructor which parses the command-line arguments.
    SimulationDecPOMDPDiscrete(const PlanningUnitDecPOMDPDiscrete &pu,
                               const ArgumentHandlers::Arguments &args);

    /// Destructor.
    ~SimulationDecPOMDPDiscrete();

    /// Run simulations using a particular discrete joint policy.
    SimulationResult
    RunSimulations(const JointPolicyDiscrete* jp) const;

    /// Run simulations using a vector of SimulationAgent.
    template <class A>
    SimulationResult
    RunSimulations(const std::vector<A*> &agents) const
    {
        SimulationResult result(_m_horizon,GetRandomSeed(),GetNrRuns());

        // Run the simulations
        int i;
        for(i=0;i<GetNrRuns();i++)
        {
            Index jaI,sI,joI,prevJoI;
            int nr=agents.size(),i;
            std::vector<Index> aIs(nr);

            unsigned int h;
            double r=0,sumR=0;

            sI = _m_pu->GetReferred()->SampleInitialState();

            if(GetVerbose())
                std::cout << "Simulation::RunSimulation set initial state to " 
                     << sI << " "
                     << _m_pu->GetReferred()->GetState(sI)->SoftPrintBrief()
                     << " (avg reward so far " << result.GetAvgReward()
                          << ")" << std::endl;

            for(i=0;i<nr;++i)
                agents[i]->ResetEpisode();

            joI=INT_MAX;
            jaI=INT_MAX;
            prevJoI=INT_MAX;
            for(h=0;h<_m_horizon;h++)
            {
                // get the action for each particular agent
                for(i=0;i<nr;++i)
                    aIs[i]=GetAction(agents,i,jaI,joI,r,prevJoI,sI);
                jaI=_m_pu->IndividualToJointActionIndices(aIs);

                prevJoI=joI;
                Step(jaI, h, sI, joI, r, sumR);
            }
            
            result.AddReward(sumR);

            if(_m_saveIntermediateResults)
                result.Save(_m_intermediateResultsFilename);
        }
        
        return(result);
    }

    /// Indicate that intermediate should be stored to file named filename.
    void SaveIntermediateResults(std::string filename);


};


#endif /* !_SIMULATIONDECPOMDPDISCRETE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
