/**\file MBDPPlanner.cpp
 *
 * Authors:
 * Christopher Jackson <christopher.jackson@gmail.com>
 *
 * Copyright 2010 Institute for Artificial Intelligence, University of Georgia
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
 * $Id: $
 */

#include "MBDPPlanner.h"
#include "JESPDynamicProgrammingPlanner.h"
#include "ValueFunctionDecPOMDPDiscrete.h"
#include "JointPolicyPureVector.h"
#include "JointBeliefInterface.h"
#include "IndividualBeliefJESP.h"
#include <float.h>

using namespace std;

#define DEBUG_DPBR 0
#define DEBUG_DPJESP 0

MBDPPlanner::MBDPPlanner(
    const PlanningUnitMADPDiscreteParameters &params,
    size_t horizon,
    DecPOMDPDiscreteInterface* p,
    int maxTrees, double exploration
    ) :
    PlanningUnitDecPOMDPDiscrete(params, horizon, p),
    _m_foundPolicy(*this)
{
}

MBDPPlanner::MBDPPlanner(
    int horizon,
    DecPOMDPDiscreteInterface* p,
    int maxTrees, double exploration
    ) :
    PlanningUnitDecPOMDPDiscrete(horizon, p),
    _m_foundPolicy(*this)
{
}

void MBDPPlanner::Plan()
{
  // Joint Beliefs are pre-initialized via
  // PlanningUnitMADPDiscrete::InitializeJointActionHistories()
  // We will take this complete reachability tree and select only
  // a subset of random beliefs at each time step
  size_t T = GetHorizon();
  size_t nrA = GetReferred()->GetNrAgents();
  BeliefInterface* B = GetJointBeliefInterface(0);
  B->SoftPrint();
  // agentI x PolicyI initialized with nrA (Number of Agents) rows
  std::vector< vector<PolicyPureVector*> > agentPolicies(nrA, vector<PolicyPureVector*>(0));
  JointPolicyPureVector* jpol = new JointPolicyPureVector(*this);
  JointPolicyPureVector* best = new JointPolicyPureVector(*this);
  // initialize all 1-step policy trees
  for (size_t a = 0; a < nrA -1; a++) {
    //int agentI = GetReferred()->GetNextAgentIndex();
  }
  Index agentI = 0;
  while (agentI < nrA - 1) {
    //agentPolicies.push_back(1);
    //GetReferred()->GetNextAgentIndex();
    agentI++;
  }
}

void MBDPPlanner::SetMaxTrees(int maxTrees) {
  _m_maxTrees = maxTrees;
}

JointActionObservationHistory* MBDPPlanner::fullBackup(JointPolicyPureVector*) {
  JointActionObservationHistory* temp_jaoh;
  return temp_jaoh;
}
