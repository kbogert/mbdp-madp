/**\file qheur.cpp
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
 * $Id: qheur.cpp 2962 2008-11-02 15:04:43Z mtjspaan $
 */


using namespace std;

#include "qheur.h"
#include "E.h"

std::string qheur::SoftPrint(Qheur_t Qheur)
{
    switch(Qheur)
    {
    case(eQMDP):
        return("QMDP");
    case(eQPOMDP):
        return("QPOMDP");
    case(eQBG):
        return("QBG");
    case(eQMDPc):
        return("QMDPc");
    }

    throw(E("qheur::SoftPrint invalid type"));

    return("INVALIDQHEUR");
}

