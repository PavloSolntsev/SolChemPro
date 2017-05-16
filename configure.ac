#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([solchempro], [0.1], [pavlo.solntsev@gmail.com])
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE
AC_CONFIG_MACRO_DIR([m4])
if test -z $CXXFLAGS; then 
    CXXFLAGS='-O0 -g2 '
fi

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
PKG_CHECK_MODULES(SOLCHEMPRO, [gtkmm-3.0 glibmm-2.54 gdkmm-3.0 giomm-2.54 libgdamm-6.0])
PKG_CHECK_MODULES(SOLCHEMPRO_GIO, [glib-2.0])

# Checks for header files.
#AC_CHECK_HEADERS([libintl.h string.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.


# Some defined variables
AC_DEFINE( MAX_USER_NUMBER,5,[Restrict connection only to five users.])
AC_DEFINE( INIFILE,"SolChemPro.ini",[Define INI file for the pproject])
GLIB_GSETTINGS
AC_CHECK_PROG(HAVE_GLIB_COMPILE_RESOURCES,glib-compile-resources, yes, no)
if test "$HAVE_GLIB_COMPILE_RESOURCES" == "yes"; then 
	AC_PATH_PROG(GLIB_COMPILE_RESOURCES,glib-compile-resources)
else
	AC_MSG_ERROR(Cannot find glib-compile-resource.)
fi
AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
