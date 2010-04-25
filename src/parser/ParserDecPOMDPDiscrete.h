/**\file ParserDecPOMDPDiscrete.h
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
 * $Id: ParserDecPOMDPDiscrete.h 2945 2008-10-25 11:14:45Z mtjspaan $
 */

#ifndef _PARSERDECPOMDPDISCRETE_H_
#define _PARSERDECPOMDPDISCRETE_H_ 1

/* the include directives */
#include <iostream>
#include <fstream>
#include "Globals.h"
#include "DecPOMDPDiscrete.h"
#include "Referrer.h"
#include "EParse.h"

#include <boost/spirit/core.hpp>
#include <boost/spirit/iterator/file_iterator.hpp>
#include <boost/spirit/iterator/position_iterator.hpp>

#include "CommentOrBlankParser.h"            
#include "ParserInterface.h"


using namespace boost::spirit;

/* constants */
//use subgrammars (or not?)
#define SUBGRAMMAR 0

//General parsing debug informations
#define DEBUG_PARSE 0

//debugging the 'comment' parser:
#define DEBUG_COMPARS 0
//debugging the 'comment or blank parser' :
#define DEBUG_COBP 0

// the 'any' individual action to denote the wildcard '*'
#define ANY_INDEX -1

//namespace{
/**Outputs the file_position structure info (gotten from 
 * postion_iterator::get_position() ). */
std::ostream& operator<<(std::ostream& out, file_position const& lc);


//}

