/**\file QFunctionJAOHTree.h
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
 * $Id: QFunctionJAOHTree.h 3604 2009-08-25 10:52:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _QFUNCTIONJOINTHISTORYTREE_H_
#define _QFUNCTIONJOINTHISTORYTREE_H_ 1

/* the include directives */
#include "Globals.h"
#include "QFunctionJAOH.h"

/** \brief QFunctionJAOHTree is represents
 * QFunctionJAOH which store Qvalues in a tree.  */
class QFunctionJAOHTree : public QFunctionJAOH
{
private:    

    bool _m_initialized; 
    
    void Initialize();
    void DeInitialize();

    /// Recursively compute Qvalues based on a particular JOAHTree.
    /** Function that should be reimplemented by derived classes that
     * use ComputeQ() (e.g., QPOMDP, QBG). */
#if QFunctionJAOH_useIndices
    virtual double ComputeRecursively(size_t time_step, 
                                      LIndex jaohI, 
                                      Index lastJAI) = 0;
#else
    virtual double ComputeRecursively(size_t time_step, 
                                      JointActionObservationHistoryTree* jaoht, 
                                      Index lastJAI) = 0;
#endif
    
    /// This function starts the recursive computing of Qvalues.
    /** A lot of Q-value functions are computed in a similar, recursive way.
     * (In particular QPOMDP and QBG)
     *
     * This function starts this calculation.
     *
     * Classes that use this function have to define (reimplement) 
     * ComputeRecursively.
     * */
    void ComputeQ();
    

protected:
    
public:
    // Constructor, destructor and copy assignment.
    /// Default constructor, requires a planning unit.
    QFunctionJAOHTree(const PlanningUnitDecPOMDPDiscrete &pu);

    /// Destructor.
    virtual ~QFunctionJAOHTree();

    //get (data) funct        
    /**Return the Qvalue for JointActionObservationHistory Index jaohI and
     * JointAction index jaI.*/
    double GetQ(Index jaohI, Index jaI) const
        {   return (_m_QValues(jaohI,jaI)); }
    
    /**Compute the heuristic. (after associated with an initialized 
     * PlanningUnitDecPOMDPDiscrete)*/
    void Compute();

    void SetPU(const PlanningUnitDecPOMDPDiscrete& pu);

    void Load(std::string filename);
    void Save(std::string filename) const;

};


#endif /* !_QFUNCTIONJOINTHISTORYTREE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
