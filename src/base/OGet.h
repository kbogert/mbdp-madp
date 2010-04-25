/**\file OGet.h
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
 * $Id: OGet.h 3604 2009-08-25 10:52:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _OGET_H_
#define _OGET_H_ 1

/* the include directives */
#include "Globals.h"

#include "ObservationModelMapping.h"
#include "ObservationModelMappingSparse.h"

/** \brief OGet can be used for direct access to the observation model.  */
class OGet 
{
public:
    virtual ~OGet() = 0;
    //get (data) functions:
    virtual double Get(Index jaI, Index sucSI, Index joI) const = 0;
};

//http://www.parashift.com/c++-faq-lite/pointers-to-members.html
//says "defined even though it's pure virtual; it's faster this way; trust me"
inline OGet::~OGet() {}

/** \brief OGet_ObservationModelMapping can be used for direct access
 * to a ObservationModelMapping.  */
class OGet_ObservationModelMapping : public OGet
{
 
private:
    std::vector<ObservationModelMapping::Matrix* > _m_O;
public:
    OGet_ObservationModelMapping( ObservationModelMapping* om)
    {
        _m_O = om->_m_O;
    };

    virtual double Get(Index jaI, Index sucSI, Index joI) const
        {  { return((*_m_O[jaI])(sucSI,joI)); } }

};

/** \brief OGet_ObservationModelMappingSparse can be used for direct
 * access to a ObservationModelMappingSparse.  */
class OGet_ObservationModelMappingSparse : public OGet
{
 
private:
    std::vector<ObservationModelMappingSparse::SparseMatrix* > _m_O;
public:
    OGet_ObservationModelMappingSparse( ObservationModelMappingSparse* om)
    {
        _m_O = om->_m_O;
    };

    virtual double Get(Index jaI, Index sucSI, Index joI) const
        {  { return((*_m_O[jaI])(sucSI,joI)); } }

};

#endif /* !_OGET_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
