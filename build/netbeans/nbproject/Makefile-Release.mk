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
	${OBJECTDIR}/_ext/1445274692/jsonreply.o \
	${OBJECTDIR}/_ext/1445274692/session.o \
	${OBJECTDIR}/_ext/1445274692/libuvconnection.o \
	${OBJECTDIR}/_ext/1445274692/handlerrouter.o \
	${OBJECTDIR}/_ext/1445274692/connection.o \
	${OBJECTDIR}/_ext/1445274692/config.o \
	${OBJECTDIR}/_ext/1445274692/jsonmodel.o \
	${OBJECTDIR}/_ext/1379188117/http_parser.o \
	${OBJECTDIR}/_ext/1445274692/stringutils.o \
	${OBJECTDIR}/_ext/1445274692/pinghandler.o \
	${OBJECTDIR}/_ext/1445274692/entrypoint.o \
	${OBJECTDIR}/_ext/1445274692/webapplication.o \
	${OBJECTDIR}/_ext/1445274692/htmlreply.o \
	${OBJECTDIR}/_ext/1445274692/httpparser.o \
	${OBJECTDIR}/_ext/1445274692/registrator.o \
	${OBJECTDIR}/_ext/1445274692/handler.o \
	${OBJECTDIR}/_ext/1445274692/query.o \
	${OBJECTDIR}/_ext/1445274692/bytebuffer.o \
	${OBJECTDIR}/_ext/1445274692/logger.o \
	${OBJECTDIR}/_ext/1445274692/reply.o \
	${OBJECTDIR}/_ext/1445274692/exception.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/netbeans

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/netbeans: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/netbeans ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/1445274692/jsonreply.o: ../../src/jsonreply.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445274692
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1445274692/jsonreply.o ../../src/jsonreply.cpp

${OBJECTDIR}/_ext/1445274692/session.o: ../../src/session.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445274692
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1445274692/session.o ../../src/session.cpp

${OBJECTDIR}/_ext/1445274692/libuvconnection.o: ../../src/libuvconnection.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445274692
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1445274692/libuvconnection.o ../../src/libuvconnection.cpp

${OBJECTDIR}/_ext/1445274692/handlerrouter.o: ../../src/handlerrouter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445274692
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1445274692/handlerrouter.o ../../src/handlerrouter.cpp

${OBJECTDIR}/_ext/1445274692/connection.o: ../../src/connection.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445274692
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1445274692/connection.o ../../src/connection.cpp

${OBJECTDIR}/_ext/1445274692/config.o: ../../src/config.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445274692
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1445274692/config.o ../../src/config.cpp

${OBJECTDIR}/_ext/1445274692/jsonmodel.o: ../../src/jsonmodel.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445274692
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1445274692/jsonmodel.o ../../src/jsonmodel.cpp

${OBJECTDIR}/_ext/1379188117/http_parser.o: ../../src/http_parser/http_parser.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1379188117
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1379188117/http_parser.o ../../src/http_parser/http_parser.c

${OBJECTDIR}/_ext/1445274692/stringutils.o: ../../src/stringutils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445274692
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1445274692/stringutils.o ../../src/stringutils.cpp

${OBJECTDIR}/_ext/1445274692/pinghandler.o: ../../src/pinghandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445274692
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1445274692/pinghandler.o ../../src/pinghandler.cpp

${OBJECTDIR}/_ext/1445274692/entrypoint.o: ../../src/entrypoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445274692
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1445274692/entrypoint.o ../../src/entrypoint.cpp

${OBJECTDIR}/_ext/1445274692/webapplication.o: ../../src/webapplication.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445274692
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1445274692/webapplication.o ../../src/webapplication.cpp

${OBJECTDIR}/_ext/1445274692/htmlreply.o: ../../src/htmlreply.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445274692
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1445274692/htmlreply.o ../../src/htmlreply.cpp

${OBJECTDIR}/_ext/1445274692/httpparser.o: ../../src/httpparser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445274692
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1445274692/httpparser.o ../../src/httpparser.cpp

${OBJECTDIR}/_ext/1445274692/registrator.o: ../../src/registrator.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445274692
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1445274692/registrator.o ../../src/registrator.cpp

${OBJECTDIR}/_ext/1445274692/handler.o: ../../src/handler.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445274692
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1445274692/handler.o ../../src/handler.cpp

${OBJECTDIR}/_ext/1445274692/query.o: ../../src/query.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445274692
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1445274692/query.o ../../src/query.cpp

${OBJECTDIR}/_ext/1445274692/bytebuffer.o: ../../src/bytebuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445274692
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1445274692/bytebuffer.o ../../src/bytebuffer.cpp

${OBJECTDIR}/_ext/1445274692/logger.o: ../../src/logger.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445274692
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1445274692/logger.o ../../src/logger.cpp

${OBJECTDIR}/_ext/1445274692/reply.o: ../../src/reply.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445274692
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1445274692/reply.o ../../src/reply.cpp

${OBJECTDIR}/_ext/1445274692/exception.o: ../../src/exception.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445274692
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1445274692/exception.o ../../src/exception.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/netbeans

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
