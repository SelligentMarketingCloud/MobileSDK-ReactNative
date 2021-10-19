//
//  SMDeviceInfos.h
//  MobileSDK
//
//  Created by Walter Tricknot on 07/02/2017.
//  Copyright © 2017 Selligent. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 */
@interface SMDeviceInfos : NSObject

/*!
 *  Any External Id in your possession that you wish to transmit to the back-end
 *
 *  @discussion NSString representing your external, custom identifier.
 *  By default, it is an empty string
 */
@property (nonatomic) NSString* _Nullable externalId;

/*!
 *  Create a generic deviceinfos object
 *
 *  @return An SMDeviceInfos object
 */
+ (instancetype _Nullable ) defaultDeviceInfos;

/*!
 *  Create a deviceinfos object with an external id property already set with the value provided
 *
 *  @param externalId An string containing the id you want to provide to the back-end
 *  @return An SMDeviceInfos object
 */
+ (instancetype _Nullable ) deviceInfosWithExternalId:(NSString*_Nullable) externalId;

@end
