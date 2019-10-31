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
@property (nonatomic) NSString     * idMessage;

/*!
 *  NSDate instance providing the creation date of the message
 */
@property (nonatomic) NSDate       * dateCreation;


@end
