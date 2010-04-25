/**\file GeneralizedMAAStarPlanner.cpp
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
 * $Id: GeneralizedMAAStarPlanner.cpp 3603 2009-08-25 10:38:25Z mtjspaan $
 */

#include <float.h>
#include <limits.h>
#include "GeneralizedMAAStarPlanner.h"
#include "JointPolicyValuePair.h"
#include "QFunctionJAOHInterface.h"
#include "PartialPolicyPoolInterface.h"
#include "PolicyPoolJPolValPair.h"

#include "PartialJointPolicyPureVector.h"

#define DEBUG_GMAA_POLS 0

using namespace std;



//Default constructor
GeneralizedMAAStarPlanner::GeneralizedMAAStarPlanner(
    int verboseness,
    double slack) :
    _m_foundPolicy(0),
    _m_verboseness(verboseness),
    _m_slack(slack)
{
    _m_intermediateResultFile = 0;
    _m_saveIntermediateTiming=false;
    _m_nrJPolBGsEvaluated=0;
    _m_nrPoliciesToProcess=UINT_MAX;
    _m_bgCounter=0;
    _m_bgBaseFilename="";
}

//Destructor
GeneralizedMAAStarPlanner::~GeneralizedMAAStarPlanner()
{
    delete _m_foundPolicy;
}

//Copy assignment operator
GeneralizedMAAStarPlanner& GeneralizedMAAStarPlanner::operator= (const GeneralizedMAAStarPlanner& o)
{
    if (this == &o) return *this;   // Gracefully handle self assignment
    // Put the normal assignment duties here...
    throw("GeneralizedMAAStarPlanner::operator= not implemented");

    return *this;
}


