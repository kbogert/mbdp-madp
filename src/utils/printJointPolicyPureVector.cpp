/**\file printJointPolicyPureVector.cpp
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
 * $Id: printJointPolicyPureVector.cpp 2116 2008-01-16 23:11:49Z mtjspaan $
 */


#include <iostream>
#include "DecPOMDPDiscrete.h"
#include "MADPParser.h"
#include "JointPolicyPureVector.h"
#include "NullPlanner.h"

#include "argumentHandlers.h"

const char *argp_program_version = "printJointPolicyPureVector";

// Program documentation
static char doc[] =
"printJointPolicyPureVector - Prints out a JointPolicyPureVector  \
\v";

//NOTE: make sure that the below value (nrChildParsers) is correct!
const int nrChildParsers = 3;
const struct argp_child childVector[] = {
    ArgumentHandlers::problemFile_child,
    ArgumentHandlers::solutionMethodOptions_child,
    ArgumentHandlers::jpolIndex_child,
    { 0 }
};

#include "argumentHandlersPostChild.h"

int main(int argc, char **argv)
{
    try {

    ArgumentHandlers::Arguments args;
    argp_parse (&ArgumentHandlers::theArgpStruc, argc, argv, 0, 0, &args);

    int h=args.horizon;
    LIndex index=args.jpolIndex;

    DecPOMDPDiscrete decpomdp("","",args.dpf);
    MADPParser parser(&decpomdp);
    PlanningUnitMADPDiscreteParameters params;
    params.SetComputeAll(true);
    params.SetComputeJointBeliefs(false);
    NullPlanner np(params,h,&decpomdp);
    JointPolicyPureVector jp(np);
    jp.SetIndex(index);

    jp.Print();
    }
    catch(E& e){ e.Print(); }

    return(0);
}
