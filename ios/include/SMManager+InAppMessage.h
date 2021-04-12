//
//  SMManager+InAppMessage.h
//  MobileSDK
//
//  Created by Samy Ziat on 30/09/15.
//  Copyright (c) 2015 Selligent. All rights reserved.
//

#import "SMManager.h"
#import "SMInAppMessage.h"
#import "SMLink.h"

@class SMManagerSettingIAM;


/*!
 *  #Introduction :#
 *  In-Application-Message (IAM) is an optional service which will **automatically** retrieve messages from the back-end at specific frequencies.
 *  Once new messages were retrieved, the library notifies the application about it.
 *  Then, the application may display any IAM as a usual notification.
 *
 *  The retrieved IAM share the exact same format as the remote-notification.
 *  However, they are not live messages and, therefore should NOT be considered as an alternative to remote-notification.
 *  Remote-push-notificaitons are almost live messages that are pushed to devices.
 *  While IAM are non-live-messages that the SDK fetch at specific intervals according to provided fetch-mode.
 *
 *  #Implementation :#
 *  In a nutshell, activate the IAM-service is a two steps process:
 *
 *  *   First, create an SMManagerSettingIAM instance and inject it in SMManagerSetting with [SMManagerSetting configureInAppMessageServiceWithSetting:]
 *  *   Then, enable the IAM-service with enableInAppMessage:
 *
 *  However, additional steps might be required according to desired fetching-mode. 
 *  Each of these steps are explained in further details bellow.
 *
 *  In order to be notified about new IAM, the application must register to correct notification *kSMNotification_Event_DidReceiveInAppMessage*
 *  (Please read SMNSNotification for additional information).
 *  This notification will provide you with the IAM's unique ID.
 *  Please be aware that it’s the unique application’s chance to capture and store that information.
 *
 *  #Displaying IAM :#
 *
 *  As IAM and remote-notification share the same format, they are both displayed using the same APIs.
 *  Please read the documentation in SMManager(RemoteNotification) to know how to display any kind of notification.
 *
 *  Since sdk v 2.5 you have the possibility to store the In App Message on your side and process them the way you want
 *  In order to do that, once you are notified that In App Messages are available you can call getInAppMessages to receive a NSArray of SMInAppMessage
 *  Once a SMInAppMessage has been displayed and has been seen by the user you need to call setInAppMessageAsSeen: to inform Selligent that the In App message has been opened
 *  In case there is links in the In App Message and in case one of the link is triggered by user please call executeLinkAction:: to process teh action related to the link and inform Selligent that the link has been clicked
 *
 *  #Fetching modes :#
 *  IAM may be retrieved from two different modes corresponding to the application's state:
 *
 *  * Foreground-fetch -- When the application is in foreground.
 *  * Background-fetch -- When the application is in background.
 *
 *  Each of these modes is **optional**. In other words, you can use one mode or the other, or even both at the same time.
 *  Choosing the adequate mode depends on the application's need and can be managed by the application's developper.
 *  Off course, to allow the SDK to retrieve IAM as fast as possible, we recommand using both modes at the same time.
 *
 *  Following documentation explains how to activate each mode:
 *
 *  #Fetching IAM in foreground :#
 *  In order to retrieve IAM while the application is running, make sure to do the folllowing:
 *
 *  - Create and configure an SMManagerSettingIAM instance accordingly.
 *  - Provide the created SMManagerSettingIAM instance to SMManager before starting the library
 *  - Enable In App message by calling enableInAppMessage: when your application needs it.
 *
 *  #Fetching IAM in background :#
 *  Initially, this mode has been added as a complementary-option to the foreground-mode.
 *  However, it can be used as a single-fetch-mode if fits best your application's need.
 *  
 *  To understand better how often the OS will execute the background-fetch, make sure to read the following [Apple-documentation](https://developer.apple.com/library/ios/documentation/iPhone/Conceptual/iPhoneOSProgrammingGuide/BackgroundExecution/BackgroundExecution.html#//apple_ref/doc/uid/TP40007072-CH4-SW56)
 *
 *  In order to support this mode, make sure to :
 *
 *  - Create the SMManagerSettingIAM instance accordingly.
 *  - Provide the created SMManagerSettingIAM instance to SMManager before starting the library.
 *  - In the application's target, enable the following: Capabilities > Background Modes > Background Fetch
 *  - Implement performFetchWithCompletionHandler: in UIApplicaiton's delegate (under delegate method application:performFetchWithCompletionHandler:)
 *  - Enable In App message by calling enableInAppMessage: when your application needs it.
 *
 *  #SMManager+InAppMessage :#
 */
@interface SMManager (InAppMessage)



/**
 *  Call this API in order to enable / disable the IAM-service according to your application's need.
 *  @param shouldEnable TRUE will enable IAM. FALSE will disable it.
 *  @discussion Most application will call this API right after starting the SDK.
 *  However, it make no harm to call it later on when user trigger, for instance, a UISwitch.
 *  @warning Before enabling IAM-service, make sure to :
 *
 *  *   Start the SDK. Enabling the IAM-service before starting the SDK will have no effect.
 *  *   Configure correctly the IAM-service via [configureInAppMessageServiceWithSetting:]([SMManagerSetting configureInAppMessageServiceWithSetting:])
 *
 */
- (void)enableInAppMessage:(BOOL)shouldEnable;



/**
 *  This will allow the SDK to fetch the IAM when the OS will allow so.
 *  @discussion To be included in application:performFetchWithCompletionHandler:
 *  @param completionHandler The block-completion to be processed. Provided by the delegate call
 *  @warning Make sure to enable background-fetch in the application's capabilities
 */
- (void)performIAMFetchWithCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler;

/*!
  * @abstract This will return an array of In App Messages
  * @discussion All the valid IAM will be retrieved even if they were already provided to the device
  * @return returns an NSArray of SMInAppMessage
  */
- (NSArray*) getInAppMessages;

/*!
  * @abstract This method will mark an IAM as viewed, send the Open event to the server and update  SMInAppMessage object in cache with isViewed property set to  true
  * @discussion The message will  still be provided to the device with the flag isViewed set to true
  * @param inAppMessage an SMInAppMessage object
  */
- (void) setInAppMessageAsSeen:(SMInAppMessage*)inAppMessage;

/*!
  * @abstract This method will mark an IAM as unseen
  * @discussion The message will be  provided to the device with the flag isViewed set to false
  * @param inAppMessage an SMInAppMessage object
  */
- (void) setInAppMessageAsUnseen:(SMInAppMessage*)inAppMessage;

/*!
  * @abstract This method will mark an IAM as deleted
  * @discussion The message will be not be provided again to the device once deleted
  * @param inAppMessage an SMInAppMessage object
  */
- (void) setInAppMessageAsDeleted:(SMInAppMessage*)inAppMessage;

/*!
  * @abstract This method must be called whenever a user has clicked on a link that you  manage to display
  * @discussion This will allow the sdk to inform the services that a link has been clicked and to process the action associated with the link
  * @param link a SMLink object
  * @param inAppMessage  a SMInAppMessage object
  */
- (void) executeLinkAction:(SMLink*)link InAppMessage:(SMInAppMessage*)inAppMessage;

@end
