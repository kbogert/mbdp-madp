/**\file QAVParameters.h
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
 * $Id: QAVParameters.h 2394 2008-03-03 12:39:37Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _QAVPARAMETERS_H_
#define _QAVPARAMETERS_H_ 1

#include "BGBackupType.h"
#include "PerseusBackupType.h"

struct QAVParameters
{
    PerseusBackupType backup;
    BGBackupType bgBackupType;
};

#endif /* !_QAVPARAMETERS_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
