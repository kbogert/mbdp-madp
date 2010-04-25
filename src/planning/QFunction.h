/**\file QFunction.h
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
 * $Id: QFunction.h 2979 2008-11-03 20:00:13Z faolieho $
 */

/* Only include this header file once. */
#ifndef _QFUNCTION_H_
#define _QFUNCTION_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "QFunctionInterface.h"

/**\brief QFunction is an abstract base class containing nothing. 
 * It only groups together all Q-Functions.
 * */
class QFunction :
    virtual public QFunctionInterface
{
private:
    
protected:
    
public:

};


#endif /* !_QFUNCTION_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
