ACLOCAL_AMFLAGS = -I m4
SUBDIRS = src 
EXTRA_DIST = src/include/versions.h \
 src/parser/dpomdp.spirit \
 problems \
 doc \
 src/boost

#removes subversion dirs before packing
dist-hook:
	rm -rf `find $(distdir) -name .svn`


bak:	bak-recursive

bak-recursive:
	list='$(SUBDIRS)'; for subdir in $$list; do \
	  test "$$subdir" = . || (cd $$subdir && $(MAKE) $(AM_MAKEFLAGS) bak); \
	done

htmldoc:
	doxygen doc/doxygen.conf
