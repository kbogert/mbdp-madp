/**\file QFunctionForDecPOMDPInterface.h
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
 * $Id: QFunctionForDecPOMDPInterface.h 3604 2009-08-25 10:52:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _QFUNCTIONFORDECPOMDPINTERFACE_H_
#define _QFUNCTIONFORDECPOMDPINTERFACE_H_ 1

/* the include directives */
#include "Globals.h"
#include "QFunctionInterface.h"

class PlanningUnitDecPOMDPDiscrete;
/** \brief QFunctionForDecPOMDPInterface is a class that represents 
 * a Q function for a Dec-POMDP. This is a base class
 * that only stores a pointer to the Dec-POMDP planning unit. */

class QFunctionForDecPOMDPInterface :
   virtual public QFunctionInterface
{
    private:    
        
    
    protected:
    
    public:
        // Constructor, destructor and copy assignment.
        /// (default) Constructor
        QFunctionForDecPOMDPInterface()
        {};
        /// Destructor.
        virtual ~QFunctionForDecPOMDPInterface(){};
/*
        /// Copy constructor.
        QFunctionForDecPOMDPInterface(const QFunctionForDecPOMDPInterface& a);
        /// Copy assignment operator
        QFunctionForDecPOMDPInterface& operator= (const QFunctionForDecPOMDPInterface& o);
*/
        //operators:

        //data manipulation (set) functions:
        virtual void SetPU(const PlanningUnitDecPOMDPDiscrete& pu) = 0;

        //get (data) functions:
        virtual const PlanningUnitDecPOMDPDiscrete* GetPU() const = 0;

};


#endif /* !_QFUNCTIONFORDECPOMDPINTERFACE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
