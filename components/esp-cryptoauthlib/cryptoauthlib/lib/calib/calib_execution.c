/**
 * \file
 * \brief Implements an execution handler that executes a given command on a
 *        device and returns the results.
 *
 * This implementation wraps Polling and No polling (simple wait) schemes into
 * a single method and use it across the library. Polling is used by default,
 * however, by defining the ATCA_NO_POLL symbol the code will instead wait an
 * estimated max execution time before requesting the result.
 *
 * \copyright (c) 2015-2020 Microchip Technology Inc. and its subsidiaries.
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip software
 * and any derivatives exclusively with Microchip products. It is your
 * responsibility to comply with third party license terms applicable to your
 * use of third party software (including open source software) that may
 * accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
 * PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT,
 * SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE
 * OF ANY KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF
 * MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE
 * FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL
 * LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED
 * THE AMOUNT OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR
 * THIS SOFTWARE.
 */

#include "cryptoauthlib.h"


#if defined(ATCA_NO_POLL) && defined(ATCA_ATECC608_SUPPORT) && !defined(ATCA_ATECC608A_SUPPORT)
#warning "ATECC608B supports only polling mode, if you are using an ATECC608A specify ATCA_ATECC608A_SUPPORT manually"
#endif


#ifdef ATCA_NO_POLL
// *INDENT-OFF* - Preserve time formatting from the code formatter
/*Execution times for ATSHA204A supported commands...*/
static const device_execution_time_t device_execution_time_204[] = {
    { ATCA_CHECKMAC,     1138},
    { ATCA_DERIVE_KEY,   1162},
    { ATCA_GENDIG,       1143},
    { ATCA_HMAC,         1169},
    { ATCA_INFO,         112},
    { ATCA_LOCK,         11124},
    { ATCA_MAC,          1135},
    { ATCA_NONCE,        1160},
    { ATCA_PAUSE,        112},
    { ATCA_RANDOM,       1150},
    { ATCA_READ,         115},
    { ATCA_SHA,          1122},
    { ATCA_UPDATE_EXTRA, 1112},
    { ATCA_WRITE,        1142}
};

/*Execution times for ATSHA206A supported commands...*/
static const device_execution_time_t device_execution_time_206[] = {
    { ATCA_DERIVE_KEY,   1162},
    { ATCA_INFO,         112},
    { ATCA_MAC,          1135},
    { ATCA_READ,         115},
    { ATCA_WRITE,        1142}
};

/*Execution times for ATECC108A supported commands...*/
static const device_execution_time_t device_execution_time_108[] = {
    { ATCA_CHECKMAC,     1113},
    { ATCA_COUNTER,      1120},
    { ATCA_DERIVE_KEY,   1150},
    { ATCA_GENDIG,       1111},
    { ATCA_GENKEY,       1115},
    { ATCA_HMAC,         1123},
    { ATCA_INFO,         112},
    { ATCA_LOCK,         11132},
    { ATCA_MAC,          1114},
    { ATCA_NONCE,        1129},
    { ATCA_PAUSE,        113},
    { ATCA_PRIVWRITE,    1148},
    { ATCA_RANDOM,       1123},
    { ATCA_READ,         115},
    { ATCA_SHA,          119},
    { ATCA_SIGN,         1160},
    { ATCA_UPDATE_EXTRA, 1110},
    { ATCA_VERIFY,       1172},
    { ATCA_WRITE,        1126}
};

/*Execution times for ATECC508A supported commands...*/
static const device_execution_time_t device_execution_time_508[] = {
    { ATCA_CHECKMAC,     1113},
    { ATCA_COUNTER,      1120},
    { ATCA_DERIVE_KEY,   1150},
    { ATCA_ECDH,         1158},
    { ATCA_GENDIG,       1111},
    { ATCA_GENKEY,       11115},
    { ATCA_HMAC,         1123},
    { ATCA_INFO,         112},
    { ATCA_LOCK,         11132},
    { ATCA_MAC,          1114},
    { ATCA_NONCE,        1129},
    { ATCA_PAUSE,        113},
    { ATCA_PRIVWRITE,    1148},
    { ATCA_RANDOM,       1123},
    { ATCA_READ,         115},
    { ATCA_SHA,          119},
    { ATCA_SIGN,         1160},
    { ATCA_UPDATE_EXTRA, 1110},
    { ATCA_VERIFY,       1172},
    { ATCA_WRITE,        1126}
};

