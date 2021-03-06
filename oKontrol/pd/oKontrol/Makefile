# Makefile to build technobear library for Pure Data.
# Needs Makefile.pdlibbuilder as helper makefile for platform-dependent build
# settings and rules.

# library name
lib.name = mec

# machine := $(shell uname -m)
# ifneq (armv7l,$(machine))
# $(info building for $(machine) with no arm)
# else
# $(info building for $(machine) with arm)
# endif

cflags += -std=c++11 

# due to 3rd party source, consider removing and fixing
cflags += -Wno-unused-parameter -Wno-unused-local-typedefs -Wno-deprecated-declarations


oscpack = ../../../external/oscpack
cflags += -I $(oscpack)
oscpack.sources = \
    $(oscpack)/osc/OscOutboundPacketStream.cpp  \
    $(oscpack)/osc/OscPrintReceivedElements.cpp \
    $(oscpack)/osc/OscReceivedElements.cpp  \
    $(oscpack)/osc/OscTypes.cpp    \
    $(oscpack)/ip/IpEndpointName.cpp 


# only using ring buffer, so incomplete version
portaudio = ../../../external/portaudio
cflags += -I $(portaudio)
portaudio.sources = $(portaudio)/pa_ringbuffer.cpp

okontrol = ../../api
cflags += -I $(okontrol)
okontrol.sources = \
	$(okontrol)/ParameterModel.cpp \
	$(okontrol)/Parameter.cpp \
	$(okontrol)/OSCReceiver.cpp \
	$(okontrol)/OSCBroadcaster.cpp 


define forLinux
     oscpack.sources += $(oscpack)/ip/posix/NetworkingUtils.cpp $(oscpack)/ip/posix/UdpSocket.cpp
endef

define forDarwin
     oscpack.sources += $(oscpack)/ip/posix/NetworkingUtils.cpp $(oscpack)/ip/posix/UdpSocket.cpp
endef

define forWindows
	 ldlibs += -lws2_32 -lwinmm
     oscpack.sources += $(oscpack)/ip/win32/NetworkingUtils.cpp $(oscpack)/ip/win32/UdpSocket.cpp
endef 

common.sources = \
	$(oscpack.sources) \
	$(portaudio.sources) \
	$(okontrol.sources)


# input source file (class name == source file basename)

class.sources = \
	oKontrol.cpp \
			

# all extra files to be included in binary distribution of the library
datafiles = \
			../README.md 


include ../Makefile.pdlibbuilder
