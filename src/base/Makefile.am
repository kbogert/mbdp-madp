# $Id: Makefile.am 4016 2010-03-11 16:56:02Z mtjspaan $

include $(top_srcdir)/src/Makefile.custom
include $(top_srcdir)/config/Make-rules

##############
# Includedirs, libdirs, libs and cflags for all programs 
INCLUDES		= $(MADP_INCLUDES) -I$(top_srcdir)/src/base\
 -I$(top_srcdir)/src/include
AM_LDFLAGS		= 
LDADD			= 
AM_CPPFLAGS		= -Wall -pipe $(MARCH_FLAGS)


GENERAL_CPPFILES=\
 NamedDescribedEntity.cpp\
 IndexTools.cpp\
 Globals.cpp \
 VectorTools.cpp\
 TimeTools.cpp\
 StringTools.cpp
GENERAL_HFILES=$(GENERAL_CPPFILES:.cpp=.h)\
 PrintTools.h\
 EInvalidIndex.h\
 ENotCached.h\
 EParse.h\
 EOverflow.h\
 E.h\
 Referrer.h\
 DiscreteEntity.h 

#the MADP files should be the more basic data types.
MADP_CPPFILES=JointActionDiscrete.cpp JointObservationDiscrete.cpp\
 TransitionModelDiscrete.cpp ObservationModelDiscrete.cpp\
 TransitionModelMapping.cpp ObservationModelMapping.cpp\
 RewardModelMapping.cpp RewardModelMappingSparse.cpp\
 RewardModelTOISparse.cpp \
 MultiAgentDecisionProcess.cpp\
 MultiAgentDecisionProcessDiscrete.cpp\
 TransitionObservationIndependentMADPDiscrete.cpp TOIDecPOMDPDiscrete.cpp\
 TOIDecMDPDiscrete.cpp TOIFactoredRewardDecPOMDPDiscrete.cpp\
 TOICompactRewardDecPOMDPDiscrete.cpp\
 MADPComponentDiscreteActions.cpp MADPComponentDiscreteObservations.cpp\
 MADPComponentDiscreteStates.cpp DecPOMDP.cpp DecPOMDPDiscrete.cpp\
 POSG.cpp POSGDiscrete.cpp\
 TransitionModelMappingSparse.cpp\
 ObservationModelMappingSparse.cpp

MADP_HFILES=$(MADP_CPPFILES:.cpp=.h) Action.h Observation.h State.h Agent.h\
 ActionDiscrete.h ObservationDiscrete.h StateDiscrete.h\
 JointAction.h JointObservation.h\
 MultiAgentDecisionProcessInterface.h\
 MultiAgentDecisionProcessDiscreteInterface.h \
 DecPOMDPInterface.h\
 DecPOMDPDiscreteInterface.h\
 POSGInterface.h POSGDiscreteInterface.h\
 RewardModel.h ObservationModel.h TransitionModel.h\
 QTableInterface.h\
 StateDistribution.h StateDistributionVector.h\
 TGet.h RGet.h OGet.h

BASE_FILES=$(MADP_CPPFILES) $(MADP_HFILES)\
 $(GENERAL_CPPFILES) $(GENERAL_HFILES)

###############
# All DYNAMIC libraries
# the LTLIBRARIES (LibTool-libraries)

# the library to be build...
lib_LTLIBRARIES =  libMADPBase.la
noinst_LTLIBRARIES =  

# sources for the library:
libMADPBase_la_SOURCES = $(BASE_FILES) 
libMADPBase_la_CPPFLAGS = $(AM_CPPFLAGS) $(CPP_OPTIMIZATION_FLAGS)
libMADPBase_la_LDFLAGS = $(AM_LDFLAGS) 

