mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS +=

APPL_CXXOBJS += \
	section_core.o \
	section.o \
	run_area.o \
	control.o \
	ev3f.o \
	pid.o \
	run.o \
	measurement_core.o \
	calibration.o \
	color.o \
	curve.o \
	vector.o \
	dataIO.o
SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif

APPL_DIRS += \
	$(mkfile_path)measurement \
	$(mkfile_path)control \
	$(mkfile_path)section

INCLUDES += \
	-I$(mkfile_path)measurement \
	-I$(mkfile_path)control \
	-I$(mkfile_path)section

#COPTS += -fno-use-cxa-atexit

COPTS += -DMAKE_EV3 -std=c++14 -std=c++1y
