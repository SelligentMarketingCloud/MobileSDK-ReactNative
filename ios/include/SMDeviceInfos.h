//
//  SMDeviceInfos.h
//  MobileSDK
//
//  Created by Walter Tricknot on 07/02/2017.
//  Copyright © 2017 Selligent. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 * #SMDeviceInfos :#
 */
@interface SMDeviceInfos : NSObject

/*!
 *  Any External Id in your possession that you wish to transmit to the back-end
 *  @discussion NSString
 *  By default, it is an empty string
 */
@property (nonatomic) NSString *externalId;

/*!
 *  Create a generic deviceinfos object
 *  @return a SMDeviceInfos object
 */
+ (instancetype)defaultDeviceInfos;

/*!
 *  Create a deviceinfos object with an external id property already set with the value provided
 *  @param externalId a string containing the id you want to provide to the back-end
 *  @return a SMDeviceInfos object
 */
+ (instancetype)deviceInfosWithExternalId:(NSString*) externalId;

@end
