# Provision ECC608

This example project is used to generate a private key and certificate sign request (CSR) using the [ATECC608A](https://www.microchip.com/wwwproducts/en/atecc608a) (TrustCustom) crypto chip. You will need to compile the example code, flash the generated firmware (binary) into the ESP32, which is connected to the ATECC608A chip through I2C, and run the firmware. The firmware will provision the ATECC608A chip, creating the public and privacy key pair. The private key will be stored inside of the ATECC608A and never go out of the ATECC608A. The firmware reads the public key and outputs it to the serial port. You HAVE to save the output CSR into a file.

The project assumes you have connected your ESP32-WROOM-32 to an ECC608 through a I2C connection. The I2C address, SDA, and SCL pins are 0xC0, 27, and 33 respectively, but these are easily configurable. This is our IoT kit configuration. You do not need to change the I2C configuraiton if our IoT kit is used.

## Get Started

Follow these instructions to generate a private key and CSR:

- Installation instructions for ESP-IDF version release/v4.2 are here: https://docs.espressif.com/projects/esp-idf/en/release-v4.2/esp32/get-started/index.html. Not needed if the provided VM is used.
- Download and configure this project using the following commands:
```
git clone --recursive https://github.com/PBearson/Provision-ECC608.git
cd Provision-ECC608
idf.py menuconfig
```
- The idf.py commaned is not needed if our IoT kit is used.
- In the menu config, navigate to **Component config -> esp-cryptoauthlib** and change the I2C SDA pins and I2C SCL pins to the appropriate pinout for your setup. Not needed if our IoT kit is used.
- If the I2C slave address is not 0xC0, or if you do not know the address, then check the option "Scan for the ATECC608A I2C address". Not needed if our IoT kit is used.
- Now quit the menuconfig and build/flash the app to your ESP32. VS Code can be used to do the same thing, i.e. flashing the binary app/firmware into the ESP32, running it and monitoring the serial port output.
```
idf.py build flash monitor
```

A public key and CSR will print to the console. Note: the private key is stored inside of ATECC608A chip and never comes out. You may save the CSR for future use in a network application (e.g., AWS IoT).

## Sample Output

Note: You have to run the firmware/app to see the output. You MUST save the CSR into a file, e.g. ecc608a.csr.

![Sample output](imgs/provision-ecc608-sample.JPG)
