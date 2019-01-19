# arduino-joystick
A generic arduino based joystick with a nrf24l01 transceiver

Hardware, bought all at aliexpress:

- Arduino UNO clone
- Joystick shield
- nrf24l01
- 16x2 characters LCD display connected via I2C

## Setup

### Install RF24 library
```
cd lib
git clone git@github.com:nRF24/RF24.git
```

### Install LiquidCrystal_I2C library
```
cd lib
git clone git@github.com:johnrickman/LiquidCrystal_I2C.git
```
