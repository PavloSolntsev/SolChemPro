## Process this file with automake to produce Makefile.in

SUBDIRS = gcl src 
ACLOCAL_AMFLAGS = -I m4

dist_doc_DATA = \
	README \
	COPYING \
	AUTHORS \
	ChangeLog \
	INSTALL \
	NEWS

CTAGSFLAGS = --c++-kinds=+p --fields=+iaS --extra=+q --language-force=C++

# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(docdir)
