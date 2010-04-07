/**\file MultiAgentDecisionProcessDiscrete.cpp
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
 * $Id: MultiAgentDecisionProcessDiscrete.cpp 3853 2009-11-26 16:38:11Z mtjspaan $
 */

#include "MultiAgentDecisionProcessDiscrete.h"    
#include "ObservationModelMapping.h"    
#include "ObservationModelMappingSparse.h"    
#include "TransitionModelMapping.h"    
#include "TransitionModelMappingSparse.h"    
#include <stdio.h>

#include "TGet.h"
#include "OGet.h"


using namespace std;

#define DEBUG_MADPD 0

MultiAgentDecisionProcessDiscrete::MultiAgentDecisionProcessDiscrete() 
{
    _m_initialized = false;
    _m_sparse = false;
    _m_p_tModel = 0;
    _m_p_oModel = 0;
}
MultiAgentDecisionProcessDiscrete::MultiAgentDecisionProcessDiscrete( 
    string name, string descr, string pf) :
    MultiAgentDecisionProcess(name, descr, pf),
    MADPComponentDiscreteStates(),
    MADPComponentDiscreteActions(),
    MADPComponentDiscreteObservations()
{
    _m_initialized = false;
    _m_sparse = false;
    _m_p_tModel = 0;
    _m_p_oModel = 0;
}


MultiAgentDecisionProcessDiscrete::MultiAgentDecisionProcessDiscrete(int 
    nrAgents, int nrS, string name, string descr, string pf) :
    MultiAgentDecisionProcess(nrAgents,name, descr, pf),
    MADPComponentDiscreteStates(nrS),
    MADPComponentDiscreteActions(),
    MADPComponentDiscreteObservations()
{
    _m_initialized = false;
    _m_sparse = false;
    _m_p_tModel = 0;
    _m_p_oModel = 0;
}

MultiAgentDecisionProcessDiscrete::~MultiAgentDecisionProcessDiscrete()
{
    if(DEBUG_MADPD)
        cout << "deleting MultiAgentDecisionProcessDiscrete "
             << "(deleting T and O model )"<<endl;
    delete (_m_p_tModel);
    delete (_m_p_oModel);
}

void MultiAgentDecisionProcessDiscrete::CreateNewTransitionModel()
{
    if(_m_initialized)
        delete(_m_p_tModel);

    if(_m_sparse)
        _m_p_tModel=new TransitionModelMappingSparse(GetNrStates(),
                                                     GetNrJointActions());
    else
        _m_p_tModel=new TransitionModelMapping(GetNrStates(),
                                               GetNrJointActions());

}

TGet* MultiAgentDecisionProcessDiscrete::GetTGet() const
{ 
    if(_m_sparse)
        return new TGet_TransitionModelMappingSparse(
                ((TransitionModelMappingSparse*)_m_p_tModel)  ); 
    else
        return new TGet_TransitionModelMapping(
                ((TransitionModelMapping*)_m_p_tModel)  );
}

OGet* MultiAgentDecisionProcessDiscrete::GetOGet() const
{ 
    if(_m_sparse)
        return new OGet_ObservationModelMappingSparse(
                ((ObservationModelMappingSparse*)_m_p_oModel)  ); 
    else
        return new OGet_ObservationModelMapping(
                ((ObservationModelMapping*)_m_p_oModel)  );
}

void MultiAgentDecisionProcessDiscrete::CreateNewObservationModel()
{
    if(_m_initialized)
        delete(_m_p_oModel);

    if(_m_sparse)
        _m_p_oModel = new 
            ObservationModelMappingSparse(GetNrStates(), 
                                          GetNrJointActions(),
                                          GetNrJointObservations());
    else
        _m_p_oModel = new ObservationModelMapping(GetNrStates(),
                                                  GetNrJointActions(), 
                                                  GetNrJointObservations());
}


bool MultiAgentDecisionProcessDiscrete::SetInitialized(bool b)
{

    if(b == true)
    {
        if(     !MADPComponentDiscreteActions::SetInitialized(b)
            ||  !MADPComponentDiscreteObservations::SetInitialized(b)
            ||  !MADPComponentDiscreteStates::SetInitialized(b) )
        {
            //error in initialization of sub-components.
            _m_initialized = false;
            return(false);
        }
        //check if transition- and observation model are present...
        if(_m_p_tModel == 0)
        {
            throw E("MultiAgentDecisionProcessDiscrete::SetInitialized() -initializing a MultiAgentDecisionProcessDiscrete which has no transition model! - make sure that CreateNewTransitionModel() has been called before SetInitialized()");
        }
        if(_m_p_oModel == 0)
        {
            throw E("MultiAgentDecisionProcessDiscrete::SetInitialized() -initializing a MultiAgentDecisionProcessDiscrete which has no observation model! - make sure that CreateNewObservationModel() has been called before SetInitialized()");

        }

        if( SanityCheck() )
        {
            _m_initialized = true;
            return(true);
        }
        else
        {
            _m_initialized = false;
            return(false);
        }
    }
    else
    {
        MADPComponentDiscreteActions::SetInitialized(b);
        MADPComponentDiscreteObservations::SetInitialized(b);
        MADPComponentDiscreteStates::SetInitialized(b); 
        _m_initialized = false;
        return(true);
    }

}


