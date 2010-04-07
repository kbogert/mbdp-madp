/**\file ObservationDiscrete.h
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
 * $Id: ObservationDiscrete.h 2151 2008-01-21 16:32:52Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _OBSERVATIONDISCRETE_H_
#define _OBSERVATIONDISCRETE_H_ 1

/* the include directives */
#include <iostream>
#include <string>

#include "Globals.h"
#include "Observation.h"
#include "DiscreteEntity.h"

/// ObservationDiscrete represents discrete observations.
/** 
 * ObservationDiscrete is a class that represent observations in a
 * discrete observation set, which are identified by their index.  */
class ObservationDiscrete : public Observation,
                            public DiscreteEntity
{
    private:    
    
    protected:
    
    public:
        // Constructor, destructor and copy assignment.
        /// (default) Constructor
        ObservationDiscrete(Index i, std::string name=std::string("undefined"),
                            std::string description=std::string("undefined")) :
            Observation(name, description),
            DiscreteEntity(i){};

};

#endif /* !_OBSERVATIONDISCRETE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
