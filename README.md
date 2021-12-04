# ESPill-Serial-Godzilla (ESP32s2/ESP32s3 2/3-Port USB-UART Serial Adapter)

This project has been inspired by https://github.com/r2axz/bluepill-serial-monster. It attempts to be its analog for the esp32s* chips. It turns any esp32s* into a usb-uart adapter, meaning you plug its usb-interface into your PC, and it enumerates 2 (esp32s2) or 3 (esp32s3) Serial Ports, each one is mapped to one of the hardware serial interfaces of the espill, which you can use to interface to any 3rd party device that exposes a serial interface. It then works like any ft2232/ch340/etc. This means you never need to buy any dedicated usb-uart adapter to program any boards over serial, since the esp32s* have a feature that if you set them into flashing mode, they automatically expose a built-in permanent virtual serial port over usb, through which you can download any firmware into it. So you can load this (espill-godzilla) itself onto that esp32s2, and once you reboot it, it becomes a 2/3-channel serial programmer for any other mcus you have, be they other esp32s*/esp32/esp8266/stm32f1/etc...

The clou is that it also supports setting/toggling dtr/rts pins, which are used by many tools (such as esptool), to automatically set the target chip into flashing mode and reset it.

Currently, I've only tested it on an esp32s2, as I don't have any esp32s3 yet (in the mail). Thus I don't have any binaries for the esp32s3 yet. Note the esp32s2 only has 2 hardware uarts, so you only get 2 channels. The esp32s3 only has 3, so you get 3. Theoretically, usb allows 5 independent serial (USB CDC-ACM) channels, but atleast the esp32s2 is limited to only 5 active USB IN-endpoints at a time, meaning even though 5 ports would show up on the PC if desired, only 3 of them would actually work (atleast for 1 direction). There might be some workarounds to atleast support these partially (ex. 1-way communication), I'll get around to this when I have time.

All this only became possible after modifying the underlying esp-idf. So the source won't actually compile unless you use the same modified esp-idf that I am using. I'll upload this later, as I'm a git noob, and am having difficulty understanding how to publish my changes (in an efficient way). I'll try patching a zipped v4.3.1 release. When it's done, I'll upload it as a separate project, then link to it here.

## Pin Mappings:
UART0:
RX: 7
Tx: 8
DTR: 9
RTS: 10

UART1:
RX: 11
TX: 12
DTR: 13
RTS: 14

Note: On your PC, different ports enumerate with different numbers, depending on which are currently available. This mapping isn't fixed. But generally, they will be in order, and the lowest number there corresponds to uart0 and so on.

# How to Setup:

Just download a finished binary from the releases section (to the right of the github page), then go to where you downloaded it in cmd/bash, and flash that image to your esp using this command (assuming you know what esptool is and have it setup in your path):
esptool.py -p PORT -b BAUD erase_flash
esptool.py -p PORT -b BAUD write_flash 0 espill_serial_godzilla-esp32s2.bin

ofcourse replace PORT with whatever serial port you usually use for flashing, and replace BAUD with whatever flashing speed you want, usually 921600 is good. If your PC doesn't already have a serial port, and you don't have any usb-uart adapters, then manually place the esp32s2 into flashing-mode (connect GPIO0 to GND, then connect EN to GND then to 3.3V). Ofcourse you have to connect its usb-pins to any USB port on your PC first (google it). Then a serial port will automatically be detected by your PC and you can use it to flash to the esp32s2/esp32s3.

# Future Plans
Support JTAG and ST-Link's SWD Interface into a single cross-platform tool, hopefully also with support for multiple independent channels (allowing simultaneous flashing and debugging of several heterogeneous boards/chips).