main = none

#include include/defines.mk

MODULES = src
MODULES_ADDITIONAL = include lib man bin etc docs schematics

all::
	@echo "+-----------------------------------------------+"
	@echo "|                                               |"
	@echo "|            Building all in src                |"
	@echo "|                                               |"
	@echo "+-----------------------------------------------+"
	for dir in $(MODULES); do (cd $$dir && $(MAKE) $@); done

clean::
	rm -f *~ *.o .*~
	for dir in $(MODULES); do (cd $$dir && $(MAKE) $@); done
	for dir in $(MODULES_ADDITIONAL); do (cd $$dir && $(MAKE) $@); done

distclean: clean
	@echo "+-----------------------------------------------+"
	@echo "|                                               |"
	@echo "|         Nothing to do for distclean           |"
	@echo "|                                               |"
	@echo "+-----------------------------------------------+"	

install:: all
	@echo "+-----------------------------------------------+"
	@echo "|                                               |"
	@echo "|            Install all in src                 |"
	@echo "|                                               |"
	@echo "+-----------------------------------------------+"
	for dir in $(MODULES); do (cd $$dir && $(MAKE) $@); done


flash::
	@echo "+-----------------------------------------------+"
	@echo "|                                               |"
	@echo "|            Flashing template                  |"
	@echo "|                                               |"
	@echo "+-----------------------------------------------+"
	for dir in $(MODULES); do (cd $$dir && $(MAKE) $@); done
