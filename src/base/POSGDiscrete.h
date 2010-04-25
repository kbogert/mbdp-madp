/**\file POSGDiscrete.h
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
 * $Id: POSGDiscrete.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _POSGDISCRETE_H_
#define _POSGDISCRETE_H_ 1

/* the include directives */
#include <vector>
#include <string>
#include "Globals.h"
#include "MultiAgentDecisionProcessDiscrete.h"
#include "RewardModelMapping.h"
#include "POSG.h"
#include "POSGDiscreteInterface.h"

/**\brief POSGDiscrete represent a discrete POSG model.
 *
 * It implements POSGDiscreteInterface. 
 *
 * Also it inherits 
 * -MultiAgentDecisionProcessDiscrete 
 * -POSG
 *
 * and thus implements 
 * -POSGInterface
 * -MultiAgentDecisionProcessDiscreteInterface
 * -MultiAgentDecisionProcessInterface
 * */
class POSGDiscrete : 
    virtual public POSGDiscreteInterface,
    public MultiAgentDecisionProcessDiscrete, 
    public POSG
{
    private:        
        ///Boolean that tracks whether this POSG is initialized.
        bool _m_initialized;        

    protected:        
        
        /// The reward model used by POSGDiscrete is a RewardModelMapping
        std::vector<RewardModelMapping*> _m_p_rModel;

    public:

        // Constructor, destructor and copy assignment.
        /// Default constructor.
        /** Constructor that sets the name, description, and problem file,
         * and subsequently loads this problem file. */
        POSGDiscrete(std::string name="received unspec. by POSGDiscrete", 
                std::string descr="received unspec. by POSGDiscrete", 
                std::string pf="received unspec. by POSGDiscrete");
        /// Destructor.
        ~POSGDiscrete();
        
        //data manipulation (set) functions:
        /// Sets _m_initialized to b.
        /** When setting to true, a verification of member elements is
         * performed. (i.e. a check whether all vectors have the
         * correct size and non-zero entries) */
        bool SetInitialized(bool b);   
        /// Creates a new reward model.
        void CreateNewRewardModel( Index agentI, size_t nrS, size_t nrJA);
        /// Set the reward for state, joint action indices 
        void SetReward(Index agentI, Index sI, Index jaI, double r)
            { _m_p_rModel.at(agentI)->Set(sI, jaI, r);}

        /// Set the reward for state, joint action , suc. state indices 
        void SetReward(Index agentI, Index sI, Index jaI, Index sucSI, 
                       double r);

        /// Set the reward for state, joint action, suc.state, joint obs indices
        void SetReward(Index agentI, Index sI, Index jaI, Index sucSI, 
                Index joI, double r);

        // 'get' functions:         
        /// Return the reward for state, joint action indices 
        double GetReward(Index agentI, Index sI, Index jaI) const
            { return(_m_p_rModel.at(agentI)->Get(sI, jaI));}
        
        ///  Prints some information on the POSGDiscrete.        
        std::string SoftPrint() const;

        //We need to implement this for POSG:        
        double GetReward(Index agentI, State* s, JointAction* ja) const;

        /// Returns a copy of this class.
        virtual POSGDiscrete* Clone() const = 0;

};

#endif /* !_POSGDISCRETE_H_ */


// Local Variables: ***
// mode:c++ ***
// End: ***
