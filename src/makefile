MODULES = template 
FLASH = template
AVR_LIBS = libavrhelper libavrserial libavradc libavrlcd libavrcyclon

all::
	@echo " "
	@echo "--> Building $(AVR_LIBS) "
	@echo " "
	for dir in $(AVR_LIBS); do (cd $$dir && $(MAKE) $@ && $(MAKE) install); done
	@echo " "
	@echo "--> Building $(MODULES) "
	@echo " "
	for dir in $(MODULES); do (cd $$dir && $(MAKE) $@); done

clean::
	rm -f *~ *.o .*~
	for dir in $(AVR_LIBS); do (cd $$dir && $(MAKE) $@); done
	for dir in $(MODULES); do (cd $$dir && $(MAKE) $@); done

install:: 
	@echo " "
	@echo "--> Install $(AVR_LIBS) "
	@echo " "
	for dir in $(AVR_LIBS); do (cd $$dir && $(MAKE) $@); done

flash::
	@echo " "
	@echo "--> Flashing $(FLASH) "
	@echo " "
	for dir in $(FLASH); do (cd $$dir && $(MAKE) $@); done
