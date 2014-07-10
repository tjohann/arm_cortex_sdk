########################################################
#
# makefile for libavrhelper 
#
########################################################
#
include ${AVR_HOME}/include/defines.mk
include $(AVR_HOME)/include/defines_compile_macros.mk
include $(PROJECT_CONTROLLER)

# target + source file list
TARGET = libavrhelper
SRC = libavrhelper.c
HEADER = libavrhelper.h

#
# common controller defines 
#
# -> see my_m168p_env

#
# common CFLAGS in $(AVR_HOME)/include/defines.mk
#
CONTROLLER = -mmcu=$(MCU) -DF_CPU=$(F_CPU)UL
OPT_FLAGS = -Os
COMPILER_SWITCHES = -DCONTROLLER_FAMILY=$(CONTROLLER_FAMILY)

#
# ---------  BUILD all in a single step ----------
#
all: $(TARGET).a $(TARGET).lst

$(TARGET).a: $(TARGET).c $(TARGET).h
	@echo "$(AVR_HOME)"
	@echo "|| "	
	@echo "|| -->   building $(TARGET).a of $(SRC) for target $(MCU)"
	@echo "|| "
	$(AVR-GCC) $(WARN) $(DEBUG) -std=$(CSTD) $(CONTROLLER) $(CFLAGS) $(OPT_FLAGS) $(COMPILER_SWITCHES) -save-temps -c $(SRC) -I$(INCLUDEDIR)
	$(AVR-AR) rcv $(TARGET).a $(TARGET).o

%.lst: %.a
	@echo " "
	@echo "|| "
	@echo "|| -->  Create $(TARGET).lst "
	@echo "|| "
	$(AVR-OBJDUMP) -h -S $< > $@

install: $(TARGET).a
	cp -d *.a $(AVR_HOME)/lib
	cp -d *.h $(AVR_HOME)/include

# 
# -> surprise surpirse a cleanup tag 
#
clean:
	rm -rf *~ *.a *.i *.s *.elf *.hex *.bin *.srec *.obj *.o *.eeprom *.lst *.map core.d





