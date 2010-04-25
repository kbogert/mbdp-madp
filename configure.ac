#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(MADP, 0.2.1, faolieho@science.uva.nl)
AM_INIT_AUTOMAKE
#old
#AC_CONFIG_SRCDIR([src/])
#AC_CONFIG_HEADER([config.h])
#AC_CONFIG_FILES -> at bottom of file!
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET


#not sure if this is correct:
#CPPFLAGS="$CPPFLAGS"
#CXXFLAGS="$CXXFLAGS"
#CFLAGS="$CFLAGS"
CPPFLAGS=" " 
CXXFLAGS=" "
CFLAGS=" "

#specified the flags in src/Makefile.am
# You can turn off shared libraries during beta-testing, since they
# make the build process take too long.
# AC_DISABLE_SHARED
# AC_DISABLE_STATIC
AC_PROG_LIBTOOL

# these doxygen macros are outdated...
#doxygen stuff: 
#DX_HTML_FEATURE(ON)
#DX_CHM_FEATURE(OFF)
#DX_CHI_FEATURE(OFF)
#DX_MAN_FEATURE(OFF)
#DX_RTF_FEATURE(OFF)
#DX_XML_FEATURE(OFF)
#DX_PDF_FEATURE(OFF)
#DX_PS_FEATURE(OFF)
#DX_INIT_DOXYGEN(MADP, doc/doxygen.conf, doc/html)

# Checks for libraries.

# Don't check for boost, since we included it in the source tree
#AX_BOOST_BASE(1.32.1)

# Checks for header files.
AC_HEADER_STDC
AC_HEADER_STDBOOL
AC_CHECK_HEADERS([float.h limits.h stdlib.h])
# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_CHECK_FUNCS([pow strtoull])

AC_CONFIG_FILES([Makefile \
                 src/Makefile \
		 src/parser/Makefile \
		 src/base/Makefile \
		 src/support/Makefile \
		 src/planning/Makefile \
                 src/examples/Makefile \
                 src/utils/Makefile])

AC_OUTPUT


