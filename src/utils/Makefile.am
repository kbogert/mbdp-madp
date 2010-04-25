# $Id: Makefile.am 3638 2009-08-31 12:49:23Z mtjspaan $

include $(top_srcdir)/src/Makefile.custom
include $(top_srcdir)/config/Make-rules

# Which programs to build. Only PROGRAMS_NORMAL will be installed.
PROGRAMS_NORMAL =  printJointPolicyPureVector printProblem \
 analyzeRewardResults getAvgReward evaluateRandomPolicy \
 evaluateJointPolicyPureVector evaluatePerseusPolicy

##############
# Includedirs, libdirs, libs and cflags for all programs 
INCLUDES		= -I.. $(MADP_INCLUDES)
AM_LDFLAGS		= 
LDADD			= 
AM_CPPFLAGS		= -Wall -pipe $(MARCH_FLAGS)

noinst_PROGRAMS = 
bin_PROGRAMS = $(PROGRAMS_NORMAL)

# Build printJointPolicyPureVector
printJointPolicyPureVector_SOURCES = printJointPolicyPureVector.cpp
printJointPolicyPureVector_LDADD = $(MADPLIBS_NORMAL) $(MADP_LD)
printJointPolicyPureVector_LDFLAGS = $(AM_LDFLAGS) 
printJointPolicyPureVector_DEPENDENCIES = $(MADPLIBS_NORMAL)
printJointPolicyPureVector_CPPFLAGS= $(AM_CPPFLAGS) $(CPP_OPTIMIZATION_FLAGS)
printJointPolicyPureVector_CXXFLAGS=
printJointPolicyPureVector_CFLAGS=

# Build printProblem
printProblem_SOURCES = printProblem.cpp
printProblem_LDADD = $(MADPLIBS_NORMAL_NOPLANNING) $(MADP_LD)
printProblem_LDFLAGS = $(AM_LDFLAGS) 
printProblem_DEPENDENCIES = $(MADPLIBS_NORMAL_NOPLANNING)
printProblem_CPPFLAGS= $(AM_CPPFLAGS) $(CPP_OPTIMIZATION_FLAGS)
printProblem_CXXFLAGS=
printProblem_CFLAGS=

# Build analyzeRewardResults
analyzeRewardResults_SOURCES = analyzeRewardResults.cpp
analyzeRewardResults_LDADD = $(MADPLIBS_NORMAL) $(MADP_LD)
analyzeRewardResults_LDFLAGS = $(AM_LDFLAGS) 
analyzeRewardResults_DEPENDENCIES = $(MADPLIBS_NORMAL_NOPARSER)
analyzeRewardResults_CPPFLAGS= $(AM_CPPFLAGS) $(CPP_OPTIMIZATION_FLAGS)
analyzeRewardResults_CXXFLAGS=
analyzeRewardResults_CFLAGS=

# Build getAvgReward
getAvgReward_SOURCES = getAvgReward.cpp
getAvgReward_LDADD = $(MADPLIBS_NORMAL) $(MADP_LD)
getAvgReward_LDFLAGS = $(AM_LDFLAGS) 
getAvgReward_DEPENDENCIES = $(MADPLIBS_NORMAL)
getAvgReward_CPPFLAGS= $(AM_CPPFLAGS) $(CPP_OPTIMIZATION_FLAGS)
getAvgReward_CXXFLAGS=
getAvgReward_CFLAGS=

# Build evaluateRandomPolicy
evaluateRandomPolicy_SOURCES = evaluateRandomPolicy.cpp
evaluateRandomPolicy_LDADD = $(MADPLIBS_NORMAL) $(MADP_LD)
evaluateRandomPolicy_LDFLAGS = $(AM_LDFLAGS) 
evaluateRandomPolicy_DEPENDENCIES = $(MADPLIBS_NORMAL)
evaluateRandomPolicy_CPPFLAGS= $(AM_CPPFLAGS) $(CPP_OPTIMIZATION_FLAGS)
evaluateRandomPolicy_CXXFLAGS=
evaluateRandomPolicy_CFLAGS=

# Build evaluateJointPolicyPureVector
evaluateJointPolicyPureVector_SOURCES = evaluateJointPolicyPureVector.cpp
evaluateJointPolicyPureVector_LDADD = $(MADPLIBS_NORMAL) $(MADP_LD)
evaluateJointPolicyPureVector_LDFLAGS = $(AM_LDFLAGS) 
evaluateJointPolicyPureVector_DEPENDENCIES = $(MADPLIBS_NORMAL)
evaluateJointPolicyPureVector_CPPFLAGS= $(AM_CPPFLAGS) $(CPP_OPTIMIZATION_FLAGS)
evaluateJointPolicyPureVector_CXXFLAGS=
evaluateJointPolicyPureVector_CFLAGS=

# Build evaluatePerseusPolicy
evaluatePerseusPolicy_SOURCES = evaluatePerseusPolicy.cpp
evaluatePerseusPolicy_LDADD = $(MADPLIBS_NORMAL) $(MADP_LD)
evaluatePerseusPolicy_LDFLAGS = $(AM_LDFLAGS) 
evaluatePerseusPolicy_DEPENDENCIES = $(MADPLIBS_NORMAL)
evaluatePerseusPolicy_CPPFLAGS= $(AM_CPPFLAGS) $(CPP_OPTIMIZATION_FLAGS)
evaluatePerseusPolicy_CXXFLAGS=
evaluatePerseusPolicy_CFLAGS=
