# $Id: Makefile.am 3598 2009-08-20 12:29:54Z mtjspaan $

include $(top_srcdir)/src/Makefile.custom
include $(top_srcdir)/config/Make-rules

##############
# Includedirs, libdirs, libs and cflags for all programs 
INCLUDES		=  $(MADP_INCLUDES) -I$(top_srcdir)/src/base\
 -I$(top_srcdir)/src/include
AM_LDFLAGS		= 
LDADD			= 
AM_CPPFLAGS		= -Wall -pipe $(MARCH_FLAGS)

PARSER_CPPFILES=ParserDecPOMDPDiscrete.cpp ParserTOIDecPOMDPDiscrete.cpp\
 ParserTOIDecMDPDiscrete.cpp ParserTOIFactoredRewardDecPOMDPDiscrete.cpp\
 ParserTOICompactRewardDecPOMDPDiscrete.cpp \
 MADPParser.cpp
PARSER_HFILES=$(PARSER_CPPFILES:.cpp=.h) ParserInterface.h\
 CommentOrBlankParser.h

PARSER_FILES=$(PARSER_CPPFILES) $(PARSER_HFILES)

###############
# All DYNAMIC libraries
# the LTLIBRARIES (LibTool-libraries)

# the library to be build...
lib_LTLIBRARIES =  libMADPParser.la
noinst_LTLIBRARIES =  

# sources for the library:
libMADPParser_la_SOURCES = $(PARSER_FILES) 
libMADPParser_la_CPPFLAGS = $(AM_CPPFLAGS) $(CPP_OPTIMIZATION_FLAGS)
libMADPParser_la_LIBADD = 
libMADPParser_la_DEPENDENCIES =

