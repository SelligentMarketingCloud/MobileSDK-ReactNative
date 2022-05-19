//
//  SMManager+UserNotification.h
//  MobileSDK
//
//  Created by Gilbert Schakal on 25/01/2017.
//  Copyright © 2017 Selligent. All rights reserved.
//

#import "SMManager+RemoteNotification.h"
#import <UserNotifications/UserNotifications.h>
#import <UserNotificationsUI/UserNotificationsUI.h>

@class SMNotificationMessage;

/**
 *  In addition to the implementation of category SMManager(RemoteNotification), this category will supply a support of iOS 10 and usage of UserNotifications framework
 *
 *  Make sure to read the category SMManager(RemoteNotification) to learn more about remote-notification for support of iOS version 8 and 9 and to correctly register for remote notification.
 *
 *  If you build against iOS 10+ and you use UserNotifications framework we then recommend you to implement those 2 methods of UNUserNotificationCenterDelegate in your appdelegate:
 *
 *      - didReceiveNotificationResponse:
 *      - didReceiveNotificationResponse:withCompletionHandler:
 *      - willPresentNotification:
 *      - willPresentNotification:withCompletionHandler:
 *
 *  Register your appdelegate to the UNUserNotificationCenter by adding the following two lines in the didFinishLaunchingWithOptions delegate.
 *
 *   `UNUserNotificationCenter *center = [UNUserNotificationCenter currentNotificationCenter];`
 *
 *   `center.delegate = self;`
 *
 *
 * __Notification extensions__
 *
 * In this category you will also find the support for notification extensions target (content and service)
 *
 *      Init extensions (to be used for each extensions that will be added to your project):
 *
 *          - startExtensionWithSetting:
 *
 *      Notification content extension :
 *
 *          - didReceiveNotification:
 *
 *      Notification service extension :
 *
 *          - didReceiveNotificationRequest:
 *          - didReceiveNotificationRequest:withContentHandler:
 *          - serviceExtensionTimeWillExpire
 *
 */
@interface SMManager (UserNotification)

/*!
 *  Mandatory API when used inside App in AppDelegate (but is optional for Notification Content Extension), when building against iOS 10+ and using UserNotifications framework, to be included in userNotificationCenter:didReceiveNotificationResponse:withCompletionHandler.
 *  Handle and display remote notification.
 *
 *  @param response An UNNotificationResponse that contains information about the notification and the interaction the user has done with it. Provided by the delegate call
 *  @discussion This method is mandatory when used in AppDelegate but is optional when implementing Notification content extension. When used in Notification Content Extension it  provides to the sdk the ability to process the action that should be triggered without opening the app (in this case don't forget to call the completionhandler with the desired UNNotificationContentExtensionResponseOption
 */
- (void) didReceiveNotificationResponse:(UNNotificationResponse*_Nonnull)response;

/*!
 *  Mandatory API, when building against iOS 10+ and using UserNotifications framework, to be included in userNotificationCenter:didReceiveNotificationResponse:withCompletionHandler
 *  Handle and display remote notification.
 *
 *  @param response An UNNotificationResponse that contains information about the notification and the interaction the user has done with it. Provided by the delegate call
 *  @param completionHandler A completion that will be called with the option UNNotificationContentExtensionResponseOptionDismiss
 */
- (void) didReceiveNotificationResponse:(UNNotificationResponse *_Nonnull)response withCompletionHandler:(void (^_Nullable)(UNNotificationContentExtensionResponseOption option))completionHandler;

/*!
 *  Mandatory API, when building against iOS 10+ and using UserNotifications framework, to be included in userNotificationCenter:willPresentNotification:withCompletionHandler
 *  Handle the remote notification when app is in foreground.
 *
 *  This allows the SDK to inform the services that the Selligent push has been received.
 *
 *  Calling this method does not call any CompletionHandler. You will have to call the completion handler with your preferred option.
 *
 *  For example you can call inside this delegate :
 *      completionHandler(UNNotificationPresentationOptionAlert);
 *
 *  @param notification A UNNotification that contains information about the notification.
 */
- (void) willPresentNotification:(UNNotification*_Nonnull)notification;

/*!
 *  Mandatory API, when building against iOS 10+ and using UserNotifications framework, to be included in userNotificationCenter:willPresentNotification:withCompletionHandler
 *  Handle the remote notification when app is in foreground and call the completionHandler(UNNotificationPresentationOptionAlert) by default (or UNNotificationPresentationOptionBanner | UNNotificationPresentationOptionList for iOS 14+).
 *
 *  This allows the SDK to inform the services that the Selligent push has been received.
 *
 *  You don't need to call the completion handler in the delegate anymore.
 *
 *  @param notification An UNNotification that contains information about the notification.
 *  @param completionHandler A Completion handler that will be called with a specific UNNotificationPresentationOption depending on the SMForegroundDisplayType value specified when starting the SDK.
 *  @see SMManagerSetting
 */
