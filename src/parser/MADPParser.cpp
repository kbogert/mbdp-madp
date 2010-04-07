/**\file MADPParser.cpp
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
 * $Id: MADPParser.cpp 3611 2009-08-25 15:02:24Z mtjspaan $
 */

#include "MADPParser.h"
#include "ParserDecPOMDPDiscrete.h"
#include "ParserTOIDecPOMDPDiscrete.h"
#include "ParserTOIDecMDPDiscrete.h"
#include "ParserTOIFactoredRewardDecPOMDPDiscrete.h"
#include "ParserTOICompactRewardDecPOMDPDiscrete.h"
#include "DecPOMDPDiscrete.h"
#include "TOIDecPOMDPDiscrete.h"
#include "TOIDecMDPDiscrete.h"
#include "TOIFactoredRewardDecPOMDPDiscrete.h"
#include "TOICompactRewardDecPOMDPDiscrete.h"

void MADPParser::Parse(DecPOMDPDiscrete *model)
{
    ParserDecPOMDPDiscrete parser(model);
    parser.Parse();
}

void MADPParser::Parse(TOIDecPOMDPDiscrete *model)
{
    ParserTOIDecPOMDPDiscrete parser(model);
    parser.Parse();
}

void MADPParser::Parse(TOIDecMDPDiscrete *model)
{
    ParserTOIDecMDPDiscrete parser(model);
    parser.Parse();
}

void MADPParser::Parse(TOIFactoredRewardDecPOMDPDiscrete *model)
{
    ParserTOIFactoredRewardDecPOMDPDiscrete parser(model);
    parser.Parse();
}

void MADPParser::Parse(TOICompactRewardDecPOMDPDiscrete *model)
{
    ParserTOICompactRewardDecPOMDPDiscrete parser(model);
    parser.Parse();
}
