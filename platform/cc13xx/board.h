
/*---------------------------------------------------------------------------*/
#ifndef BOARD_H_
#define BOARD_H_
/*---------------------------------------------------------------------------*/
#include "ioc.h"
/*---------------------------------------------------------------------------*/
/**
 * \name LED configurations
 *
 * Those values are not meant to be modified by the user
 * @{
 */
/* Some files include leds.h before us, so we need to get rid of defaults in
 * leds.h before we provide correct definitions */
#undef LEDS_GREEN
#undef LEDS_YELLOW
#undef LEDS_RED
#undef LEDS_CONF_ALL

#define LEDS_RED       1 /**< LED1 (Red)    */
#define LEDS_YELLOW    2 /**< LED2 (Yellow) */
#define LEDS_GREEN     4 /**< LED3 (Green)  */
#define LEDS_ORANGE    8 /**< LED4 (Orange) */

#define LEDS_CONF_ALL 15

/* Notify various examples that we have LEDs */
#define PLATFORM_HAS_LEDS        1
/** @} */
/*---------------------------------------------------------------------------*/
/**
 * \name LED IOID mappings
 *
 * Those values are not meant to be modified by the user
 * @{
 */
#define BOARD_IOID_LED          IOID_30
#define BOARD_LED              (1 << BOARD_IOID_LED)
/** @} */
/*---------------------------------------------------------------------------*/
/**
 * \name UART IOID mapping
 *
 * Those values are not meant to be modified by the user
 * @{
 */
#define BOARD_IOID_UART_RX        IOID_28
#define BOARD_IOID_UART_TX        IOID_27
#define BOARD_IOID_UART_CTS       IOID_UNUSED
#define BOARD_IOID_UART_RTS       IOID_UNUSED
#define BOARD_UART_RX             (1 << BOARD_IOID_UART_RX)
#define BOARD_UART_TX             (1 << BOARD_IOID_UART_TX)
#define BOARD_UART_CTS            (1 << BOARD_IOID_UART_CTS)
#define BOARD_UART_RTS            (1 << BOARD_IOID_UART_RTS)
/** @} */


/*---------------------------------------------------------------------------*/
#define BOARD_IOID3          IOID_3
#define BOARD_IO3              (1 << BOARD_IOID3)
#define BOARD_IOID4          IOID_4
#define BOARD_IO4              (1 << BOARD_IOID4)
#define BOARD_IOID5          IOID_5
#define BOARD_IO5              (1 << BOARD_IOID5)
#define BOARD_IOID6          IOID_6
#define BOARD_IO6              (1 << BOARD_IOID6)
#define BOARD_IOID7         IOID_7
#define BOARD_IO7              (1 << BOARD_IOID7)
#define BOARD_IOID8          IOID_8
#define BOARD_IO8              (1 << BOARD_IOID8)
#define BOARD_IOID9         IOID_9
#define BOARD_IO9             (1 << BOARD_IOID9)
#define BOARD_IOID10          IOID_10
#define BOARD_IO10              (1 << BOARD_IOID10)
#define BOARD_IOID11          IOID_11
#define BOARD_IO11             (1 << BOARD_IOID11)
#define BOARD_IOID12          IOID_12
#define BOARD_IO12             (1 << BOARD_IOID12)

#define BOARD_IOID13          IOID_13
#define BOARD_IO13              (1 << BOARD_IOID13)
#define BOARD_IOID14          IOID_14
#define BOARD_IO14              (1 << BOARD_IOID14)
#define BOARD_IOID15          IOID_15
#define BOARD_IO15              (1 << BOARD_IOID15)
#define BOARD_IOID16          IOID_16
#define BOARD_IO16              (1 << BOARD_IOID16)
#define BOARD_IOID17         IOID_17
#define BOARD_IO17              (1 << BOARD_IOID17)
#define BOARD_IOID18          IOID_18
#define BOARD_IO18              (1 << BOARD_IOID18)
#define BOARD_IOID19         IOID_19
#define BOARD_IO19             (1 << BOARD_IOID19)
#define BOARD_IOID20          IOID_20
#define BOARD_IO20              (1 << BOARD_IOID20)
#define BOARD_IOID21          IOID_21
#define BOARD_IO21             (1 << BOARD_IOID21)
#define BOARD_IOID22          IOID_22
#define BOARD_IO22             (1 << BOARD_IOID22)

#define BOARD_IOID23          IOID_23
#define BOARD_IO23              (1 << BOARD_IOID23)
#define BOARD_IOID24          IOID_24
#define BOARD_IO24              (1 << BOARD_IOID24)
#define BOARD_IOID25          IOID_25
#define BOARD_IO25              (1 << BOARD_IOID25)
#define BOARD_IOID26          IOID_26
#define BOARD_IO26              (1 << BOARD_IOID26)


#define BOARD_IOID29         IOID_29
#define BOARD_IO29             (1 << BOARD_IOID29)


/*---------------------------------------------------------------------------*/
/**
 * \name Device string used on startup
 * @{
 */
#define BOARD_STRING "HIT CPSGroup Evaluation Board"
/** @} */
/*---------------------------------------------------------------------------*/
#endif /* BOARD_H_ */
/*---------------------------------------------------------------------------*/
/**
 * @}
 * @}
 */
