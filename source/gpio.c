#include <gpio.h>

#define GPIO_SET_DIR_OUT(dir, bit) ( (dir->DIRSET) = (1 << (bit)) )
#define GPIO_SET_DIR_IN(dir, bit)  ( (dir->DIRCLR) = (1 << (bit)) )

#define GPIO_SET_HI(port, bit) ( (port->OUTSET) = (1 << (bit)) )
#define GPIO_SET_LO(port, bit) ( (port->OUTCLR) = (1 << (bit)) )

#define GET_GPIO_INPUT(port, bit)  ( (port->IN) &  (1 << (bit)) )

typedef volatile struct __attribute__((packed)) {
	uint32_t reserved0[321];/* 0x000 - 0x500 reserved */
	uint32_t OUT;		/* 0x504 Write GPIO port */
	uint32_t OUTSET;	/* 0x508 Set individual bits in GPIO port */
	uint32_t OUTCLR;	/* 0x50C Clear individual bit in GPIO port */
	uint32_t IN;		/* 0x510 Read GPIO port */
	uint32_t DIR;		/* 0x514 Direction of GPIO port */
	uint32_t DIRSET;	/* 0x518 DIR set register */
	uint32_t DIRCLR;	/* 0x51C DIR clear register */
	uint32_t LATCH;		/* 0x520 Latch register indicating what GPIO pins
				   that have met the criteria set in the
				   PIN_CNF[n].SENSE registers*/
	uint32_t DETECTMODE;	/* 0x524 Select between default DETECT signal
				   behaviour and LDETECT mode*/
	uint32_t reserved1[118];/* 0x528 - 0x6FC reserved */
	uint32_t PIN_CNF[32];	/* 0x700 - 0x77C Configuration of GPIO pins*/
} GpioRegisters;

static GpioRegisters* gpio0 = (GpioRegisters* )0x50000000u;
static GpioRegisters* gpio1 = (GpioRegisters* )0x50000300u;


void setGpioDir(GpioPort gpioPort, GpioPin gpioPin, GpioDir gpioDir) {
	GpioRegisters* gpio;

	switch (gpioPort) {
		case GPIO_0:
			gpio = gpio0;
			break;
		case GPIO_1:
			gpio = gpio1;
			break;
		default:
			break;
	}

	switch (gpioDir) {
		case GPIO_INPUT:
			GPIO_SET_DIR_IN(gpio, gpioPin);
			break;
		case GPIO_OUTPUT:
			GPIO_SET_DIR_OUT(gpio, gpioPin);
			break;
		default:
			break;
	}
}

void setGpioOutput(GpioPort gpioPort, GpioPin gpioPin, GpioOut gpioOut) {
	GpioRegisters* gpio;

	switch (gpioPort) {
		case GPIO_0:
			gpio = gpio0;
			break;
		case GPIO_1:
			gpio = gpio1;
			break;
		default:
			break;
	}
	
	switch (gpioOut) {
	case GPIO_LOW:
		GPIO_SET_LO(gpio, gpioPin);
		break;
	case GPIO_HIGH:
		GPIO_SET_HI(gpio, gpioPin);
		break;
	default:
		break;
	}
}

#define GET_GPIO_INPUT(port, bit)  ( (port->IN) &  (1 << (bit)) )
GpioOut getGpioInput(GpioPort gpioPort, GpioPin gpioPin) {
	GpioRegisters* gpio;

	switch (gpioPort) {
		case GPIO_0:
			gpio = gpio0;
			break;
		case GPIO_1:
			gpio = gpio1;
			break;
		default:
			break;
	}

	GpioOut gpioOut;

	if ( GET_GPIO_INPUT(gpio, gpioPin) ) {
		gpioOut = GPIO_HIGH;
	} else {
		gpioOut = GPIO_LOW;
	}

	return gpioOut;
}