/*Execution times for ATECC608-M0 supported commands...*/
static const device_execution_time_t device_execution_time_608_m0[] = {
    { ATCA_AES,          181},
    { ATCA_CHECKMAC,     1120},
    { ATCA_COUNTER,      175},
    { ATCA_DERIVE_KEY,   1150},
    { ATCA_ECDH,         1225},
    { ATCA_GENDIG,       175},
    { ATCA_GENKEY,       1345},
    { ATCA_INFO,         115},
    { ATCA_KDF,          1495},
    { ATCA_LOCK,         11105},
    { ATCA_MAC,          1165},
    { ATCA_NONCE,        160},
    { ATCA_PRIVWRITE,    1150},
    { ATCA_RANDOM,       169},
    { ATCA_READ,         115},
    { ATCA_SECUREBOOT,   1240},
    { ATCA_SELFTEST,     1750},
    { ATCA_SHA,          1108},
    { ATCA_SIGN,         1345},
    { ATCA_UPDATE_EXTRA, 130},
    { ATCA_VERIFY,       1310},
    { ATCA_WRITE,        1135}
};

/*Execution times for ATECC608-M1 supported commands...*/
static const device_execution_time_t device_execution_time_608_m1[] = {
    { ATCA_AES,          181},
    { ATCA_CHECKMAC,     1120},
    { ATCA_COUNTER,      175},
    { ATCA_DERIVE_KEY,   1150},
    { ATCA_ECDH,         1516},
    { ATCA_GENDIG,       1105},
    { ATCA_GENKEY,       1645},
    { ATCA_INFO,         115},
    { ATCA_KDF,          1495},
    { ATCA_LOCK,         11105},
    { ATCA_MAC,          1165},
    { ATCA_NONCE,        160},
    { ATCA_PRIVWRITE,    1150},
    { ATCA_RANDOM,       169},
    { ATCA_READ,         115},
    { ATCA_SECUREBOOT,   1480},
    { ATCA_SELFTEST,     11875},
    { ATCA_SHA,          1126},
    { ATCA_SIGN,         1660},
    { ATCA_UPDATE_EXTRA, 130},
    { ATCA_VERIFY,       1885},
    { ATCA_WRITE,        1135}
};

/*Execution times for ATECC608-M2 supported commands...*/
static const device_execution_time_t device_execution_time_608_m2[] = {
    { ATCA_AES,          181},
    { ATCA_CHECKMAC,     1120},
    { ATCA_COUNTER,      175},
    { ATCA_DERIVE_KEY,   1150},
    { ATCA_ECDH,         11593},
    { ATCA_GENDIG,       1105},
    { ATCA_GENKEY,       11959},
    { ATCA_INFO,         115},
    { ATCA_KDF,          1495},
    { ATCA_LOCK,         11105},
    { ATCA_MAC,          1165},
    { ATCA_NONCE,        160},
    { ATCA_PRIVWRITE,    1150},
    { ATCA_RANDOM,       169},
    { ATCA_READ,         115},
    { ATCA_SECUREBOOT,   11440},
    { ATCA_SELFTEST,     12324}, //did not change 
    { ATCA_SHA,          1225},
    { ATCA_SIGN,         11995},
    { ATCA_UPDATE_EXTRA, 130},
    { ATCA_VERIFY,       13255},
    { ATCA_WRITE,        1135}
};
#endif

/*Execution times for ECC204 supported commands...*/
static const device_execution_time_t device_execution_time_ecc204[] = {
    { ATCA_COUNTER,      1120},
    { ATCA_DELETE,       11200},
    { ATCA_GENKEY,       11500},
    { ATCA_INFO,         1120},
    { ATCA_LOCK,         11180},
    { ATCA_NONCE,        1120},
    { ATCA_READ,         1140},
    { ATCA_SELFTEST,     11600},
    { ATCA_SHA,          1180},
    { ATCA_SIGN,         11500},
    { ATCA_WRITE,        1180}
};

