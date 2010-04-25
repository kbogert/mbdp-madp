/**\file CommentOrBlankParser.h
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
 * $Id: CommentOrBlankParser.h 2945 2008-10-25 11:14:45Z mtjspaan $
 */

/* Only include this header file once. */
#ifndef _COMMENTORBLANKPARSER_H_
#define _COMMENTORBLANKPARSER_H_ 1

/* the include directives */
#include <boost/spirit/core.hpp>

namespace boost { namespace spirit
{
    template <typename DerivedT>
    struct sub_grammar : public parser<DerivedT>
    {
	typedef sub_grammar self_t;
	typedef DerivedT const& embed_t;

	template <typename ScannerT>
	struct result
	{
	    typedef typename parser_result<
		typename DerivedT::start_t, ScannerT>::type
	    type;
	};

	DerivedT const& derived() const
	{ return *static_cast<DerivedT const*>(this); }

	template <typename ScannerT>
	typename parser_result<self_t, ScannerT>::type
	parse(ScannerT const& scan) const
	{
	    return derived().start.parse(scan);
	}
    };
}}

using namespace boost::spirit;

/* aliases */

/* constants */
#define DEBUG_COMPARS 0
#define DEBUG_COBP 0

namespace comment {
    typedef char                    char_t;
    //typedef file_iterator<char_t>   iterator_t;
    typedef file_iterator<char_t>   iterator_t_fi;
    typedef position_iterator<iterator_t_fi>  iterator_t;
    typedef scanner<iterator_t>     scanner_t;
    typedef rule<scanner_t>         rule_t;
   
namespace{    
    void    cp_eol(iterator_t, iterator_t)
    { if(DEBUG_COMPARS)	std::cout << "EOL\n"; }
    void    cp_endinput(iterator_t, iterator_t)
    { if(DEBUG_COMPARS)	std::cout << "END OF INPUT\n"; }
    void    cp_startcomment(char_t)
    { if(DEBUG_COMPARS) std::cout<< "#-STARTCOMMENT\n"; }

    void    cobp_blank(char_t)    {if(DEBUG_COBP)
	std::cout << "SKIPPED BLANK\n";};
    void    cobp_emptyline(iterator_t str, iterator_t end)    
	{ if(DEBUG_COBP) std::cout << "SKIPPED EMPTYLINE\n"; };
    void    cobp_comment(iterator_t str, iterator_t end)
    {
        std::string  s(str, end);
	if(DEBUG_COBP)
	    std::cout<< "SKIPPED COMMENT: \""<< s << "\""<< std::endl; 
    };
}

//CommentParser
struct CommentParser : public sub_grammar<CommentParser>
{    
    typedef
	boost::spirit::sequence<boost::spirit::sequence<boost::spirit::action<boost::spirit::chlit<char>, void (*)(comment::char_t)>, boost::spirit::kleene_star<boost::spirit::alternative<boost::spirit::print_parser, boost::spirit::blank_parser> > >, boost::spirit::kleene_star<boost::spirit::action<boost::spirit::eol_parser, void (*)(comment::iterator_t, comment::iterator_t)> > >
    start_t;

    CommentParser() 
    : start
	(   //commenttoken 
	    ch_p('#')[&cp_startcomment]
	    >> 
	    //lineremainder
	    *( print_p | /*  alnum_p |*/ blank_p ) 
	    >>	
	    *(   eol_p[&cp_eol] )
	)
    {}

    start_t start;
};

CommentParser const commentParser_p = CommentParser();
struct CommentOrBlankParser : public sub_grammar<CommentOrBlankParser>
{

    typedef
	boost::spirit::alternative<boost::spirit::action<boost::spirit::blank_parser, void (*)(comment::char_t)>, boost::spirit::action<comment::CommentParser, void (*)(comment::iterator_t, comment::iterator_t)> >
    start_t;

    CommentOrBlankParser()
    : start
	(
	    blank_p[&cobp_blank]
	    |
	    commentParser_p[&cobp_comment]
	)
    {}

    start_t start;

};

}
#endif /* !_COMMENTORBLANKPARSER_H_ */

