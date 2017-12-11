#AUTOMAKE_OPTIONS=foreign subdir-objects

includedir = @includedir@/TinyEv
include_HEADERS = ./*.h

TinyEv_VERSION_INFO = 1:0:0
lib_LTLIBRARIES = libTinyEv.la

EXTRA_DIST = *.h
libTinyEv_la_CPPFLAGS = ${CXXFLAGS} -I ./
libTinyEv_la_LDFLAGS = ${LDFLAGS} -shared -fPIC -version-info $(TinyEv_VERSION_INFO)
libTinyEv_la_SOURCES = Ev_Event.cpp Ev_Fifo.cpp Ev_Handle.cpp Ev_Vector.cpp \
					Ev_SocketCli.cpp Ev_SocketSvr.cpp Ev_Stream.cpp \
					Ev_IPCCli.cpp Ev_IPCSvr.cpp Ev_IPCSvrHandle.cpp \
					Ev_Mod_Manager.cpp Ev_Module.cpp \
					Ev_Time.cpp Ev_Timer.cpp \
					Ev_Http.cpp \
					Ev_Uart.cpp \
					Ev_Logger_Console.cpp \
					Ev_Logger_Syslog.cpp \
					Ev_Logger_File.cpp \
					Mod_Logger.cpp \
					Ev_Thread.cpp \
					Ev_Thread_Manager.cpp

