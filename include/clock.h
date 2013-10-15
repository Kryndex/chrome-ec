/* Copyright (c) 2012 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/* Clocks and power management settings */

#ifndef __CROS_EC_CLOCK_H
#define __CROS_EC_CLOCK_H

#include "common.h"

/**
 * Set the CPU clocks and PLLs.
 */
void clock_init(void);

/**
 * Return the current clock frequency in Hz.
 */
int clock_get_freq(void);

/**
 * Enable or disable the PLL.
 *
 * @param enable	Enable PLL if non-zero; disable if zero.
 * @param notify	Notify other modules of the PLL change.  This should
 *			be 1 unless you're briefly turning on the PLL to work
 *			around a chip errata at init time.
 */
void clock_enable_pll(int enable, int notify);

/**
 * Wait for a number of clock cycles.
 *
 * Simple busy waiting for use before clocks/timers are initialized.
 *
 * @param cycles	Number of cycles to wait.
 */
void clock_wait_cycles(uint32_t cycles);

/* Clock gate control modes for clock_enable_peripheral() */
#define CGC_MODE_RUN    (1 << 0)
#define CGC_MODE_SLEEP  (1 << 1)
#define CGC_MODE_DSLEEP (1 << 2)
#define CGC_MODE_ALL    (CGC_MODE_RUN | CGC_MODE_SLEEP | CGC_MODE_DSLEEP)

/**
 * Enable clock to peripheral by setting the CGC register pertaining
 * to run, sleep, and/or deep sleep modes.
 *
 * @param offset  Offset of the peripheral. See enum clock_gate_offsets.
 * @param mask    Bit mask of the bits within CGC reg to set.
 * @param mode    Which mode(s) to enable the clock for
 */
void clock_enable_peripheral(uint32_t offset, uint32_t mask, uint32_t mode);

/**
 * Disable clock to peripheral by setting the CGC register pertaining
 * to run, sleep, and/or deep sleep modes.
 *
 * @param offset  Offset of the peripheral. See enum clock_gate_offsets.
 * @param mask    Bit mask of the bits within CGC reg to clear.
 * @param mode    Which mode(s) to enable the clock for
 */
void clock_disable_peripheral(uint32_t offset, uint32_t mask, uint32_t mode);

/**
 * Notify the clock module that the UART for the console is in use.
 */
void clock_refresh_console_in_use(void);

#endif  /* __CROS_EC_CLOCK_H */
