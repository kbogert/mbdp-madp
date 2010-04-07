/**\file BGIP_SolverCreator_AM.h
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
 * $Id: BGIP_SolverCreator_AM.h 3603 2009-08-25 10:38:25Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _BGIP_SOLVERCREATOR_AM_H_
#define _BGIP_SOLVERCREATOR_AM_H_ 1

/* the include directives */
#include "Globals.h"
#include "BGIP_SolverCreatorInterface.h"

//We have to include this (otherwise compiler doesn't know that 
//BGIP_SolverAlternatingMaximization is-a BayesianGameIdenticalPayoffSolver
//and thus that the virtual function "operator()" is implemented...
#include "BGIP_SolverAlternatingMaximization.h"
//class BGIP_SolverAlternatingMaximization;

/** \brief BGIP_SolverCreator_AM returns an Alternating Maximization
 * BGIP_Solver. */
template<class JP>
class BGIP_SolverCreator_AM : public BGIP_SolverCreatorInterface<JP>
{
    private:    
        size_t _m_nrRestarts;
        int _m_verbose;
        size_t _m_nrSolutions;
    
    protected:
    
    public:
        // Constructor, destructor and copy assignment.
        /// (default) Constructor
        BGIP_SolverCreator_AM( size_t nrRestarts=10, 
                            int verbose=0,
                            size_t nrSolutions=1)
            :
                _m_nrRestarts(nrRestarts),
                _m_verbose(verbose),
                _m_nrSolutions(nrSolutions)
        {}
        virtual ~BGIP_SolverCreator_AM(){};

        //operators:
        BGIP_SolverAlternatingMaximization<JP>* operator()
                (const BayesianGameIdenticalPayoffInterface& bg) const
        {
            if(_m_verbose >= 2)
            {
                std::cout << "BGIP_SolverCreator_AM:: creating a new BGIP_SolverAlternatingMaximization with nrRestarts=" << _m_nrRestarts<< ", verbose=" << _m_verbose << ", nrSols="<<_m_nrSolutions << std::endl;
            }
            return( 
                new BGIP_SolverAlternatingMaximization<JP>(
                    bg,
                    _m_nrRestarts,
                    _m_verbose,
                    _m_nrSolutions
                    )
                );
        }


        //data manipulation (set) functions:
        
        //get (data) functions:
         std::string SoftPrint() const
        {
            std::stringstream ss;
            ss << "BGIP_SolverCreator_AM object with "<<
                ", _m_verbose="<<_m_verbose <<
                ", _m_nrSolutions="<<_m_nrSolutions<<
                ", _m_nrRestarts="<<_m_nrRestarts<< 
                std::endl;
            return (ss.str());
        }

};


#endif /* !_BGIP_SOLVERCREATOR_AM_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
