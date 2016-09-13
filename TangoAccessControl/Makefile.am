SUBDIRS = ../AbstractClass

AM_CPPFLAGS = -I$(top_srcdir)/lib/cpp/client \
	   	   -I$(top_srcdir)/lib/cpp/server $(ORB_INCLUDE_PREFIX) \
           -I$(top_srcdir)/lib/cpp/log4tango/include \
           -I$(top_builddir)/lib/cpp/log4tango/include \
           -I$(top_builddir)/lib/cpp/server \
		   -I$(top_srcdir)/cppserver/AbstractClass/AccessControl \
		   $(MYSQLCLIENT_CFLAGS) $(LIBZMQ_CFLAGS)

bin_PROGRAMS=TangoAccessControl

TangoAccessControl_SOURCES=ClassFactory.cpp     		\
                  TangoAccessControlClass.cpp  	 		\
                  TangoAccessControl.cpp 				\
                  TangoAccessControlStateMachine.cpp 	\
				  DbUtils.cpp 							\
                  main.cpp 								\
				  TangoAccessControl.h  				\
				  TangoAccessControlClass.h          


TangoAccessControl_LDADD = -L$(top_builddir)/lib/cpp/client -ltango \
        					-L$(top_builddir)/lib/cpp/log4tango/src -llog4tango \
							$(MYSQLCLIENT_LDFLAGS) $(MYSQLCLIENT_LIBS) $(LIBZMQ_LIBS) \
							../AbstractClass/AccessControl/libaccesscontrol.la
