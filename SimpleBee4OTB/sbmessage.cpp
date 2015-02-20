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

#include "sbmessage.h"

/*
 * Calc checksum and store in dest.
 * dest size is 2
 */
void SBCheckSum(char * start, int length, char * dest) {
	unsigned char csum=0;
	char * stop = start+ length;
	while (start < stop) {
		csum +=(unsigned char) *start++;
	}
	dest[0] = ((csum & 0xF0) >> 4) + '0';
	dest[1] = (csum & 0x0F)        + '0';
}


/**
 * SBMessageIdentificationReq methods
 */

//unsigned short SBMessageIdentificationReq::getLength(void) {
//	return sizeof(SBMessageIdentificationReq);
//}
