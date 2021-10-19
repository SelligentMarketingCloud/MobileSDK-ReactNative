//
//  SMManager+StyleOptions.h
//  MobileSDK
//
//  Created by Gilbert Schakal on 30/04/16.
//  Copyright © 2016 Selligent. All rights reserved.
//

#import "SMManager.h"

@class SMInAppContentStyleOptions;

/*!
 *  Allows you to customise the appearance of all the In App Content containers
 *
 *  ##Implementation
 *      * First create a SMInAppContentStyleOptions object instance
 *      * load it with loadStyleOptions:
 */

@interface SMManager (StyleOptions)

/*!
 * This will allow you to load your custom SMInAppContentStyleOptions object
 *
 * @param options a SMInAppContentStyleOptions object
 * @see SMInAppContentStyleOptions
 */
- (void) loadStyleOptions:(SMInAppContentStyleOptions*_Nullable)options;

/*!
 * Reset style options to default one
 */
- (void) resetStyleOptions;

@end
