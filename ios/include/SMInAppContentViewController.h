//
//  SMIACSimpleViewController.h
//  MobileSDK
//
//  Created by Gilbert Schakal on 24/02/16.
//  Copyright © 2016 Selligent. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "SMInAppContentType.h"
#import "SMInAppContentStyleOptions.h"

@class SMInAppContentMessage;


/*!
 *  parent class for SMInAppContentURLViewController, SMInAppContentHTMLViewController, SMInAppContentImageViewController
 *  #SMInAppContentViewController :#
 */
@interface SMInAppContentViewController : UIViewController

/*!
 *  NSString containing the category of the SMInAppContentViewController
 */
@property (nonatomic,strong) NSString* category;

/*!
 * bool set with true when the SMInAppContentViewController is empty
 */
@property (nonatomic) bool isEmpty;


@end