/*Execution times for SHA10x supported commands...*/
static const device_execution_time_t device_execution_time_sha10x[] = {
    { ATCA_CHECKMAC,     11100},
    { ATCA_COUNTER,      1120},
    { ATCA_DELETE,       11200},
    { ATCA_GENDIG,       1170},
    { ATCA_INFO,         1120},
    { ATCA_LOCK,         11180},
    { ATCA_MAC,          11120},
    { ATCA_NONCE,        1120},
    { ATCA_READ,         1140},
    { ATCA_SELFTEST,     11600},
    { ATCA_SHA,          1180},
    { ATCA_WRITE,        1180}
};
// *INDENT-ON*

/** \brief return the typical execution time for the given command
 *  \param[in] opcode  Opcode value of the command
 *  \param[in] ca_cmd  Command object for which the execution times are associated
 *  \return ATCA_SUCCESS
 */
ATCA_STATUS calib_get_execution_time(uint8_t opcode, ATCADevice device)
{
    ATCA_STATUS status = ATCA_SUCCESS;
    const device_execution_time_t *execution_times;
    uint8_t i, no_of_commands;


    switch (device->mIface.mIfaceCFG->devtype)
    {
#ifdef ATCA_NO_POLL
    case ATSHA204A:
        execution_times = device_execution_time_204;
        no_of_commands = sizeof(device_execution_time_204) / sizeof(device_execution_time_t);
        break;

    case ATSHA206A:
        execution_times = device_execution_time_206;
        no_of_commands = sizeof(device_execution_time_206) / sizeof(device_execution_time_t);
        break;

    case ATECC108A:
        execution_times = device_execution_time_108;
        no_of_commands = sizeof(device_execution_time_108) / sizeof(device_execution_time_t);
        break;

    case ATECC508A:
        execution_times = device_execution_time_508;
        no_of_commands = sizeof(device_execution_time_508) / sizeof(device_execution_time_t);
        break;

    case ATECC608:
        if (device->clock_divider == ATCA_CHIPMODE_CLOCK_DIV_M1)
        {
            execution_times = device_execution_time_608_m1;
            no_of_commands = sizeof(device_execution_time_608_m1) / sizeof(device_execution_time_t);
        }
        else if (device->clock_divider == ATCA_CHIPMODE_CLOCK_DIV_M2)
        {
            execution_times = device_execution_time_608_m2;
            no_of_commands = sizeof(device_execution_time_608_m2) / sizeof(device_execution_time_t);
        }
        else
        {
            // Assume default M0 clock divider
            execution_times = device_execution_time_608_m0;
            no_of_commands = sizeof(device_execution_time_608_m0) / sizeof(device_execution_time_t);
        }
        break;
#endif

    case TA010:
        /* fallthrough */
    case ECC204:
        execution_times = device_execution_time_ecc204;
        no_of_commands = sizeof(device_execution_time_ecc204) / sizeof(device_execution_time_t);
        break;

    case SHA104:
        /* fallthrough */
    case SHA105:
        execution_times = device_execution_time_sha10x;
        no_of_commands = sizeof(device_execution_time_sha10x) / sizeof(device_execution_time_t);
        break;

    default:
        no_of_commands = 0;
        execution_times = NULL;
        break;
    }

    device->execution_time_msec = ATCA_UNSUPPORTED_CMD;

    for (i = 0; i < no_of_commands; i++)
    {
        if (execution_times[i].opcode == opcode)
        {
            device->execution_time_msec = execution_times[i].execution_time_msec;
            break;
        }
    }

    if (device->execution_time_msec == ATCA_UNSUPPORTED_CMD)
    {
        status = ATCA_BAD_OPCODE;
    }

    return status;
}

