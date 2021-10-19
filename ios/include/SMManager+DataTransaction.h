//
//  SMManager+DataTransaction.h
//  MobileSDK
//
//  Created by Gilbert Schakal on 08/02/2017.
//  Copyright © 2017 Selligent. All rights reserved.
//

#import "SMManager.h"
#import "SMDeviceInfos.h"

/**
 *  This category will help you to retrieve or send specific information to the selligent platform.
 */
@interface SMManager (DataTransaction)

/**
 *  @discussion In order to send device informations to the back-end you can use
 *  @warning Deprecated method
 */
- (void) sendDeviceInfo __deprecated __deprecated_msg("Use sendDeviceInfo: instead.");

/*!
 *  This method allow you to send an event with pre-defined devices informations to the back-end
 *
 *  @discussion The informations to be sent will be set in a SMDeviceInfos object. Each property of the created object will be a data that will be provided to the back-end. For additional informations you can refer to SMDevicesInfos.
 *  This call can be done at any time  after starting the library and if the properties of SMDeviceInfos object has not changed from a previous call, the event will not be sent to avoid platform unnecessarily overload.
 *  @param deviceInfos SMDeviceInfos object
 *  @see SMDeviceInfos
 */
- (void) sendDeviceInfo:(SMDeviceInfos*_Nullable)deviceInfos;

@end
