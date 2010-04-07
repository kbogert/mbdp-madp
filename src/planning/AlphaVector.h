/**\file AlphaVector.h
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
 * $Id: AlphaVector.h 2944 2008-10-23 16:10:26Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _ALPHAVECTOR_H_
#define _ALPHAVECTOR_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"


/**AlphaVector represent an alpha vector used in POMDP solving. It's
 * basically a vector of values and an action index.  */
class AlphaVector 
{
private:    
    
    Index _m_action;
    int _m_betaI;
    std::vector<double> _m_values;
    
protected:
    
public:
    // Constructor, destructor and copy assignment.

    /// Default constructor
    AlphaVector();

    /// Constructor that reserves memory for \a nrS values.
    AlphaVector(size_t nrS);

    /// Constructor that reserves memory for \a nrS values, and sets
    /// every value to \a val.
    AlphaVector(size_t nrS, double val);

    /// Destructor.
    ~AlphaVector();
    /// Copy assignment operator
    AlphaVector& operator= (const AlphaVector& o);
    
    //operators:
    
    //data manipulation (set) functions:
    void SetAction(Index a){ _m_action=a; }
    void SetValues(const std::vector<double> &vs);
    void SetValue(double v,Index i){ _m_values.at(i)=v; }
    void SetBetaI(int betaI){ _m_betaI=betaI; }
    
    //get (data) functions:
    Index GetAction() const { return(_m_action); }
    const std::vector<double> &GetValues() const { return(_m_values); }
    double GetValue(Index i) const { return(_m_values.at(i)); }

    unsigned int GetNrValues() const { return(_m_values.size()); }
    int GetBetaI() const { return(_m_betaI); }

    std::string SoftPrint() const;
    void Print() const { std::cout << SoftPrint(); }

    bool Equal(const AlphaVector &alpha) const;
};

#endif /* !_ALPHAVECTOR_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