- (void) willPresentNotification:(UNNotification*_Nonnull)notification withCompletionHandler:(void (^_Nullable)(UNNotificationPresentationOptions options))completionHandler;

/*!
 *  Mandatory method which allows sdk initialisation when building against iOS 10+ and using Notification Extensions .
 *  To be included in didReceiveNotification: when implementing Notification content extension and/or in didReceiveNotificationRequest:withContentHandler: when implementing Notification service extension
 *
 *  @param setting  mandatory SMManagerSetting instance to start-up the library - this setting mus tbe initialized with only url, clienID and privateKet provided by selligent
 *  @see SMManagerSetting
 *  @discussion This method is mandatory in order to start / initialize the library and should be called in in didReceiveNotification: when implementing Notification content extension and/or in didReceiveNotificationRequest:withContentHandler: when implementing Notification service extension
 *  @see SMManagerSetting
 */
- (void) startExtensionWithSetting:(SMManagerSetting*_Nonnull)setting;

/*!
 *  Optional API, when building against iOS 10+ and using a Notification Content Extension target, to be included in NotificationViewController didReceiveNotification:
 *  Handle the push action buttons that may be present in the selligent notification payload
 *
 *  This allows the SDK to display the action buttons in the push notification outside of the app.
 *
 *  The category that must be added to Info.plist of the Notification Content Extension target is mandatory and must be SELLIGENT_BUTTON.
 *
 *  @param notification A UNNotification that contains information about the notification.
 */
- (void) didReceiveNotification:(UNNotification*_Nonnull)notification __deprecated_msg("Method deprecated. Use `didReceiveNotification:withContext:`");

/*!
 *  Optional API, when building against iOS 10+ and using a Notification Content Extension target, to be included in NotificationViewController didReceiveNotification:
 *  Handle the push action buttons that may be present in the selligent notification payload
 *
 *  This allows the SDK to display the action buttons in the push notification outside of the app.
 *
 *  The category that must be added to Info.plist of the Notification Content Extension target is mandatory and must be SELLIGENT_BUTTON.
 *
 *  @param notification A UNNotification that contains information about the notification.
 *  @param context A NSExtensionContext that contains the context information of the extension.
 */
- (void) didReceiveNotification:(UNNotification*_Nonnull)notification withContext:(NSExtensionContext*_Nullable)context;

/*!
 *  Optional API, when building against iOS 10+ and using a Notification Service Extension target, to be included in NotificationService didReceiveNotificationRequest:withContentHandler:
 *  Handle the selligent payload before displaying it to the user
 *
 *  This allows the SDK to decrypt the payload before displaying it to the user if you have activated the encryption of push.
 *
 *  @param request An UNNotificationRequest that contains the original notification request.
 *  @return UNMutableNotificationContent the updated content of the payload.
 *  @discussion you can use this method if you have decided to trigger the block to execute with the modified content by yourself otherwise if you want the sdk to manage all steps please use SMManager didReceiveNotificationRequest:withContentHandler:
 */
- (UNMutableNotificationContent*_Nullable) didReceiveNotificationRequest:(UNNotificationRequest*_Nonnull)request;

/*!
 *  Optional API, when building against iOS 10+ and using a Notification Service Extension target, to be included in NotificationService didReceiveNotificationRequest:withContentHandler:
 *  Handle the selligent payload before displaying it to the user
 *
 *  This allows the SDK to decrypt the payload before displaying it to the user if you have activated the encryption of push.
 *
 *  @param request An UNNotificationRequest that contains the original notification request.
 *  @param contentHandler The block to execute with the modified content
 *  @discussion you can use this method if you want the sdk to manage the display of the notification after the decryption has been processed
 */
- (void) didReceiveNotificationRequest:(UNNotificationRequest*_Nonnull)request withContentHandler:(void (^_Nullable)(UNNotificationContent*_Nonnull))contentHandler;

/*!
 *  Optional API, when building against iOS 10+ and using a Notification Service Extension target, to be included in NotificationService serviceExtensionTimeWillExpire
 *  Tells the sdk that the extension is about to be terminated.
 *  @discussion this method is to be implemented only if you have implemented SMManager didReceiveNotificationRequest:withContentHandler:
 */
- (void) serviceExtensionTimeWillExpire;

/**
 *  Optional API, retrieves the SMNotificationMessage object from a given userInfo
 *
 *  @param userInfo An NSDictionary
 *  @return SMNotificationMessage instance containing the information extracted from the given userInfo.
 *  @discussion This is a convinient method to get the SMNotificationMessage from an incoming remote-notification.
 *  It can be used for custom purposes when receiving a remote-notification in foreground for iOS 10+.
 *  @see SMNotificationMessage
 */
- (SMNotificationMessage*_Nullable) retrieveNotificationMessage:(NSDictionary*_Nullable)userInfo;

@end
