#!/usr/bin/env bash
################################################################################
#
# Title       :    get_toolchain.sh
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
#   A simple tool to get the toolchain and untar it to $ARM_CORTEX_BIN_HOME  ...
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

#
# latest version
#
# DOWNLOAD_STRING:
# -> https://launchpad.net/gcc-arm-embedded/5.0/5-2016-q2-update/+download/gcc-arm-none-eabi-5_4-2016q2-20160622-linux.tar.bz2
#
TOOLCHAIN_STRING='https://launchpad.net/gcc-arm-embedded/5.0/5-2016-q2-update/+download'
TOOLCHAIN_TARBALL='gcc-arm-none-eabi-5_4-2016q2-20160622-linux.tar.bz2'
TOOLCHAIN_TARBALL_DIR='gcc-arm-none-eabi-5_4-2016q2'

# program name
PROGRAM_NAME=${0##*/}

# my usage method
my_usage()
{
    echo " "
    echo "+------------------------------------------+"
    echo "| Usage: ${PROGRAM_NAME} "
    echo "|        [-v] -> print version info        |"
    echo "|        [-h] -> this help                 |"
    echo "|                                          |"
    echo "+------------------------------------------+"
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
    echo "+------------------------------------------+"
    echo "|          Cheers $USER                   |"
    echo "+------------------------------------------+"
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
# ***                      The functions for main_menu                       ***
# ******************************************************************************


# --- create download string
create_download_string()
{
   TOOLCHAIN_DOWNLOAD_STRING="${TOOLCHAIN_STRING}/${TOOLCHAIN_TARBALL}"
  
   echo "INFO: set toolchain download string to ${TOOLCHAIN_DOWNLOAD_STRING}"
}

# --- download toolchain tarball
get_toolchain_tarball()
{
    if [ "$TOOLCHAIN_DOWNLOAD_STRING" = 'none' ]; then
	echo " "
	echo "+--------------------------------------+"
	echo "|  ERROR: TOOLCHAIN_DOWNLOAD_STRING is |"
	echo "|         none!                        |"
	echo "+--------------------------------------+"
	echo " "
	my_exit
    fi

    if [ -f ${TOOLCHAIN_TARBALL} ]; then
	echo "${TOOLCHAIN_TARBALL} already exists -> wont download"
    else
	wget $TOOLCHAIN_DOWNLOAD_STRING
	if [ $? -ne 0 ] ; then
	    echo "ERROR -> could not download ${TOOLCHAIN_DOWNLOAD_STRING}" >&2
	    my_exit
	fi
    fi
}

# --- untar toolchain source
untar_toolchain()
{
    if [ -f ${TOOLCHAIN_TARBALL} ]; then
	tar xjvf ${TOOLCHAIN_TARBALL}
	if [ $? -ne 0 ] ; then
	    echo "ERROR -> could not untar ${TOOLCHAIN_TARBALL}" >&2
	    my_exit
	fi
	mv ${TOOLCHAIN_TARBALL_DIR} toolchain
	if [ $? -ne 0 ] ; then
	    echo "ERROR -> could not mv ${TOOLCHAIN_TARBALL_DIR} to toolchain" >&2
	    my_exit
	fi
    else
	echo "ERROR -> ${TOOLCHAIN_TARBALL} does not exist" >&2
	my_exit
    fi
}


# ******************************************************************************
# ***                         Main Loop                                      ***
# ******************************************************************************

echo " "
echo "+----------------------------------------+"
echo "|  get/install latest toolchain tarball  |"
echo "+----------------------------------------+"
echo " "

if [ $(uname -m) == 'x86_64' ]; then

    if [ -d $ARM_CORTEX_BIN_HOME ]; then
	cd $ARM_CORTEX_BIN_HOME
    else
	echo "ERROR -> ${ARM_CORTEX_BIN_HOME} doesn't exist -> do a make init_sdk" >&2
	my_exit
    fi

    create_download_string
    get_toolchain_tarball
    untar_toolchain
else
    echo "INFO: no toolchain for your architecture $(uname -m)"
fi

cleanup
echo " "
echo "+----------------------------------------+"
echo "|            Cheers $USER"
echo "+----------------------------------------+"
echo " "

