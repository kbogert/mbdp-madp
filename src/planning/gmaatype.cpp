/**\file gmaatype.cpp
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
 * $Id: gmaatype.cpp 2962 2008-11-02 15:04:43Z mtjspaan $
 */

#include <list>

using namespace std;

#include "gmaatype.h"
#include "E.h"

std::string GMAAtype::SoftPrint(GMAA_t type)
{
    switch(type)
    {
    case MAAstar:
        return("MAAstar");
        break;
    case FSPC:
        return("FSPC");
        break;
    case kGMAA:
        return("kGMAA");
        break;
    }

    throw(E("GMAAtype::SoftPrint invalid type"));

    return("INVALIDQMAATYPE");
}
