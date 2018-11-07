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
 *  - willPresentNotification:withCompletionHandler:
 *  - didReceiveNotificationResponse:withCompletionHandler:
 *
 *  Register your appdelegate to the UNUserNotificationCenter by adding the following two lines in the didFinishLaunchingWithOptions delegate.
 *
 *  @code
 *   UNUserNotificationCenter *center = [UNUserNotificationCenter currentNotificationCenter];
 *   center.delegate = self;
 *  @endcode
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

@end
