# common defines

# add global include dir
INCLUDEDIR = ./includes 
INCLUDEDIR += -I${AVR_HOME}/include

# add global lib dir
LIBDIR = ./lib 
LIBDIR += -L${AVR_HOME}/lib

# install dirs 
INSTALL_BIN = $(AVR_HOME)/bin
INSTALL_LIB = $(AVR_HOME)/lib
INSTALL_INCL = $(AVR_HOME)/include
INSTALL_MAN = $(AVR_HOME)/man
INSTALL_ETC = $(AVR_HOME)/etc
INSTALL_SHARE = $(AVR_HOME)/share

# common cflags
CFLAGS = -ffunction-sections -fdata-sections 
LDFLAGS = -Wl,--relax,--gc-sections -Wl,-Map,$(TARGET).map

# common stuff
#WARN = -Wall -Wstrict-prototypes
WARN = -Wall 
DEBUG = -g -ggdb
CSTD = gnu99

# common tool defines
AVR-GCC = avr-gcc
AVR-AR = avr-ar
AVR-OBJCOPY = avr-objcopy
AVR-OBJDUMP = avr-objdump
AVRSIZE = avr-size

# atmege168 defaults 
LFUSE = 0x62
# full-speed-mode -> CLDIV8 = 1 
# -> LFUSE = 0xE2 
HFUSE = 0xdf
# preserve eeprom across flashing 
# -> HFUSE = 0xD7
EFUSE = 0x00

# default fuses 
FUSE_DEFAULT = -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m -U efuse:w:$(EFUSE):m

