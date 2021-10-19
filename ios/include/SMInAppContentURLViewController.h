//
//  SMInAppContentURLViewController.h
//  MobileSDK
//
//  Created by Gilbert Schakal on 08/04/16.
//  Copyright © 2016 Selligent. All rights reserved.
//

#import "SMInAppContentViewController.h"

/*!
 *  A view controller for URL In App Content
 */
@interface SMInAppContentURLViewController : SMInAppContentViewController

/*!
 * This will provide you a custom viewcontroller with one web view loaded with the url provided by an in app content for a specific category of an URL type
 *
 * @discussion The viewcontroller will take all available space in screen and will contain a close button if it is presented as it is. Otherwise the app will have to provide a UIContainerView which will contain the view controller
 * @param category An NSString of the desired category of In App Content
 * @return An SMInAppContentURLViewController
 */
+ (instancetype _Nonnull) viewControllerForCategory:(NSString*_Nullable)category;

/*!
 * This will provide you a custom viewcontroller with one web view loaded with the url provided by an in app content for a specific category of an URL type
 *
 * @discussion The viewcontroller will take all available space in screen and will contain a close button if it is presented as it is. Otherwise the app will have to define a UIContainerView which will contain the view controller
 * @param category An NSString of the desired category of In App Content
 * @param options An SMInAppContentStyleOptions object allowing you to customise the in app content
 * @return a SMInAppContentURLViewController
 * @see SMInAppContentStyleOptions
 */
+ (instancetype _Nonnull) viewControllerForCategory:(NSString*_Nullable)category AndOptions:(SMInAppContentStyleOptions*_Nullable)options;

@end
