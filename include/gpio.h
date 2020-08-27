#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

typedef enum { GPIO_0 = 0, GPIO_1 } GpioPort;
typedef enum { GPIO_INPUT = 0, GPIO_OUTPUT } GpioDir;
typedef enum { GPIO_LOW = 0, GPIO_HIGH } GpioOut;
typedef enum {
    GPIO_PIN_0 = 0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3,
    GPIO_PIN_4,  GPIO_PIN_5,  GPIO_PIN_6,  GPIO_PIN_7,
    GPIO_PIN_8,  GPIO_PIN_9,  GPIO_PIN_10, GPIO_PIN_11,
    GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15,
    GPIO_PIN_16, GPIO_PIN_17, GPIO_PIN_18, GPIO_PIN_19,
    GPIO_PIN_20, GPIO_PIN_21, GPIO_PIN_22, GPIO_PIN_23,
    GPIO_PIN_24, GPIO_PIN_25, GPIO_PIN_26, GPIO_PIN_27,
    GPIO_PIN_28, GPIO_PIN_29, GPIO_PIN_30, GPIO_PIN_31
} GpioPin;

void setGpioDir(GpioPort gpioPort, GpioPin gpioPin, GpioDir gpioDir);
void setGpioOutput(GpioPort gpioPort, GpioPin gpioPin, GpioOut gpioOut);
GpioOut getGpioInput(GpioPort gpioPort, GpioPin gpioPin);
GpioOut getGpioDriver(GpioPort gpioPort, GpioPin gpioPin);

#endif	// GPIO_H
