//
//  SMLinks.h
//  MobileSDK
//
//  Created by Gilbert Schakal on 13/05/16.
//  Copyright © 2016 Selligent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SMNotificationButtonType.h"

/**
 *
 */
@interface SMLink : NSObject

/*!
 *  NSString instance providing the id of the button
 */
@property (readonly, nonatomic, strong) NSString *_Nullable idButtonData;

/*!
 *  NSString instance providing the label of the button
 */
@property (readonly, nonatomic, strong) NSString *_Nullable label;

/*!
 *  NSString instance providing the value of the button
 */
@property (readonly, nonatomic, strong) NSString *_Nullable value;

/*!
 *  The type (SMNotificationButtonType) of action that the button will execute.
 *  
 *  @see SMNotificationButtonType 
 */
@property (readonly, nonatomic) SMNotificationButtonType type;

@end
