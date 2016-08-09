#
# my simple makefile act as something like a user interface
#

ifeq "${ARM_CORTEX_HOME}" ""
    $(error error: please source arm_cortex_env first!)
endif

ifeq "${ARM_CORTEX_BIN_HOME}" ""
    $(error error: please source armhf_env first!)
endif


MODULES = $(shell ls -d */ | cut -f1 -d'/')
DOCS =

all::
	@echo Cheers

install::
	(install $(ARM_CORTEX_HOME)/scripts/get_toolchain.sh $(HOME)/bin/arm_cortex_get_toolchain.sh)

uninstall::
	(rm -rf $(HOME)/bin/arm_cortex_get_toolchain.sh)

clean::
	rm -f *~
	for dir in $(MODULES); do (cd $$dir && $(MAKE) $@); done

distclean: clean
