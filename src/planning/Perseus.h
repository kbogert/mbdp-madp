/**\file Perseus.h
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
 * $Id: Perseus.h 3050 2008-12-10 17:02:10Z faolieho $
 */

/* Only include this header file once. */
#ifndef _PERSEUS_H_
#define _PERSEUS_H_ 1

/* the include directives */
#include <iostream>
#include <iomanip>
#include "Globals.h"

#include "BeliefValue.h"
#include "AlphaVectorPlanning.h"
#include "directories.h"
#include "PlanningUnitDecPOMDPDiscrete.h"
#include "QAVParameters.h"
#include "argumentHandlers.h"

class BeliefSetNonStationary;

/**Perseus contains basic functionality for the Perseus planner. */
class Perseus :
    virtual public AlphaVectorPlanning
{
private:

    const PlanningUnitDecPOMDPDiscrete *_m_pu;

    int _m_minimumNumberOfIterations;
    int _m_maximumNumberOfIterations;

    int _m_verbose;

    bool _m_initializeWithImmediateReward;
    bool _m_initializeWithZero;

    size_t GetSize(const ValueFunctionPOMDPDiscrete &V) const
        { return(V.size()); }
    size_t GetSize(const QFunctionsDiscrete &Q) const
        {
            size_t nr=0;
            for(QFDcit i=Q.begin();i!=Q.end();++i)
                nr+=i->size();
            return(nr);
        }
    size_t GetSize(const QFunctionsDiscreteNonStationary &Q) const
        {
            size_t nr=0;
            for(QFDNScit i=Q.begin();i!=Q.end();++i)
                nr+=GetSize(*i);
            return(nr);
        }

protected:

    double _m_bestValue;

    /// Whether or not the belief set has been set.
    bool _m_beliefsInitialized;

    std::string _m_identification, _m_valueFunctionFilename, _m_resultsFilename;

    ValueFunctionPOMDPDiscrete GetInitialValueFunction() const;

    QFunctionsDiscrete GetInitialQFunctions() const;

    QFunctionsDiscreteNonStationary GetInitialNonStationaryQFunctions() const;

    bool _m_storeIntermediateValueFunctions;

    bool _m_storeTimings;

    bool _m_computeVectorForEachBelief;

    bool _m_dryrun;

    template <class VF>
    void PlanStartOfIteration(int iter,
                              const std::vector<double> &VB,
                              const VF &V) const
        {
            double x=0;
            for(unsigned int i=0;i!=VB.size();i++)
                x+=VB[i];
            JointBeliefInterface* jb0 = _m_pu->GetNewJointBeliefFromISD();
            if(GetVerbose() >= -1)
                std::cout 
                    << GetIdentification() << ": iteration " << std::setw(6)
                    << iter 
                    << " |V| " << GetSize(V)
                    << " sumV/nrB " << x/VB.size() << " V0 " 
                    << BeliefValue::GetValue( *jb0, V)
                    << " (best " << _m_bestValue << ")" << std::endl;
            delete jb0;

            if(_m_storeIntermediateValueFunctions && !_m_dryrun)
            {
                std::string resultsDir=directories::MADPGetResultsDir("POMDP",
                                                                 _m_pu);
                std::stringstream valueFunctionFilename;
                valueFunctionFilename << resultsDir << "/intermediate/"
                                      << GetIdentification()
                                      << "ValueFunction_h"
                                      << _m_pu->GetHorizon() << "_iter_" 
                                      << std::setw(4) << std::setfill('0')
                                      << iter;
                AlphaVectorPlanning::
                    ExportValueFunction(valueFunctionFilename.str(),V);
            }
        }
    
    template <class VF>
    void PlanEndOfIteration(const VF &V)
        {
            PlanEndOfIteration();
            
            JointBeliefInterface* jb0 = _m_pu->GetNewJointBeliefFromISD();
            double value=BeliefValue::GetValue(*jb0, V);
            delete jb0;

            if(value>_m_bestValue)
            {
                _m_bestValue=value;
                StoreValueFunction(V);
                if(!_m_dryrun)
                    ExportValueFunction(_m_valueFunctionFilename);
            }
        }

    void PlanEndOfIteration() const;

    /// Prints the maximum immediate reward present in the belief set.
    void PrintMaxRewardInBeliefSet() const;

    void PlanLeadIn();

    void PlanLeadOut();

    GaoVectorSet BackupStageLeadIn(const ValueFunctionPOMDPDiscrete &V) const;

    void BackupStageLeadOut(GaoVectorSet Gao) const;

    void UpdateValueFunctionName();

    virtual std::vector<double> GetImmediateRewardBeliefSet() const = 0;

    virtual void InitializeBeliefs(int nrB, bool uniquify) = 0;

    virtual void StoreValueFunction(const ValueFunctionPOMDPDiscrete &V);
    virtual void StoreValueFunction(const QFunctionsDiscrete &Q);
    virtual void StoreValueFunction(const QFunctionsDiscreteNonStationary &Q);
    
public:
    // Constructor, destructor and copy assignment.
    /// (default) Constructor
    Perseus(const PlanningUnitDecPOMDPDiscrete& pu);
    /// Destructor.
    virtual ~Perseus();

    void Initialize();

    /** Exports the computed value function in a simple text format
     * used by Tony Cassandra for .alpha files. */
    virtual void ExportValueFunction(const std::string &filename) const = 0;

    virtual double GetQ(const JointBeliefInterface &b, Index jaI) const = 0;

    virtual double GetQ(const JointBeliefInterface &b, Index jaI,
                        int &betaMaxI) const = 0;
    
    virtual double GetQ(const JointBeliefInterface &b, Index t,
                        Index jaI) const = 0;

    virtual double GetQ(const JointBeliefInterface &b, Index t, Index jaI,
                        int &betaMaxI) const = 0;

    virtual void SetValueFunction(const std::string &filename) = 0;

    /// Sample an index of a belief in the set which has not been improved.
    int SampleNotImprovedBeliefIndex(std::vector<bool> stillNeedToBeImproved,
                                     int nrNotImproved) const;

    bool CheckConvergence(const std::vector<double> &VB,
                          const std::vector<double> &VBnew,
                          int iter) const;

    virtual void Plan() = 0;

    void SetSaveIntermediateValueFunctions(bool save)
        { _m_storeIntermediateValueFunctions=save; }

    void SetSaveTimings(bool save)
        { _m_storeTimings=save; }

    void SetIdentification(std::string identification);
    
    void SetResultsFilename(std::string filename);

    std::string GetIdentification() const { return(_m_identification); }

    static std::string BackupTypeToString(const QAVParameters &params);

    static QAVParameters ProcessArguments(const ArgumentHandlers::Arguments
                                          &args);

    void SetComputeVectorForEachBelief(bool compute)
        { _m_computeVectorForEachBelief = compute; }

    void SetMinimumNumberOfIterations(int nr)
        { _m_minimumNumberOfIterations=nr; }
    void SetMaximumNumberOfIterations(int nr)
        { _m_maximumNumberOfIterations=nr; }

    void SetInitializeWithImmediateReward(bool initReward)
        { _m_initializeWithImmediateReward=initReward; }

    void SetInitializeWithZero(bool initZero)
        { _m_initializeWithZero=initZero; }

    void SetDryrun(bool dryrun)
        { _m_dryrun=dryrun; }
    void SetVerbose(int verbose) { _m_verbose=verbose; }
    int GetVerbose() const { return(_m_verbose); }

};

#endif /* !_PERSEUS_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
