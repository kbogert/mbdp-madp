/**\file QTableInterface.h
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
 * $Id: QTableInterface.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _QTABLEINTERFACE_H_
#define _QTABLEINTERFACE_H_ 1

/* the include directives */
#include "Globals.h"

/** \brief QTableInterface is the abstract base class for Q(., a) functions.
 * It represents functions mapping from some domain (e.g. states, local states,
 * histories, etc.) and some action domain (individual, joint or group actions)
 * to a real number representing some form of payoff (long term reward, or 
 * immediate reward).
 *
 * Note the argument of the functions defined here assume Q(s,a), but is
 * should be clear that for s_i any general domain index may be used.
 *
 * */
class QTableInterface 
{
    private:    
    
    protected:
    
    public:
        virtual double Get(Index s_i, Index ja_i) const = 0;
        virtual void Set(Index s_i, Index ja_i, double rew) = 0;

        virtual ~QTableInterface(){};

        /// Returns a pointer to a copy of this class.
        virtual QTableInterface* Clone() const = 0;

};


#endif /* !_QTABLEINTERFACE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
