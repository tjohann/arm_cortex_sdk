#
# my simple makefile act as something like a user interface
#

ifeq "${ARM_CORTEX_HOME}" ""
    $(error error: please source arm_cortex_env first!)
endif

ifeq "${ARM_CORTEX_BIN_HOME}" ""
    $(error error: please source armhf_env first!)
endif

MODULES = Documentation include lib schematics pics scripts
MODULES += src projects
BUILD = src projects

all::
	@echo "+-----------------------------------------------------------+"
	@echo "|                                                           |"
	@echo "|                  Nothing to build                         |"
	@echo "|                                                           |"
	@echo "+-----------------------------------------------------------+"
	@echo "| Example:                                                  |"
	@echo "| make init_sdk       -> init all needed part               |"
	@echo "| make build          -> build all                          |"
	@echo "| make get_toolchain  -> install toolchain                  |"
	@echo "| make clean          -> clean all dir/subdirs              |"
	@echo "| make distclean      -> complete cleanup/delete "
	@echo "|                        (inclusive toolchain and downloads)|"
	@echo "| ...                                                       |"
	@echo "| make install        -> install some scripts to $(HOME)     "
	@echo "| make uninstall      -> remove scripts from $(HOME)         "
	@echo "+-----------------------------------------------------------+"

build::
	@echo "+-----------------------------------------------------------+"
	@echo "|                                                           |"
	@echo "|                     Building all                          |"
	@echo "|                                                           |"
	@echo "+-----------------------------------------------------------+"
	for dir in $(BUILD); do (cd $$dir && $(MAKE) all); done

clean::
	rm -f *~ *.o .*~
	for dir in $(MODULES); do (cd $$dir && $(MAKE) $@); done

distclean: clean_opt clean_libs
	for dir in $(MODULES); do (cd $$dir && $(MAKE) $@); done

clean_opt::
	($(ARM_CORTEX_HOME)/scripts/clean_sdk.sh -t)

clean_libs::
	@echo "TODO -> cleanup libboard and libchip"

mrproper: clean
	($(ARM_CORTEX_HOME)/scripts/clean_sdk.sh -m)

init_sdk: distclean
	@echo "+----------------------------------------------------------+"
	@echo "|                                                          |"
	@echo "|              Init SDK -> you may need sudo               |"
	@echo "|                                                          |"
	@echo "+----------------------------------------------------------+"
	($(ARM_CORTEX_HOME)/scripts/init_sdk.sh)

get_toolchain::
	@echo "+----------------------------------------------------------+"
	@echo "|                                                          |"
	@echo "|        Download latest supported toolchain version       |"
	@echo "|                                                          |"
	@echo "+----------------------------------------------------------+"
	($(ARM_CORTEX_HOME)/scripts/get_toolchain.sh)

install::
	(install $(ARM_CORTEX_HOME)/scripts/init_sdk.sh $(HOME)/bin/arm_cortex_init_sdk.sh)
	(install $(ARM_CORTEX_HOME)/scripts/get_toolchain.sh $(HOME)/bin/arm_cortex_get_toolchain.sh)

uninstall::
	(rm -rf $(HOME)/bin/arm_cortex_get_toolchain.sh)
	(rm -rf $(HOME)/bin/arm_cortex_init_sdk.sh)
