//
//  SellNotificationMessage.h
//  MobileSDK
//
//  Created by Gilbert Schakal on 19/05/15.
//  Copyright (c) 2015 Selligent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SMBaseMessage.h"
#import "SMInAppMessageType.h"

/*!
 *
 *  #SMInAppMessage :#
 */
@interface SMInAppMessage : SMBaseMessage

/*!
 *  NSString instance providing the title of the message
 */
@property (nonatomic) NSString     *title;
/*!
 *  NSString instance providing the content of the message
 */
@property (nonatomic) NSString     *body;

/*!
 *  NSArray of SMNotificationAnnotationData  objects for map In App message
 */
@property (nonatomic) NSArray *arrayMapAnnotations;

/*!
 *  NSArray of SMLink objects
 */
@property (nonatomic) NSArray *arrayIAMLinks;

/*!
 *  SMInAppMessageType instance providing the in app message  type
 */
@property (nonatomic) SMInAppMessageType  iamType;

@end
