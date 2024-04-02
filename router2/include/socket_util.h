/*******************************************************************************
 * Copyright 2005  Hon Hai Precision Ind. Co. Ltd.
 * All Rights Reserved.
 * No portions of this material shall be reproduced in any form without the
 * written permission of Hon Hai Precision Ind. Co. Ltd.
 *
 * All information contained in this document is Hon Hai Precision Ind.
 * Co. Ltd. company private, proprietary, and trade secret property and
 * are protected by international intellectual property laws and treaties.
 *
 ******************************************************************************/

#ifndef _SOCKET_UTIL_H
#define _SOCKET_UTIL_H

extern int connectWithTimeout(int sock, struct sockaddr *adrs, int adrsLen, struct timeval *timeVal);

#endif
