# ESP32-IDF RMT module API wraper for nanoFramework

## Support
* __ONLY Tx supported yet__
* Autoselect RTM challen (0..7) for each new C# object
* Connect to designed GPIO pin
* RTM module clock source select (wraped but not supported in IDF yet)
* Clock devider select
* Carier mode control
* Transmitter idle output level
* Async Transmission a raw byte array containing a set of instructions for the RTM module (see [rmt_item32_t](https://github.com/espressif/esp-idf/blob/39f090a4f/components/soc/esp32/include/soc/rmt_struct.h))