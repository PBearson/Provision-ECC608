# ESP-CRYPTOAUTHLIB

This is a port of Microchip's [cryptoauthlib](https://github.com/MicrochipTech/cryptoauthlib) for ESP-IDF. It contains necessary build support to use cryptoauthlib with ESP-IDF.

The  `esp_cryptoauthlib_utility` has been removed in this fork. Instead, users should refer to [Provision ECC608](https://github.com/PBearson/Provision-ECC608) for provisioning the ATECC608A with their ESP32-WROOM-32.

## Changes
Due to an update to this library some changes were made. Additionally we manually overrode the execution_or_wait_time in ``` cryptoauthlib/lib/calib/calib_execution.c ```, additionally the ```/cryptoauthlib/lib/mbedtls/atca_mbedtls_wrap.c ``` file was edited to make it compatible with MBEDTLS versions 3.x.

``` cryptoauthlib/lib/calib/calib_execution.c ```
* Increase *execution_or_wait_time* variable manually
  * This is due to an increased processing time in the chip we are using

```/cryptoauthlib/lib/mbedtls/atca_mbedtls_wrap.c ```
* Change ``` #include "pk_internal.h" ``` to ``` #include "pk_wrap.h" ```
* Modify ``` atca_mbedtls_eckey_check_pair ``` to be the following 
    ```
        static int atca_mbedtls_eckey_check_pair(const void *pub, const void *prv, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng)
        {
            return mbedtls_pk_info_from_type(MBEDTLS_PK_ECKEY)->check_pair_func(pub, prv, f_rng, p_rng);
        }
    ```
* Modify any calls to  ``` atca_mbedtls_eckey_check_pair ``` 
* Comment out ```if (ATECC608 == device->mIface.mIfaceCFG->devtype) ``` block in ``` cryptoauthlib/lib/calib/calib_sign.c ```  as out chip does not have a message buffer.