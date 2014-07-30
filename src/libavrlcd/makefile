########################################################
#
# makefile for libavrlcd
#
########################################################
#
include $(AVR_HOME)/include/defines.mk
include $(AVR_HOME)/include/defines_compile_macros.mk
include $(PROJECT_CONTROLLER)

# target + source file list
TARGET = libavrlcd
SRC = libavrlcd.c
HEADER = libavrlcd.h


#
# common controller defines 
#
# -> see my_*

#
# common CFLAGS in $(AVR_HOME)/include/defines.mk
#
CONTROLLER = -mmcu=$(MCU) -DF_CPU=$(F_CPU)UL 
OPT_FLAGS = -Os
COMPILER_SWITCHES = -DCONTROLLER_FAMILY=$(CONTROLLER_FAMILY) -DUSE_LCD=$(USE_LCD) -DLCD_ERROR=$(LCD_ERROR) -DLCD_COMMON_PORT=$(LCD_COMMON_PORT)

#
# ---------  BUILD all in a single step ----------
#
all: $(TARGET).a $(TARGET).lst

$(TARGET).a: $(TARGET).c $(TARGET).h $(TARGET)_priv.h
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






