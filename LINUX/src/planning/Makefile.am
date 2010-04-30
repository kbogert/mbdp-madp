# $Id: Makefile.am 3652 2009-09-07 17:14:02Z mtjspaan $

include $(top_srcdir)/src/Makefile.custom
include $(top_srcdir)/config/Make-rules

##############
# Includedirs, libdirs, libs and cflags for all programs 
INCLUDES		= $(MADP_INCLUDES) -I$(top_srcdir)/src/base\
 -I$(top_srcdir)/src/include -I$(top_srcdir)/src/support -I$(top_srcdir)/src/planning\
 -I$(top_srcdir)/src/parser 

AM_LDFLAGS		= 
AM_CPPFLAGS		= -Wall -pipe $(MARCH_FLAGS)

SIMULATION_CPPFILES=SimulationResult.cpp\
 SimulationDecPOMDPDiscrete.cpp \
 AgentPOMDP.cpp\
 AgentBG.cpp\
 AgentQMDP.cpp\
 AgentRandom.cpp

SIMULATION_HFILES=$(SIMULATION_CPPFILES:.cpp=.h) \
 Simulation.h\
 SimulationAgent.h \
 AgentDecPOMDPDiscrete.h\
 AgentDelayedSharedObservations.h\
 AgentFullyObservable.h\
 AgentSharedObservations.h\
 AgentLocalObservations.h

GMAA_CPPFILES=\
 GeneralizedMAAStarPlanner.cpp \
 GeneralizedMAAStarPlannerForDecPOMDPDiscrete.cpp \
 GMAA_MAAstar.cpp\
 GMAA_kGMAA.cpp\
 PolicyPoolJPolValPair.cpp\
 PolicyPoolPartialJPolValPair.cpp\
 JPPVValuePair.cpp \
 JPPVIndexValuePair.cpp\
 PartialJPDPValuePair.cpp\
 PartialJPPVIndexValuePair.cpp
GMAA_HFILES=$(GMAA_CPPFILES:.cpp=.h)\
 PolicyPoolInterface.h\
 PartialPolicyPoolInterface.h\
 PartialPolicyPoolItemInterface.h\
 PolicyPoolItemInterface.h


POMDP_CPPFILES=\
 BeliefValue.cpp\
 AlphaVector.cpp \
 AlphaVectorPlanning.cpp\
 Perseus.cpp \
 AlphaVectorPOMDP.cpp\
 PerseusPOMDPPlanner.cpp\
 AlphaVectorBG.cpp\
 PerseusBGPlanner.cpp \
 PerseusQFunctionPlanner.cpp\
 PerseusStationary.cpp
POMDP_HFILES=$(POMDP_CPPFILES:.cpp=.h)\
 ValueFunctionPOMDPDiscrete.h\
 BGBackupType.h\
 PerseusBackupType.h\
 BeliefSet.h \
 QAV.h QAVParameters.h


PLANNING_CPPFILES=\
 BruteForceSearchPlanner.cpp\
 JESPExhaustivePlanner.cpp\
 JESPDynamicProgrammingPlanner.cpp\
 DICEPSPlanner.cpp\
 MBDPPlanner.cpp\
 QBG.cpp QPOMDP.cpp QMDP.cpp\
 MDPSolver.cpp\
 MDPValueIteration.cpp \
 BayesianGameIdenticalPayoffSolver.cpp\
 BGIP_SolverRandom.cpp \
 QFunction.cpp\
 QFunctionForDecPOMDP.cpp\
 QFunctionJAOHInterface.cpp\
 QFunctionJAOH.cpp\
 QFunctionJAOHTree.cpp\
 QFunctionJointBelief.cpp \
 qheur.cpp\
 gmaatype.cpp\
 JESPtype.cpp\
 BGIP_SolverType.cpp\
 BayesianGameBase.cpp \
 BayesianGame.cpp \
 BayesianGameIdenticalPayoff.cpp\
 BayesianGameForDecPOMDPStage.cpp\
 BGforStageCreation.cpp\
 BayesianGameForDecPOMDPStageInterface.cpp\
 Type.cpp\
 Type_AOHIndex.cpp\
 BGIPSolution.cpp\
 ValueFunctionDecPOMDPDiscrete.cpp\
 argumentHandlers.cpp\
 argumentUtils.cpp\
 directories.cpp

PLANNING_HFILES=$(PLANNING_CPPFILES:.cpp=.h) \
 argumentHandlersPostChild.h\
 JointPolicyValuePair.h\
 PartialJointPolicyValuePair.h\
 ValueFunction.h\
 QFunctionInterface.h\
 QFunctionForDecPOMDPInterface.h\
 QFunctionJAOHInterface.h\
 QFunctionJointBeliefInterface.h\
 BGIP_SolverCreatorInterface.h\
 BGIP_SolverCreator_AM.h\
 BGIP_SolverCreator_BFS.h\
 BayesianGameIdenticalPayoffInterface.h\
 BGIP_SolverBruteForceSearch.h\
 BGIP_SolverAlternatingMaximization.h

PLANNING_FILES=$(PLANNING_CPPFILES) $(PLANNING_HFILES)\
 $(SIMULATION_CPPFILES) $(SIMULATION_HFILES)\
 $(POMDP_CPPFILES) $(POMDP_HFILES)\
 $(GMAA_CPPFILES) $(GMAA_HFILES)

###############
# All DYNAMIC libraries
# the LTLIBRARIES (LibTool-libraries)

# the library to be build...
lib_LTLIBRARIES =  libMADPPlanning.la
noinst_LTLIBRARIES =  

# sources for the library:
libMADPPlanning_la_SOURCES = $(PLANNING_FILES)
libMADPPlanning_la_CPPFLAGS = $(AM_CPPFLAGS) $(CPP_OPTIMIZATION_FLAGS)
libMADPPlanning_la_LDFLAGS = $(AM_LDFLAGS)
libMADPPlanning_la_LIBADD = 
