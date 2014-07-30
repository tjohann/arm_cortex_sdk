# common compiler switches to active/deactivate code fragments
#
# Note: also edit avr/arm_compile_macros.h if needed

# which controller do i use?
# -> __AVR__
# -> __ARM__ (cortex-m3)
CONTROLLER_FAMILY = __AVR__

# ----------- ERRNO parts -------------

# use adc_errno to indicate adc specific erros
# -> ON  (use it)
# -> OFF (no i can do it better)
ADC_ERROR = __ON__


# use serial_errno to indicate serial specific erros
# -> ON  (use it)
# -> OFF (no i can do it better)
SERIAL_ERROR = __ON__


# use lcd_errno to indicate lcd specific erros
# -> ON  (use it)
# -> OFF (no i can do it better)
LCD_ERROR = __ON__




