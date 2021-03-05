//
//  SMEventLogout.h
//  MobileSDK
//
//  Created by Gilbert Schakal on 03/06/15.
//  Copyright (c) 2015 Selligent. All rights reserved.
//

#import "SMEventUser.h"

/*!
 * @class SMEventUserLogout
 * @inherits SMEventUser
 * @discussion user logout event class
 * #SMEventUserLogout:#
 */
@interface SMEventUserLogout : SMEventUser

/*!
 *  Create a UserLogout event object that will be sent to selligent platform when user logged out
 *
 *  @param mail the e-mail of the user
 *  @return a SMEventUserLogout object
 */
+ (instancetype _Nonnull)eventWithEmail:(NSString*_Null_unspecified)mail;

/*!
 *  Create a UserLogout event object that will be sent to selligent platform when user logged out
 *
 *  @param mail the e-mail of the user
 *  @param dict a Dictionary containing a string as data that must be stored and managed by platform
 *  If email is not provided you can use in the dictionary an alternate key/value field to search for the user
 *     example: [SMEventUserLogout eventWithEmail @"" Dictionary: @{@"userID": @"1234"}];
 *  @return a SMEventUserLogout object
 */
+ (instancetype _Nonnull)eventWithEmail:(NSString*_Null_unspecified)mail Dictionary:(NSDictionary<NSString*,NSString*>*_Nullable)dict;

/*!
 *  Create a UserLogout event object that will be sent to platform
 *  @param dict a Dictionary containing an alternate key/value field to search for the user
 *     example: [SMEventUserLogout eventWithDictionary:@{@"userID": @"1234"}];
 *  @return a SMEventUserLogout object
 */
+ (instancetype _Nonnull)eventWithDictionary:(NSDictionary* _Nullable)dict;

@end
