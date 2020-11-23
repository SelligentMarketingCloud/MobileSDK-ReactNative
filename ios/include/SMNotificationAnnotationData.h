//
//  SMNotificationAnnotationData.h
//  MobileSDK
//
//  Created by Samy Ziat on 19/08/15.
//  Copyright (c) 2015 Selligent. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 *
 *  #SMNotificationAnnotationData :#
 */
@interface SMNotificationAnnotationData : NSObject

/*!
 *  NSString instance providing the title of the annotation
 */
@property (nonatomic, strong) NSString *titleAnnotation;

/*!
 *  NSString instance providing the description of the annotation
 */
@property (nonatomic, strong) NSString *descriptionAnnotation;

/*!
 *  NSString instance providing the latitude of the annotation
 */
@property (nonatomic) float latitude;

/*!
 *  NSString instance providing the longitude of the message
 */
@property (nonatomic) float longitude;

@end
