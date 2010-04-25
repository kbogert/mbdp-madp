/**\file VectorTools.h
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
 * $Id: VectorTools.h 3604 2009-08-25 10:52:24Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _VECTORTOOLS_H_
#define _VECTORTOOLS_H_ 1

/* the include directives */
#include "Globals.h"
#include <algorithm>

namespace VectorTools{

    template <typename T>
    bool Equal( const std::vector<T>& vec1,  const std::vector<T>& vec2 )
    {
        size_t s1 = vec1.size();
        if( s1 != vec2.size())
            return false;

        return( std::equal(vec1.begin(), vec1.end(), vec2.begin() ) );
/*
        typename std::vector< T >::const_iterator it1, it2;
        it1 = vec1.begin();
        it2 = vec2.begin();
        while(it1 != vec1.end() )
        {
            if( (*it1) != (*it2) )
            it1++;
            it2++;
        }
        */
        
    }

    template <typename T>
    T InnerProduct( const std::vector<T>& vec1,  const std::vector<T>& vec2 )
    {
        size_t s1 = vec1.size();
        if( s1 != vec2.size())
            throw E("VectorTools::InnerProduct - vec sizes not equal");

        typename std::vector< T >::const_iterator it1, it2;
        T inprod;
        it1 = vec1.begin();
        it2 = vec2.begin();
        while(it1 != vec1.end() )
        {
            inprod += (*it1) * (*it2) ;
            it1++;
            it2++;
        }
        return(inprod);
    }    
    
    ///Compute the product of the vector's elements
    /**
     * clearly the product operator* should be defined for type T
     */        
    template <typename T>
    T VectorProduct( const std::vector<T>& vec )
    {
        if(vec.size() == 0)
            throw E("IndexTools::VectorProduct - vector product of vec of size 0 is undefined!");

        T product = *(vec.begin());//the first element
        typename std::vector< T >::const_iterator it;
        it = vec.begin() + 1;//second element
        while(it != vec.end() )
        {
            product = product * (*it);
            it++;
        }
        return(product); 
    }

    template <typename T>
    T MaxNorm(  const std::vector<T>& vec )
    {
        T norm = 0.0 ;
        for (Index i = 0 ; i < vec.size() ; i++)
            norm = max (fabs (vec [i]), norm) ;
        return norm;
    }

}

#endif /* !_VECTORTOOLS_H_ */

// Local Variables: ***
// mode:c++ ***
// End: ***