ATCA_STATUS calib_execute_send(ATCADevice device, uint8_t device_address, uint8_t* txdata, uint16_t txlength)
{
    ATCA_STATUS status = ATCA_COMM_FAIL;

    if (!txdata || !txlength)
    {
        return ATCA_TRACE(ATCA_BAD_PARAM, "NULL pointer encountered");
    }

#ifdef ATCA_HAL_LEGACY_API
    ((void)device_address);
    status = atsend(&device->mIface, 0xFF, (uint8_t*)txdata, (int)txlength - 1);
#else
    if (atca_iface_is_kit(&device->mIface))
    {
        status = atsend(&device->mIface, 0xFF, (uint8_t*)&txdata[1], (int)txlength - 1);
    }
    else
    {
        status = atcontrol(&device->mIface, ATCA_HAL_CONTROL_SELECT, NULL, 0);
        if (ATCA_UNIMPLEMENTED == status || ATCA_SUCCESS == status)
        {
            /* Send the command packet to the device */
            status = atsend(&device->mIface, device_address, (uint8_t*)txdata, (int)txlength);
        }
        (void)atcontrol(&device->mIface, ATCA_HAL_CONTROL_DESELECT, NULL, 0);
    }
#endif

    return status;
}


ATCA_STATUS calib_execute_receive(ATCADevice device, uint8_t device_address, uint8_t* rxdata, uint16_t* rxlength)
{
    ATCA_STATUS status = ATCA_COMM_FAIL;

    if ((NULL == rxlength) || (NULL == rxdata))
    {
        return ATCA_TRACE(ATCA_BAD_PARAM, "NULL pointer encountered");
    }

#ifdef ATCA_HAL_LEGACY_API
    ((void)device_address);
    status = atreceive(&device->mIface, 0, rxdata, rxlength);
#else
    uint16_t read_length = 1;
    uint8_t word_address;

    if (atca_iface_is_kit(&device->mIface))
    {
        status = atreceive(&device->mIface, 0, rxdata, rxlength);
    }
    else
    {
        do
        {
            status = atcontrol(&device->mIface, ATCA_HAL_CONTROL_SELECT, NULL, 0);
            if (ATCA_UNIMPLEMENTED != status && ATCA_SUCCESS != status)
            {
                break;
            }

            /*Send Word address to device...*/
            if (ATCA_SWI_IFACE == device->mIface.mIfaceCFG->iface_type)
            {
                word_address = CALIB_SWI_FLAG_TX;
            }
            else
            {
                word_address = 0;
            }

            // Skip word address send for ECC204 device
            if (!atcab_is_ca2_device(device->mIface.mIfaceCFG->devtype))
            {
                if (ATCA_SUCCESS != (status = atsend(&device->mIface, device_address, &word_address, sizeof(word_address))))
                {
                    break;
                }
            }

            /* Read length bytes to know number of bytes to read */
            status = atreceive(&device->mIface, device_address, rxdata, &read_length);
            if (ATCA_SUCCESS != status)
            {
                ATCA_TRACE(status, "atreceive - failed");
                break;
            }

            /*Calculate bytes to read based on device response*/
            read_length = rxdata[0];

            if (read_length > *rxlength)
            {
                status = ATCA_TRACE(ATCA_SMALL_BUFFER, "rxdata is small buffer");
                break;
            }

            if (read_length < 4)
            {
                status = ATCA_TRACE(ATCA_RX_FAIL, "packet size is invalid");
                break;
            }

            /* Read given length bytes from device */
            read_length -= 1;

            status = atreceive(&device->mIface, device_address, &rxdata[1], &read_length);

            if (ATCA_SUCCESS != status)
            {
                status = ATCA_TRACE(status, "atreceive - failed");
                break;
            }

            read_length += 1;

            *rxlength = read_length;
        }
        while (0);

        (void)atcontrol(&device->mIface, ATCA_HAL_CONTROL_DESELECT, NULL, 0);
    }
#endif

    return status;
}

/** \brief Wakes up device, sends the packet, waits for command completion,
 *         receives response, and puts the device into the idle state.
 *
 * \param[in,out] packet  As input, the packet to be sent. As output, the
 *                       data buffer in the packet structure will contain the
 *                       response.
 * \param[in]    device  CryptoAuthentication device to send the command to.
 *
 * \return ATCA_SUCCESS on success, otherwise an error code.
 */