/* this is the high-level pseudo-code for what happens:
    start with a horizon 0 joint policy - i.e. specifying 0 actions
    JPolValPool.push( <jpol,val=0.0> )    
    do
        ppi = <pol,val> = JPolValPool.GetNext()

        //poolOfNextPolicies     = {<pol,vals>} 
        //isLowerBound  = bool   - whether the vals are lower bounds to the 
        //                optimal value (i.e. value for the optimal policy)
        <poolOfNextPolicies, isLowerBound> = ConstructAndValuateNextPolicies(ppi)
        if(isLowerBound)
            Prune( JPolValPool, max(lowerBound) )

        poolOfNextPolicies = SelectPoliciesToProcessFurther(poolOfNextPolicies);
        JPolValPool.insert(poolOfNextPolicies)
      
    while !empty JPolValPool
*/
void GeneralizedMAAStarPlanner::Plan()    
{
    if( _m_foundPolicy != 0)
        delete _m_foundPolicy;

    StartTimer("GMAA::Plan");

    //stuff for timing (if used)
    tms ts_start;   //the time struct
    clock_t tck_start;  //ticks
    tck_start = times(&ts_start);
    //the intermediate timing stream
    ofstream & its = *_m_intermediateResultFile;

    //this counter maintains the maximum policy pool size.
    _m_maxJPolPoolSize = 0;
    double maxLB = -DBL_MAX;
    PartialJointPolicyDiscretePure * bestJPol = NewJPol();
    bestJPol->SetPastReward(-DBL_MAX);
#if DEBUG_GMAA_POLS    
    cout << "GMAA initialized with empty policy:"<<endl;
    bestJPol->Print();
#endif                 
    PartialPolicyPoolInterface * pp_p = NewPP(); 
    pp_p->Init( GetThisFromMostDerivedPU() ); //initialize with empty joint policy
    do
    {
        StartTimer("GMAA::Plan::iteration");
        if(_m_saveIntermediateTiming)
            SaveTimers(_m_intermediateTimingFilename);

        if(_m_verboseness >= 2) {
            cout << "\n---------------------------------------------------\n";
            cout << "-->>Start of new GMAA iteration, polpool size="<<
                pp_p->Size()<<"<<--"<<endl;
        }

        PartialPolicyPoolItemInterface* ppi = pp_p->Select();
        PartialJointPolicyDiscretePure * jpol_sel =  ppi->GetJPol();
        double v_sel = ppi->GetValue();
        size_t depth_sel = jpol_sel->GetDepth();
        if(_m_verboseness >= 3) {
            cout << "Select returned the following policy to expand:\n";
            ppi->GetJPol()->Print();
            cout << "of depth="<< depth_sel << " and heur. val="<<v_sel<<endl;
        }
        
        if( (v_sel + _m_slack) < maxLB) //the highest upperbound < the best lower
        {
            //TODO: 
            //  1)if JPolValPool is no priority queue, this should be changed.
            //  2)this is only necessary, because PRUNE (see todo below) is nyi
            if(_m_verboseness >= 0)
                cout<<"highest upper < best found lower bound, stopping\n";
            break;
        }

        //poolOfNextPolicies     = {<pol,vals>} 
        //isLowerBound  = bool   - whether the vals are lower bounds to the 
        //                optimal value (i.e. value for the optimal policy)
        //<poolOfNextPolicies,isLowerBound>=ConstructAndValuateNextPolicies(ppi)

        PartialPolicyPoolInterface * poolOfNextPolicies = NewPP();
        bool are_LBs = ConstructAndValuateNextPolicies(ppi, poolOfNextPolicies);

        //Clean up ppi
        if(pp_p->Size() > 0) //should always be true
        {
            pp_p->Pop();
            delete ppi;
        }
        else //should not happen
            throw E("GeneralizedMAAStarPlanner.cpp:policy pool empty? - should not happen?");

#if DEBUG_GMAA4        
        if(DEBUG_GMAA4){
            cout << "\n>>>The next policies found, poolOfNextPolicies:"<<endl;
            PartialPolicyPoolInterface* pp_copy = NewPP();
            *pp_copy = *poolOfNextPolicies;
            while(! pp_copy->Empty())
            {
                PartialPolicyPoolItemInterface* it = pp_copy->Select();
                it->Print();
                cout << endl;
                pp_copy->Pop();
            }
        }
#endif        

        //if(isLowerBound)
        //    Prune( JPolValPool, max(lowerBound) )
        if(are_LBs && poolOfNextPolicies->Size() > 0)
        {
            PartialPolicyPoolItemInterface* bestRanked_ppi = poolOfNextPolicies->
                GetBestRanked();
            poolOfNextPolicies->PopBestRanked();
            double bestNextVal = bestRanked_ppi->GetValue();
            if(bestNextVal > maxLB) //new best lowerbound (and policy) found
            {
                maxLB = bestNextVal;
                *bestJPol = *(bestRanked_ppi->GetJPol());
                if(_m_verboseness >= 2) {
                    cout << "new bestJPol (and max. lowerbound) found!" << endl;
                    cout << "Its value v="
                         << bestNextVal <<" - "
                         << bestRanked_ppi->GetJPol()->SoftPrintBrief() << endl;
                }
                if(_m_verboseness >= 3) 
                    cout << "new bestJPol->SoftPrint():"<<bestJPol->SoftPrint();

                //if we maintain the internal timings...
                if(_m_intermediateResultFile != 0)
                {
                    tms ts_cur;
                    clock_t tck_cur;
                    tck_cur = times(&ts_cur);
                    clock_t diff = tck_cur - tck_start;
                    its << diff << "\t" <<  maxLB << endl;
                }
                // prune JPolValPool
                pp_p->Prune(maxLB - _m_slack );
            }
            delete bestRanked_ppi;

        }
        SelectPoliciesToProcessFurther(poolOfNextPolicies, are_LBs, maxLB - _m_slack);
        pp_p->Union(poolOfNextPolicies);

        delete poolOfNextPolicies;

        if( _m_maxJPolPoolSize < pp_p->Size())
            _m_maxJPolPoolSize = pp_p->Size();
        
        StopTimer("GMAA::Plan::iteration");
        if(_m_verboseness >= 2) { 
            cout << "\nGMAA::Plan::iteration ending, best policy found so far:";
            cout << endl << bestJPol->SoftPrintBrief()  <<endl;
            if(_m_verboseness >= 3)  
                cout << endl << bestJPol->SoftPrint()  <<endl;
        }

    } 
    while(! pp_p->Empty() ); //<- end do...while
    //we don't want to do any conversions here... takes (sometimes too much)
    //time...
    _m_foundPolicy=bestJPol;  //->ToJointPolicyPureVector());


    _m_expectedRewardFoundPolicy=maxLB;
    if(_m_verboseness >= 1) {
        cout << "\nGMAA::Plan ending, best policy found: ";
        cout << bestJPol->SoftPrintBrief() << " = " <<endl;
        if(_m_verboseness >= 3) 
            cout << _m_foundPolicy->SoftPrint() << endl;
        cout << endl;
#if 0
    JointPolicyPureVector* jppv = _m_foundPolicy->ToJointPolicyPureVector();
    jppv->Print();
#endif                 
    }
    if(_m_verboseness >= 2)    
        cout << "\n\n ";
    if(_m_verboseness >= 0)    
        cout << "GMAA::Plan GMAA ENDED"<<endl;
    if(_m_verboseness >= 2)    
        cout << "\n\n ";

    delete pp_p;
    
    StopTimer("GMAA::Plan");
}

