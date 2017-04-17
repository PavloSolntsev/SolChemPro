## Process this file with automake to produce Makefile.in

#ui_DATA = solchempro.ui \
#	ScpMainwindow.ui \
#	Settingswindow.ui \
#	NewComponentWindow.ui \
#	Newrmexpwindow.ui


bin_PROGRAMS = solchempro

#DEVMODE_CXX = -Wall -g2 -O0
AM_CXXFLAGS = -Wall -std=c++11
CTAGSFLAGS = --c++-kinds=* --fields=+iaSmKz --extra=+q --language-force=C++

solchempro_CXXFLAGS = $(SOLCHEMPRO_CFLAGS) $(AM_CXXFLAGS) 
solchempro_CFLAGS = $(SOLCHEMPRO_GIO_CFLAGS) $(AM_CFLAGS) 
solchempro_LDADD = $(SOLCHEMPRO_LIBS)  

BUILT_SOURCES = solchempro.gresource.c

GRESOURCE_FILE = solchempro.gresource.xml
glade_FILES = ScpMainwindow.glade
gresource_FILES = $(GRESOURCE_FILE) \
					$(glade_FILES)

.PRECIOUS: $(gresource_FILES)

solchempro.gresource.c: $(gresource_FILES)
	$(AM_V_GEN)	$(GLIB_COMPILE_RESOURCES) $(srcdir)/$(GRESOURCE_FILE) \
			--target=$@ --sourcedir=$(srcdir) --generate-source

test.gresource: $(GLIB_COMPILE_RESOURCES) 
	$(AM_V_GEN) $(GLIB_COMPILE_RESOURCES) --generate-dependencies $(GRESOURCE_FILE) 


solchempro_SOURCES = \
	main.cpp \
	ScpMainwindow.hpp \
	ScpMainwindow.cpp \
	ScpApplication.hpp \
	ScpApplication.cpp \
	ScpAssistant.hpp \
	ScpAssistant.cpp \
	ScpKeyfile.hpp \
	solchempro.gresource.c \
	ScpEnum.hpp \
	ScpTime.hpp \
	ScpTime.cpp \
	ScpReccord.hpp \
	ScpReccord.cpp \
	ScpProject.hpp \
	ScpProject.cpp \
	$(NULL)

