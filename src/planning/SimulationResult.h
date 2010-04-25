/**\file SimulationResult.h
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
 * $Id: SimulationResult.h 2151 2008-01-21 16:32:52Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _SIMULATIONRESULT_H_
#define _SIMULATIONRESULT_H_ 1

/* the include directives */
#include <iostream>
#include <vector>
#include <string>
#include "Globals.h"

/** \brief SimulationResult stores the results from simulating a joint
 * policy, the obtained rewards in particular.
 *
 * At the moment only applies to DecPOMDPs. */
class SimulationResult 
{
private:    

    double _m_avg_reward;
    std::vector<double> _m_rewards;
    
    unsigned int _m_horizon;
    int _m_random_seed;
    
    unsigned int _m_nr_stored;

    void UpdateStatistics();
    
protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    SimulationResult();

    /// Construct an object with certain parameters.
    SimulationResult(int horizon,int random_seed,int nrRuns);
    
    /// Destructor.
    ~SimulationResult();
    
    /// Add a sampled reward to the results set.
    void AddReward(double r);
    
    /// Get the full set of stored reward samples.
    std::vector<double> GetRewards(void);

    /// The average of the stored reward samples.
    double GetAvgReward(void){ return(_m_avg_reward); }

    /// Save the reward samples to disk.
    void Save(std::string filename);

    /// Load reward samples from file.
    void Load(std::string filename);

    /// Print out the stored reward samples.
    void Print(void);

    /// Print out a summary.
    void PrintSummary(void);
};


#endif /* !_SIMULATIONRESULT_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
