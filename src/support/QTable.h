/**\file QTable.h
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
 * $Id: QTable.h 4016 2010-03-11 16:56:02Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _QTABLE_H_
#define _QTABLE_H_ 1

/* the include directives */
#include "Globals.h"
#include "QTableInterface.h"
#include <boost/numeric/ublas/matrix.hpp>

typedef boost::numeric::ublas::matrix<double> matrix_t;

/** \brief QTable implements QTableInterface using a full matrix. */
class QTable
    : 
        public QTableInterface
        , public matrix_t
{
    private:    
    
    protected:
    
    public:
        // Constructor, destructor and copy assignment.
        /// (default) Constructor
        QTable()
        {}
        QTable(size_t S, size_t A)
            :   matrix_t(S,A)
        {}
        /// Copy constructor.
        QTable(const QTable& a)
            :   matrix_t(a)
        {};
/*        
        /// Destructor.
        ~QTable();
*/        
        /// Copy assignment operator
//        QTable& operator= (const QTable& o);

        virtual double Get(Index s_i, Index ja_i) const
        { return this->operator() (s_i, ja_i); }
        virtual void Set(Index s_i, Index ja_i, double rew)
        { this->operator() (s_i, ja_i) = rew; }

        /// Returns a pointer to a copy of this class.
        virtual QTable* Clone() const
        { return new QTable(*this); }

};

/// A Q-table for each time step.
typedef std::vector<QTable> QTables;

#endif /* !_QTABLE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
