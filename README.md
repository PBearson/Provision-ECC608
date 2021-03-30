# Provision ECC608

This project can be used to generate a private key and certificate sign request (CSR) using the ATECC608A (TrustCustom) crypto chip. More information about the chip can be found here: https://www.microchip.com/wwwproducts/en/atecc608a

The project assumes you have connected your ESP32-WROOM-32 to an ECC608 through a I2C connection. The I2C address, SDA, and SCL pins are 0xC0, 27, and 33 respectively, but these are easily configurable.

## Get Started

- Installation instructions for ESP-IDF version release/v4.2 are here: https://docs.espressif.com/projects/esp-idf/en/release-v4.2/esp32/get-started/index.html
- Download this project using the following command:
```
git clone --recursive https://github.com/PBearson/Provision-ECC608.git
```

To get started, you will need to edit the "main/crypto_settings.h" file to reflect your configuration. For example, if you are using the ATECC508A chip, you need to change ECCX08_TYPE to "508". You will also likely need to change the SDA and SCL pins, which are currently configured for the HelTec WiFi Kit 32 board.



currently written to generate a private ECC key in slot 0 of the cryptochip, then return a CSR which can be used to generate a valid certificate for the host device (e.g., your ESP32). This can be used in applications such as TLS client-side authentication, where the ECCx08 provides a hardware root of trust.
