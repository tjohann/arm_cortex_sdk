#!/usr/bin/env bash
################################################################################
#
# Title       :    clean_sdk.sh
#
# License:
#
# GPL
# (c) 2016, thorsten.johannvorderbrueggen@t-online.de
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
#
################################################################################
#
# Date/Beginn :    09.08.2016/09.08.2015
#
# Version     :    V0.01
#
# Milestones  :    V0.01 (aug 2016) -> first functional version (taken from
#                                      a20_sdk.git and adapt it)
#
# Requires    :
#
################################################################################
# Description
#
#   A simple tool to cleanup parts of the sdk
#
# Some features
#   - ...
#
# Notes
#   - ...
#
################################################################################
#

# VERSION-NUMBER
VER='0.01'

# if env is sourced
MISSING_ENV='false'

# what to clean
CLEAN_TOOLCHAIN='false'
MRPROPER='false'

# program name
PROGRAM_NAME=${0##*/}

# my usage method
my_usage()
{
    echo " "
    echo "+--------------------------------------------------------+"
    echo "| Usage: ${PROGRAM_NAME} "
    echo "|        [-a] -> cleanup all dir                         |"
    echo "|        [-t] -> cleanup toolchain parts                 |"
    echo "|        [-m] -> remove /opt/arm_cortex_sdk also         |"
    echo "|        [-v] -> print version info                      |"
    echo "|        [-h] -> this help                               |"
    echo "|                                                        |"
    echo "+--------------------------------------------------------+"
    echo " "
    exit
}

# my cleanup
cleanup() {
    rm $_temp 2>/dev/null
    rm $_log 2>/dev/null
}

# my exit method
my_exit()
{
    echo "+-----------------------------------+"
    echo "|          Cheers $USER            |"
    echo "+-----------------------------------+"
    cleanup
    # http://tldp.org/LDP/abs/html/exitcodes.html
    exit 3
}

# print version info
print_version()
{
    echo "+------------------------------------------------------------+"
    echo "| You are using ${PROGRAM_NAME} with version ${VER} "
    echo "+------------------------------------------------------------+"
    cleanup
    exit
}

# --- Some values for internal use
_temp="/tmp/${PROGRAM_NAME}.$$"
_log="/tmp/${PROGRAM_NAME}.$$.log"


# check the args
while getopts 'hvatm' opts 2>$_log
do
    case $opts in
	t) CLEAN_TOOLCHAIN='true' ;;
	m) MRPROPER='true' ;;
	a) CLEAN_TOOLCHAIN='true'
           ;;
        h) my_usage ;;
	v) print_version ;;
        ?) my_usage ;;
    esac
done


# ******************************************************************************
# ***             Error handling for missing shell values                    ***
# ******************************************************************************

if [[ ! ${ARM_CORTEX_HOME} ]]; then
    MISSING_ENV='true'
fi

if [[ ! ${ARM_CORTEX_BIN_HOME} ]]; then
    MISSING_ENV='true'
fi

# show a usage screen and exit
if [ "$MISSING_ENV" = 'true' ]; then
    cleanup
    echo " "
    echo "+--------------------------------------+"
    echo "|                                      |"
    echo "|  ERROR: missing env                  |"
    echo "|         have you sourced env-file?   |"
    echo "|                                      |"
    echo "|          Cheers $USER               |"
    echo "|                                      |"
    echo "+--------------------------------------+"
    echo " "
    exit
fi

# ******************************************************************************
# ***                      The functions for main_menu                       ***
# ******************************************************************************

clean_toolchain()
{
    if [ -d $ARM_CORTEX_BIN_HOME ]; then
	cd $ARM_CORTEX_BIN_HOME
    	echo "cleanup toolchain parts"
	rm -rf toolchain*
	# TODO: get rid of linaro toolchain
	rm -rf gcc-arm-none-eabi*
    else
        echo "INFO: no directory $ARM_CORTEX_BIN_HOME"
    fi
}

do_mrproper()
{
    if [ -d $ARM_CORTEX_BIN_HOME ]; then
	cd $ARM_CORTEX_HOME
	sudo rm -rf $ARM_CORTEX_BIN_HOME
    else
        echo "INFO: no directory $ARM_CORTEX_BIN_HOME"
    fi
}

# ******************************************************************************
# ***                         Main Loop                                      ***
# ******************************************************************************

echo " "
echo "+----------------------------------------+"
echo "|             cleanup the sdk            |"
echo "| --> prepare your password for sudo     |"
echo "+----------------------------------------+"
echo " "

if [ "$CLEAN_TOOLCHAIN" = 'true' ]; then
    clean_toolchain
else
    echo "do not clean toolchain parts"
fi

if [ "$MRPROPER" = 'true' ]; then
	do_mrproper
else
    echo "do not mrproper"
fi

cleanup
echo " "
echo "+----------------------------------------+"
echo "|            Cheers $USER"
echo "+----------------------------------------+"
echo " "
