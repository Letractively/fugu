#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/526502843/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lboost_system -lrt -lboost_thread -Wl,-rpath ../redis4cpp/dist/Release/GNU-Linux-x86 -L../redis4cpp/dist/Release/GNU-Linux-x86 -lredis4cpp

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../redis4cpp/${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/redisclient

../redis4cpp/${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/redisclient: ../redis4cpp/dist/Release/GNU-Linux-x86/libredis4cpp.so

../redis4cpp/${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/redisclient: ${OBJECTFILES}
	${MKDIR} -p ../redis4cpp/${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ../redis4cpp/${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/redisclient ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/526502843/main.o: ../../src/redisclient/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/526502843
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../src -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/526502843/main.o ../../src/redisclient/main.cpp

# Subprojects
.build-subprojects:
	cd ../redis4cpp && ${MAKE}  -f Makefile CONF=Release

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../redis4cpp/${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/redisclient

# Subprojects
.clean-subprojects:
	cd ../redis4cpp && ${MAKE}  -f Makefile CONF=Release clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