string MultiAgentDecisionProcessDiscrete::SoftPrint() const
{
    stringstream ss;

    ss << MultiAgentDecisionProcess::SoftPrint();
    ss << MADPComponentDiscreteStates::SoftPrint();
    ss << MADPComponentDiscreteActions::SoftPrint();
    ss << MADPComponentDiscreteObservations::SoftPrint();   
   
    if(_m_initialized)
    {
        ss << "Transition model: " << endl;
        ss << _m_p_tModel->SoftPrint();
        ss << "Observation model: " << endl;
        ss << _m_p_oModel->SoftPrint();
    }
    return(ss.str());
}

bool MultiAgentDecisionProcessDiscrete::SanityCheck(void)
{
    size_t nrJA=GetNrJointActions(),
          nrS=GetNrStates(),
          nrJO=GetNrJointObservations();

    double sum,p;
    bool sane=true;

    // check transition model
    for(Index a=0;a<nrJA;a++)
    {
        for(Index from=0;from<nrS;from++)
        {
            sum=0.0;
            for(Index to=0;to<nrS;to++)
            {
                p=GetTransitionProbability(from,a,to);
                if(p<0)
                {
                    sane=false;
                    stringstream ss;
                    ss << "MultiAgentDecisionProcessDiscrete::SanityCheck "<<
                        "failed: negative probability " << p << 
                        " for p(s'|s,a)==p(" << GetStateName(to) << "|" << 
                        GetStateName(from)<<"," << GetJointActionName(a) << ")";
                    throw E(ss);
                }
                if(_isnan(p))
                {
                    sane=false;
                    stringstream ss;
                    ss << "MultiAgentDecisionProcessDiscrete::SanityCheck "<<
                        "failed: NaN " << 
                        " for p(s'|s,a)==p(" << GetStateName(to) << "|" << 
                        GetStateName(from)<<"," << GetJointActionName(a) << ")";
                    throw E(ss);
                }
                sum+=p;
            }
            if((sum>(1.0 + PROB_PRECISION/2)) ||
               (sum < (1.0 - PROB_PRECISION/2)))
            {
                sane=false;
                stringstream ss;
                //string float_str;
                char float_str[30];
                sprintf(float_str, "%10.10f", sum);
                ss << "MultiAgentDecisionProcessDiscrete::SanityCheck failed:"<<
                   " transition does not sum to 1 but to:\n" << float_str << 
                   "\n for (s,a)==(" << GetStateName(from) << "[" << from << 
                   "]," << GetJointActionName(a) << "[" << a << "])";
                throw E(ss);
            }
        }
    }

    // check observation model
    for(Index a=0;a<nrJA;a++)
    {
        for(Index to=0;to<nrS;to++)
        {
            sum=0;
            for(Index o=0;o<nrJO;o++)
            {
                p=GetObservationProbability(a,to,o);
                if(p<0)
                {
                    stringstream ss;
                    ss << "MultiAgentDecisionProcessDiscrete::SanityCheck "
                       << "failed: negative probability " << p 
                       << " for p(o|s',a)==p(" 
                       << GetJointObservationName(o)
                       << "|" << GetStateName(to) 
                       << "," 
                       << GetJointActionName(a) 
                       << ")";
                    throw E(ss);
                }
                if(_isnan(p))
                {
                    stringstream ss;
                    ss << "MultiAgentDecisionProcessDiscrete::SanityCheck "
                       << "failed: NaN for p(o|s',a)==p(" 
                       << GetJointObservationName(o)
                       << "|" << GetStateName(to) 
                       << "," 
                       << GetJointActionName(a) 
                       << ")";
                    throw E(ss);
                }
                sum+=p;
            }
            if((sum>(1.0 + PROB_PRECISION/2)) ||
               (sum < (1.0 - PROB_PRECISION/2)))
            {
                char float_str[30];
                sprintf(float_str, "%10.10f", sum);
                sane=false;
                stringstream ss;
                ss << "MultiAgentDecisionProcessDiscrete::SanityCheck "
                   << "failed: observation does not sum to 1 but to \n" 
                   << float_str << "\n for (s',a)==(" << GetStateName(to) 
                   << "[" << to << "],"
                   << GetJointActionName(a) 
                   << "[" << a << "])";
                throw E(ss);
            }
        }
    }

    return(sane);
}

void MultiAgentDecisionProcessDiscrete::SetSparse(bool sparse)
{
    _m_sparse=sparse;
}
