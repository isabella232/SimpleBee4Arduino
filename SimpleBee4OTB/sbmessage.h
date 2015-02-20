/*
 * Copyright (C) 2015 Orange
 *
 * This software is distributed under the terms and conditions of the 'Apache-2.0'
 * license which can be found in the file 'LICENSE.txt' in this package distribution
 * or at 'http://www.apache.org/licenses/LICENSE-2.0'.
 */

/* Message Type for SimpleBee Protocol
 *
 * Version:     0.1.0
 * Created:     2015-02-18 by Franck Roudet
 */
#ifndef __SBMESSAGE_H__
#define __SBMESSAGE_H__
#include <string.h>



// Size of module address
#define ADR_TYPE_SIZEOF 4

#define SBTResponseType(SBMsgReq) (SBMsgReq | 0x20)




/*
 * Calc checksum and store in dest.
 * dest size is 2
 */
extern void SBCheckSum(char * start, int length, char * dest);

/**
 * Message Request type.
 * Sensor/actuator/object to Open The Box
 */
struct SBMsgReqType {
	enum SBMsgReqType_enum : char {
		identification='I',
		watchdog='W',
		data='D',
		request='R',
	};
};

/**
 * Device type.
 * Sensor/actuator/object to Open The Box
 */
struct SBDeviceType {
	enum SBDeviceType_enum :char {
		actuator='A',
		sensor='C'
	};
};

const char SBEndOfMessage='\r';


/**
 * Base class for requests
 */
class SBMessage {
public:
	const char type;

	SBMessage(const char type):type(type) {}
};

/**
 * Request Message for identification.
 * Les modules neuf ont une adresse ‘0000’ et restent muets  à la mise sous tension.
 * Lorsqu’on appuie sur le petit bouton en bas à gauche, le module envoie un message de demande d’adresse une seule fois à chaque appuie. Si pas de réponse, il se rendort.
 * Si la réponse est correcte, il fonctionne normalement et commence à envoyer des données. L’adresse est conservée dans le module et celui-ci fonctionnera normalement à une prochaine mise sous tension.
 *
 */
class SBMessageIdentificationReq : public SBMessage {
public:
	static const char MODULE_TYPE_SIZEOF=3;

	char deviceType =SBDeviceType::sensor;
	char moduleType[MODULE_TYPE_SIZEOF];


	/**
	 * Contructors
	 */
	SBMessageIdentificationReq(char *moduleType):SBMessage(SBMsgReqType::identification) {
		memcpy(this->moduleType, moduleType, MODULE_TYPE_SIZEOF);
	};
	SBMessageIdentificationReq(char deviceType,char *moduleType): SBMessageIdentificationReq(moduleType) {
		this->deviceType=deviceType;
	};

};


class SBMessageIdentificationResponse : public SBMessage {
public:
	char address[ADR_TYPE_SIZEOF];

	/**
	 * Contructors
	 */
	SBMessageIdentificationResponse(char *moduleType):SBMessage(SBTResponseType(SBMsgReqType::identification)) {};

};


#endif // __SBMESSAGE_H__
