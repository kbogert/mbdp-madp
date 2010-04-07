/**\file argumentHandlersPostChild.h
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
 * $Id: argumentHandlersPostChild.h 3604 2009-08-25 10:52:24Z mtjspaan $
 */


namespace ArgumentHandlers {

static struct argp_option options_main[] = {
    { 0 }
};
static error_t
parse_main (int key, char *arg, struct argp_state *state)
{
    struct arguments *theArgumentsStruc = (struct arguments*) state->input;
    switch (key)
    {
        case ARGP_KEY_INIT:
            //give child_parsers access to the arguments structure on 
            //initialization.
            for(int i = 0; i < nrChildParsers; i++)
                state->child_inputs[i] = theArgumentsStruc;
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}
/* Our argp parser. */
static argp theArgpStruc = {options_main, parse_main, 0, doc, childVector };

}
