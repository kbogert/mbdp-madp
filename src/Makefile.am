# $Id: Makefile.am 2095 2008-01-16 15:17:27Z mtjspaan $

# Lists all the subdirs where 'make' has to look
# When changing the subdirs, also change AC_CONFIG_FILES in configure.ac
SUBDIRS = base support parser planning utils examples

include $(top_srcdir)/src/Makefile.custom
include $(top_srcdir)/config/Make-rules

htmldoc:
	cd ../doc; doxygen doxygen.conf