void 
GeneralizedMAAStarPlanner::SelectKBestPoliciesToProcessFurther(
        PartialPolicyPoolInterface* poolOfNextPolicies, bool are_LBs,
            double bestLB, size_t k)
{
    if(are_LBs)
    {
        //if all policies are full policies, we don't return any
        //of them (these need not be expanded further)
        while(!poolOfNextPolicies->Empty())
            poolOfNextPolicies->Pop();
        return;
    }
    PartialPolicyPoolInterface * pp_new = NewPP();
    
    size_t nr_done = 0;
    while(poolOfNextPolicies->Size() > 0 ) // && nr_done < k) 
    {
        PartialPolicyPoolItemInterface* best_ppi = poolOfNextPolicies->GetBestRanked();
        poolOfNextPolicies->PopBestRanked();
        if(nr_done >= k || best_ppi->GetValue() < bestLB)
        {
            //we do not want this policy, so discard it:
            delete best_ppi;
        }
        else
        {
            //we do want this policy, so store it:
            pp_new->Insert(best_ppi);
        }
        nr_done++;
    }
    //done: - free the memory of the policies in poolOfNextPolicies
    //that we will not consider further!

    //copy by value: //TODO check if this is what we want?
                     // separte input/output arguments might be better?
    *poolOfNextPolicies = *pp_new;
    //remove elements from pp_new before delete! (otherwise they will be deleted    //with them) and we get a segfault later on...
    while(pp_new->Size() > 0)
        pp_new->Pop();
    
    delete pp_new;

}

void GeneralizedMAAStarPlanner::Prune(PartialPolicyPoolInterface& pp, size_t k)
{
    /**\todo TODO this should retain the best k policies? if so, use 
     *SelectKBestPoliciesToProcessFurther
     *or let that function refer here...?
     */
    if(pp.Size()<=k)
        return;

    PartialPolicyPoolInterface * ppPruned = NewPP();

    while(ppPruned->Size()<k)
    {
        ppPruned->Insert(pp.GetBestRanked());
        pp.PopBestRanked();
    }

    //delete the rest which we will not use further...
    while(pp.Size()>0)
    {
        delete pp.Select();
    }
    pp=*ppPruned;
}

void GeneralizedMAAStarPlanner::SetIntermediateTimingFilename(string filename)
{
    _m_saveIntermediateTiming=true;
    _m_intermediateTimingFilename=filename;
}

void GeneralizedMAAStarPlanner::SetVerbose(int verbose)
{
    _m_verboseness = verbose;
}        

JointPolicy* GeneralizedMAAStarPlanner::GetJointPolicy()
{ return(_m_foundPolicy); }
JointPolicyDiscrete* GeneralizedMAAStarPlanner::GetJointPolicyDiscrete()
{ return(_m_foundPolicy); }
JointPolicyDiscretePure* GeneralizedMAAStarPlanner::GetJointPolicyDiscretePure()
{ return(_m_foundPolicy); }
