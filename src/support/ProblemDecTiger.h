/**\file ProblemDecTiger.h
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
 * $Id: ProblemDecTiger.h 2151 2008-01-21 16:32:52Z mtjspaan $
 */

#ifndef _PROBLEMDECTIGER_H_
#define _PROBLEMDECTIGER_H_ 1

/* the include directives */

#include <iostream>
#include <string>

#include "DecPOMDPDiscrete.h"
#include "ActionDiscrete.h"
#include "JointActionDiscrete.h"
#include "ObservationDiscrete.h"
#include "JointObservationDiscrete.h"

/// ProblemDecTiger implements the DecTiger problem.
/** This class can be used as an alternative to parsing
 * \link dectiger.dpomdp \endlink.*/
class ProblemDecTiger : public DecPOMDPDiscrete
{
private:

    /* aliases */
    typedef std::vector<ActionDiscrete> ActionIVec;
    typedef std::vector<ObservationDiscrete> ObservationIVec;

     /* constants */
    const size_t NUMBER_OF_STATES;
    const size_t NUMBER_OF_AGENTS;
    const size_t NUMBER_OF_OBSERVATIONS;
    const size_t NUMBER_OF_ACTIONS;

    enum state_enum{
        SLEFT,
        SRIGHT
    };

    enum action_enum{
        LISTEN,
        OPENLEFT,
        OPENRIGHT
    };
    
    enum jointAction_enum{
        LISTEN_LISTEN,
        LISTEN_OPENLEFT,
        LISTEN_OPENRIGHT,
        OPENLEFT_LISTEN,
        OPENLEFT_OPENLEFT,
        OPENLEFT_OPENRIGHT,
        OPENRIGHT_LISTEN,
        OPENRIGHT_OPENLEFT,
        OPENRIGHT_OPENRIGHT
    };

    enum observation_enum{
        HEARLEFT,
        HEARRIGHT
    };
    
    enum jointObservation_enum{
        HEARLEFT_HEARLEFT,
        HEARLEFT_HEARRIGHT,
        HEARRIGHT_HEARLEFT,
        HEARRIGHT_HEARRIGHT
    };

    ///Construct all the Actions and actionSets (the vector _m_actionVecs).
    void ConstructActions();
    ///Construct all the observations and observation sets.
    void ConstructObservations();
    ///Fills the transition model with the tiger problem transitions.
    void FillTransitionModel();
    ///Fills the observation model with the tiger problem obs. probs.
    void FillObservationModel();
    ///Fills the reward model with the tiger problem rewards.
    void FillRewardModel();

protected:    
public:
    // constructors etc.
    /// Default constructor.
    ProblemDecTiger();
    /// Destructor.
    ~ProblemDecTiger();

};

#endif //! _PROBLEMDECTIGER_H_

// Local Variables: ***
// mode:c++ ***
// End: ***
