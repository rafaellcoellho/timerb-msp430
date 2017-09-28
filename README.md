# Timer b routines in MSP430 microcontroller (MSP430x5xx)

No matter what applications you are designing with some microcontroller, counting time intervals is almost mandatory. So I'm sharing my general timer that I use whenever I need to mark intervals without a specific reason.

## Getting Started

Clone or download this repository on your computer. In the doc folder there is the x5xx manual. In the src folder is the header and the implementation of the functions.

### Prerequisites

When writing this code I was using MSP-EXP430F5529LP, so I guarantee that this code works perfectly well with it. Other variations of the x5xx series may not work the same, but I believe they are similar and this code is a good start.

I used the 4MHz XT1 oscillator, if there is not one with the same value attached to your MSP, you will need to adjust some things. Any questions just look in the manual.

Since the count is within an interrupt, you must be careful not to disable peripheral interrupts for a significant amount of time. This can cause various logics to behave the wrong way because time has stopped counting for a while. At CCS this is how we enable peripheral interruptions:

```
_enable_interrupts();
```

And this is how disable:

```
_disable_interrupts();
```
So it's good to be careful with this factor.

## Built With

* IDE: Code Composer Studio v6.1.1.00022
* Compiler: TI v4.4.5

I do not know if previous versions have problems. Just in case you make sure nothing has changed much in your compiler.

## How to use

```c
unsigned long millis(void);
void timerbStart(unsigned int countVal);
unsigned long int timerbRead(void);
void timerbWait(void);
bool timerbFinished(void);
void timerbInit(void);
```
The name of the functions are very self explanatory, so there is not much to explain. Include this library in the code you want to use, and call the above functions just like any library.

```c
#include "timerB.h"
```

### How init

The value of TB0CCR0 I calculated based on the clock of 4MHz that feeds the timer and the pescaler that divides that clock by 4, making it only 1MHz. 

```c
TB0CCR0 = 0x07CE;
TB0CTL = TBSSEL__SMCLK + ID__2 + TBIE + TBCLR;

counter = 0;

TB0CTL |= MC__UP;
```
Want to learn how to calculate this value for any timer peripheral of any microcontroller? Read the book Making Embedded Systems from Elecia White.

### Suggested way of using

You can do things while counting time, and make sure each action lasts a fixed time:

```c
timerbStart(1000);
doThingLessThan1000MS();
timerbWait();
```

It is only allowed to have a time counting instance in the whole code, so it is discouraged to call this function in interrupts. Never do things that take too long in interruptions, and using this timer is bad practice.

This is basically the way I use it, but I believe that the timerbFinished and timerbRead functions enable other logic.

I add the millis function, which counts the number of milliseconds since the system start. Who uses microcontrollers already knows very well how to use, I do not need to say much xD.

I use a 64-bit variable, so millis counts 2^64 milliseconds :D.

## Contributing

Well, these routines are a good start when you're designing your own general purpose timer, hope it helps someone someday. I believe there are far better implementations than this, and if anyone suggests changes, I'd be grateful.

Please contact me.

## Author

* **Rafael Coelho Silva** - [rafaellcoellho](https://github.com/rafaellcoellho)

## License

This project is licensed under the Beerware licence. For more information:

https://en.wikipedia.org/wiki/Beerware
