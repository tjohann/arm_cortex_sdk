#
# my simple makefile act as something like a user interface
#

ifeq "${ARM_CORTEX_HOME}" ""
    $(error error: please source arm_cortex_env first!)
endif

MODULES = Documentation include lib schemantics pics scripts
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
