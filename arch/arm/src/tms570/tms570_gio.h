/************************************************************************************
 * arch/arm/src/tms570/tms570_gio.h
 *
 *   Copyright (C) 2015 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ************************************************************************************/

#ifndef __ARCH_ARM_SRC_TMS570_TMS570_GIO_H
#define __ARCH_ARM_SRC_TMS570_TMS570_GIO_H

/************************************************************************************
 * Included Files
 ************************************************************************************/

#include <nuttx/config.h>

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

/************************************************************************************
 * Pre-processor Definitions
 ************************************************************************************/

/* Bit-encoded input to tms570_configgio() ********************************************/

/* 32-bit Encoding:
 *
 *   .... .... .... .... MCCC .IIV PPP. .BBB
 */

/* Input/Output mode:
 *
 *   .... .... .... .... M... .... .... ....
 */

#define GIO_MODE_SHIFT            (15)        /* Bit 15: GIO mode */
#define GIO_MODE_MASK             (1 << GIO_MODE_SHIFT)
#  define GIO_INPUT               (0 << GIO_MODE_SHIFT) /* GIO Input */
#  define GIO_OUTPUT              (1 << GIO_MODE_SHIFT) /* GIO Output */

/* These bits set the configuration of the pin:
 * NOTE: No definitions for parallel capture mode
 *
 *   .... .... .... .... .CCC .... .... ....
 */

#define GIO_CFG_SHIFT             (12)        /* Bits 12-14: GIO configuration bits */
#define GIO_CFG_MASK              (7 << GIO_CFG_SHIFT)
#  define GIO_CFG_DEFAULT         (0 << GIO_CFG_SHIFT) /* Default, no attribute */
#  define GIO_CFG_PULLUP          (1 << GIO_CFG_SHIFT) /* Bit 16: Internal pull-up */
#  define GIO_CFG_PULLDOWN        (2 << GIO_CFG_SHIFT) /* Bit 17: Internal pull-down */
#  define GIO_CFG_OPENDRAIN       (4 << GIO_CFG_SHIFT) /* Bit 19: Open drain */

/* Interrupt modes:
 *
 *   .... .... .... .... .... .II. .... ....
 */

#define GIO_INT_SHIFT             (9)         /* Bits 9-10: GIO interrupt bits */
#define GIO_INT_MASK              (3 << GIO_INT_SHIFT)
#  define GIO_INT_NONE            (0 << GIO_INT_SHIFT)
#  define GIO_INT_RISING          (1 << GIO_INT_SHIFT)
#  define GIO_INT_FALLING         (2 << GIO_INT_SHIFT)
#  define GIO_INT_BOTHEDGES       (3 << GIO_INT_SHIFT)

/* If the pin is an GIO output, then this identifies the initial output value:
 *
 *   .... .... .... .... .... ...V .... ....
 */

#define GIO_OUTPUT_SET            (1 << 8)    /* Bit 8: Initial value of output */
#define GIO_OUTPUT_CLEAR          (0)

/* This identifies the GIO port:
 *
 *   .... .... .... .... .... .... PPP. ....
 */

#define GIO_PORT_SHIFT            (5)         /* Bit 5-7:  Port number */
#define GIO_PORT_MASK             (7 << GIO_PORT_SHIFT)
#  define GIO_PORT_GIOA           (0 << GIO_PORT_SHIFT)
#  define GIO_PORT_GIOB           (1 << GIO_PORT_SHIFT)
#  define GIO_PORT_GIOC           (2 << GIO_PORT_SHIFT)
#  define GIO_PORT_GIOD           (3 << GIO_PORT_SHIFT)
#  define GIO_PORT_GIOE           (4 << GIO_PORT_SHIFT)
#  define GIO_PORT_GIOF           (5 << GIO_PORT_SHIFT)
#  define GIO_PORT_GIOG           (6 << GIO_PORT_SHIFT)
#  define GIO_PORT_GIOH           (7 << GIO_PORT_SHIFT)

/* This identifies the bit in the port:
 *
 *   .... .... .... .... .... .... .... .BBB
 */

#define GIO_PIN_SHIFT             (0)         /* Bits 0-2: GIO number: 0-7 */
#define GIO_PIN_MASK              (7 << GIO_PIN_SHIFT)
#  define GIO_PIN0                (0  << GIO_PIN_SHIFT)
#  define GIO_PIN1                (1  << GIO_PIN_SHIFT)
#  define GIO_PIN2                (2  << GIO_PIN_SHIFT)
#  define GIO_PIN3                (3  << GIO_PIN_SHIFT)
#  define GIO_PIN4                (4  << GIO_PIN_SHIFT)
#  define GIO_PIN5                (5  << GIO_PIN_SHIFT)
#  define GIO_PIN6                (6  << GIO_PIN_SHIFT)
#  define GIO_PIN7                (7  << GIO_PIN_SHIFT)

