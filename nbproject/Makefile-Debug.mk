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
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Background.o \
	${OBJECTDIR}/Gtk_Widget.o \
	${OBJECTDIR}/main.o


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
LDLIBSOPTIONS=-lgtk-x11-2.0 -lgdk-x11-2.0 -latk-1.0 -lgdk_pixbuf-2.0 -lm -lpangocairo-1.0 -lfontconfig -lXext -lXrender -lXinerama -lXi -lXrandr -lXcursor -lXfixes -lpango-1.0 -lcairo -lX11 -lgobject-2.0 -ldl -lglib-2.0 -lgtkdatabox -lgmodule-2.0

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gestione-borsa

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gestione-borsa: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gestione-borsa ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Background.o: Background.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -I/usr/include/gtk-2.0 -I/usr/include/cairo -I/usr/include/glib-2.0 -I/usr/include/atk-1.0 -I/usr/include/pango-1.0 -I/usr/include/libpng16 -I/usr/include/freetype2 -I/usr/lib/glib-2.0/include -I/usr/lib/gtk-2.0/include -I/usr/include/gdk-pixbuf-2.0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Background.o Background.c

${OBJECTDIR}/Gtk_Widget.o: Gtk_Widget.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -I/usr/include/gtk-2.0 -I/usr/include/cairo -I/usr/include/glib-2.0 -I/usr/include/atk-1.0 -I/usr/include/pango-1.0 -I/usr/include/libpng16 -I/usr/include/freetype2 -I/usr/lib/glib-2.0/include -I/usr/lib/gtk-2.0/include -I/usr/include/gdk-pixbuf-2.0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Gtk_Widget.o Gtk_Widget.c

${OBJECTDIR}/main.o: main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -I/usr/include/gtk-2.0 -I/usr/include/cairo -I/usr/include/glib-2.0 -I/usr/include/atk-1.0 -I/usr/include/pango-1.0 -I/usr/include/libpng16 -I/usr/include/freetype2 -I/usr/lib/glib-2.0/include -I/usr/lib/gtk-2.0/include -I/usr/include/gdk-pixbuf-2.0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gestione-borsa

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
