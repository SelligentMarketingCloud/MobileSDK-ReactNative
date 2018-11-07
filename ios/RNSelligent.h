#if __has_include(<React/RCTBridgeModule.h>)
#import <React/RCTBridgeModule.h>
#import <React/RCTEventEmitter.h>
#else
#import "RCTBridgeModule.h"
#import <RCTEventEmitter.h>
#endif

#import <UserNotifications/UserNotifications.h>

@interface RNSelligent : RCTEventEmitter <RCTBridgeModule>

+ (void)configureWithLaunchOptions:(NSDictionary *)launchOptions;
+ (void)performIAMFetchWithCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler;
+ (void)didRegisterForRemoteNotificationsWithDeviceToken:(NSData*)deviceToken;
+ (void)didRegisterUserNotificationSettings:(UIUserNotificationSettings *)notificationSettings;
+ (void)didFailToRegisterForRemoteNotificationsWithError:(NSError *)error;
+ (void)didReceiveRemoteNotification:(NSDictionary *)notification;
+ (void)willPresentNotification:(UNNotification *)notification withCompletionHandler:(void (^)(UNNotificationPresentationOptions options))completionHandler;
+ (void)didReceiveNotificationResponse:(UNNotificationResponse *)response withCompletionHandler:(void(^)(void))completionHandler;

@end