/************************************************************************************
 * Public Types
 ************************************************************************************/

#ifndef __ASSEMBLY__

/* Must be big enough to hold the 32-bit encoding */

typedef uint16_t gio_pinset_t;

/************************************************************************************
 * Public Data
 ************************************************************************************/

#undef EXTERN
#if defined(__cplusplus)
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/************************************************************************************
 * Inline Functions
 ************************************************************************************/

/****************************************************************************
 * Name: tms570_gio_base
 *
 * Description:
 *   Return the base address of the GIO register set
 *
 ****************************************************************************/

static inline uintptr_t tms570_gio_base(gio_pinset_t cfgset)
{
  int port = (cfgset & GIO_PORT_MASK) >> GIO_PORT_SHIFT;
  return TMS570_GIO_PORTBASE(n);
}

/****************************************************************************
 * Name: tms570_gio_port
 *
 * Description:
 *   Return the GIO port number
 *
 ****************************************************************************/

static inline int tms570_gio_port(gio_pinset_t cfgset)
{
  return (cfgset & GIO_PORT_MASK) >> GIO_PORT_SHIFT;
}

/****************************************************************************
 * Name: tms570_gio_pin
 *
 * Description:
 *   Return the GIO pin number
 *
 ****************************************************************************/

static inline int tms570_gio_pin(gio_pinset_t cfgset)
{
  return (cfgset & GIO_PIN_MASK) >> GIO_PIN_SHIFT;
}

/****************************************************************************
 * Name: tms570_gio_pinmask
 *
 * Description:
 *   Return the GIO pin bit maskt
 *
 ****************************************************************************/

static inline int tms570_gio_pinmask(gio_pinset_t cfgset)
{
  return 1 << ((cfgset & GIO_PIN_MASK) >> GIO_PIN_SHIFT);
}

/************************************************************************************
 * Public Function Prototypes
 ************************************************************************************/

/************************************************************************************
 * Name: tms570_gioirqinitialize
 *
 * Description:
 *   Initialize logic to support a second level of interrupt decoding for GIO pins.
 *
 ************************************************************************************/

#ifdef CONFIG_TMS570_GIO_IRQ
void tms570_gioirqinitialize(void);
#else
#  define tms570_gioirqinitialize()
#endif

/************************************************************************************
 * Name: tms570_configgio
 *
 * Description:
 *   Configure a GIO pin based on bit-encoded description of the pin.
 *
 ************************************************************************************/

int tms570_configgio(gio_pinset_t cfgset);

/************************************************************************************
 * Name: tms570_giowrite
 *
 * Description:
 *   Write one or zero to the selected GIO pin
 *
 ************************************************************************************/

void tms570_giowrite(gio_pinset_t pinset, bool value);

/************************************************************************************
 * Name: tms570_gioread
 *
 * Description:
 *   Read one or zero from the selected GIO pin
 *
 ************************************************************************************/

bool tms570_gioread(gio_pinset_t pinset);

/************************************************************************************
 * Name: tms570_gioirq
 *
 * Description:
 *   Configure an interrupt for the specified GIO pin.
 *
 ************************************************************************************/

#ifdef CONFIG_TMS570_GIO_IRQ
void tms570_gioirq(gio_pinset_t pinset);
#else
#  define tms570_gioirq(pinset)
#endif

/************************************************************************************
 * Name: tms570_gioirqenable
 *
 * Description:
 *   Enable the interrupt for specified GIO IRQ
 *
 ************************************************************************************/

#ifdef CONFIG_TMS570_GIO_IRQ
void tms570_gioirqenable(int irq);
#else
#  define tms570_gioirqenable(irq)
#endif

/************************************************************************************
 * Name: tms570_gioirqdisable
 *
 * Description:
 *   Disable the interrupt for specified GIO IRQ
 *
 ************************************************************************************/

#ifdef CONFIG_TMS570_GIO_IRQ
void tms570_gioirqdisable(int irq);
#else
#  define tms570_gioirqdisable(irq)
#endif

/************************************************************************************
 * Function:  tms570_dumpgio
 *
 * Description:
 *   Dump all GIO registers associated with the base address of the provided pinset.
 *
 ************************************************************************************/

#ifdef CONFIG_DEBUG_GIO
int tms570_dumpgio(uint32_t pinset, const char *msg);
#else
#  define tms570_dumpgio(p,m)
#endif

#undef EXTERN
#if defined(__cplusplus)
}
#endif

#endif /* __ASSEMBLY__ */
#endif /* __ARCH_ARM_SRC_TMS570_TMS570_GIO_H */
