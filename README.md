avr_sdk ... a simple sdk with libs and tools for using with 8 bit controller
==========================

Setup AVR dev environment
--------------------------

This is a short introduction for using my avr_sdk.

* Files: *
- bin ... some usefull bin (x86_64)
- docs ... some usefull docs
- env_avr_dev_latest -> env_avr_dev_v1
- env_avr_dev_v1 ... env script which set needed variables 
  usage: ~/avr_sdk$. ./env_avr_dev_latest
- etc ... some usefull config
- include ... the avr specific headers
  usage: see ~/avr_sdk/src/template for usage
- lib ... the avr specific libs 
   usage: see ~/avr_sdk/src/template for usage
- man ... some manpages for the avr specific libs
- my_m168p_env/my_m32_env ... the controller specific config 
   usage: ~/avr_sdk$. ./my_m168p_env
- src ... sources for avr specific libs and tools
- projects ... here are my real projects
  Note: - to build a project, you have to source the corresponding env file in
          projects -> my_ext_ctrl_modul_env as an example
	- this env files only include needed switches and not more (like my_m32_env)
	- a build started in $(AVR_SDK_HOME) wont build projects!
- FEATURE_OVERVIEW ... a short decription of the feartures and the configuration

* General usage: *
- Create an controller specific file like my_m168p_env ... source it and try to build content
of ~/avr_sdk/src$ ... 

...~/avr_sdk$ . ./my_m168p_env 
Setup env for target atmega168p with 1000000Hz and 9600baud
...:~/avr_sdk$ cd src
~/avr_sdk/src$ ls
libavrcyclon  libavrhelper  libavrserial  makefile  template ...
~/avr_sdk/src$ make
.... A lot of output ...
Check for errors ... there shouldn't be any 

*HOTWO use it: *
Check Notes file and also
Check the template for a general overview and/or check the lib*s ...
Check FEATURE_OVERVIEW and 
Check HOWTO


Pls report errors to thorsten.johannvorderbrueggen@t-online.de with subject [AVR_SDK_ERRORS] ...

 Cheers
  Thorsten


Note: There will be another project based on cortex-m3 (arm_cortex_sdk) ... 