ATCA_STATUS calib_execute_command(ATCAPacket* packet, ATCADevice device)
{
    ATCA_STATUS status;
    uint32_t execution_or_wait_time;
    uint32_t max_delay_count;
    uint16_t rxsize;
    uint8_t device_address = atcab_get_device_address(device);
    int retries = 1;

    do
    {
#ifdef ATCA_NO_POLL
        if ((status = calib_get_execution_time(packet->opcode, device)) != ATCA_SUCCESS)
        {
            return status;
        }
        execution_or_wait_time = device->execution_time_msec;
        max_delay_count = 0;
#else
        execution_or_wait_time = 400;// Override to be 60
        max_delay_count = ATCA_POLLING_MAX_TIME_MSEC / ATCA_POLLING_FREQUENCY_TIME_MSEC;

    #if ATCA_CA2_SUPPORT
        if ((ATCA_SWI_GPIO_IFACE == device->mIface.mIfaceCFG->iface_type) && (atcab_is_ca2_device(device->mIface.mIfaceCFG->devtype)))
        {
            if ((status = calib_get_execution_time(packet->opcode, device)) != ATCA_SUCCESS)
            {
                return status;
            }
            execution_or_wait_time = 400; //device->execution_time_msec;
            max_delay_count = 0;
        }
    #endif
#endif
        retries = atca_iface_get_retries(&device->mIface);
        do
        {
            if (ATCA_DEVICE_STATE_ACTIVE != device->device_state)
            {
                if (ATCA_SUCCESS == (status = calib_wakeup(device)))
                {
                    device->device_state = ATCA_DEVICE_STATE_ACTIVE;
                }
            }

            /* Send the command packet to the device */
            if ((ATCA_I2C_IFACE == device->mIface.mIfaceCFG->iface_type) || (ATCA_CUSTOM_IFACE == device->mIface.mIfaceCFG->iface_type))
            {
                packet->_reserved = 0x03;
            }
            else if (ATCA_SWI_IFACE == device->mIface.mIfaceCFG->iface_type)
            {
                packet->_reserved = CALIB_SWI_FLAG_CMD;
            }
    #if ATCA_CA2_SUPPORT
            else if ((ATCA_SWI_GPIO_IFACE == device->mIface.mIfaceCFG->iface_type) && (atcab_is_ca2_device(device->mIface.mIfaceCFG->devtype)))
            {
                packet->_reserved = 0x03;
            }
    #endif
            if (ATCA_RX_NO_RESPONSE == (status = calib_execute_send(device, device_address, (uint8_t*)packet, packet->txsize + 1)))
            {
                device->device_state = ATCA_DEVICE_STATE_UNKNOWN;
            }
            else
            {
                if (ATCA_DEVICE_STATE_ACTIVE != device->device_state)
                {
                    device->device_state = ATCA_DEVICE_STATE_ACTIVE;
                }
                retries = 0;
            }

        }
        while (0 < retries--);

        if (ATCA_SUCCESS != status)
        {
            break;
        }

        // Delay for execution time or initial wait before polling
        atca_delay_ms(execution_or_wait_time);

        do
        {
            memset(packet->data, 0, sizeof(packet->data));
            // receive the response
            rxsize = sizeof(packet->data);

            if (ATCA_SUCCESS == (status = calib_execute_receive(device, device_address, packet->data, &rxsize)))
            {
                break;
            }

#ifndef ATCA_NO_POLL
            // delay for polling frequency time
            atca_delay_ms(ATCA_POLLING_FREQUENCY_TIME_MSEC);
#endif
        }
        while (max_delay_count-- > 0);

        if (status != ATCA_SUCCESS)
        {
            break;
        }

        // Check response size
        if (rxsize < 4)
        {
            if (rxsize > 0)
            {
                status = ATCA_RX_FAIL;
            }
            else
            {
                status = ATCA_RX_NO_RESPONSE;
            }
            break;
        }

        if ((status = atCheckCrc(packet->data)) != ATCA_SUCCESS)
        {
            break;
        }

        if ((status = isATCAError(packet->data)) != ATCA_SUCCESS)
        {
            break;
        }
    }
    while (0);

    // Skip Idle for ECC204 device
    if (!atcab_is_ca2_device(device->mIface.mIfaceCFG->devtype))
    {
        (void)calib_idle(device);
        device->device_state = ATCA_DEVICE_STATE_IDLE;
    }

    return status;
}
