//
//  SMInAppContentHTMLViewController.h
//  MobileSDK
//
//  Created by Gilbert Schakal on 15/04/16.
//  Copyright © 2016 Selligent. All rights reserved.
//

#import "SMInAppContentViewController.h"
#import "SMInAppContentStyleOptions.h"

/*!
 *  a view controller for HTML In App Content
 *  #SMInAppContentHTMLViewController :#
 */
@interface SMInAppContentHTMLViewController : SMInAppContentViewController


/*!
 * This will provide you a custom viewcontroller with all HTML in app content for a specific category
 * @discussion The viewcontroller will take all available space in screen and will contain a close button if it is presented as it is. Otherwise the app will have to define a UIContainerView which will contain the view controller
 * @param category a NSString of the desired category of In App Content
 * @return a SMInAppContentHTMLViewController
 */
+ (instancetype) viewControllerForCategory:(NSString*)category ;

/*!
 * This will provide you a custom viewcontroller with all HTML in app content for a specific category
 * @discussion The viewcontroller will take all available space in screen and will contain a close button if it is presented as it is. Otherwise the app will have to define a UIContainerView which will contain the view controller
 * @param category a NSString of the desired category of In App Content
 * @param options a SMInAppContentStyleOptions object allowing you to customise the in app content
 * @return a SMInAppContentHTMLViewController
 */
+ (instancetype) viewControllerForCategory:(NSString*)category AndOptions:(SMInAppContentStyleOptions*)options  ;

/*!
 * This will provide you a custom viewcontroller with HTML in app content for a specific category
 * @discussion The viewcontroller will take all available space in screen and will contain a close button if it is presented as it is. Otherwise the app will have to provide a UIContainerView which will contain the view controller
 * @param category a NSString of the desired category of In App Content
 * @param numberofboxes an int corresponding to the maximum numbers of html boxes that the view controller must contain
 * @return a SMInAppContentHTMLViewController
 */
+ (instancetype) viewControllerForCategory:(NSString*)category InNumberOfBoxes:(int) numberofboxes ;


/*!
 * This will provide you a custom viewcontroller with HTML in app content for a specific category
 * @discussion The viewcontroller will take all available space in screen and will contain a close button if it is presented as it is. Otherwise the app will have to provide a UIContainerView which will contain the view controller
 * @param category a NSString of the desired category of In App Content
 * @param numberofboxes an int corresponding to the maximum numbers of html boxes that the view controller must contain
 * @param options a SMInAppContentStyleOptions object allowing you to customise the in app content
 * @return a SMInAppContentHTMLViewController
 */
+ (instancetype) viewControllerForCategory:(NSString*)category InNumberOfBoxes:(int) numberofboxes AndOptions:(SMInAppContentStyleOptions*)options ;


@end
