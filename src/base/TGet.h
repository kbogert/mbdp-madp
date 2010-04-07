/**\file TGet.h
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
 * $Id: TGet.h 3604 2009-08-25 10:52:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _TGET_H_
#define _TGET_H_ 1

/* the include directives */
#include "Globals.h"

#include "TransitionModelMapping.h"
#include "TransitionModelMappingSparse.h"

/** \brief TGet can be used for direct access to the transition model.  */
class TGet 
{
public:
    virtual ~TGet() = 0;
    //get (data) functions:
    virtual double Get(Index sI, Index jaI, Index sucSI) const = 0;
};

//http://www.parashift.com/c++-faq-lite/pointers-to-members.html
//says "defined even though it's pure virtual; it's faster this way; trust me"
inline TGet::~TGet() {}

/** \brief TGet_TransitionModelMapping can be used for direct access
 * to a TransitionModelMapping.  */
class TGet_TransitionModelMapping : public TGet
{
 
private:
    std::vector<TransitionModelMapping::Matrix* > _m_T;
public:
    TGet_TransitionModelMapping( TransitionModelMapping* tm)
    {
        _m_T = tm->_m_T;
    };

    virtual double Get(Index sI, Index jaI, Index sucSI) const
    {  { return((*_m_T[jaI])(sI,sucSI)); } }

};

/** \brief TGet_TransitionModelMappingSparse can be used for direct
 * access to a TransitionModelMappingSparse.  */
class TGet_TransitionModelMappingSparse : public TGet
{
 
private:
    std::vector<TransitionModelMappingSparse::SparseMatrix* > _m_T;
public:
    TGet_TransitionModelMappingSparse( TransitionModelMappingSparse* tm)
    {
        _m_T = tm->_m_T;
    };

    virtual double Get(Index sI, Index jaI, Index sucSI) const
    {  { return((*_m_T[jaI])(sI,sucSI)); } }

};

#endif /* !_TGET_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
