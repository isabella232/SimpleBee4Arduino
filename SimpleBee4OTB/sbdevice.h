/*
 * Copyright (C) 2015 Orange
 *
 * This software is distributed under the terms and conditions of the 'Apache-2.0'
 * license which can be found in the file 'LICENSE.txt' in this package distribution
 * or at 'http://www.apache.org/licenses/LICENSE-2.0'.
 */

/* Device for SimpleBee Protocol
 *
 * Version:     0.1.0
 * Created:     2015-02-24 by Franck Roudet
 */
#ifndef __SBDEVICE_H_
#define __SBDEVICE_H_
#include <sbdevicecom.h>
#include <SBMessenger.h>

/**
 * Base class for Simple Bee Device
 */
class SBDevice {
public:
	char sbaddress[SBAddress_size];
	char deviceType;
	const char *moduleType;
	unsigned long heartbeat_time;   // next time to emit heartbeat (ms)
	unsigned long heartbeat_period; // heart_beat period in milliseconds
	unsigned char batteryLevel=9;   // Must be 0 empty to 9 full

	SBMessenger * sbmessenger;    // Message manager

	/**
	 * State machine type
	 */
	struct state {
		enum state_enum : char {
			idle=' ',       // Inactive device
			started='S',    // Need an address
			ukn='U',        // Address in progress
			identified='I', // address OK
			newvalue='V',
			valueack='v',
		};
	};


	char currentState = SBDevice::state::idle;

	/**
	 * Contructors
	 * Default module type is LED 0001
	 */
	SBDevice(const char * moduleType="001") { this->moduleType = moduleType; currentState = SBDevice::state::idle;}

	/**
	 * Address attribution
	 */
	void setAddr(const char * newAddress);

	/**
	 * Start device
	 */
	virtual void start(void) {
		this->currentState = SBDevice::state::started;
	}

	/**
	 * Send Heart Beat message
	 */
	virtual void sendHeartBeat(void)=0;

	/**
	 * Incoming message for the device
	 */
	virtual void newMessage(char *message)=0;
};


/**
 * Base class for actuator
 */
class SBActuator : public SBDevice {
public:
	/**
	 * Contructors
	 */
	SBActuator(const char * moduleType=0L, unsigned long hearbeat_period_ms=500) : SBDevice(moduleType) {
		deviceType=SBDeviceType::actuator;
		heartbeat_period=hearbeat_period_ms;
	}

	/**
	 * Send Heart Beat message
	 */
	//virtual void sendHeartBeat(void);

};


/***
 * Actuators
 */

/**
 * SimpleBee Led
 */
class SBLed: public SBActuator {
public:
	char value; // 0 or 1

	/**
	 * Contructors
	 */
	SBLed(const char * moduleType="001", unsigned long hearbeat_period_ms=500) : SBActuator(moduleType, hearbeat_period_ms) {};

	/**
	 * Send Heart Beat message
	 */
	virtual void sendHeartBeat(void);

	/**
	 * Incoming message for the device
	 */
	virtual void newMessage(char *message);
};



/**
 * Base class for Sensor
 */
class SBSensor : public SBDevice {
public:
	/**
	 * Contructors
	 */
	SBSensor(const char * moduleType=0L, unsigned long hearbeat_period_ms=60000 /* 1 min */) : SBDevice(moduleType) {
		deviceType=SBDeviceType::sensor;
		heartbeat_period=hearbeat_period_ms;
	}

	/**
	 * Send Heart Beat message
	 */
	//virtual void sendHeartBeat(void);

};


/**
 * SimpleBee Switch
 * 2 state device = 0 and 1
 */
class SBSwitch: public SBSensor {
public:
	char value; // 0 or 1

	/**
	 * Contructors
	 */
	SBSwitch(const char * moduleType="001", unsigned long hearbeat_period_ms=60000 /* 1 min */) : SBSensor(moduleType, hearbeat_period_ms) {};

	/**
	 * Send Heart Beat message
	 */
	virtual void sendHeartBeat(void);

	/**
	 * Incoming message for the device
	 */
	virtual void newMessage(char *message);
};

#endif // __SBDEVICE_H_
