//
//  SMEventRegistration.h
//  MobileSDK
//
//  Created by Gilbert Schakal on 03/06/15.
//  Copyright (c) 2015 Selligent. All rights reserved.
//

#import "SMEventUser.h"

/*!
 * @class SMEventUserRegistration
 * @inherits SMEventUser
 * @discussion user registration event class
 * #SMEventUserRegistration:#
 */
@interface SMEventUserRegistration : SMEventUser


/*!
 *  Create a UserRegistration event object that will be sent to selligent platform when user registered
 *
 *  @param mail the e-mail of the user
 *  @return a SMEventUserRegistration object
 */
+ (instancetype)eventWithEmail:(NSString*)mail;

/*!
 *  Create a UserRegistration event object that will be sent to selligent platform when user registered
 *
 *  @param mail the e-mail of the user
 *  @param dict a Dictionary containing a string a string as data that must be stored and managed by platform
 *  If email is not provided you can use in the dictionary an alternate key/value field to search for the user
 *     example: [SMEventUserRegistration eventWithEmail @"" Dictionary: @{@"userID": @"1234"}];
 *  @return a SMEventUserRegistration object
 */
+ (instancetype)eventWithEmail:(NSString*)mail Dictionary:(NSDictionary<NSString*,NSString*>*)dict;

@end
