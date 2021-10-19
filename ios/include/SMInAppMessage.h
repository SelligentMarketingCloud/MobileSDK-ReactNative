//
//  SMInAppMessage.h
//  MobileSDK
//
//  Created by Gilbert Schakal on 19/05/15.
//  Copyright (c) 2015 Selligent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SMBaseMessage.h"
#import "SMInAppMessageType.h"

@interface SMInAppMessage : SMBaseMessage

/*!
 *  NSString instance providing the title of the inapp-notification
 */
@property (readonly, nonatomic) NSString *_Nullable title;

/*!
 *  NSString instance providing the content of the inapp-notification
 */
@property (readonly, nonatomic) NSString *_Nullable body;

/*!
 *  NSArray of SMNotificationAnnotationData  objects for map inapp-notification
 */
@property (readonly, nonatomic) NSArray *_Nullable arrayMapAnnotations;

/*!
 *  NSArray of SMLink objects from the inapp-notification
 */
@property (readonly, nonatomic) NSArray *_Nullable arrayIAMLinks;

/*!
 *  SMInAppMessageType instance providing the in inapp-notification type
 *  @see SMInAppMessageType
 */
@property (readonly, nonatomic) SMInAppMessageType iamType;

/*!
 *  NSString instance providing the title of the remote-notification
 */
@property (readonly, nonatomic) NSString *_Nullable apsTitle;

/*!
 *  NSString instance providing the body of the remote-notification
 */
@property (readonly, nonatomic) NSString *_Nullable apsBody;

@end
