/**\file DecPOMDPDiscrete.h
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
 * $Id: DecPOMDPDiscrete.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _DECPOMDPDISCRETE_H_
#define _DECPOMDPDISCRETE_H_ 1

/* the include directives */
#include <vector>
#include <string>
#include "Globals.h"
#include "MultiAgentDecisionProcessDiscrete.h"
#include "RewardModel.h"
#include "DecPOMDP.h"
#include "DecPOMDPDiscreteInterface.h"

class RGet;

/**\brief DecPOMDPDiscrete represent a discrete DEC-POMDP model.
 *
 * It implements DecPOMDPDiscreteInterface. 
 *
 * Also it inherits 
 * -MultiAgentDecisionProcessDiscrete 
 * -DecPOMDP
 *
 * and thus implements 
 * -DecPOMDPInterface
 * -MultiAgentDecisionProcessDiscreteInterface
 * -MultiAgentDecisionProcessInterface
 * */
class DecPOMDPDiscrete : 
    virtual public DecPOMDPDiscreteInterface,
    public MultiAgentDecisionProcessDiscrete, 
    public DecPOMDP
{
    private:        
        ///Boolean that tracks whether this DecPOMDP is initialized.
        bool _m_initialized;        

    protected:        
        
        /// The reward model used by DecPOMDPDiscrete.
        RewardModel* _m_p_rModel;

    public:

        // Constructor, destructor and copy assignment.
        /// Default constructor.
        /** Constructor that sets the name, description, and problem file,
         * and subsequently loads this problem file. */
        DecPOMDPDiscrete(std::string name="received unspec. by DecPOMDPDiscrete", 
                std::string descr="received unspec. by DecPOMDPDiscrete", 
                std::string pf="received unspec. by DecPOMDPDiscrete");

        /// Destructor.
        ~DecPOMDPDiscrete();
        
        //data manipulation (set) functions:
        /// Sets _m_initialized to b.
        /** When setting to true, a verification of member elements is
         * performed. (i.e. a check whether all vectors have the
         * correct size and non-zero entries) */
        bool SetInitialized(bool b);   
        /// Creates a new reward model.
        void CreateNewRewardModel();
        /// Set the reward for state, joint action indices 
        void SetReward(Index sI, Index jaI, double r)
            { _m_p_rModel->Set(sI, jaI, r);}

        /// Set the reward for state, joint action , suc. state indices 
        void SetReward(Index sI, Index jaI, Index sucSI, double r);

        /// Set the reward for state, joint action, suc.state, joint obs indices
        void SetReward(Index sI, Index jaI, Index sucSI, Index joI, 
                       double r);

        // 'get' functions:         
        /// Return the reward for state, joint action indices 
        double GetReward(Index sI, Index jaI) const
            { return(_m_p_rModel->Get(sI, jaI));}
        
        ///  Prints some information on the DecPOMDPDiscrete.        
        std::string SoftPrint() const;

        /// Get the MADPDiscrete components from this DecPOMDPDiscrete.
        void ExtractMADPDiscrete(MultiAgentDecisionProcessDiscrete *madp);

        /// Get a pointer to the reward model.
        RewardModel* GetRewardModelPtr() const
            { return(_m_p_rModel); }

    //functions to implement the DecPOMDPInterface:        
        ///implements the DecPOMDPInterface
        double GetReward(State* s, JointAction* ja) const    
        {
            return GetReward(
            ((StateDiscrete*)s)->GetIndex(), 
            ((JointActionDiscrete*)ja)->GetIndex());
        }
        ///implements the DecPOMDPInterface
        void SetReward(State* s, JointAction* ja, double r)
        {
            return SetReward(
                    ((StateDiscrete*)s)->GetIndex(), 
                    ((JointActionDiscrete*)ja)->GetIndex(), r);
        }


        
    //functions to implement the POSGInterface:
        
        /// Function that sets the reward for an agent, state and joint action.
        /** This should be very generic.*/
        void SetRewardForAgent(Index agentI, State* s, JointAction* ja, double r)
        {SetReward(s, ja, r); }
        /// Function that returns the reward for a state and joint action.
        /** This should be very generic.*/
        double GetRewardForAgent(Index agentI, State* s, JointAction* ja) const
        {return GetReward(s, ja); }

    //functions to implement the POSGDiscreteInterface:

        ///implementation of POSGDiscreteInterface 
        void CreateNewRewardModelForAgent(Index agentI)
        {CreateNewRewardModel();}

        void SetRewardForAgent(Index agentI, Index sI, Index jaI, double r)
        {SetReward(sI, jaI, r);}

        /// Set the reward for state, joint action , suc. state indices 
        void SetRewardForAgent(Index agentI, Index sI, Index jaI,
                               Index sucSI, double r) 
        {SetReward(sI, jaI, sucSI, r);}

        /// Set the reward for state, joint action, suc.state, joint obs indices
        void SetRewardForAgent(Index agentI, Index sI, Index jaI, 
                Index sucSI, Index joI, double r)
        {SetReward(sI, jaI, sucSI, joI, r);}

        /// Return the reward for state, joint action indices 
        double GetRewardForAgent(Index agentI, Index sI, Index jaI) const
        {return GetReward(sI, jaI);}

        RGet* GetRGet() const;
        /// Returns a pointer to a copy of this class.
        virtual DecPOMDPDiscrete* Clone() const
        { return new DecPOMDPDiscrete(*this); }

};
#endif /* !_DECPOMDPDISCRETE_H_ */


// Local Variables: ***
// mode:c++ ***
// End: ***
