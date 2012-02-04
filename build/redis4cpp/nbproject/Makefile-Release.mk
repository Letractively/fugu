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
	${OBJECTDIR}/_ext/1591920417/sender.o \
	${OBJECTDIR}/_ext/1591920417/connection.o \
	${OBJECTDIR}/_ext/1591920417/bytebuffer.o \
	${OBJECTDIR}/_ext/1591920417/reciever.o \
	${OBJECTDIR}/_ext/1591920417/interfaceimpl.o \
	${OBJECTDIR}/_ext/1591920417/commands.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libredis4cpp.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libredis4cpp.so: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -shared -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libredis4cpp.so -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/1591920417/sender.o: ../../src/redis4cpp/sender.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1591920417
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../src -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1591920417/sender.o ../../src/redis4cpp/sender.cpp

${OBJECTDIR}/_ext/1591920417/connection.o: ../../src/redis4cpp/connection.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1591920417
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../src -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1591920417/connection.o ../../src/redis4cpp/connection.cpp

${OBJECTDIR}/_ext/1591920417/bytebuffer.o: ../../src/redis4cpp/bytebuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1591920417
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../src -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1591920417/bytebuffer.o ../../src/redis4cpp/bytebuffer.cpp

${OBJECTDIR}/_ext/1591920417/reciever.o: ../../src/redis4cpp/reciever.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1591920417
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../src -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1591920417/reciever.o ../../src/redis4cpp/reciever.cpp

${OBJECTDIR}/_ext/1591920417/interfaceimpl.o: ../../src/redis4cpp/interfaceimpl.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1591920417
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../src -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1591920417/interfaceimpl.o ../../src/redis4cpp/interfaceimpl.cpp

${OBJECTDIR}/_ext/1591920417/commands.o: ../../src/redis4cpp/commands.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1591920417
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../src -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1591920417/commands.o ../../src/redis4cpp/commands.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libredis4cpp.so

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
