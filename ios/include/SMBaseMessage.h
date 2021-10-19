//
//  SMBaseMessage.h
//  MobileSDK
//
//  Created by Gilbert Schakal on 16/03/16.
//  Copyright (c) 2016 Selligent. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 *  @discussion This is the Base class for message (push notif, in app message and in app content)
 */
@interface SMBaseMessage : NSObject

/*!
 *  NSString instance providing the id of the message
 */
@property (readonly, nonatomic) NSString *_Nullable idMessage;

/*!
 *  NSDate instance providing the creation date of the message
 *
 *  @warning Deprecated - use receptionDate  instead
 */
@property (readonly, nonatomic) NSDate *_Nullable dateCreation __deprecated __deprecated_msg("Use receptionDate instead");

/*!
 *  NSDate instance providing the reception date on sdk side of the message
*/
@property (readonly, nonatomic) NSDate *_Nullable receptionDate;

/*!
 *  NSDate instance providing the expiration date of the message
 */
@property (readonly, nonatomic) NSDate *_Nullable expirationDate;

/*!
 *  NSDate instance providing the creation date of the message
 */
@property (readonly, nonatomic) NSDate *_Nullable creationDate;

/*!
 *  bool instance infiorming if the message has already been displayed and viewed by user
 */
@property (readonly, nonatomic) bool isViewed;

@end
