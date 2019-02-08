//
//  SMEventLogin.h
//  MobileSDK
//
//  Created by Gilbert Schakal on 03/06/15.
//  Copyright (c) 2015 Selligent. All rights reserved.
//

#import "SMEventUser.h"

/*!
 * @class SMEventUserLogin
 * @inherits SMEventUser
 * @discussion user login event class
 * #SMEventUserLogin:#
 */
@interface SMEventUserLogin : SMEventUser


/*!
 *  Create a UserLogin event object that will be sent to selligent platform when user logged in
 *
 *  @param mail the e-mail of the user
 *  @return a SMEventUserLogin object
 */
+ (instancetype)eventWithEmail:(NSString*)mail;

/*!
 *  Create a UserLogin event object that will be sent to selligent platform when user logged in
 *
 *  @param mail the e-mail of the user
 *  @param dict a Dictionary containing a string as data that must be stored and managed by platform
 *  If email is not provided you can use in the dictionary an alternate key/value field to search for the user
 *     example: [SMEventUserLogin eventWithEmail @"" Dictionary: @{@"userID": @"1234"}];
 *  @return a SMEventUserLogin object
 */
+ (instancetype)eventWithEmail:(NSString*)mail Dictionary:(NSDictionary<NSString*,NSString*>*)dict;


@end
