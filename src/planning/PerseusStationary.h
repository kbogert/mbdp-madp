/**\file PerseusStationary.h
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
 * $Id: PerseusStationary.h 3010 2008-11-12 11:30:18Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _PERSEUSSTATIONARY_H_
#define _PERSEUSSTATIONARY_H_ 1

/* the include directives */
#include "Globals.h"
#include "Perseus.h"

/** \brief PerseusStationary is Perseus for stationary policies. */
class PerseusStationary : public Perseus
{
private:    
    
protected:
    
    /// The resulting value function.
    ValueFunctionPOMDPDiscrete _m_valueFunction;
    /// The resulting Q functions, derived from \a _m_valueFunction.
    QFunctionsDiscrete _m_qFunction;

    /// The belief set.
    BeliefSet *_m_beliefs;

    void StoreValueFunction(const ValueFunctionPOMDPDiscrete &V);
    void StoreValueFunction(const QFunctionsDiscrete &Q);

    void InitializeBeliefs(int nrB, bool uniquify);

    std::vector<double> GetImmediateRewardBeliefSet() const;

public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    PerseusStationary(const PlanningUnitDecPOMDPDiscrete& pu);
    /// Destructor.
    virtual ~PerseusStationary();

    /// Sets the belief set \a S that Perseus should use.
    void SetBeliefSet(const BeliefSet &S);

    /// Exports the belief set in a simple matrix format.
    void ExportBeliefSet(const std::string &filename) const;

    /// Sets the value function
    void SetValueFunction(const std::string &filename);

    ValueFunctionPOMDPDiscrete GetValueFunction() const
        { return(_m_valueFunction); }

    QFunctionsDiscrete GetQFunctions() const
        { return(_m_qFunction); }

    double GetQ(const JointBeliefInterface &b, Index jaI) const;

    double GetQ(const JointBeliefInterface &b, Index jaI, int &betaMaxI) const;

    double GetQ(const JointBeliefInterface &b, Index t, Index jaI) const;
    double GetQ(const JointBeliefInterface &b, Index t, Index jaI,
                int &betaMaxI) const;

    void ExportValueFunction(const std::string &filename) const;

};



#endif /* !_PERSEUSSTATIONARY_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
