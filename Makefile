#
# my simple makefile act as something like a user interface
#

ifeq "${ARM_CORTEX_HOME}" ""
    $(error error: please source arm_cortex_env first!)
endif

MODULES = Documenation include lib schemantics pics
MODULES += src projects

all::
	@echo "+-----------------------------------------------+"
	@echo "|                                               |"
	@echo "|              Building all                     |"
	@echo "|                                               |"
	@echo "+-----------------------------------------------+"
	for dir in $(MODULES); do (cd $$dir && $(MAKE) $@); done

clean::
	rm -f *~ *.o .*~
	for dir in $(MODULES); do (cd $$dir && $(MAKE) $@); done

distclean: clean

flash::
	@echo "+-----------------------------------------------+"
	@echo "|                                               |"
	@echo "|            Flashing template                  |"
	@echo "|                                               |"
	@echo "+-----------------------------------------------+"
	for dir in $(MODULES); do (cd $$dir && $(MAKE) $@); done
