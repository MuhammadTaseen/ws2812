# Firmware for RBG strip ws2812 with ESP8266 RTOS SDK



## Introduction

The software is helping to stand alone run led strip ws2812 using esp8266 with its esp8266 rtos sdk.

The main part is to develop the main led strip controlling module using the available  [Adafruit led strip](https://www.adafruit.com/product/1138). The main code was in Arduino platform io. But this available module is converted and ready to build with the old [ESP8266 RTOS SDK](https://github.com/espressif/ESP8266_RTOS_SDK) of `release/v2.1`

## Usage

1. The main directory contain 2x directories

- The main directory, having the main user app
- The ws2812 directory having the main driver which is ready to build with the `ESP8266 RTOS SDK`


## Inspired from 

The main inspiration to convert this library for esp8266 rtos sdk is to run that led strip with rto's rather then using platform io.


## How to build

1. Clone [ESP8266 RTOS SDK](https://github.com/espressif/ESP8266_RTOS_SDK) `release/v2.1`.
2. Now export the RTO's sdk environment and open the directly to build the LED strip
3. The step for exporting the RTO's SDK will be explain in next version.
4. After opening the directory just build the code


```sh

idf.py build

```

## References

- **AdafruitNeoPixel:** `https://www.adafruit.com/product/1138`
- **ESP8266RTO's Sdk:** `https://github.com/espressif/ESP8266_RTOS_SDK`

- **Language:** `C/C++`
- **SDK:** `ESP8266 RTOS SDK`

## Author

**Developer Name:** `M.Taseen`


