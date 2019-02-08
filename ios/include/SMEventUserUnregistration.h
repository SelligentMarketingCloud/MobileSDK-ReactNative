//
//  SMEventUnregistration.h
//  MobileSDK
//
//  Created by Gilbert Schakal on 03/06/15.
//  Copyright (c) 2015 Selligent. All rights reserved.
//

#import "SMEventUser.h"

/*!
 * @class SMEventUserUnregistration
 * @inherits SMEventUser
 * @discussion user unregistration event class
 * #SMEventUserUnregistration:#
 */
@interface SMEventUserUnregistration : SMEventUser

/*!
 *  Create a UserUnregistration event object that will be sent to selligent platform when user unregistered
 *
 *  @param mail the e-mail of the user
 *  @return a SMEventUserUnregistration object
 */
+ (instancetype)eventWithEmail:(NSString*)mail;

/*!
 *  Create a UserUnregistration event object that will be sent to selligent platform when user unregistered
 *
 *  @param mail the e-mail of the user
 *  @param dict a Dictionary containing a String that must be stored and managed by platform
 *  @return a SMEventUserUnregistration object
 */
+ (instancetype)eventWithEmail:(NSString*)mail Dictionary:(NSDictionary<NSString*,NSString*>*)dict;


@end
