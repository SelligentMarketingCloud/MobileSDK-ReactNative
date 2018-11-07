//
//  SMInAppContentImageViewController.h
//  MobileSDK
//
//  Created by Gilbert Schakal on 05/04/16.
//  Copyright © 2016 Selligent. All rights reserved.
//

#import "SMInAppContentViewController.h"


/*!
 *  a view controller for Image In App Content
 *  #SMInAppContentImageViewController :#
 */
@interface SMInAppContentImageViewController : SMInAppContentViewController

/*!
 * This will provide you a custom viewcontroller with one image view loaded with the url provided by an in app content for a specific category of image type
 * @discussion The viewcontroller will take all available space in screen and will contain a close button if it is presented as it is. Otherwise the app will have to provide a UIContainerView which will contain the view controller
 * @param category a NSString of the desired category of In App Content
 * @return a SMInAppContentImageViewController
 */
+ (instancetype) viewControllerForCategory:(NSString*)category;

/*!
 * This will provide you a custom viewcontroller with one web view loaded with the url provided by an in app content for a specific category of an Image type
 * @discussion The viewcontroller will take all available space in screen and will contain a close button if it is presented as it is. Otherwise the app will have to define a UIContainerView which will contain the view controller
 * @param category a NSString of the desired category of In App Content
 * @param options a SMInAppContentStyleOptions object allowing you to customise the in app content
 * @return a SMInAppContentImageViewController
 */
+ (instancetype) viewControllerForCategory:(NSString*)category AndOptions:(SMInAppContentStyleOptions*)options  ;


@end
