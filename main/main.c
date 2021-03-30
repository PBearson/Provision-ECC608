#include <stdio.h>
#include "cryptoauthlib.h"
#include "atcacert/atcacert_client.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "csr_def.h"
#include "esp_log.h"

void print_csr(char*, size_t);
void print_pubkey(uint8_t*, size_t);

static const char *TAG = "provision-ecc608";

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
	printf("04:");
	for(int i = 0; i < pubkey_size; i++)
	{
		if((i + 1) % 15 == 0 && i != 0) printf("\n");
		if(i < pubkey_size - 1) printf("%02x:", pubkey[i]);
		else printf("%02x", pubkey[i]);
	}
	printf("\n\n");
}


// Initialize ECC608
void initialize_ecc608()
{
    int ret;
    ESP_LOGI(TAG, "Initializing ECC608");

    #ifdef CONFIG_SCAN_FOR_I2C_ADDRESS

    ESP_LOGI(TAG, "Scanning for the correct I2C address");
    for(int i = 0; i < 256; i++)
    {
        ESP_LOGI(TAG, "Scanning address %02X", i);
        cfg_ateccx08a_i2c_default.atcai2c.slave_address = i;
        ret = atcab_init(&cfg_ateccx08a_i2c_default);
        if(!ret) break;
    }

    #else

    int default_address = cfg_ateccx08a_i2c_default.atcai2c.slave_address;
    ESP_LOGI(TAG, "Scanning default address %02X", default_address);
    ret = atcab_init(&cfg_ateccx08a_i2c_default);

    #endif

    assert(!ret);

    ESP_LOGI(TAG, "Successfully initialized ECC608");
}

void app_main()
{
	initialize_ecc608();

	uint8_t pubkey[64];
	char csr[512];
	size_t csr_size = sizeof(csr);

	// Lock the config and data zones. This is one-time only.
	atcab_lock_config_zone();
	atcab_lock_data_zone();

	// Generate a private key in slot 0
	assert(!atcab_genkey(0, pubkey));

	// Generate a CSR from the private key and CSR template.
	assert(!atcacert_create_csr_pem(&csr_def, csr, &csr_size));

	// Print public key and CSR
	print_pubkey(pubkey, sizeof(pubkey));
	print_csr(csr, csr_size);

	printf("Please save this CSR to a file.\n");
}
