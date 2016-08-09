ARM Cortex M3 SDK
=================

A simple sdk with libs and tools for using with 32 bit Cortex-M3 controller.

WARNING: This is work in progress! So it's possible that something is not working or possibly not implemented yet. If you face a bug then pls use create an issue (https://github.com/tjohann/arm_cortex_sdk/issues).


Background
----------

For my smaller projects like clocks (./projects/clock) and can/lin-bus nodes (./projects/can_node) i like to use bare-metal devices. So this repository is the entry point for such projects.


Requirement
-----------

The only yet know requirements are git (to clone/update the repository).


Supported devices
-----------------

At the moment I use Olimex SAM3-P256/H256 (https://www.olimex.com/Products/ARM/Atmel/SAM3-P256/ and https://www.olimex.com/Products/ARM/Atmel/SAM3-H256/) and Olimex LPC-P1343 (https://www.olimex.com/Products/ARM/NXP/LPC-P1343/).

Both devices need a libchip (processor specific parts -> here the same for both) and a libboard (board specific parts). I provide a small script wich downloads the already compiled librarys from sourceforge. If you want to build it on your own, checkout my repository (https://github.com/tjohann/sam3_p256_libboard and https://github.com/tjohann/lpc_p1343_libboard) which is based on the Atmel/NXP/Olimex zip files.


Setup
-----

Follow the steps below to setup your enviroment.

Clone this repo:

    git clone https://github.com/tjohann/arm_cortex_sdk.git


Source the environment file arm_cortex_env

    . ./arm_cortex_env

or add it to your .bashrc

    # setup the a20_sdk environment
    if [ -f ${HOME}/arm_cortex_sdk/arm_cortex_env ]; then
      . ${HOME}/arm_cortex_sdk/arm_cortex_env
    fi

or copy arm_cortex_env.sh to /etc/profile.d/

    sudo cp arm_cortex_env.sh /etc/profile.d/

Init the SDK:

    cd arm_cortex_sdk
    make init_sdk

Download the compiler to /opt/arm_cortex_sdk/

    make get_toolchain


Update
------

I regulary update the libs, toolchain and more. To stay up to date you can simply do the following steps.

Pull the latest changes:

    cd arm_cortex_sdk
    git pull

Take a look at the NEWS file to see what i've changed. See also UPGRADE_HINTS.

If there're changes of the toolchain, then fist distclean all:

    make distclean

and then proceed with the normal setup process above.

In short:

    make get_toolchain


Build
-----

To build everthing do a

	make

This will build the librarys and install them in ${ARM_CORTEX_HOME}/lib. It also build all below ./projects.


Versioninfo
-----------

I use a standard version scheme via git tags based on 3 numbers:

	ARM_CORTEX_SDK_V0.0.1

The first number is the mayor number which reflect bigger changes like

	- new functions
	- add new devices
	- restructe of all
	- ...

The second number (minor) will change because of

	- new scripts
	- api changes

So a simple version update of the olimex kernel will not increase the minor number, instead it will increase the third number (age number):

	- bugfixes
	- all smaller changes


Repository structure
--------------------

Some comments to the structure of the directory.

	include -> common include (also for Makefile)
	lib -> downloaded libs from sourceforge and own librarys from ./src
	src -> the sourcecode of my librarys
	projects -> the different projects (use ./lib and ./include)
	scripts -> some useful scripts like download (called from Makefile)
	pics -> some pictures of my devices and environment
	schematics -> something like building blocks
	Documentation -> docs/howtos and more


Directory/File structure on sourceforge
---------------------------------------

All binary/bigger files (toolchain or libraries like libboard) are on sourceforge (https://sourceforge.net/projects/cortexm-sdk/files/). The scripts to setup the environment using that location to download them.

In the root directory you find the toolchain tarballs and the checksum.sh256 from the git-repository. The boards are represented through the named directorys. Below them you find all device specific files.

Naming convention:

	toochain_x86_64.tgz -> cross-toolchain for x86_64 hosts
	toochain_armhf.tgz -> cross-toolchain for armhf hosts like Bananapi (see https://github.com/tjohann/a20_sdk/pics)
	sam3-p256 -> Olimex SAM3-H/P256
	lpc-p1343 -> Olimex LPC-P1343


Development model
-----------------

I support only one version described by a tag. The toolchain and images are for that version. Older tags wont be supported anymore.


Outlook (next development steps)
--------------------------------

(until end of august)
- First complete working skelekton (blink an led) for the sam3 board
- Ged rid of Linaro toolchain (which I actually use)

(until end of september)
- First complete working skelekton (blink an led) for the lpc board


