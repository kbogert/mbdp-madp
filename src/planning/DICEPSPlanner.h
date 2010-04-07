/**\file DICEPSPlanner.h
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
 * $Id: DICEPSPlanner.h 3637 2009-08-31 12:47:58Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _DICEPSPlannerPLANNER_H_
#define _DICEPSPlannerPLANNER_H_ 1

/* the include directives */
#include <iostream>
#include <vector>
#include <list>
#include <fstream>

#include "Globals.h"
#include "PlanningUnitDecPOMDPDiscrete.h"
#include "ValueFunctionDecPOMDPDiscrete.h"
#include "JointPolicyPureVector.h"
#include "JointPolicy.h"
#include "TimedAlgorithm.h"


class JPPVValuePair;

using std::vector;
using std::list;

/** \brief DICEPSPlanner implements the Direct Cross-Entropy Policy
 * Search method.
 *
 * The algorithm is described in #refDICEPS (see DOC-References.h).
 */
class DICEPSPlanner : 
    public PlanningUnitDecPOMDPDiscrete,
    public TimedAlgorithm
{
    
private:    
    //output settings:
    bool _m_outputConvergenceStatistics;
    std::ofstream* _m_outputConvergenceFile;
    int _m_verbose;

    // CE Settings
    size_t _m_nrRestarts;
    size_t _m_nrIterations;
    size_t _m_nrSampledJointPolicies;
    size_t _m_nrJointPoliciesForUpdate;
    bool _m_use_gamma;
    double _m_alpha;
    size_t _m_nrEvalRuns;

    //the best found policy
    JointPolicyPureVector _m_foundPolicy;
    //the expected reward of the best found policy
    double _m_expectedRewardFoundPolicy;

protected:

    static void SampleIndividualPolicy(PolicyPureVector& pol, 
            const vector< vector<double> >&  ohistActionProbs );
    static void OrderedInsertJPPVValuePair( JPPVValuePair* pv, 
            list< JPPVValuePair*>& l );
    static void PrintBestSamples( const list< JPPVValuePair*>& l );
    
    void UpdateCEProbDistribution(
            vector< vector< vector<double> > >& Xi, 
            const list<JPPVValuePair* >& best_samples);
    double ApproximateEvaluate(JointPolicyDiscrete &jpol, int nrRuns);

    public:
        
        // Constructor, destructor and copy assignment.
        // (default) Constructor
        //DICEPSPlanner();
        DICEPSPlanner(
            const PlanningUnitMADPDiscreteParameters &params,
            DecPOMDPDiscreteInterface* p,
            size_t horizon,
            size_t nrRestarts,
            size_t nrIterations,
            size_t nrSamples,
            size_t nrSamplesForUpdate,
            bool use_hard_threshold, //(gamma in CE papers)
            double CEalpha, //the learning rate
            size_t nrEvalRuns, // policy evaluation runs (set 0 for exact eval)
            int verbose = 0
            );
        DICEPSPlanner(
            DecPOMDPDiscreteInterface* p,
            int horizon,
            size_t nrRestarts,
            size_t nrIterations,
            size_t nrSamples,
            size_t nrSamplesForUpdate,
            bool use_hard_threshold, //(gamma in CE papers)
            double CEalpha, //the learning rate
            size_t nrEvalRuns, // policy evaluation runs (set 0 for exact eval)
            int verbose = 0
            );
        DICEPSPlanner(
            const PlanningUnitMADPDiscreteParameters &params,
            DecPOMDPDiscreteInterface* p,
            size_t horizon,
            size_t nrRestarts,
            size_t nrIterations,
            size_t nrSamples,
            size_t nrSamplesForUpdate,
            bool use_hard_threshold, //(gamma in CE papers)
            double CEalpha, //the learning rate
            size_t nrEvalRuns, // policy evaluation runs (set 0 for exact eval)
            bool convergenceStats,
            std::ofstream & convergenceStatsFile,
            int verbose = 0
            );
        DICEPSPlanner(
            DecPOMDPDiscreteInterface* p,
            int horizon,
            size_t nrRestarts,
            size_t nrIterations,
            size_t nrSamples,
            size_t nrSamplesForUpdate,
            bool use_hard_threshold, //(gamma in CE papers)
            double CEalpha, //the learning rate
            size_t nrEvalRuns, // policy evaluation runs (set 0 for exact eval)
            bool convergenceStats,
            std::ofstream & convergenceStatsFile,
            int verbose = 0
            );

        //operators:

        //data manipulation (set) functions:
        /**
         * The methods that performs the planning according to 
         * the CE for Dec-POMDP algorithm. */
        void Plan();

        //get (data) functions:
        JointPolicy* GetJointPolicy(void)
            { return(&_m_foundPolicy); }
        JointPolicyDiscrete* GetJointPolicyDiscrete(void)
            { return(&_m_foundPolicy); }
        JointPolicyPureVector* GetJointPolicyPureVector(void)
            { return(&_m_foundPolicy); }
        double GetExpectedReward(void) const
            { return(_m_expectedRewardFoundPolicy); }

};


#endif /* !_DICEPSPlannerPLANNER_H_ */


// Local Variables: ***
// mode:c++ ***
// End: ***
