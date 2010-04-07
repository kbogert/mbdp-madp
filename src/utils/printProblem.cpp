/**\file printProblem.cpp
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
 * $Id: printProblem.cpp 2151 2008-01-21 16:32:52Z mtjspaan $
 */

// Very simple programs that only uses the Parser and Base libraries.

#include <iostream>
#include "DecPOMDPDiscrete.h"
#include "MADPParser.h"

using namespace std;

int main(int argc, char **argv)
{
    if(argc!=2)
    {
        cout << "Use as follows: printProblem "
             << "<problem>" << endl;
        return(1);
    }

    try {

        DecPOMDPDiscrete dpomdp("","",argv[1]);
        MADPParser parser(&dpomdp);
        dpomdp.Print();

    }
    catch(E& e){ e.Print(); }

    return(0);
}
