########################################################
#
# template makefile 
#
########################################################
#
include $(AVR_HOME)/include/defines.mk
include $(AVR_HOME)/include/defines_compile_macros.mk
include $(PROJECT_CONTROLLER)

# target + source file (NOTE: only one src file)
TARGET = template
USED_LIBS = avrhelper -lavrserial -lavradc -lavrcyclon
SRC = template.c
HEADER = template.h

#
# common controller defines 
#
# -> see my_m168p_env

#
# my programmer -> a old stk500 on usb<->serial adapter
#
# -> see my_m168p_env

#
# common CFLAGS in $(AVR_HOME)/include/defines.mk
#
CONTROLLER = -mmcu=$(MCU) -DF_CPU=$(F_CPU)UL
OPT_FLAGS = -Os
COMPILER_SWITCHES = -DCONTROLLER_FAMILY=$(CONTROLLER_FAMILY) -DSERIAL_ERROR=$(SERIAL_ERROR) -DADC_ERROR=$(ADC_ERROR)

#
# common fuses in $(AVR_HOME)/include/defines_m168p.mk
#
# to add some useful changes set the below values
# full-speed-mode -> CLDIV8 = 1 -> LFUSE = 0xE2 
# preserve eeprom across flashing -> HFUSE = 0xD7
export FUSE_STRING = -U lfuse:w:${LFUSE}:m -U hfuse:w:${HFUSE}:m -U efuse:w:${EFUSE}:m

#
# ---------  BUILD all in a single step ----------
#
all: $(TARGET).elf $(TARGET).hex $(TARGET).srec $(TARGET).bin $(TARGET)_eeprom.hex $(TARGET)_eeprom.srec $(TARGET)_eeprom.bin $(TARGET).lst size
	@echo "|| "	
	@echo "|| -->   Finished building $(TARGET).* of $(SRC) "
	@echo "|| "

#
# -> compile to object file and link them all to elf
#
# Note: split compile and linkage although only one src file 
%.elf: $(SRC) $(HEADER)
	@echo " "
	@echo "|| "
	@echo "|| -->  Start building $(TARGET).elf "
	@echo "|| "
	$(AVR-GCC) $(WARN) $(DEBUG) -std=$(CSTD) $(CONTROLLER) $(CFLAGS) $(OPT_FLAGS) $(COMPILER_SWITCHES) -save-temps -c $(SRC) -I$(INCLUDEDIR)
	$(AVR-GCC) $(WARN) $(DEBUG) -std=$(CSTD) $(CONTROLLER) $(LDFLAGS) $(TARGET).o --output $@ -L$(LIBDIR) -l$(USED_LIBS)


#
# -> building hex, srec and binary
#
%.hex: %.elf
	@echo " "
	@echo "|| "	
	@echo "|| -->  Start building $(TARGET).hex "
	@echo "|| "
	$(AVR-OBJCOPY) -R .eeprom -O ihex $< $@

%.srec: %.elf
	@echo " "
	@echo "|| "	
	@echo "|| -->  Start building $(TARGET).srec "
	@echo "|| "
	$(AVR-OBJCOPY) -R .eeprom -O srec $< $@

%.bin: %.elf
	@echo " "
	@echo "|| "	
	@echo "|| -->  Start building $(TARGET).bin "
	@echo "|| "
	$(AVR-OBJCOPY) -R .eeprom -O binary $< $@


#
# -> building eeprom files
#
%_eeprom.hex: %.elf
	@echo " "
	@echo "|| "
	@echo "|| -->  Start building $(TARGET).eeprom "
	@echo "|| "
	$(AVR-OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@ 

%_eeprom.srec: %.elf
	@echo " "
	@echo "|| "
	@echo "|| -->  Start building $(TARGET).srec "
	@echo "|| "
	$(AVR-OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O srec $< $@ 

%_eeprom.bin: %.elf
	@echo " "
	@echo "|| "
	@echo "|| -->  Start building $(TARGET).bin "
	@echo "|| "
	$(AVR-OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O binary $< $@ 


%.lst: %.elf
	@echo " "
	@echo "|| "
	@echo "|| -->  Create $(TARGET).lst "
	@echo "|| "
	$(AVR-OBJDUMP) -h -S  $< > $@


# 
# -> surprise surpirse a cleanup tag 
#
clean:
	rm -rf *~ *.i *.s *.elf *.hex *.bin *.srec *.obj *.o *.eeprom *.lst *.map core.d


#
# -> nothing to install
#
install:
	@echo "Nothing to install"

#
# tag needed to build the eeprom file within a clean dir
#
eeprom: $(TARGET).elf
	@echo " "
	@echo "|| "
	@echo "|| -->  Start building $(TARGET).* "
	@echo "|| "
	$(AVR-OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $(TARGET)_eeprom.hex
	$(AVR-OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O srec $< $(TARGET)_eeprom.srec
	$(AVR-OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O binary $< $(TARGET)_eeprom.bin


# 
# show mem usage ... for more use tag readelf
#
size: $(TARGET).elf
	@echo " "
	@echo "|| "
	@echo "|| --> Mem usage "
	@echo "|| "
	$(AVRSIZE) -C --mcu=$(MCU) $(TARGET).elf

#
# show defailed elf infos
#
readelf: $(TARGET).elf
	@echo " "
	@echo "|| "
	@echo "|| --> detailed elf infos "
	@echo "|| "
	readelf --all $(TARGET).elf


#
# --------- fuses programming ----------
#
fuses_prog: 
	$(PROGRAMMER) -c $(PROGRAMMER_HW) -p $(MCU) $(PROGRAMMER_ARGS) $(FUSE_STRING)

fuses_read:
	$(PROGRAMMER) -c $(PROGRAMMER_HW) -p $(MCU) $(PROGRAMMER_ARGS) -nv	

fuses_prog_defaults:
	$(PROGRAMMER) -c $(PROGRAMMER_HW) -p $(MCU) $(PROGRAMMER_ARGS) $(FUSE_DEFAULT)



#
# --------- flash programming ----------
#
flash_all: flash flash_eeprom

flash: $(TARGET).hex 
	$(PROGRAMMER) -c $(PROGRAMMER_HW) -p $(MCU) $(PROGRAMMER_ARGS) -U flash:w:$<

flash_eeprom: $(TARGET).eeprom
	$(PROGRAMMER) -c $(PROGRAMMER_HW) -p $(MCU) $(PROGRAMMER_ARGS) -U eeprom:w:$<


