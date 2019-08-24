# ESP32-IDF RMT module API wraper for nanoFramework

## Support
* __ONLY Tx supported yet__
* Autoselect RTM challen (0..7) for each new C# object, throws an exception, if all channels are used
* Connect to designed GPIO pin
* RTM module clock source select (wraped but not supported in IDF yet)
* Clock devider select
* Carier mode control
* Transmitter idle output level control
* Async Transmission a raw byte array containing a set of instructions for the RTM module (see [rmt_item32_t](https://github.com/espressif/esp-idf/blob/39f090a4f/components/soc/esp32/include/soc/rmt_struct.h))

## Example
```cs
using nanoFramework.Hardware.Esp32.RMT.Tx;

...

// Register new RTM transmitter on GPIO15
var rmt_transmitter = Transmitter.Register(GPIO: 15);

// transmitter configuration
rmt_transmitter.CarierEnabled = false;
rmt_transmitter.isSource80MHz = true;
rmt_transmitter.ClockDivider = 4; // base period 80 MHz / 4 => 20 MHz -> 0.05 us
rmt_transmitter.IsTransmitIdleEnabled = true;
rmt_transmitter.TransmitIdleLevel = false;

// create new pulse command for to transmitt
// IDLE  0.5us  1us       1.5 us           2 us             2.5 us	   IDLE..
//      |----|        |------------|                |--------------------|
// -----|    |--------|            |----------------|                    |------
var commandlist = new PulseCommandList();
commandlist
	.AddLevel(true, 10)
	.AddLevel(false, 20)
	.AddLevel(true, 30)
	.AddLevel(false, 40)
	.AddLevel(true, 50);

rmt_transmitter.Send(commandlist);

// destroy transmitter instance and free associated RMT channel
rmt_transmitter.Dispose();
```
Result on GPIO15

![Logick_analiser](asserts/example_pilses.png)

## Build

1. Clone repository into any dirrectory
```
git clone https://github.com/ololoshka2871/nanoFramework.Hardware.Esp32.RMT.git
```

2. Setup nf-interpreter build environment. [Manual](http://docs.nanoframework.net/articles/getting-started-guides/build-esp32.html).

3. Copy file **Native/FindINTEROP-nanoFramework.Hardware.Esp32.RMT.cmake.template** to **nf-interpreter\CMake\Modules\FindINTEROP-nanoFramework.Hardware.Esp32.RMT.cmake**

4. Edit file **nf-interpreter/CMake/Modules/FindINTEROP-nanoFramework.Hardware.Esp32.RMT.cmake**
Replace `${PROJECT_SOURCE_DIR}/<PATH_TO_YOUR nanoFramework.Hardware.Esp32.RMT/Native folder>` to **path** of cloned repository.

5. Add string `
"NF_INTEROP_ASSEMBLIES" : [ "nanoFramework.Hardware.Esp32.RMT" ]` to in file cmake-variants.json in nf-interpreter folder

6. Build and flash nf-interpreter into ESP32

7. Add reference to **nanoFramework.Hardware.Esp32.RMT** library into your C# project.

8. Build and deploy application into ESP32

9. Enjoy!

## Applications
* Control WS2812 Led strips [Library](https://github.com/ololoshka2871/nanoFramework.Hardware.Esp32.RMT.NeoPixel.git)
