## Process this file with automake to produce Makefile.in

#ui_DATA = solchempro.ui \
#	ScpMainwindow.ui \
#	Settingswindow.ui \
#	NewComponentWindow.ui \
#	Newrmexpwindow.ui

bin_PROGRAMS = solchempro
#DEVMODE_CXX = -Wall -g2 -O0
AM_CXXFLAGS = -Wall -std=c++11 -I$(srcdir)/gcl
AM_CFLAGS = $(SOLCHEMPRO_CFLAGS) 
CTAGSFLAGS = --c++-kinds=* --fields=+iaSmKz --extra=+q --language-force=C++

solchempro_CXXFLAGS = $(SOLCHEMPRO_CFLAGS) $(AM_CXXFLAGS) 
solchempro_CFLAGS = $(SOLCHEMPRO_CFLAGS) $(AM_CFLAGS) 
solchempro_LDADD = $(SOLCHEMPRO_LIBS) -lgcl 
solchempro_LDFLAGS = -L$(top_builddir)/gcl 

BUILT_SOURCES = solchempro.gresource.c

solchempro_SOURCES = \
	main.cpp \
	ScpMainwindow.hpp \
	ScpMainwindow.cpp \
	ScpApplication.hpp \
	ScpApplication.cpp \
	ScpAssistant.hpp \
	ScpAssistant.cpp \
	ScpKeyfile.hpp \
	ScpEnum.hpp \
	ScpTime.hpp \
	ScpTime.cpp \
	ScpReccord.hpp \
	ScpReccord.cpp \
	ScpProject.hpp \
	ScpProject.cpp \
	ScpNewproject.hpp \
	ScpNewproject.cpp \
	ScpTable.hpp \
	ScpTable.cpp \
	ScpSettings.hpp \
	ScpSettings.cpp \
	ScpGuipath.hpp \
	ScpGUISettings.hpp \
	ScpGUISettings.cpp \
	$(BUILT_SOURCES) \
	$(NULL)

GRESOURCE_FILE = $(top_srcdir)/data/solchempro.gresource.xml
glade_FILES = $(top_srcdir)/data/scp-guisettings.glade \
			  $(top_srcdir)/data/scp-mainwindow.glade

gresource_FILES = $(GRESOURCE_FILE) \
					$(glade_FILES)

.PRECIOUS: $(gresource_FILES)

solchempro.gresource.c: $(gresource_FILES)
	$(AM_V_GEN)	$(GLIB_COMPILE_RESOURCES) $(GRESOURCE_FILE) \
			--target=$@ --sourcedir=$(top_srcdir)/data --generate-source

solchempro.gresource: $(GLIB_COMPILE_RESOURCES) 
	$(AM_V_GEN) $(GLIB_COMPILE_RESOURCES) --generate-dependencies $(srcdir)/$(GRESOURCE_FILE) 


