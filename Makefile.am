AUTOMAKE_OPTIONS=foreign subdir-objects

lib_LTLIBRARIES = libTinyEv.la
bin_PROGRAMS = TinyEv_domain

#1.libTinyEv.so
libTinyEv_la_LDFLAGS = ${LDFLAGS} -shared -fPIC
libTinyEv_la_CPPFLAGS = ${CXXFLAGS} -I ./src
libTinyEv_la_SOURCES = src/Ev_Event.cpp src/Ev_Fifo.cpp src/Ev_Handle.cpp src/Ev_Vector.cpp \
					src/Ev_SocketCli.cpp src/Ev_SocketSvr.cpp src/Ev_Stream.cpp \
					src/Ev_IPCCli.cpp src/Ev_IPCSvr.cpp src/Ev_IPCSvrHandle.cpp \
					src/Ev_Mod_Manager.cpp src/Ev_Module.cpp \
					src/Ev_Time.cpp src/Ev_Timer.cpp \
					src/Ev_Http.cpp \
					src/Ev_Uart.cpp

#2.TinyEv_domain
TinyEv_domain_LDFLAGS = ${LDFLAGS} -lTinyEv -lev -lpthread
TinyEv_domain_CPPFLAGS = ${CXXFLAGS} -I ./src
TinyEv_domain_SOURCES = daemon/TinyEv_domain.cpp

