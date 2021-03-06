#ifndef __DAP_CONFIG_H__
#define __DAP_CONFIG_H__

#include "stm32f3xx_hal.h"

#define CPU_CLOCK             48000000        ///< Specifies the CPU Clock in Hz
#define IO_PORT_WRITE_CYCLES  2 ///< I/O Cycles: 2=default, 1=Cortex-M0+ fast I/0

#define DAP_PACKET_SIZE       64
#define DAP_PACKET_COUNT      1

#define PIN_nRESET_LOW()   do { GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODER6) | GPIO_MODER_MODER6_0; \
                                GPIOB->OTYPER |= GPIO_OTYPER_OT_6;                                        \
                                GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6; } while (0)
#define PIN_nRESET_HIGH()  do { GPIOB->MODER &= ~GPIO_MODER_MODER6; } while (0)

/** SWDIO I/O pin: Switch to Output mode (used in SWD mode only).
Configure the SWDIO DAP hardware I/O pin to output mode. This function is
called prior \ref PIN_SWDIO_OUT function calls.
*/
#define PIN_SWDIO_OUT_ENABLE(void)   \
    do {                             \
        GPIOB->MODER   |= GPIO_MODER_MODER4_0;    \
        GPIOB->OTYPER  &= GPIO_OTYPER_OT_4;       \
        GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4; \
        GPIOB->BRR      = SWDIO_Pin;              \
    } while(0)

/** SWDIO I/O pin: Switch to Input mode (used in SWD mode only).
Configure the SWDIO DAP hardware I/O pin to input mode. This function is
called prior \ref PIN_SWDIO_IN function calls.
*/
#define PIN_SWDIO_OUT_DISABLE(void) \
    do {                            \
        GPIOB->MODER   &= ~GPIO_MODER_MODER4_0;  \
        GPIOB->BSRR     = SWDIO_Pin;             \
    } while(0)

// SWCLK/TCK I/O pin -------------------------------------

/** SWCLK/TCK I/O pin: Get Input.
\return Current status of the SWCLK/TCK DAP hardware I/O pin.
*/
static inline __attribute__((always_inline)) uint32_t PIN_SWCLK_TCK_IN(void)
{
  return (GPIOB->ODR & SWCLK_Pin) ? 1 : 0;
}

/** SWCLK/TCK I/O pin: Set Output to High.
Set the SWCLK/TCK DAP hardware I/O pin to high level.
*/
static inline __attribute__((always_inline)) void     PIN_SWCLK_TCK_SET(void)
{
  GPIOB->BSRR = SWCLK_Pin;
}

/** SWCLK/TCK I/O pin: Set Output to Low.
Set the SWCLK/TCK DAP hardware I/O pin to low level.
*/
static inline __attribute__((always_inline)) void     PIN_SWCLK_TCK_CLR(void)
{
  GPIOB->BRR = SWCLK_Pin;
}

// SWDIO/TMS Pin I/O --------------------------------------

/** SWDIO/TMS I/O pin: Get Input.
\return Current status of the SWDIO/TMS DAP hardware I/O pin.
*/
static inline __attribute__((always_inline))  uint32_t PIN_SWDIO_TMS_IN(void)
{
  return (GPIOB->IDR & SWDIO_Pin) ? 1 : 0;
}

/** SWDIO/TMS I/O pin: Set Output to High.
Set the SWDIO/TMS DAP hardware I/O pin to high level.
*/
static inline __attribute__((always_inline))  void     PIN_SWDIO_TMS_SET(void)
{
  GPIOB->BSRR = SWDIO_Pin;
}

/** SWDIO/TMS I/O pin: Set Output to Low.
Set the SWDIO/TMS DAP hardware I/O pin to low level.
*/
static inline __attribute__((always_inline))   void     PIN_SWDIO_TMS_CLR(void)
{
  GPIOB->BRR = SWDIO_Pin;
}

/** SWDIO I/O pin: Get Input (used in SWD mode only).
\return Current status of the SWDIO DAP hardware I/O pin.
*/
static inline __attribute__((always_inline))   uint32_t PIN_SWDIO_IN(void)
{
  return (GPIOB->IDR & SWDIO_Pin) ? 1 : 0;
}

/** SWDIO I/O pin: Set Output (used in SWD mode only).
\param bit Output value for the SWDIO DAP hardware I/O pin.
*/
static inline __attribute__((always_inline))   void     PIN_SWDIO_OUT(uint32_t bit)
{
  if (bit & 0x1) {
    GPIOB->BSRR = SWDIO_Pin;
  } else {
    GPIOB->BRR = SWDIO_Pin;
  }
}



// nRESET Pin I/O------------------------------------------

/** nRESET I/O pin: Get Input.
\return Current status of the nRESET DAP hardware I/O pin.
*/
static inline __attribute__((always_inline))   uint32_t PIN_nRESET_IN(void)
{
  return (GPIOB->IDR & SWRST_Pin) ? 1 : 0;
}

/** nRESET I/O pin: Set Output.
\param bit target device hardware reset pin status:
           - 0: issue a device hardware reset.
           - 1: release device hardware reset.
*/
static inline __attribute__((always_inline))   void     PIN_nRESET_OUT(uint32_t bit)
{
  if (bit) {
    PIN_nRESET_HIGH();
  } else {
    PIN_nRESET_LOW();
  }
}

#endif