/**ParserDecPOMDPDiscrete is a parser for DecPOMDPDiscrete. */
class ParserDecPOMDPDiscrete :
    public Referrer<DecPOMDPDiscrete>,
    public ParserInterface
{    
    typedef char                    char_t;
    typedef file_iterator<char_t>   iterator_t_fi;
    typedef position_iterator<iterator_t_fi>  iterator_t;
    typedef scanner<iterator_t>     scanner_t;
    typedef rule<scanner_t>         rule_t;

    //used to now what has been parsed:
    enum parsed_t { INT, DOUBLE, UINT, STRING, ASTERICK, UNIFORM, IDENTITY };
    private:
        struct Initialize
        {
            ParserDecPOMDPDiscrete* _m_po;
            Initialize (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const
            {
                _m_po->_m_first = &str;
            }
        };
        
        struct DebugOutputNoParsed 
        {
            std::string s;
            DebugOutputNoParsed (std::string s2){s = s2;}
            void operator()(iterator_t str, iterator_t end) const;            
            void operator()(const unsigned int&) const;            
            void operator()(const double &) const;            
        };
        struct DebugOutput
        {
            std::string s;
            DebugOutput (std::string s2){s = s2;}
            void operator()(iterator_t str, iterator_t end) const;            
            void operator()(const int&) const;            
            void operator()(const unsigned int&) const;            
            void operator()(const double&) const;            
        };
        struct StoreLastParsedElement
        {
            ParserDecPOMDPDiscrete* _m_po;
            StoreLastParsedElement(ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(const int i) const;            
            void operator()(const unsigned int i) const;            
            void operator()(const double f) const;            
            void operator()(iterator_t str, iterator_t end) const;
        };
        struct SetLastParsedType
        {
            ParserDecPOMDPDiscrete* _m_po;
            parsed_t _m_lastParsedType;
            SetLastParsedType (ParserDecPOMDPDiscrete* po, parsed_t lpt)
            {
                _m_po = po;
                _m_lastParsedType = lpt;
            }
            void operator()(iterator_t str, iterator_t end) const
            {
                _m_po->_m_lp_type = _m_lastParsedType;
            }
        };

        struct NYI//Not Yet Implemented
        {
            std::string msg;
            NYI(std::string s){msg = s;}
            void operator()(iterator_t str, iterator_t end) const
            {
                file_position fp =  str.get_position();
                std::stringstream ermsg;
                ermsg << "sorry, \""<< msg <<"\" is not yet implemented."
                    << std::endl << "(at " << fp << ")"<<std::endl;
                throw E(ermsg.str().c_str());
            }
        };

/*
        struct XXX
        {
            ParserDecPOMDPDiscrete* _m_po;
            XXX (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const
            {
            }
        };
*/
        struct SetAgentIndex
        {
            ParserDecPOMDPDiscrete* _m_po;
            Index _m_temp_stor;
            SetAgentIndex (ParserDecPOMDPDiscrete* po, Index AI)
            {_m_po = po; _m_temp_stor = AI; }
            void operator()(iterator_t str, iterator_t end) const
            {
                _m_po->_m_curAI = _m_temp_stor;
            }
        };        
        struct SetNextAgentIndex
        {
            ParserDecPOMDPDiscrete* _m_po;
            SetNextAgentIndex (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const
            {
                if(_m_po->_m_curAI < _m_po->_m_nrA)
                    _m_po->_m_curAI++;
                else
                    std::cout << "SetNextAgentIndex - ERROR: current agent index ("<<
                               _m_po->_m_curAI<<") out of bounds (number of agents="<<
                        _m_po->_m_nrA<<")"<<std::endl;            
            }
        };

        struct NextRowOfMatrix
        {
            ParserDecPOMDPDiscrete* _m_po;
            NextRowOfMatrix (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const
            {
                //TODO:check whether correct nr of row elements parsed...
                _m_po->_m_curMatrix.push_back( std::vector<double>() );
            }
        };
        struct NextFloatOfRow
        {
            ParserDecPOMDPDiscrete* _m_po;
            NextFloatOfRow (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const
            {
                if(_m_po->_m_lp_type != DOUBLE)
                {
                    std::cout <<"NextFloatOfRow - ERROR parsing probabilities, which"
                        <<" means that doubles are expected, however last found"
                        <<" type is #"<<_m_po->_m_lp_type<<std::endl;
                }
                if(DEBUG_PARSE){//DEBUG
                    Index s =_m_po->_m_curMatrix.size();
                    std::cout <<" _m_po->_m_curMatrix.size()= " << s <<std::endl;
                    if(s>0)
                    std::cout <<" _m_po->_m_curMatrix.back().size()= " <<
                        _m_po->_m_curMatrix.back().size()<<std::endl;
                }
                size_t s =_m_po->_m_curMatrix.size();
                if(s > 0)
                {
                    double d = _m_po->_m_lp_double;
                    //_m_curMatrix.back() isa  vector<double>
                    _m_po->_m_curMatrix.back().push_back(d);
                    _m_po->_m_matrixModified = true;
                }
                else
                    std::cout << "NextFloatOfRow - ERROR _m_curMatrix contains no "<<
                        "elements (i.e. there are no rows to add to...).";

                if(DEBUG_PARSE){//DEBUG
                    size_t s =_m_po->_m_curMatrix.size();
                    std::cout <<" _m_po->_m_curMatrix.size()= " << s <<std::endl;
                    if(s>0)
                    std::cout <<" _m_po->_m_curMatrix.back().size()= " <<
                        _m_po->_m_curMatrix.back().size()<<std::endl;
                }

            }
        };        
        struct NextStringOfIdentList
        {
            ParserDecPOMDPDiscrete* _m_po;
            NextStringOfIdentList (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const
            {
                _m_po->_m_curIdentList.push_back(std::string(str,end));
                _m_po->_m_identListModified = true;

            }
        };
        struct SetNrStates
        {
            ParserDecPOMDPDiscrete* _m_po;
            size_t _m_target;
        bool _m_haveTarget;
            SetNrStates (ParserDecPOMDPDiscrete* po){
                _m_po = po;
                _m_target = 0;
        _m_haveTarget = false;
            }
            SetNrStates (ParserDecPOMDPDiscrete* po, size_t i){
                _m_po = po;
                _m_target = i;
        _m_haveTarget = true;
            }
            void operator()(const size_t& i) const
            {
                if(_m_haveTarget)
                    _m_po->GetReferred()->SetNrStates(_m_target);
                else
                    _m_po->GetReferred()->SetNrStates( i );

            }
        void operator()(iterator_t str, iterator_t end) const
            {
                if(_m_haveTarget)
                    _m_po->GetReferred()->SetNrStates(_m_target);
                else if(_m_po->_m_lp_type == UINT)// || _m_lp_type
                    _m_po->GetReferred()->SetNrStates(_m_po->_m_lp_uint);
                else
                    throw E("SetNrStates: no target value set and last parsed data type != UINT...");
            }
        };
        //this processes the start state specification in case of a specified
        //probability vector and in case of the keyword uniform.
        struct StartStateRowProbs
        {
            ParserDecPOMDPDiscrete* _m_po;
            StartStateRowProbs (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const            
            {
                if(_m_po->_m_lp_type == UNIFORM)
                {
                    _m_po->GetReferred()->SetUniformISD();
                    return;
                }

                //check size - it should be a row matrix...
                if( !_m_po->IsRowMatrixLP() )        
                    throw E("StartStateRowProbs: _m_po->_m_curMatrix should \
                           be a row vector!");
                if(_m_po->_m_curMatrix[0].size() != _m_po->GetReferred()->
                        GetNrStates())
                {
                    std::string err = "StartStateRowProbs: _m_po->_m_curMatrix";
                    err += " [0] should contain NrStates(="; 
                    std::stringstream ss;
                    ss << "StartStateRowProbs: _m_po->_m_curMatrix[0] " << 
                        "should contain NrStates(=" << _m_po->GetReferred()->
                        GetNrStates() << ") entries! (not "<<
                        _m_po->_m_curMatrix[0].size()<<")\n";

                    throw E( ss.str().c_str() );
                }

                _m_po->GetReferred()->SetISD(_m_po->_m_curMatrix[0]);
            }
        };
        //this adds states to the start state list - the first stage in 
        //processing the other ways of specifying the start state distribution.
        struct AddStartState
        {
            ParserDecPOMDPDiscrete* _m_po;
            AddStartState (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const
            {
                if(_m_po->_m_lp_type != STRING)
                {
                    std::stringstream ss; ss << "SetStartState::operator()(iterator_t str, iterator_t end) - expected a string as last parsed type! (at"<<str.get_position() <<")"<<std::endl;
                    throw E(ss);
                }
                try
                {
                    Index sI = _m_po->GetReferred()->GetStateIndexByName(
                            _m_po->_m_lp_string);
                    _m_po->_m_startStateListSI.push_back(sI);
                }
                catch(E e)
                {
                    std::stringstream ss; ss << e.SoftPrint() << "(at"<<
                        str.get_position() <<")"<<std::endl;
                    throw E(ss);
                }
            };
            void operator()(const unsigned int& i) const
            {
                if(_m_po->_m_lp_type != UINT)
                {
                    std::stringstream ss; ss << "SetStartState::operator()(const unsigned int i&) - expected a UINT as last parsed type!  (at"<< _m_po->_m_first->get_position() <<")"<<std::endl;
                    throw E(ss);
                }
                _m_po->_m_startStateListSI.push_back( _m_po->_m_lp_uint);
            }
        };
        //this functor specified that the states in the start state list should
        //be excluded, not included.
        struct StartStateExludes
        {
            ParserDecPOMDPDiscrete* _m_po;
            StartStateExludes (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const
            {
                _m_po->_m_startStateListExclude = true;
            }
        };
        struct ProcessStartStateList
        {
            ParserDecPOMDPDiscrete* _m_po;
            ProcessStartStateList (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(const unsigned int& i) const
            {
                ProcessList();
            }
            void operator()(iterator_t str, iterator_t end) const
            {
                ProcessList();
            }
            void ProcessList() const
            {
                size_t nrS = _m_po->GetReferred()->GetNrStates();
                size_t listSize = _m_po->_m_startStateListSI.size();
                size_t nrIncS = (_m_po->_m_startStateListExclude)? nrS - listSize:
                    listSize;
                double u_prob = 1.0 / nrIncS;
                
                std::vector<double> init_probs;
                if(!_m_po->_m_startStateListExclude)
                    //elems in list get uniform prob.
                    init_probs = std::vector<double>(nrS, 0.0);
                else //other elems get uniform prob
                    init_probs = std::vector<double>(nrS, u_prob);

                std::vector<Index>::iterator it = _m_po->_m_startStateListSI.begin();
                std::vector<Index>::iterator last = _m_po->_m_startStateListSI.end();
                while(it != last)
                {
                    init_probs[*it] = _m_po->_m_startStateListExclude? 
                        0.0 : u_prob;
                    it++;
                }
                _m_po->GetReferred()->SetISD(init_probs);
                init_probs.clear();                
                _m_po->_m_startStateListSI.clear();

            }
        };
        struct SetNrActions
        {
            ParserDecPOMDPDiscrete* _m_po;
            SetNrActions (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const
            {
                if(DEBUG_PARSE)
                {
                    std::string s(str,end);
                    std::cout << "SetNrActions: setting "<<_m_po->_m_lp_uint<<
                        " actions for agent "<<_m_po->_m_curAI<<std::endl
                        << "(parsed string=" << s <<")"<<std::endl;
                }
                _m_po->GetReferred()->SetNrActions(_m_po->_m_curAI, 
                        _m_po->_m_lp_uint);

            }
            void operator()(const unsigned int&) const
            {
                _m_po->GetReferred()->SetNrActions(_m_po->_m_curAI, 
                        _m_po->_m_lp_uint);
                if(DEBUG_PARSE)
                    std::cout << "SetNrActions: set "<<_m_po->_m_lp_uint<<
                        " actions for agent "<<_m_po->_m_curAI<<std::endl;
            }
        };
        struct AddAction
        {
            ParserDecPOMDPDiscrete* _m_po;
            AddAction (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const
            {
                std::string s(str, end);
                _m_po->GetReferred()->AddAction(_m_po->_m_curAI, s);
                if(DEBUG_PARSE)
                    std::cout << "AddAction: added action "<<s <<
                        " for agent "<<_m_po->_m_curAI<<std::endl;
            }
        };
        struct SetNrObservations
        {
            ParserDecPOMDPDiscrete* _m_po;
            SetNrObservations (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const
            {
                _m_po->GetReferred()->SetNrObservations(_m_po->_m_curAI, 
                        _m_po->_m_lp_uint);
                if(DEBUG_PARSE)
                    std::cout << "SetNrObservations: set "<<_m_po->_m_lp_uint<<
                        " observations for agent "<<_m_po->_m_curAI<<std::endl;
            }            
            void operator()(const unsigned int&) const
            {
                _m_po->GetReferred()->SetNrObservations(_m_po->_m_curAI, 
                        _m_po->_m_lp_uint);
                if(DEBUG_PARSE)
                    std::cout << "SetNrObservations: set "<<_m_po->_m_lp_uint<<
                        " observations for agent "<<_m_po->_m_curAI<<std::endl;
            }
        };
        struct AddObservation
        {
            ParserDecPOMDPDiscrete* _m_po;
            AddObservation (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const
            {
                std::string s(str, end);
                _m_po->GetReferred()->AddObservation(_m_po->_m_curAI, s);
                if(DEBUG_PARSE)
                    std::cout << "AddObservation: added action "<<s <<
                        " for agent "<<_m_po->_m_curAI<<std::endl;
            }
        };

        struct InitializeStates
        {
            ParserDecPOMDPDiscrete* _m_po;
            InitializeStates (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const
            {
                //TODO: nothing else to be done for states...?
                _m_po->_m_anyStateIndex = _m_po->GetReferred()->GetNrStates();
                _m_po->GetReferred()->
                    MADPComponentDiscreteStates::SetInitialized(true);

            }
        };

        struct InitializeActions
        {
            ParserDecPOMDPDiscrete* _m_po;
            InitializeActions (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const
            {
                _m_po->GetReferred()->ConstructJointActions();
                _m_po->GetReferred()->
                    MADPComponentDiscreteActions::SetInitialized(true);
                _m_po->_m_anyJAIndex = _m_po->GetReferred()->
                    GetNrJointActions();
            }
        };
        struct InitializeObservations
        {
            ParserDecPOMDPDiscrete* _m_po;
            InitializeObservations (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const
            {
                _m_po->GetReferred()->ConstructJointObservations();
                _m_po->GetReferred()->
                    MADPComponentDiscreteObservations::SetInitialized(true);
                _m_po->_m_anyJOIndex = _m_po->GetReferred()->
                    GetNrJointObservations();
            }
        };

        struct AddModels
        {
            ParserDecPOMDPDiscrete* _m_po;
            AddModels (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const
            {
                DecPOMDPDiscrete* p = _m_po->GetReferred();
                // add the transition model
                p->CreateNewTransitionModel();
                p->CreateNewObservationModel();
                p->CreateNewRewardModel();
                //if(DEBUG_PARSE) _m_po->GetReferred()->PrintInfo();
            }

        };
        struct StoreLPAction
        {
            ParserDecPOMDPDiscrete* _m_po;
            StoreLPAction (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const
            {

                if(DEBUG_PARSE)
                    std::cout << "StoreLPAction: pushing "<<std::string(str,end)<< 
                        " on _m_lp_JA"<<std::endl;
                if(_m_po->_m_lp_type == UINT)
                    _m_po->_m_lp_JA.push_back(_m_po->_m_lp_uint);
                else if(_m_po->_m_lp_type == STRING)
                {
                    //make sure that _m_lp_JA is cleared after each joint action
                    //so we can do this:
                    Index curAgIndex =  _m_po->_m_lp_JA.size();
                    try
                    {
                        Index aI = _m_po->GetReferred()->GetActionIndexByName(
                            _m_po->_m_lp_string, curAgIndex);
                        _m_po->_m_lp_JA.push_back(aI);
                    }
                    catch(E e)
                    {
                        std::stringstream ermsg; ermsg << e.SoftPrint() << " (at " << 
                            str.get_position() << ")"<<std::endl;
                        throw E(ermsg);
                    }
                }
                else if(_m_po->_m_lp_type == ASTERICK )
                    _m_po->_m_lp_JA.push_back(_m_po->_m_anyJAIndex);
                else
                    throw E("StoreLPAction expected that the last parsed type is a action index(uint), action name (string) or wilcard ('*').");
            }
        };
        /**called before StoreLPJointAction in case of a wildcard '*' joint
         * action. Effectively, this functions sets _m_lp_JA to a vector of
         * _m_po->_m_anyJAIndexs (one for each agent) .*/
        struct WildCardJointAction
        {
            ParserDecPOMDPDiscrete* _m_po;
            WildCardJointAction (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const;            
        };
        struct StoreLPJointAction
        {
            ParserDecPOMDPDiscrete* _m_po;
            bool _m_isJointActionIndex;
            StoreLPJointAction (ParserDecPOMDPDiscrete* po, bool b = false)
            {
                _m_po = po;
                _m_isJointActionIndex = b;
            }
            void operator()(iterator_t str, iterator_t end) const{Store();}
            void operator()(const unsigned int&) const{Store();}
            void Store() const;
            /**This function constructs the vector (_m_lp_JAI) of joint actions 
             * that match with the vector with individual action indices.*/
            void MatchingJointActions (Index curAgent, std::vector<Index> indIndices)
                const;

        };
        struct StoreLPObservation
        {
            ParserDecPOMDPDiscrete* _m_po;
            StoreLPObservation (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const
            {

                if(DEBUG_PARSE)
                    std::cout << "StoreLPObservation: pushing "<<std::string(str,end)<< 
                        " on _m_lp_JO"<<std::endl;
                if(_m_po->_m_lp_type == UINT)
                    _m_po->_m_lp_JO.push_back(_m_po->_m_lp_uint);
                else if(_m_po->_m_lp_type == STRING)
                {
                    //make sure that _m_lp_JO is cleared after each joint action
                    //so we can do this:
                    Index curAgIndex =  _m_po->_m_lp_JO.size();
                    try
                    {
                        Index aI = _m_po->GetReferred()->GetObservationIndexByName(
                            _m_po->_m_lp_string, curAgIndex);
                        _m_po->_m_lp_JO.push_back(aI);
                    }
                    catch(E e)
                    {
                        std::stringstream ermsg; ermsg << e.SoftPrint() << " (at " << 
                            str.get_position() << ")"<<std::endl;
                        throw EParse(ermsg);
                    }
                }
                else if(_m_po->_m_lp_type == ASTERICK )
                    _m_po->_m_lp_JO.push_back(_m_po->_m_anyJOIndex);
                else
                    throw E("StoreLPObservation expected that the last parsed type is a action index(uint), action name (string) or wilcard ('*').");
            }
        };
        /**called before StoreLPJointObservation in case of a wildcard '*' joint
         * action. Effectively, this functions sets _m_lp_JO to a vector of
         * ANY_INDEXs (=_m_anyJOIndex) (one for each agent) .*/
        struct WildCardJointObservation
        {
            ParserDecPOMDPDiscrete* _m_po;
            WildCardJointObservation (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const;            
        };
        struct StoreLPJointObservation
        {
            ParserDecPOMDPDiscrete* _m_po;
            bool _m_isJointObservationIndex;
            StoreLPJointObservation (ParserDecPOMDPDiscrete* po, bool b = false)
            {
                _m_po = po;
                _m_isJointObservationIndex = b;
            }
            void operator()(iterator_t str, iterator_t end) const{Store();}
            void operator()(const unsigned int&) const{Store();}
            void Store() const;
            
            /**This function constructs the vector (_m_lp_JOI) of joint actions 
             * that match with the vector with individual action indices.*/
            void MatchingJointObservations(Index curAgent, std::vector<Index> indIndices)
                const;

        };
        struct StoreLPFromState
        {
            ParserDecPOMDPDiscrete* _m_po;
            StoreLPFromState (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const;
            
        };
        struct StoreLPToState
        {
            ParserDecPOMDPDiscrete* _m_po;
            StoreLPToState (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const;
            
        };
        struct ProcessTProb
        {
            ParserDecPOMDPDiscrete* _m_po;
            ProcessTProb (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const;
            
        };
        struct ProcessTRow
        {
            ParserDecPOMDPDiscrete* _m_po;
            ProcessTRow (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const;

        };
        struct ProcessTMatrix
        {
            ParserDecPOMDPDiscrete* _m_po;
            ProcessTMatrix (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const;            
            
        };
        struct ProcessOProb
        {
            ParserDecPOMDPDiscrete* _m_po;
            ProcessOProb (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const;
            
        };
        struct ProcessORow
        {
            ParserDecPOMDPDiscrete* _m_po;
            ProcessORow (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const;

        };
        struct ProcessOMatrix
        {
            ParserDecPOMDPDiscrete* _m_po;
            ProcessOMatrix (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const;            
            
        };
        struct ProcessR
        {
            ParserDecPOMDPDiscrete* _m_po;
            ProcessR (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const;
            
        };
        struct ProcessRRow
        {
            ParserDecPOMDPDiscrete* _m_po;
            ProcessRRow (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const;

        };
        struct ProcessRMatrix
        {
            ParserDecPOMDPDiscrete* _m_po;
            ProcessRMatrix (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const;            
            
        };
        struct InitializeDPOMDP
        {
            ParserDecPOMDPDiscrete* _m_po;
            InitializeDPOMDP (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const
            {
                _m_po->GetReferred()->SetInitialized(true);
            }
        };
        struct SetNrAgents
        {
            ParserDecPOMDPDiscrete* _m_po;
            SetNrAgents(ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t first, iterator_t last) const;
            void operator()(const int&) const;
        }; 
        struct AddAgents
        {
            ParserDecPOMDPDiscrete* _m_po;
            AddAgents(ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t first, iterator_t last) const
            {   
                _m_po->GetReferred()->SetNrAgents(0);
                std::vector<std::string>::iterator it = _m_po->_m_curIdentList.begin();
                std::vector<std::string>::iterator l = _m_po->_m_curIdentList.end();
                while(it != l)
                {
                    _m_po->GetReferred()->AddAgent(*it);
                    it++;
                    _m_po->_m_nrA++;
                }
                _m_po->ClearCurIdentList();
            }
        };
        //discount param
        static void dp_number(iterator_t str, iterator_t end);
        struct dp_SetDiscountParam{            
            ParserDecPOMDPDiscrete* _m_po;
            dp_SetDiscountParam(ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t first, iterator_t last) const
            {
                std::string  s(first, last);
                if(DEBUG_PARSE){std::cout << "discount="<<s << std::endl;}
                double discount = -1.0;
                if( _m_po->_m_lp_type == DOUBLE )
                {
                    if(DEBUG_PARSE){std::cout <<"last parsed number was a DOUBLE"<<
                        "(_m_po->_m_lp_double = "<<_m_po->_m_lp_double<<")\n";}
                    discount = _m_po->_m_lp_double;
                }
                else if (_m_po->_m_lp_type == INT)
                { 
                    if(DEBUG_PARSE){std::cout <<"last parsed number was a INT"<<
                        "(_m_po->_m_lp_int = "<<_m_po->_m_lp_int<<")\n";}
                    //the discount was parsed as an int
                    discount = (double) _m_po->_m_lp_int;
                }                
                else if (_m_po->_m_lp_type == UINT)
                { 
                    if(DEBUG_PARSE){std::cout <<"last parsed number was a UINT"<<
                        "(_m_po->_m_lp_uint = "<<_m_po->_m_lp_uint<<")\n";}
                    //the discount was parsed as an int
                    discount = (double) _m_po->_m_lp_uint;
                }
                
                if(DEBUG_PARSE){std::cout <<"dp_SetDiscountParam - discount="<<
                    discount<<std::endl;} 
                _m_po->GetReferred()->SetDiscount(discount);
            }                
        };        
        //value param
        static void vp_value_tail(iterator_t str, iterator_t end);
        struct vt_REWARDTOK        
        {
            ParserDecPOMDPDiscrete* _m_po;
            vt_REWARDTOK (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const
            {
                _m_po->GetReferred()->SetRewardType(REWARD);
            }
        };
        struct vt_COSTTOK        
        {
            ParserDecPOMDPDiscrete* _m_po;
            vt_COSTTOK (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const
            {
                _m_po->GetReferred()->SetRewardType(COST);
            }
        };
        //This is the functor which is called from the grammar (i.e.
        //dpomdp.spirit) to add the parsed state (names) to the problem.
        struct AddState
        {
            ParserDecPOMDPDiscrete* _m_po;
            AddState(ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t first, iterator_t last) const
            {
                if(DEBUG_PARSE){std::cout << "AddState - adding state \""<<
                    _m_po->_m_lp_string<<"\"\n";}
                _m_po->GetReferred()->AddState(_m_po->_m_lp_string);
            }
        };

        struct DecPOMDPFileParser : public grammar<DecPOMDPFileParser>
        {
            ParserDecPOMDPDiscrete* _m_parserObject;
            DecPOMDPDiscrete* _m_problem;
            DecPOMDPFileParser(ParserDecPOMDPDiscrete* parserObject)
            {
                _m_parserObject = parserObject;
                _m_problem = _m_parserObject->GetReferred();
            }
            template <typename ScannerT>
            struct definition
            {
#if SUBGRAMMAR   
#include "sub_grammar_defs.h"
                agentstok_parser AGENTSTOK;
                discounttok_parser DISCOUNTTOK;
                valuestok_parser VALUESTOK;
                statestok_parser STATESTOK;
                actionstok_parser ACTIONSTOK;
                observationstok_parser OBSERVATIONSTOK;
                ttok_parser TTOK;
                otok_parser OTOK;
                rtok_parser RTOK;
                //the parsers that need a reference:
                uniformtok_parser UNIFORMTOK;
                inttok_parser INTTOK;
#endif                
                definition(DecPOMDPFileParser const& self) 
#if SUBGRAMMAR   
                    :
                    INTTOK(self._m_parserObject),
                    UNIFORMTOK(self._m_parserObject) 
#endif                
                {
#include "dpomdp.spirit"            
                }

#if SUBGRAMMAR == 0
rule<ScannerT> AGENTSTOK, DISCOUNTTOK,VALUESTOK,STATESTOK,ACTIONSTOK,OBSERVATIONSTOK,TTOK,OTOK,RTOK,UNIFORMTOK, INTTOK;
#endif
rule<ScannerT> 
    EOLTOK, IDENTITYTOK,REWARDTOK,COSTTOK,STARTTOK,INCLUDETOK,EXCLUDETOK,RESETTOK,COLONTOK,ASTERICKTOK,PLUSTOK,MINUSTOK,FLOATTOK,STRINGTOK,
    dpomdp_file,preamble,agents_param,discount_param,value_param,value_tail,state_param,state_tail,action_param,action_tail,obs_param,obs_tail,start_state,start_state_list,param_list,param_spec,trans_prob_spec,trans_spec_tail,obs_prob_spec,obs_spec_tail,reward_spec,reward_spec_tail,ui_matrix,u_matrix,prob,
    action_param_line,obs_param_line,joint_obs,joint_action,state_or_indiv_act_or_obs,agents_tail,prob_row_vector,num_row_vector,reserved_word,state_list, float_r, int_r, action_list,obs_list, floats_matrix, floats_row_vector, dpomdp, from_state, to_state 
    ;
                rule<ScannerT> const&
                start() const { return dpomdp_file; }
            };
        };


    protected:
        
    public:
        
        // Constructor, destructor and copy assignment.
        /// (default) Constructor
        ParserDecPOMDPDiscrete(DecPOMDPDiscrete* problem=0);
        // Copy constructor.
        //ParserDecPOMDPDiscrete(const ParserDecPOMDPDiscrete& a);
        // Destructor.
        //~ParserDecPOMDPDiscrete();
        
        //operators:

        //data manipulation (set) functions:
        /**The function that starts the parsing.*/
        void Parse();
        
        //get (data) functions:
        
        
        ///The last parsed ...        
        unsigned int _m_lp_uint;    
        int _m_lp_int;    
        double _m_lp_double;
        std::string _m_lp_string;
        ///The type (INT or DOUBLE) of the last parsed number.
        parsed_t _m_lp_type;
        ///Whether the last 'number' used an optional sign ('+' or '-')
        bool _m_lp_number_used_opt_sign;
        ///Whether the last optional sign was a '-'
        bool _m_lp_number_negated;

        //the number of agents - used often therefore also stored here        
        size_t _m_nrA;
        //the current agent index.
        Index _m_curAI;
        //The following are special indices denoting any state, (joint) action
        //or (joint) observation
        Index _m_anyJAIndex;
        Index _m_anyJOIndex;
        Index _m_anyStateIndex;

        std::vector< std::vector<double> > _m_curMatrix;
        bool _m_matrixModified;
        struct ResetCurMatrix //TODO: move to proper place
        {
            ParserDecPOMDPDiscrete* _m_po;
            ResetCurMatrix (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const
            {
                if(_m_po->_m_matrixModified)
                    _m_po->ClearCurMatrix();
            }
        };
        void ClearCurMatrix()//TODO:move to proper place...
        {
            _m_curMatrix.clear();//no pointers stored, so this should not leak
            _m_curMatrix.push_back( std::vector<double>() );
            _m_matrixModified = false;
        }
        bool IsDimensionOfMatrix(size_t rows, size_t cols)
        {
            if(_m_curMatrix.size() != rows + 1)
                return false;
            for(Index r=0; r<rows; r++)
                if(_m_curMatrix[r].size() != cols)
                    return(false);
            //last row entry should be empty
            return(_m_curMatrix[rows].size() == 0);
        }
        bool IsRowMatrixLP()
        {
            //as at the end of 1 line (row) a new row is added to the matrix
            //_m_curMatrix should contain 2 rows, of which the second is
            //empty
             return(_m_curMatrix.size() == 2 && _m_curMatrix[1].size() == 0 );
        }

        std::vector<std::string> _m_curIdentList;        
        bool _m_identListModified;
        struct ResetCurIdentList //TODO: move to proper place
        {
            ParserDecPOMDPDiscrete* _m_po;
            ResetCurIdentList (ParserDecPOMDPDiscrete* po){_m_po = po;}
            void operator()(iterator_t str, iterator_t end) const
            {
                //TODO:check whether the previous matrix was consistent
                if(_m_po->_m_identListModified)
                    _m_po->ClearCurIdentList();
            }
        };        
        void ClearCurIdentList()//TODO:move to proper place...
        {
            _m_curIdentList.clear();//no pointers stored, should not leak
            _m_identListModified = false;
        }

        /**A vector in which the currently parsed individual action indices 
         * of a joint action are stored. (by StoreLPAction).
         * wild-cards (asterik) are stored as _m_anyJAIndex . */
        std::vector<Index> _m_lp_JA;
        /**similar for the observations...*/
        std::vector<Index> _m_lp_JO;
        
        /**A vector that stores the indices of joint actions that match the 
         * last parsed joint action. (if the last parsed joint action didn't
         * contain any wildcards, the size of this vector is 1.)
         * This vector is constructed by StoreLPJointAction by transforming
         * the above vector (_m_lp_JA).*/
        std::vector<Index> _m_lp_JAI;
        /**similar for the joint observations...*/
        std::vector<Index> _m_lp_JOI;

        /**A vector that stores the last parsed from-state index.
         * Contrary to _m_lp_JAI above, this vector contains only 1 element,\
         * which can be the ANY_INDEX (_m_anyStateIndex) . This is more 
         * convenient, as it allows
         * easier selection of the proper AddReward and AddObservation 
         * functions.*/
        std::vector<Index> _m_lp_fromSI;
        /**idem, but for to-state.*/
        std::vector<Index> _m_lp_toSI;
        
        /**A vector used to store the state indices for the start state
         * specification.*/
        std::vector<Index> _m_startStateListSI;
        /**A boolean indicating whether the states in the start state list
         * should be excluded (versus the default: uniform prob. over the 
         * specified states). */
        bool _m_startStateListExclude;

        /**Pointer to the first iterator. This is used to give informative error messages.
         * (Specifically the position of the error.*/
        iterator_t* _m_first;
};


#endif /* !_PARSERDECPOMDPDISCRETE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
