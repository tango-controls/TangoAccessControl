

INCLUDES = -I$(top_srcdir)/lib/cpp/client \
	   	   -I$(top_srcdir)/lib/cpp/server $(ORB_INCLUDE_PREFIX) \
           -I$(top_srcdir)/lib/cpp/log4tango/include \
           -I$(top_builddir)/lib/cpp/log4tango/include $(LIBZMQ_CFLAGS)

AM_CXXFLAGS= @CPP_ELEVEN@

# We're making a libtool convenience library which is not to be installed,
# therefore the automake noinst variable
noinst_LTLIBRARIES = libaccesscontrol.la

# These are the sources for the library.
libaccesscontrol_la_SOURCES =	AccessControl.cpp \
								AccessControlClass.cpp \
								AccessControlStateMachine.cpp \
								AccessControl.h \
								AccessControlClass.h
					   
