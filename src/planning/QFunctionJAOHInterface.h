/**\file QFunctionJAOHInterface.h
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
 * $Id: QFunctionJAOHInterface.h 3604 2009-08-25 10:52:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _QFUNCTIONJAOHINTERFACE_H_
#define _QFUNCTIONJAOHINTERFACE_H_ 1

/* the include directives */
#include <iostream>
#include "Globals.h"
#include "QFunctionForDecPOMDP.h"



/**\brief QFunctionJAOHInterface is a class that is an interface for heuristics
 * of the shape
 * Q(JointActionObservationHistory, JointAction)
 *
 * (As these type of heuristics specify only 1 reward, they are (implicitly) for
 * Dec-POMDPs only.)
 **/
class QFunctionJAOHInterface 
    : virtual public QFunctionForDecPOMDPInterface
{
    private:
    
    protected:
    
    public:
        QFunctionJAOHInterface(){}
        /**Destructor. there is a (big) chance that we will call 
         *     delete base_class_pointer
         * where base_class_pointer actually points to a derived object. To 
         * make sure that the derived destructor is called, this destructor is
         * declared virtual.*/
        virtual ~QFunctionJAOHInterface() {};

        //operators:

        //data manipulation (set) functions:
        
        //get (data) functions:
        
        /// Returns Q(joint A-O history \a jaohI, \a jaI).
        virtual double GetQ(Index jaohI, Index jaI) const = 0;

    //TODO the load and save functions should probably be moved up in the hierarchy?!?
        /// Load the Qvalues from disk.
        void Load();
        /// Load the Qvalues from disk from a file named \a filename.
        virtual void Load(std::string filename)
        {throw E("QFunctionJAOHInterface::Load in order to have Load functionality this function should be overriden in the relevant derived class.");}
        /// Stores the Qvalues to disk.
        void Save() const;
        /// Stores the Qvalues to disk in file named \a filename.
        virtual void Save(std::string filename) const
        {throw E("QFunctionJAOHInterface::Save in order to have Save functionality this function should be overriden in the relevant derived class.");}

        /// Gets the filename where the Qvalues should be stored.
        virtual std::string GetCacheFilename() const 
        {throw E("QFunctionJAOHInterface::GetCacheFilename in order to have cache (Load/Save)functionality this function should be overriden in the relevant derived class.");}


};


#endif /* !_QFUNCTIONJAOHINTERFACE_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
