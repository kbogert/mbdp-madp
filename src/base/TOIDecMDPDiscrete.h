/**\file TOIDecMDPDiscrete.h
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
 * $Id: TOIDecMDPDiscrete.h 3603 2009-08-25 10:38:25Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _TOIDECMDPDISCRETE_H_
#define _TOIDECMDPDISCRETE_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "TOIDecPOMDPDiscrete.h"



/**\brief TOIDecMDPDiscrete is a class that represents a transition
 * observation indepedent discrete DecMDP. */
class TOIDecMDPDiscrete :
    public TOIDecPOMDPDiscrete
{
private:    
    /**Boolean that tracks whether this TOIDecMDPDiscrete is initialized.*/
    bool _m_initialized;         
    
protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    TOIDecMDPDiscrete(
        std::string name="received unspec. by TOI-DecMDPDiscrete", 
        std::string descr="received unspec. by TOI-DecMDPDiscrete", 
        std::string pf="received unspec. by TOI-DecMDPDiscrete");
    /// Destructor.
    virtual ~TOIDecMDPDiscrete();
    
    /** Sets _m_initialized to b. When setting to true, a verification of
     * member elements is performed. (i.e. a check whether all vectors
     * have the correct size and non-zero entries) */
    bool SetInitialized(bool b);   
    
    /**This function creates the 'state observations'. I.e., for each agent
     * the same number of observations as local states is created. The
     * observation probabilities are set such that in a particular state
     * the corresponding observation is received with certainty.*/
    void CreateStateObservations();
};


#endif /* !_TOIDECMDPDISCRETE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
