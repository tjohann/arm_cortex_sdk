#!/usr/bin/env bash
################################################################################
#
# Title       :    init_sdk.sh
#
# License:
#
# GPL
# (c) 2015-2016, thorsten.johannvorderbrueggen@t-online.de
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
#   A simple tool to init the sdk
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

# program name
PROGRAM_NAME=${0##*/}

# my usage method
my_usage()
{
    echo " "
    echo "+--------------------------------------------------------+"
    echo "| Usage: ${PROGRAM_NAME} "
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
while getopts 'hv' opts 2>$_log
do
    case $opts in
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
# ***                         Main Loop                                      ***
# ******************************************************************************

echo " "
echo "+----------------------------------------+"
echo "|             init the sdk               |"
echo "+----------------------------------------+"
echo " "

if [ -d $ARM_CORTEX_BIN_HOME ]; then
    echo "$ARM_CORTEX_BIN_HOME already available"
else
    echo "Create $ARM_CORTEX_BIN_HOME -> need sudo rights! "
    sudo mkdir -p $ARM_CORTEX_BIN_HOME
    if [ $? -ne 0 ] ; then
	echo "ERROR -> could not mkdir -p $ARM_CORTEX_BIN_HOME" >&2
	my_exit
    fi
    
    sudo chown $USER:users $ARM_CORTEX_BIN_HOME
    if [ $? -ne 0 ] ; then
	echo "ERROR -> could not chown $USER:users $ARM_CORTEX_BIN_HOME" >&2
	my_exit
    fi
    
    sudo chmod 775 $ARM_CORTEX_BIN_HOME
    if [ $? -ne 0 ] ; then
	echo "ERROR -> could not chmod 775 $ARM_CORTEX_BIN_HOME" >&2
	my_exit
    fi
fi

cleanup
echo " "
echo "+----------------------------------------+"
echo "|            Cheers $USER"
echo "+----------------------------------------+"
echo " "
