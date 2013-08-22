/*
 * Sun Cobalt Raq550 platform driver
 * Copyright (C)2013 by Sergio Aguayo <sergioag@fuelcontrol.com.pe>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/reboot.h>
#include <linux/pm.h>
#include <asm/io.h>
#include <asm/reboot.h>

static void cobalt_power_off(void)
{
}

static void cobalt_restart(void)
{
	/* set "Enable Hard Reset" bit to 1 */
	outb(0x02, 0x0cf9);

	/* 0-to-1 transition of bit 2 will cause reset of processor */
	outb(0x06, 0x0cf9);

	mdelay(3000);

	/* we should not get here unless there is a BAD error */
	printk(KERN_ERR "cannot restart - halting\n");
	machine_halt();
}

void __init x86_cobalt_early_setup(void)
{
	/* Moorestown specific power_off/restart method */
	pm_power_off = cobalt_power_off;
	machine_ops.emergency_restart  = cobalt_restart;
}
