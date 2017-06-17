## Process this file with automake to produce Makefile.in

noinst_LIBRARIES = libscpgui.a

BUILT_SOURCES = solchempro.gresource.c

libscpgui_a_CFLAGS = $(SOLCHEMPRO_CFLAGS)

GRESOURCE_FILE = solchempro.gresource.xml
glade_FILES = scp-guisettings.glade \
	      scp-mainwindow.glade

gresource_FILES = $(GRESOURCE_FILE) \
					$(glade_FILES)

.PRECIOUS: $(gresource_FILES)

solchempro.gresource.c: $(gresource_FILES)
	$(AM_V_GEN)	$(GLIB_COMPILE_RESOURCES) $(srcdir)/$(GRESOURCE_FILE) \
			--target=$@ --sourcedir=$(srcdir) --generate-source

solchempro.gresource: $(GLIB_COMPILE_RESOURCES) 
	$(AM_V_GEN) $(GLIB_COMPILE_RESOURCES) --generate-dependencies $(srcdir)/$(GRESOURCE_FILE) 

libscpgui_a_SOURCES = \
	$(BUILT_SOURCES) \
	$(NULL)

