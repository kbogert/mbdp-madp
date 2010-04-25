/**\file QFunctionForDecPOMDP.h
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
 * $Id: QFunctionForDecPOMDP.h 3604 2009-08-25 10:52:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _QFUNCTIONFORDECPOMDP_H_
#define _QFUNCTIONFORDECPOMDP_H_ 1

/* the include directives */
#include "Globals.h"
#include "QFunction.h"
#include "QFunctionForDecPOMDPInterface.h"

class PlanningUnitDecPOMDPDiscrete;
/** \brief QFunctionForDecPOMDP is a class that represents 
 * a Q function for a Dec-POMDP. This is a base class
 * that only stores a pointer to the Dec-POMDP planning unit. */

class QFunctionForDecPOMDP : 
    virtual public QFunctionForDecPOMDPInterface,   //inherited interface
    public QFunction                        //inherited implementation

{
    private:    
        const PlanningUnitDecPOMDPDiscrete* _m_pu;
        
    
    protected:
    
    public:
        // Constructor, destructor and copy assignment.
        /// (default) Constructor
        QFunctionForDecPOMDP(const PlanningUnitDecPOMDPDiscrete& pu)
            :
                _m_pu(&pu) 
        {};
/*
        /// Copy constructor.
        QFunctionForDecPOMDP(const QFunctionForDecPOMDP& a);
        /// Destructor.
        ~QFunctionForDecPOMDP();
        /// Copy assignment operator
        QFunctionForDecPOMDP& operator= (const QFunctionForDecPOMDP& o);
*/
        //operators:

        //data manipulation (set) functions:
        void SetPU(const PlanningUnitDecPOMDPDiscrete& pu)
        { _m_pu = &pu; }

        //get (data) functions:
        const PlanningUnitDecPOMDPDiscrete* GetPU() const
        { return _m_pu; }

};


#endif /* !_QFUNCTIONFORDECPOMDP_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
