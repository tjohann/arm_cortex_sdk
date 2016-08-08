ARM Cortex M3 SDK
=================

A simple sdk with libs and tools for using with 32 bit Cortex-M3 controller.


Background
----------

For my smaller projects like clocks (./projects/clock) and can/lin-bus nodes (./projects/can_node) i like to use bare-metal devices. So this repository is the entry point for such projects.


Supported devices
-----------------

At the moment I use Olimex SAM3-P256/H256 (https://www.olimex.com/Products/ARM/Atmel/SAM3-P256/ and https://www.olimex.com/Products/ARM/Atmel/SAM3-H256/) and Olimex LPC-P1343 (https://www.olimex.com/Products/ARM/NXP/LPC-P1343/).

Both devices need a libchip (processor specific parts -> here the same for both) and a libboard (board specific parts). I provide a small script wich downloads the already compiled librarys from sourceforge. If you want to build it on your own, checkout my repository (https://github.com/tjohann/sam3_p256_libboard and https://github.com/tjohann/lpc_p1343_libboard) which is based on the Atmel/NXP/Olimex zip files.


Setup dev environment
---------------------

https://sourceforge.net/projects/cortexm-sdk/


Repository structure
--------------------

Some comments to the structure of the directory.

	include -> common include (also for Makefile)
	lib -> downloaded libs from sourceforge and own librarys from ./src
	src -> the sourcecode of my librarys
	project -> the different projects (use ./lib and ./include)
	scripts -> some useful scripts like download (called from Makefile)
	pics -> some pictures of my devices and environment
	schematics -> something like building blocks
