# +--------------------- setup the arm dev environment -----------------------+
# |                              arm_cortex_env                               |
# +---------------------------------------------------------------------------+

# set MY_HOST_ARCH
export MY_HOST_ARCH=$(uname -m)

# set arm cortex home
export ARM_CORTEX_HOME=${HOME}/arm_cortex_sdk

# home of the bin's
export ARM_CORTEX_BIN_HOME=/opt/arm_cortex_sdk

# extend PATH
export PATH=${ARM_CORTEX_HOME}/toolchain:$PATH

echo "Setup env for host \"${MY_HOST_ARCH}\" with root dir \"${ARM_CORTEX_HOME}\" and binary folder \"${ARM_CORTEX_BIN_HOME}\""

#EOF