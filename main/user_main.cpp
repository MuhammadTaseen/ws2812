#include <stdio.h>
#include <string.h>

#include "esp_event.h"
#include "esp_system.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "freertos/task.h"

#include "lwip/dns.h"
#include "lwip/netdb.h"
#include "lwip/sockets.h"

#include "esp_log.h"

#include "Adafruit_NeoPixel.h"

static const char *TAG = "MAIN";

#define PIN 14
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

#ifdef __cplusplus
extern "C"
{
#endif

    // Input a value 0 to 255 to get a color value.
    // The colours are a transition r - g - b - back to r.
    uint32_t Wheel(uint8_t WheelPos)
    {
        WheelPos = 255 - WheelPos;
        if (WheelPos < 85)
        {
            return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
        }
        if (WheelPos < 170)
        {
            WheelPos -= 85;
            return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
        }
        WheelPos -= 170;
        return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    }

    // Fill the dots one after the other with a color
    void colorWipe(uint32_t c, uint8_t wait)
    {
        for (uint16_t i = 0; i < strip.numPixels(); i++)
        {
            strip.setPixelColor(i, c);
            strip.show();
            vTaskDelay(wait / portTICK_RATE_MS);
        }
    }

    void rainbow(uint8_t wait)
    {
        uint16_t i, j;

        for (j = 0; j < 256; j++)
        {
            for (i = 0; i < strip.numPixels(); i++)
            {
                strip.setPixelColor(i, Wheel((i + j) & 255));
            }
            strip.show();
            vTaskDelay(wait / portTICK_RATE_MS);
        }
    }

    // Slightly different, this makes the rainbow equally distributed throughout
    void rainbowCycle(uint8_t wait)
    {
        uint16_t i, j;

        for (j = 0; j < 256 * 5; j++)
        { // 5 cycles of all colors on wheel
            for (i = 0; i < strip.numPixels(); i++)
            {
                strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
            }
            strip.show();
            vTaskDelay(wait / portTICK_RATE_MS);
        }
    }

    // Theatre-style crawling lights.
    void theaterChase(uint32_t c, uint8_t wait)
    {
        for (int j = 0; j < 10; j++)
        { // do 10 cycles of chasing
            for (int q = 0; q < 3; q++)
            {
                for (uint16_t i = 0; i < strip.numPixels(); i = i + 3)
                {
                    strip.setPixelColor(i + q, c); // turn every third pixel on
                }
                strip.show();

                vTaskDelay(wait / portTICK_RATE_MS);

                for (uint16_t i = 0; i < strip.numPixels(); i = i + 3)
                {
                    strip.setPixelColor(i + q, 0); // turn every third pixel off
                }
            }
        }
    }

    // Theatre-style crawling lights with rainbow effect
    void theaterChaseRainbow(uint8_t wait)
    {
        for (int j = 0; j < 256; j++)
        { // cycle all 256 colors in the wheel
            for (int q = 0; q < 3; q++)
            {
                for (uint16_t i = 0; i < strip.numPixels(); i = i + 3)
                {
                    strip.setPixelColor(i + q, Wheel((i + j) % 255)); // turn every third pixel on
                }
                strip.show();

                vTaskDelay(wait / portTICK_RATE_MS);

                for (uint16_t i = 0; i < strip.numPixels(); i = i + 3)
                {
                    strip.setPixelColor(i + q, 0); // turn every third pixel off
                }
            }
        }
    }

    void app_main(void)
    {
        strip.begin();
        strip.setBrightness(30);
        strip.show(); // Initialize all pixels to 'off'
        strip.setPixelColor(0, strip.Color(0, 255, 0));
        strip.setPixelColor(2, strip.Color(255, 0, 0));

        while (1)
        {
            printf("cont ... \n");

            colorWipe(strip.Color(255, 0, 0), 50); // Red
            colorWipe(strip.Color(0, 255, 0), 50); // Green
            colorWipe(strip.Color(0, 0, 255), 50); // Blue
                                                   // colorWipe(strip.Color(0, 0, 0, 255), 50); // White RGBW
            //  Send a theater pixel chase in...
            theaterChase(strip.Color(127, 127, 127), 50); // White
            theaterChase(strip.Color(127, 0, 0), 50);     // Red
            theaterChase(strip.Color(0, 0, 127), 50);     // Blue

            rainbow(20);
            rainbowCycle(20);
            theaterChaseRainbow(50);
            vTaskDelay(10 / portTICK_RATE_MS);
        }
    }

#ifdef __cplusplus
}
#endif
