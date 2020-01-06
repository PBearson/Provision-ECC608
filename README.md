# Provision ECCx08

### Author: Bryan Pearson

Download or clone this repository into your ESP-IDF workspace in order to quickly provision the ECCx08 cryptochip for your needs. 

To get started, you will need to edit the "main/crypto_settings.h" file to reflect your configuration. For example, if you are using the ATECC508A chip, you need to change ECCX08_TYPE to "508". You will also likely need to change the SDA and SCL pins, which are currently configured for the HelTec WiFi Kit 32 board.

The "main/main.c" file is currently written to generate a private ECC key in slot 0 of the cryptochip, then return a CSR which can be used to generate a valid certificate for the host device (e.g., your ESP32). This can be used in applications such as TLS client-side authentication, where the ECCx08 provides a hardware root of trust.

Currently, the generated CSR will have a validity period of about 30 years. This setting (and other CSR settings) can be adjusted in the "main/csr_def.h" file.

Prior to provisioning the ECCx08, it is assumed that the configuration zone is locked and and the data zone is unlocked. Moreover, slot 0 must be configured with the following permissions:
* P256 key type
* No read/write access
* Can sign/verify data
* Can derive the public key
* Slot is unlocked, but lockable

The preconfiguration of the ECCx08 must be done beforehand. Consult the ATECC508A datasheet to find out more: http://ww1.microchip.com/downloads/en/DeviceDoc/20005927A.pdf
