//
//  SMManager+SMLog.h
//  MobileSDK
//
//  Created by Samy Ziat on 29/09/15.
//  Copyright (c) 2015 Selligent. All rights reserved.
//

#import "SMManager.h"

#import "SMLog.h"


/**
 *  This category will help you debug the library.
 *  Please check SMLogLevel for all available possibilities.
 *
 *  Should you want to get back to us, please set logLevel to kSMLogLevel_All and provide with console logs.
 *
 *  #SMManager+Log :#
 */
@interface SMManager (Log)



/*!
 *  Set the log level of the library console
 *  @discussion This is an optional setting that may help you debug the library calls.
 *  This call can be done at any time (before or after starting the library).
 *  However, in order to avoid missing any error log, we recommand setting this value before starting the library.
 *  @param logLevel SMLogLevel enumeration type. Default = kSMLoLevel_None
 *  @warning It is developer's responsability to enable log-level in Debug or release mode. 
 *  No distinction are being aplied by the library.
 *  For obvious performance reason, it is always recommended to turn log off in release mode.
 */
- (void)applyLogLevel:(SMLogLevel)logLevel;





@end
