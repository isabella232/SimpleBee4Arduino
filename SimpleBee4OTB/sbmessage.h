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
#ifndef __SBMESSAGE_H_
#define __SBMESSAGE_H_
#include <sbdevicecom.h>
#include <string.h>



// Size of module address
#define ADR_TYPE_SIZEOF 4

#define SBTResponseType(SBMsgReq) (SBMsgReq | 0x20)




/*
 * Calc checksum and store in dest.
 * dest size is 2
 */
extern void SBCheckSum(const char * start, int length, char * dest);

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
	SBMessageIdentificationReq(const char *moduleType):SBMessage(SBMsgReqType::identification) {
		memcpy(this->moduleType, moduleType, MODULE_TYPE_SIZEOF);
	};
	SBMessageIdentificationReq(char deviceType,const char *moduleType): SBMessageIdentificationReq(moduleType) {
		this->deviceType=deviceType;
	};

};


class SBMessageIdentificationResponse : public SBMessage {
public:
	char address[ADR_TYPE_SIZEOF];

	/**
	 * Constructors
	 */
	SBMessageIdentificationResponse(const char *moduleType):SBMessage(SBTResponseType(SBMsgReqType::identification)) {};

};



/**
 * Request Message for LED.
 * Message request :
 * Les actionneurs envoient toutes les 500 ms une requête, ils attendent pendant 100 ms une réponse.
 *
 */
class SBMessageRequestReq : public SBMessage {
public:

	char sbaddress[ADR_TYPE_SIZEOF];
	char value;
	const char batDelimit='B';
	char batterylevel; // Must be '0' empty to '9' full

	/**
	 * Contructors
	 */
	SBMessageRequestReq(const char *sbaddress):SBMessage(SBMsgReqType::request) {
		memcpy(this->sbaddress, sbaddress, ADR_TYPE_SIZEOF);
	};
	SBMessageRequestReq(const char *sbaddress, char value): SBMessageRequestReq(sbaddress) {
		this->value= '0' + (value % 2);
	};
	SBMessageRequestReq(const char *sbaddress, char value, char batterylevel): SBMessageRequestReq(sbaddress,value) {
		this->batterylevel= '0' + (batterylevel % 10);
	};

};

/**
 * Request Respnose Message for LED.
 */
class SBMessageRequestResponse : public SBMessage {
public:

	char sbaddress[ADR_TYPE_SIZEOF];
	char value;

	/**
	 * Contructors
	 */
	SBMessageRequestResponse(const char *sbaddress):SBMessage(SBTResponseType(SBMsgReqType::request)) {
		memcpy(this->sbaddress, sbaddress, ADR_TYPE_SIZEOF);
	};
	SBMessageRequestResponse(const char *sbaddress, char value): SBMessageRequestResponse(sbaddress) {
		this->value= '0' + (value % 2);
	};

};
#endif // __SBMESSAGE_H_
