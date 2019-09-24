/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "cryptoauthlib.h"
#include "atcacert/atcacert_client.h"
#include "atcacert/atcacert_host_hw.h"
#include "driver/i2c.h"
#include "crypto_settings.h"
#include "freertos/task.h"
#include "csr_def.h"

void print_csr(char*, size_t);
void print_pubkey(uint8_t*, size_t);

/*
 * Check the return status of a function.
 * Assume 0 = SUCCESS.
 * If non-zero, stop the code.
 */
void check_ret(int ret)
{
	if(ret != 0)
	{
		printf("There is a problem. Error code %X. Refer here for more information:\n%s\n", ret, "https://github.com/MicrochipTech/cryptoauthlib/blob/master/lib/atca_status.h");
		while(true) vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

/*
 * Similar to check_ret except we print the CSR before stalling.
 * Call this if the device fails to generate a public key in slot 0.
 */
void check_ret_csr(int ret)
{
	uint8_t pubkey[64];
	char csr[512];
	size_t pubkey_size = 64;
	size_t csr_size = 512;

	if(ret != 0)
	{
		// Using the public key, create a CSR
		check_ret(atcab_get_pubkey(0, pubkey));
		check_ret(atcacert_create_csr_pem(&csr_def, csr, &csr_size));

		// Print public key and CSR
		print_pubkey(pubkey, pubkey_size);
		print_csr(csr, csr_size);
		
		// Still need to check the ret value
		check_ret(ret);
	}
}

/*
 * Lock the ECCx08 data zone.
 */
void lock_data_zone()
{
	check_ret(atcab_lock_data_slot(0));
	check_ret(atcab_lock_data_zone());
	printf("Your cryptochip's data zone has been successfully locked.\n");
}

/*
 * Print a CSR
 */
void print_csr(char* csr, size_t csr_size)
{
	printf("Your CSR:\n");
	for(int i = 0; i < csr_size; i++) printf("%c", csr[i]);
	printf("\n\n");
}

/*
 * Print a public key
 */
void print_pubkey(uint8_t* pubkey, size_t pubkey_size)
{
	printf("Your public key:\n");
	for(int i = 0; i < pubkey_size; i++) printf("%X ", pubkey[i]);
	printf("\n\n");
}

/*
 * Create a new private ECC in slot 0 and generate a CSR.
 * Only run this after successfully calling "atcab_init()"
 */
void run()
{	
     	uint8_t pubkey[64];
	char csr[512];
	size_t pubkey_size = 64;
	size_t csr_size = 512;
	
	// 1: Generate a private key
	check_ret_csr(atcab_genkey(0, pubkey));
	
	// 2: Create a CSR from the private key
	check_ret(atcacert_create_csr_pem(&csr_def, csr, &csr_size));

	// Print public key and CSR
	print_pubkey(pubkey, pubkey_size);
	print_csr(csr, csr_size);

	// Lock data zone
	lock_data_zone();
}

/*
 * Start here
 */
void app_main()
{
	ATCAIfaceCfg cfg = atca_cfg_init();	
	i2c_init();
	check_ret(atcab_init(&cfg));
	printf("Your cryptochip is successfully connected!\n");
	run();
}
