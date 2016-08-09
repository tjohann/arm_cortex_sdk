#
# my simple makefile act as something like a user interface
#

ifeq "${ARM_CORTEX_HOME}" ""
    $(error error: please source arm_cortex_env first!)
endif

ifeq "${ARM_CORTEX_BIN_HOME}" ""
    $(error error: please source armhf_env first!)
endif

MODULES = clock can_node

all::
	@echo " "
	@echo "--> Building $(MODULES) "
	@echo " "
	for dir in $(MODULES); do (cd $$dir && $(MAKE) $@); done

clean::
	rm -f *~ *.o .*~
	for dir in $(MODULES); do (cd $$dir && $(MAKE) $@); done

distclean: clean
	for dir in $(MODULES); do (cd $$dir && $(MAKE) $@); done
