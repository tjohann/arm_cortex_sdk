# common defines for m168(pa)

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

#
# Note: 
#       set FUSE_STRING in project makefile
#
# to add some useful changes set the below values
# full-speed-mode -> CLDIV8 = 1 -> LFUSE = 0xE2 
# preserve eeprom across flashing -> HFUSE = 0xD7
# FUSE_STRING = -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m -U efuse:w:$(EFUSE):m 
