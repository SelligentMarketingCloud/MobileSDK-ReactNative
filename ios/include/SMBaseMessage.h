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
 *  #SMBaseMessage :#
 */
@interface SMBaseMessage : NSObject

/*!
 *  NSString instance providing the id of the message
 */
@property (nonatomic) NSString *idMessage;

/*!
 *  NSDate instance providing the creation date of the message
 *  @deprecated Deprecated use receptionDate  instead
 */
@property (nonatomic) NSDate *dateCreation __deprecated __deprecated_msg("Use receptionDate instead");

/*!
 *  NSDate instance providing the reception date on sdk side of the message
*/
@property (nonatomic) NSDate *receptionDate;

/*!
 *  NSDate instance providing the expiration date of the message
 */
@property (nonatomic) NSDate   *expirationDate;

/*!
 *  NSDate instance providing the creation date of the message
 */
@property (nonatomic) NSDate   *creationDate;

/*!
 *  bool instance infiorming if the message has already been displayed and viewed by user
 */
@property (nonatomic) bool    isViewed;

/*!
 *  bool instance infiorming if the message has  been deleted
 */
@property (nonatomic) bool    isDeleted;
@end
