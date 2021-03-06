/*
 * Copyright (c) 2015, Texas Instruments Incorporated - http://www.ti.com/
 * Copyright (c) 2017, University of Bristol - http://www.bristol.ac.uk/
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*---------------------------------------------------------------------------*/
/**
 * \addtogroup rf-core
 * @{
 *
 * \defgroup rf-core-ble CC13xx/CC26xx BLE driver
 *
 * @{
 *
 * \file
 * Header file for the CC13xx/CC26xx BLE driver
 */
/*---------------------------------------------------------------------------*/
#ifndef RF_BLE_H_
#define RF_BLE_H_
/*---------------------------------------------------------------------------*/
#include "contiki.h"
#include "rf-core/rf-core.h"
#include "radio.h"

#include <stdint.h>
/*---------------------------------------------------------------------------*/
#ifdef RF_BLE_CONF_ENABLED
#define RF_BLE_ENABLED RF_BLE_CONF_ENABLED
#else
#define RF_BLE_ENABLED 1
#endif
/*---------------------------------------------------------------------------*/
#define RF_BLE_IDLE   0
#define RF_BLE_ACTIVE 1
/*---------------------------------------------------------------------------*/
/* Memory address of BLE MAC address. Can be overwritten by the user by defining BLE_ADDRESS_PTR. */
#ifndef BLE_ADDRESS_PTR
#define BLE_ADDRESS_PTR         (0x500012E8)
#endif
/*---------------------------------------------------------------------------*/
/* BLE Advertisement channels. Not to be changed by the user. */
#define BLE_ADV_CHANNEL_MASK    0x07

#define BLE_ADV_CHANNEL_37      0x01
#define BLE_ADV_CHANNEL_38      0x02
#define BLE_ADV_CHANNEL_39      0x04

#define BLE_ADV_CHANNEL_ALL     (BLE_ADV_CHANNEL_37 | BLE_ADV_CHANNEL_38 | BLE_ADV_CHANNEL_39)
/*---------------------------------------------------------------------------*/
/* Maximum BLE advertisement size. Not to be changed by the user. */
#define BLE_ADV_MAX_SIZE        31
/*---------------------------------------------------------------------------*/
/**
 * \brief Set the device name to use with the BLE advertisement/beacon daemon
 * \param interval The interval (ticks) between two consecutive beacon bursts
 * \param name The device name to advertise
 *
 * If name is NULL it will be ignored. If interval==0 it will be ignored. Thus,
 * this function can be used to configure a single parameter at a time if so
 * desired.
 */
void rf_ble_beacond_config(clock_time_t interval, const char *name);

/**
 * \brief Start the BLE advertisement/beacon daemon
 * \return RF_CORE_CMD_OK: Success, RF_CORE_CMD_ERROR: Failure
 *
 * Before calling this function, the name to advertise must first be set by
 * calling rf_ble_beacond_config(). Otherwise, this function will return an
 * error.
 */
uint8_t rf_ble_beacond_start(void);

/**
 * \brief Stop the BLE advertisement/beacon daemon
 */
void rf_ble_beacond_stop(void);

/**
 * \brief Check whether the BLE beacond is currently active
 * \retval 1 The radio is in BLE mode
 * \retval 0 The BLE daemon is not active, or disabled
 */
uint8_t rf_ble_is_active(void);

/**
 * \brief Set TX power for BLE advertisements
 * \param power The 'at least' TX power in dBm, values avove 5 dBm will be ignored
 *
 * Set TX power to 'at least' power dBm.
 * This works with a lookup table. If the value of 'power' does not exist in
 * the lookup table, TXPOWER will be set to the immediately higher available
 * value
 */
void rf_ble_set_tx_power(radio_value_t power);

/**
 * \brief Get TX power for BLE advertisements
 * \return The TX power for BLE advertisements
 */
radio_value_t rf_ble_get_tx_power(void);

/**
 * \brief Transmit a single BLE advertisement in one or more advertisement channels
 * \param channel Bitmask of advertisement channels to be used: use
 * BLE_ADV_CHANNEL_37 for channel 37, BLE_ADV_CHANNEL_38 for channel 38,
 * BLE_ADV_CHANNEL_39 for channel 39, or any 'or' combination of those
 * \param data A pointer to the advertisement data buffer
 * \param len The length of the advertisement data. If more than BLE_ADV_MAX_SIZE,
 * the first BLE_ADV_MAX_SIZE bytes will be used.
 *
 * Transmits a given advertisement payload once in one or any arbitrary combination
 * of advertisement channels.
 */
void rf_ble_beacon_single(uint8_t channel, uint8_t *data, uint8_t len);
/*---------------------------------------------------------------------------*/
#endif /* RF_BLE_H_ */
/*---------------------------------------------------------------------------*/
/**
 * @}
 * @}
 */
