/**\file RGet.h
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
 * $Id: RGet.h 3604 2009-08-25 10:52:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _RGET_H_
#define _RGET_H_ 1

/* the include directives */
#include "Globals.h"

#include "RewardModelMapping.h"
#include "RewardModelMappingSparse.h"

/** \brief RGet can be used for direct access to a reward model.
 */
class RGet 
{
public:
    virtual ~RGet() = 0;
    //get (data) functions:
    virtual double Get(Index sI, Index jaI) const = 0;
};

//http://www.parashift.com/c++-faq-lite/pointers-to-members.html
//says "defined even though it's pure virtual; it's faster this way; trust me"
inline RGet::~RGet() {}

/** \brief RGet can be used for direct access to a RewardModelMapping.
 */
class RGet_RewardModelMapping : public RGet
{
 
private:
    const RewardModelMapping::Matrix& _m_R;
public:
    RGet_RewardModelMapping( RewardModelMapping* rm)
        :
            _m_R ( rm->_m_R )
    {};

    virtual double Get(Index sI, Index jaI) const
    {
        return( _m_R(sI,jaI)) ;  
    }
};

/** \brief RGet can be used for direct access to a RewardModelMappingSparse.
 */
class RGet_RewardModelMappingSparse : public RGet
{
 
private:
    
    const RewardModelMappingSparse::SparseMatrix&  _m_R;
public:
    RGet_RewardModelMappingSparse( RewardModelMappingSparse* rm)
        :
            _m_R ( rm->_m_R )
    {};

    virtual double Get(Index sI, Index jaI) const
    {
        return( _m_R(sI,jaI)) ;  
    }
        

};

#endif /* !_RGET_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
