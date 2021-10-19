//
//  SMInAppContent.h
//  MobileSDK
//
//  Created by Gilbert Schakal on 15/03/16.
//  Copyright © 2016 Selligent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SMBaseMessage.h"
#import "SMInAppContentType.h"
#import "SMDisplayMode.h"

@interface SMInAppContentMessage : SMBaseMessage

/*!
 *  NSString instance providing the title of the message
 */
@property (readonly, nonatomic) NSString *_Nullable title;

/*!
 *  NSString instance providing the content of the message
 */
@property (readonly, nonatomic) NSString *_Nullable body;

/*!
 *  NSString instance providing the category of the message
 */
@property (readonly, nonatomic) NSString *_Nullable category;

/*!
 *  SMInAppContentType instance providing the in app content type of the message
 *  @see SMInAppContentType
 */
@property (readonly, nonatomic) SMInAppContentType iacType;

/*!
 *  NSDate instance providing the expiration date of the message
 *  
 *  @warning Deprecated - use expirationDate on SMBaseMessage instead
 */
@property (readonly, nonatomic) NSDate *_Nullable contentExpiration __deprecated __deprecated_msg("Use expirationDate instead.");

/*!
 *  NSDate instance providing the creation date of the message
 *
 *  @warning Deprecated - use creationDate on SMBaseMessage instead
 */
@property (readonly, nonatomic) NSDate *_Nullable contentCreation __deprecated __deprecated_msg("Use creationDate instead.");

/*!
 *  NSArray of SMLink objects
 */
@property (readonly, nonatomic) NSArray *_Nullable arrayIACLinks;

@end
