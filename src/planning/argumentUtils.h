/**\file argumentUtils.h
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
 * $Id: argumentUtils.h 3635 2009-08-27 13:33:33Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _ARGUMENTUTILS_H_
#define _ARGUMENTUTILS_H_ 1

/* the include directives */
#include "Globals.h"
 
class DecPOMDPDiscreteInterface;

#include "argumentHandlers.h"
//namespace ArgumentHandlers;
//class ArgumentHandlers::Arguments;

/** \brief argumentUtils provides a way to get problem instantations 
 * directly from the command-line arguments. */
namespace ArgumentUtils 
{
    DecPOMDPDiscreteInterface* GetDecPOMDPDiscreteInterfaceFromArgs(
            const ArgumentHandlers::Arguments& args);
    
}


#endif /* !_ARGUMENTUTILS_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
