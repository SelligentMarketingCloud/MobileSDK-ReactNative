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
 *  #SMLink :#
 */
@interface SMLink : NSObject

/*!
 *  NSString instance providing the id of the button
 */
@property (nonatomic, strong) NSString     * idButtonData;

/*!
 *  NSString instance providing the label of the button
 */
@property (nonatomic, strong) NSString     * label;

/*!
 *  NSString instance providing the value of the button
 */
@property (nonatomic, strong) NSString     * value;

/*!
 *  The type (SMNotificationButtonType) of action that the button will execute.
 *  @see SMNotificationButtonType for more information about each type
 */
@property (nonatomic) SMNotificationButtonType type;


@end
