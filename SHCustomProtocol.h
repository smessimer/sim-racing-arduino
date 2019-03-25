#ifndef __SHCUSTOMPROTOCOL_H__
#define __SHCUSTOMPROTOCOL_H__

#include <Arduino.h>

class SHCustomProtocol {
private:

public:

	/*
	CUSTOM PROTOCOL CLASS
	SEE https://github.com/zegreatclan/SimHub/wiki/Custom-Arduino-hardware-support

	GENERAL RULES :
		- ALWAYS BACKUP THIS FILE, reinstalling/updating SimHub would overwrite it with the default version.
		- Read data AS FAST AS POSSIBLE in the read function
		- NEVER block the arduino (using delay for instance)
		- Make sure the data read in "read()" function READS ALL THE DATA from the serial port matching the custom protocol definition
		- Idle function is called hundreds of times per second, never use it for slow code, arduino performances would fall
		- If you use library suspending interrupts make sure to use it only in the "read" function when ALL data has been read from the serial port.
			It is the only interrupt safe place

	COMMON FUNCTIONS :
		- FlowSerialReadStringUntil('\n')
			Read the incoming data up to the end (\n) won't be included
		- FlowSerialReadStringUntil(';')
			Read the incoming data up to the separator (;) separator won't be included
		- FlowSerialDebugPrintLn(string)
			Send a debug message to simhub which will display in the log panel and log file (only use it when debugging, it would slow down arduino in run conditions)

	*/

  const int LOW_RPM_LED_PIN 0
  const int MID_RPM_LED_PIN 1
  const int HI_RPM_LED_PIN 2

	// Called when starting the arduino (setup method in main sketch)
	void setup() {
    pinMode(LOW_RPM_LED_PIN, OUTPUT);
    pinMode(MID_RPM_LED_PIN, OUTPUT);
    pinMode(HI_RPM_LED_PIN, OUTPUT);

    digitalWrite(LOW_RPM_LED_PIN, LOW);
    digitalWrite(LOW_RPM_LED_PIN, LOW);
    digitalWrite(LOW_RPM_LED_PIN, LOW);
	}

	// Called when new data is coming from computer
	void read() {
		// EXAMPLE 1 - read the whole message and sent it back to simhub as debug message
		// Protocol formula can be set in simhub to anything, it will just echo it
		// -------------------------------------------------------
//		String message = FlowSerialReadStringUntil('\n');
//		FlowSerialDebugPrintLn("Message received : " + message);

    // Let's assuming the message contains [RPM;MAX_RPM;GEAR];
    int rpm = FlowSerialReadStringUntil(';').toInt();
    int maxRpm = FlowSerialReadStringUntil(';')toInt();
    int gear = FlowSerialReadStringUntil('\n');

    FlowSerialDebugPrintLn("RPM: " + rpm + "; MAX_RPM: " + maxRpm + "; GEAR: " + gear);
	
		/*
		// -------------------------------------------------------
		// EXAMPLE 2 - reads speed and gear from the message
		// Protocol formula must be set in simhub to
		// format([DataCorePlugin.GameData.NewData.SpeedKmh],'0') + ';' + isnull([DataCorePlugin.GameData.NewData.Gear],'N')
		// -------------------------------------------------------

		int speed = FlowSerialReadStringUntil(';').toInt();
		String gear = FlowSerialReadStringUntil('\n');

		FlowSerialDebugPrintLn("Speed : " + String(speed));
		FlowSerialDebugPrintLn("Gear : " + gear);
		*/
	}

	// Called once per arduino loop, timing can't be predicted, 
	// but it's called betweene each command sent to the arduino
	void loop() {
	}

	// Called once between each byte read on arduino,
	// THIS IS A CRITICAL PATH :
	// AVOID ANY TIME CONSUMING ROUTINES !!!
	// PREFER READ OR LOOP METHOS AS MUCH AS POSSIBLE
	// AVOID ANY INTERRUPTS DISABLE (serial data would be lost!!!)
	void idle() {
	}
};

#endif
