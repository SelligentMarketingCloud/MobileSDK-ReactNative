//
//  SMManager+UserNotification.h
//  MobileSDK
//
//  Created by Gilbert Schakal on 25/01/2017.
//  Copyright © 2017 Selligent. All rights reserved.
//

#import "SMManager+RemoteNotification.h"
#import <UserNotifications/UserNotifications.h>

/**
 *  In addition to the implementation of category SMManager(RemoteNotification), this category will supply a support of iOS 10 and usage of UserNotifications framework
 *
 *  Make sure to read the category SMManager(RemoteNotification) to learn more about remote-notification for support of iOS version 8 and 9 and to correctly register for remote notification.
 *
 *  If you build against iOS 10+ and you use UserNotifications framework we then recommend you to implement those 2 methods of UNUserNotificationCenterDelegate in your appdelegate:
 *
 *      - SMManager didReceiveNotificationResponse:
 *      - SMManager didReceiveNotificationResponse:withCompletionHandler:
 *      - SMManager willPresentNotification:
 *      - SMManager willPresentNotification:withCompletionHandler:
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
 *          - SMManager startExtensionWithSetting:
 *
 *      Notification content extension :
 *
 *          - SMManager didReceiveNotification:
 *
 *      Notification service extension :
 *
 *          - SMManager didReceiveNotificationRequest:
 *          - SMManager didReceiveNotificationRequest:withContentHandler:
 *          - SMManager serviceExtensionTimeWillExpire
 *
 *  #SMManager+UserNotifications :#
 *
 */
@interface SMManager (UserNotification)

/*!
 *  Mandatory API, when building against iOS 10+ and using UserNotifications framework, to be included in userNotificationCenter:didReceiveNotificationResponse:withCompletionHandler.
 *  Handle and display remote notification.
 *
 *  @param response A UNNotificationResponse that contains information about the notification and the interaction the user has done with it. Provided by the delegate call
 */
- (void)didReceiveNotificationResponse:(UNNotificationResponse *)response;


/*!
 *  Mandatory API, when building against iOS 10+ and using UserNotifications framework, to be included in userNotificationCenter:didReceiveNotificationResponse:withCompletionHandler
 *  Handle and display remote notification.
 *
 *  @param response A UNNotificationResponse that contains information about the notification and the interaction the user has done with it. Provided by the delegate call
 *  @param completionHandler A completion that will be called.
 */
- (void)didReceiveNotificationResponse:(UNNotificationResponse *)response withCompletionHandler:(void (^)(void))completionHandler;

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
- (void)willPresentNotification:(UNNotification *)notification;

/*!
 *  Mandatory API, when building against iOS 10+ and using UserNotifications framework, to be included in userNotificationCenter:willPresentNotification:withCompletionHandler
 *  Handle the remote notification when app is in foreground and call the completionHandler(UNNotificationPresentationOptionAlert) by default.
 *
 *  This allows the SDK to inform the services that the Selligent push has been received.
 *
 *  You don't need to call the completion handler in the delegate anymore.
 *
 *  @param notification A UNNotification that contains information about the notification.
 *  @param completionHandler A Completion handler that will be called with UNNotificationPresentationOptionAlert by default.
 */
- (void)willPresentNotification:(UNNotification *)notification withCompletionHandler:(void (^)(UNNotificationPresentationOptions options))completionHandler;


/*!
 *  Mandatory method which allows sdk initialisation when building against iOS 10+ and using Notification Extensions .
 *  To be included in didReceiveNotification: when implementing Notification content extension and/or in didReceiveNotificationRequest:withContentHandler: when implementing Notification service extension
 *
 *  @param setting  mandatory SMManagerSetting instance to start-up the library - this setting mus tbe initialised with only url, clienID and privateKet provided by selligent
 *  @see  SMManagerSetting
 *  @discussion This method is mandatory in order to start / initialise the library and should be called in in didReceiveNotification: when implementing Notification content extension and/or in didReceiveNotificationRequest:withContentHandler: when implementing Notification service extension
 */
- (void)startExtensionWithSetting:(SMManagerSetting*)setting;

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
- (void)didReceiveNotification:(UNNotification *)notification;


/*!
 *  Optional API, when building against iOS 10+ and using a Notification Service Extension target, to be included in NotificationService didReceiveNotificationRequest:withContentHandler:
 *  Handle the selligent payload before displaying it to the user
 *
 *  This allows the SDK to decrypt the payload before displaying it to the user if you have activated the encryption of push.
 *
 *  @param request A UNNotificationRequest that contains the original notification request.
 *  @return UNMutableNotificationContent the updated content of the payload.
 *  @discussion you can use this method if you have decided to trigger the block to execute with the modified content by yourself otherwise if you want the sdk to manage all steps please use SMManager didReceiveNotificationRequest:withContentHandler:
 */
- (UNMutableNotificationContent *)didReceiveNotificationRequest:(UNNotificationRequest *)request;

/*!
 *  Optional API, when building against iOS 10+ and using a Notification Service Extension target, to be included in NotificationService didReceiveNotificationRequest:withContentHandler:
 *  Handle the selligent payload before displaying it to the user
 *
 *  This allows the SDK to decrypt the payload before displaying it to the user if you have activated the encryption of push.
 *
 *  @param request A UNNotificationRequest that contains the original notification request.
 *  @param contentHandler The block to execute with the modified content
 *  @discussion you can use this method if you want the sdk to manage the display of the notification after teh decryption has been processed
 */
- (void)didReceiveNotificationRequest:(UNNotificationRequest *)request withContentHandler:(void (^)(UNNotificationContent *))contentHandler;

/*!
 *  Optional API, when building against iOS 10+ and using a Notification Service Extension target, to be included in NotificationService serviceExtensionTimeWillExpire
 *  Tells the sdk that the extension is about to be terminated.
 *  @discussion this method is to be implemented only if you have implemented SMManager didReceiveNotificationRequest:withContentHandler:
 */
- (void)serviceExtensionTimeWillExpire;
@end
