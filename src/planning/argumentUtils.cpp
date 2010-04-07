/**\file argumentUtils.cpp
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
 * $Id: argumentUtils.cpp 3638 2009-08-31 12:49:23Z mtjspaan $
 */

#include <list>

using namespace std;


#include "argumentUtils.h"
#include "argumentHandlers.h"
#include "MADPParser.h"
#include "directories.h"
#include "TOIFactoredRewardDecPOMDPDiscrete.h"

#include "ProblemDecTiger.h"
#include "ProblemFireFighting.h"
using namespace ArgumentHandlers;
namespace ArgumentUtils {

DecPOMDPDiscreteInterface* GetDecPOMDPDiscreteInterfaceFromArgs(const Arguments& args)
{
    DecPOMDPDiscreteInterface * dp;
    switch(args.problem_type) 
    {

        case(ProblemType::DT):
        {
            ProblemDecTiger* p = new ProblemDecTiger();            
            dp = p;
            break;
        }
        case(ProblemType::FF):
        {
            dp = new ProblemFireFighting(args.nrAgents, args.nrHouses, 
                    args.nrFLs);
            break;
        }

        case(ProblemType::PARSE):
        default: //try to open the .dpomdp file and parse it
        {
            string dpomdpFile=directories::MADPGetProblemFilename(args);
            // load the DecPOMDP problem 
            if(args.isTOI)
            {
                TOIFactoredRewardDecPOMDPDiscrete *toi=
                    new TOIFactoredRewardDecPOMDPDiscrete("","",dpomdpFile);
                if(args.sparse)
                    toi->SetSparse(true);
                MADPParser parser(toi);
                if(args.sparse)
                    toi->CreateCentralizedSparseModels();
                else
                    toi->CreateCentralizedFullModels();
                
                dp=toi;
            }
            else{

                DecPOMDPDiscrete* decpomdp = 
                    new DecPOMDPDiscrete("","",dpomdpFile);
                if(args.sparse)
                    decpomdp->SetSparse(true);
                MADPParser parser(decpomdp);
                dp = decpomdp;
            }
            if(args.verbose >= 0)
                cout << "ArgumentUtils: Problem file parsed" << endl;
        }
    }
    if(args.discount > 0)
        dp->SetDiscount(args.discount);
            
    if(args.verbose >= 0)
        cout << "ArgumentUtils: Problem instantiated." << endl;

    return dp;
}

} //namespace
