//
//  SMManager+InAppContent.h
//  MobileSDK
//
//  Created by Gilbert Schakal on 11/03/16.
//  Copyright © 2016 Selligent. All rights reserved.
//

#import "SMManager.h"
#import "SMInAppContentType.h"
#import "SMInAppContentMessage.h"
#import "SMLink.h"

@class SMInAppContentViewController;


/*!
 *  #Introduction :#
 *  In-Application-Content (IAC) is an optional service which will retrieve messages from the back-end each time the application enters foregrounds at specific frequencies and if connection is available.
 *
 *  Once new messages were retrieved, the library notifies the application about it.
 *
 *  Each IAC is is from a specific type [SMInAppContentType] and is also linked to a category defined by yourself
 *
 *  #Implementation :#
 *  In a nutshell, activate the IAC-service is a one step process:
 *
 *  *  Create an SMManagerSettingIAC instance and inject it in SMManagerSetting with [SMManagerSetting configureInAppContentServiceWithSetting:]
 *
 *  In order to be notified about new IAC, the application must register to correct notification *kSMNotification_Event_DidReceiveInAppContent*
 *  (Please read SMNSNotification for additional information).
 *  This notification will provide you with the number of IAC's by category.
 *  Please be aware that it’s the unique application’s chance to capture and store that information.
 *
 *  #Displaying IAC :#
 *
 *  * With the SDK view controllers:
 *
 *  Each IAC is from a specific type for a specific category.
 *
 *  Selligent SDK provide a specific view controller for each type of in app content
 *
 *   * SMInAppContentHTMLViewController for IAC of type kSMInAppContentType_HTML
 *   * SMInAppContentURLViewController for IAC of type kSMInAppContentType_Url
 *   * SMInAppContentImageViewController for IAC of type kSMInAppContentType_Image
 *
 *  You can check each of this object for more information about how to use them. 
 *  
 *  All this view controller can also be customised with the use of SMInAppContentStyleOptions.
 *
 *  Once the sdk has provided you with the correct view controller
 *
 *      `SMInAppContentURLViewController* vc = [SMInAppContentURLViewController viewControllerForCategory:@"anycategory"];`
 *
 *  You can call showSMController:InContainerView:OfParentViewController: if you expect to display the In App Content in a UIContainerView that is defined in your app :
 *
 *      `[[SMManager sharedInstance] showSMController:vc InContainerView:_containerView OfParentViewController:self];`
 *
 *  Or you can present it to be displayed in full screen mode :
 *
 *       `[self presentViewController:vc animated:YES completion:nil];`
 *
 *  Be aware that if your UIContainerView is defined in storyboard and that no category has been provided to it you will need to inform it with prepareForSegue:sender:
 *
 * ` -(void) prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
 * {
 *   if([segue.identifier isEqualToString:@"YourSegue"]){
 *       _sminappcontentviewcontroller = segue.destinationViewController;
 *       [self.sminappcontentviewcontroller setCategory:@"anycategory"];
 *   }
 * }`
 *
 *  * With your own view controllers
 *
 *  In this case you can call getInAppContentsForCategory:Type: or getInAppContentsForCategory:Type:Max:
 *
 *  Those methods will present you an NSArray of SMInAppContentMessage with all (or a maximum number, precised by the Max parameter) IAC for a category and for a type.
 *
 *  If you decide to use this way of interacting with IAC it is important that you keep in mind that you will be responsible of the display of the content and you will have to call to setInAppContentAsSeen: whenever an InAppContent is showed to the user and to executeLinkAction:InAppContent: whenever user interact with an action link of the in app content.
 *
 *  #Fetching modes :#
 *  IAC may be retrieved from two different modes corresponding to the application's state:
 *
 *  * Foreground-fetch -- When the application is in foreground.
 *  * Background-fetch -- When the application is in background.
 *
 *  Each of these modes is **optional**. In other words, you can use one mode or the other, or even both at the same time.
 *  Choosing the adequate mode depends on the application's need and can be managed by the application's developper.
 *  Off course, to allow the SDK to retrieve IAC as fast as possible, we recommand using both modes at the same time.
 *
 *  Following documentation explains how to activate each mode:
 *
 *  #Fetching IAC in foreground :#
 *  In order to retrieve IAC while the application is running, make sure to do the folllowing:
 *
 *  - Create and configure an SMManagerSettingIAC instance accordingly.
 *  - Provide the created SMManagerSettingIAC instance to SMManager before starting the library
 *
 *  #Fetching IAC in background :#
 *  Initially, this mode has been added as a complementary-option to the foreground-mode.
 *  However, it can be used as a single-fetch-mode if fits best your application's need.
 *
 *  To understand better how often the OS will execute the background-fetch, make sure to read the following [Apple-documentation](https://developer.apple.com/library/ios/documentation/iPhone/Conceptual/iPhoneOSProgrammingGuide/BackgroundExecution/BackgroundExecution.html#//apple_ref/doc/uid/TP40007072-CH4-SW56)
 *
 *  In order to support this mode, make sure to :
 *
 *  - Create the SMManagerSettingIAC instance accordingly.
 *  - Provide the created SMManagerSettingIAC instance to SMManager before starting the library.
 *  - In the application's target, enable the following: Capabilities > Background Modes > Background Fetch
 *  - Implement performFetchWithCompletionHandler: in UIApplication's delegate (under delegate method application:performFetchWithCompletionHandler:)
 *
 *  #SMManager+InAppContent :#
 */

