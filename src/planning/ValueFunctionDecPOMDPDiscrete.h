/**\file ValueFunctionDecPOMDPDiscrete.h
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
 * $Id: ValueFunctionDecPOMDPDiscrete.h 3004 2008-11-09 18:40:15Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _VALUEFUNCTIONDECPOMDPDISCRETE_H_
#define _VALUEFUNCTIONDECPOMDPDISCRETE_H_ 1

/* the include directives */
#include <iostream>
#include <map>
#include "Globals.h"
#include "ValueFunction.h"
#include "Referrer.h"
#include "PlanningUnitDecPOMDPDiscrete.h"
#include "JointPolicyDiscretePure.h"
#include <boost/numeric/ublas/matrix.hpp>

/** \brief ValueFunctionDecPOMDPDiscrete represents and calculates the
 * value function of a (pure) joint policy for a discrete Dec-POMDP.
 */
class ValueFunctionDecPOMDPDiscrete : 
    public ValueFunction,
    public Referrer<PlanningUnitDecPOMDPDiscrete>,
    public Referrer<JointPolicyDiscretePure>
{
    private:
    PlanningUnitDecPOMDPDiscrete* _m_pu;
    JointPolicyDiscretePure* _m_jpol;

    //some number we cache for speed:
    size_t _m_nrJOH;
    size_t _m_nrJO;
    size_t _m_nrS;
    size_t _m_h;
    bool _m_V_initialized;
    typedef boost::numeric::ublas::matrix<double> Matrix;

    Matrix* _m_p_V; //stores V(sI, JOHistI)
    std::map<Index, bool> _m_cached; // (s,JOHist)-index -> bool

    Index GetCombinedIndex(Index sI, Index JOHI) const
    //{  return( sI*GetPU()->GetNrJointObservationHistories() + JOHI ); }
    {  return( sI*_m_nrJOH + JOHI ); }
    bool IsCached(Index sI, Index JOHI)
    {    return(_m_cached[GetCombinedIndex(sI, JOHI)]); }
    void SetCached(Index sI, Index JOHI);

    /// Deletes the current value function.
    void DeleteV();
    /** \brief Creates a brand new value function (deleting the
     * current one if it exists).
     */
    void CreateV();

    PlanningUnitDecPOMDPDiscrete* GetPU() const 
        {  return _m_pu;
            //return( Referrer<PlanningUnitDecPOMDPDiscrete>::GetReferred() ); 
        }
    JointPolicyDiscretePure* GetJPol() const 
        {   return _m_jpol; 
            //return( Referrer<JointPolicyDiscretePure>::GetReferred() ); 
        }

    /**Function used by CalculateV0Recursively. This recursively 
     * Calculates the expected payoff of the joint policy starting from 
     * state sI and joint observation history johI.*/
    double CalculateVsjohRecursivelyNotCached(Index sI, Index johI,Index stage);
    /**Function used by CalculateV0Recursively. This recursively 
     * Calculates the expected payoff of the joint policy starting from 
     * state sI and joint observation history johI.*/
    double CalculateVsjohRecursivelyCached(Index sI, Index johI, Index stage);
    double CalculateV0RecursivelyCached();
    double CalculateV0RecursivelyNotCached();

    protected:
    
    public:
    // Constructor, destructor and copy assignment.
    /// Constructor
    ValueFunctionDecPOMDPDiscrete(PlanningUnitDecPOMDPDiscrete& p , 
                                  JointPolicyDiscretePure& jp);
    /// Constructor
    ValueFunctionDecPOMDPDiscrete(PlanningUnitDecPOMDPDiscrete* p , 
                                  JointPolicyDiscretePure* jp);
    /// Copy constructor.
    ValueFunctionDecPOMDPDiscrete(const ValueFunctionDecPOMDPDiscrete& a);
    /// Destructor.
    ~ValueFunctionDecPOMDPDiscrete();

    /// Calculates the value function, which is stored and returns V(0).
    double CalculateV(bool cache = true);    

};


#endif /* !_VALUEFUNCTIONDECPOMDPDISCRETE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
