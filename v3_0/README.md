BlackLib library is written for controlling Beaglebone Black's feature. It takes power from C++ language. It is created for reading analog input, generating pwm signal, using gpio pins, and communicating with other devices over uart, spi and i2c. In addition to them, it includes debugging feature. So you can check errors after call any function in the library. It also takes parallel programming, mutex usability, realization of directory operation and realization of time operation ability with the last update(BlackLiv v3.0).


--------------------------------------------------------------------------------
## Debugging

It always tracks member functions errors and records these errors to data structures. All end nodes which interact with end users, have overloaded fail() functions. So you can check all errors or specific error whichever you want.


--------------------------------------------------------------------------------
## Class Hierarchy

### Library Core

BlackLib includes BlackCore class for doing core process. End users can't access to it. Because it is abstract class and all member functions, except constructor and destructor, are private or protected.

### Sub Level Cores

BlackLib includes sub level cores for GPIO, ADC and PWM features. Preparing stages are realized in here, at sub level cores. Therefore, if you don't like end nodes or you don't want to use these, you can derive your own class(es), from these sub level cores. But end nodes designed for taking care of your all need.

### End Node Classes

End node classes are designed for interacting with end user. You can read, set or control Beaglebone Black's ADC, GPIO or PWM features or you can communicate with other devices with using UART, SPI or I2C protocol, from these classes. Also you can develop professional applications with using parallel programming, mutexes, directory operations and time operations. These classes include primary functions like read or set properties of Beaglebone Black's features and include additional functions like ADC parser, gpio pin toggle etc. to make easier your life.


--------------------------------------------------------------------------------
## Definitions

BlackLib includes enum type definitions for your and Beaglebone Black's safety. GPIO, ADC, PWM, UART, SPI, I2C names; PWM, GPIO values; GPIO directions and a lot more features defined with enums. It means you can't call some member functions without use this enums. These enums avoid user errors like write 345 to gpio export file instead of 34.


--------------------------------------------------------------------------------
## Contact

For any comment or suggestion please contact the creator of BlackLib Library at contact[at]blacklib.yigityuce.com


--------------------------------------------------------------------------------
		http://blacklib.yigityuce.com	