@interface SMManager (InAppContent)


/*!
 * Call when SDK has already provided you with a SMInAppContentViewController (of any type : SMInAppContentHTMLViewController , SMInAppContentImageViewController or SMInAppContentURLViewController) and you want to display it in a UIContainerView defined anywhere in your app.
 * @discussion The viewcontroller will take all available space in  the UIContainerView
 * @param smViewController a SMInAppContentViewController
 * @param containerView the UIContainerView in which In App Content will be displayed
 * @param parentViewController the parent UIViewController of your UIContainerView
 */
-(void) showSMController: (SMInAppContentViewController*)smViewController InContainerView:(UIView*)containerView OfParentViewController:(UIViewController*)parentViewController;


/*!
  * @abstract This will return an array of In App Contents
  * @discussion All the IAC will be retrieved
  * @param category NSString the category for which you want your In App Contents
  * @param type An SMInAppContentType - Url, Html or image
  * @return returns an NSArray of SMInAppContentMessage
  */
- (NSArray*) getInAppContentsForCategory:(NSString*)category Type:(SMInAppContentType)type;

/*!
  * @abstract This will return an array of In App Contents
  * @discussion This overload allows you to define the max number of IAC to retrieve
  * @param category An NSString the category for which you want your In App Contents
  * @param type An SMInAppContentType - Url, Html or image
  * @param max An int
  * @return returns an NSArray of SMInAppContentMessage
  */
- (NSArray*) getInAppContentsForCategory:(NSString*)category Type:(SMInAppContentType)type Max:(int)max;

/*!
  * @abstract This method will mark an IAC as viewed, save it in the cache and send the Open event to the server
  * @discussion If the display mode is set to 0 (display once), the IAC will be discarded from the cache and will not be provided to you anymore with getInAppContentsForCategory:Type: or getInAppContentsForCategory:Type:Max:
  * @param inAppContent an SMInAppContentMessage object
  */
- (void) setInAppContentAsSeen:(SMInAppContentMessage*)inAppContent;


/*!
  * @abstract This method must be called whenever a user has clicked on a link that you  manage to display
  * @discussion This will allow the sdk to inform the services that a link has been clicked and to process the action associated with the link
  * @param link a SMLink object
  * @param inAppContent a SMInAppContentMessage object
  */
- (void) executeLinkAction:(SMLink*)link InAppContent:(SMInAppContentMessage*)inAppContent;


/**
 *  This will allow the SDK to fetch the IAC when the OS will allow so.
 *  @discussion To be included in application:performFetchWithCompletionHandler:
 *  @param completionHandler The block-completion to be processed. Provided by the delegate call
 *  @warning Make sure to enable background-fetch in the application's capabilities
 */
- (void)performIACFetchWithCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler;


@end
