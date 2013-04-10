#!/usr/bin/env node

/* blinkin.js
**
** Copyright (c) 2012 Meadhbh S. Hamrick, All Rights Reserved
**
** @License( https://raw.github.com/OhMeadhbh/node-wiringpi/master/LICENSE )
**
** This is a simple example of the node-wiringpi package. It assumes you have
** LEDs attached to pins 0, 1 & 2. Check out this URL for a good guide to 
** hooking up LEDs to a Raspberry Pi:
**
**   https://projects.drogon.net/raspberry-pi/gpio-examples/tux-crossing/gpio-examples-1-a-single-led/
**
*/

var wiringpi = require( './node-wiringpi' );

if(wiringpi.wiringPiSetup() !== -1) {

	wiringpi.pinMode( 8, wiringpi.PIN_MODE.OUTPUT );

	var HIGH = wiringpi.WRITE.HIGH;
	var LOW  = wiringpi.WRITE.LOW;

	var current = HIGH;

	setInterval( function () {
    		current = current == HIGH ? LOW : HIGH;
    		wiringpi.digitalWrite( 8, current);    
	}, 125);

}

