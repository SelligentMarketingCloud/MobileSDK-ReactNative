#import "RNSelligent.h"
#import "SMManager.h"
#import "SMNSNotification.h"
#import "SMManager+DataTransaction.h"
#import "SMManagerSetting+ClientSettings.h"
#import "SMManager+Location.h"
#import "SMManager+Log.h"
#import "SMManager+SMEvent.h"
#import "SMManager+RemoteNotification.h"
#import "SMManager+UserNotification.h"
#import "SMManager+InAppMessage.h"
#import "SMManager+SilentPush.h"
#import "Event.h"
#import "Event+SMEvent.h"
#import "LogLevel.h"
#import "EnumMapper.h"
#import "SMDeviceInfos.h"
#import "ClientSettings.h"
#import "SelligentLogger.h"
#import "SMNotificationButtonData.h"

static RNSelligent *rnSelligent = nil;

static NSString * const BROADCAST_BUTTON_CLICKED = @"ButtonClicked";
static NSString * const BROADCAST_RECEIVED_IN_APP_MSG = @"ReceivedInAppMessage";
static NSString * const BROADCAST_WILL_DISPLAY_NOTIFICATION = @"WillDisplayNotification";
static NSString * const BROADCAST_WILL_DISMISS_NOTIFICATION = @"WillDismissNotification";
static NSString * const BROADCAST_RECEIVED_REMOTENOTIFICATION = @"ReceivedRemoteNotification";
static NSString * const FETCHED_REMOTE_NOTIFICATION = @"FetchedRemoteNotification";

@interface RNSelligent()
@property (nonatomic, strong) NSNumber *requestedForcedRemoteNotificationBackgroundFetchResult;
@end

@implementation RNSelligent

RCT_EXPORT_MODULE(RNSelligent)

+ (nonnull instancetype)instance {
    return rnSelligent;
}

- (instancetype)init {
    self = [super init];
    if (self != nil) {
        rnSelligent = self;
    }
    return self;
}

+ (void)configureWithLaunchOptions:(NSDictionary *)launchOptions {
    NSArray *selligentSettingsJSONPathComponents = @[[[NSBundle mainBundle] bundlePath], @"selligent.json"];
    NSString *selligentSettingsJSONPath = [NSString pathWithComponents:selligentSettingsJSONPathComponents];
    if ([[NSFileManager defaultManager] fileExistsAtPath:selligentSettingsJSONPath]) {
        NSData *data = [NSData dataWithContentsOfFile:selligentSettingsJSONPath];
        NSDictionary *settingsJson = [NSJSONSerialization JSONObjectWithData:data options:kNilOptions error:nil];
        ClientSettings *clientSettings = [ClientSettings fromDictionary:settingsJson];
        SMManagerSetting *settings = [SMManagerSetting smManagerSettingsFrom:clientSettings];
        [[SMManager sharedInstance] startWithLaunchOptions:launchOptions Setting:settings];
    } else {
        [SelligentLogger log:@"no selligent.json file found. Please provide a selligent.json file as a bundle resource of your iOS application."];
    }
}

+ (void)performIAMFetchWithCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler {
    [[SMManager sharedInstance] performIAMFetchWithCompletionHandler:completionHandler];
}

+ (void)didRegisterForRemoteNotificationsWithDeviceToken:(NSData*)deviceToken {
    [[SMManager sharedInstance] didRegisterForRemoteNotificationsWithDeviceToken:deviceToken];
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
+ (void)didRegisterUserNotificationSettings:(UIUserNotificationSettings *)notificationSettings {
    [[SMManager sharedInstance] didRegisterUserNotificationSettings:notificationSettings];
}
#pragma clang diagnostic pop

+ (void)didFailToRegisterForRemoteNotificationsWithError:(NSError *)error {
    [[SMManager sharedInstance] didFailToRegisterForRemoteNotificationsWithError:error];
}

+ (void)didReceiveRemoteNotification:(NSDictionary *)notification {
    void (^fetchCompletionHandler)(UIBackgroundFetchResult) = ^(UIBackgroundFetchResult backgroundResult) {
        NSDictionary *message = @{
            @"backgroundFetchResult": @([[EnumMapper sharedEnumMapper] backgroundFetchResultForUIBackgroundFetchResult:backgroundResult]),
            @"notification" : notification,
        };
        [[RNSelligent instance] sendEventWithName:FETCHED_REMOTE_NOTIFICATION body:message];
    };

    NSNumber *requestedFetchResult = [[RNSelligent instance] requestedForcedRemoteNotificationBackgroundFetchResult];
    if (requestedFetchResult) {
        [[SMManager sharedInstance] didReceiveRemoteNotification:notification fetchCompletionHandler:fetchCompletionHandler ForceResultFetch:requestedFetchResult.integerValue];
    } else {
        [[SMManager sharedInstance] didReceiveRemoteNotification:notification fetchCompletionHandler:fetchCompletionHandler];
    }
}

+ (void)willPresentNotification:(UNNotification *)notification withCompletionHandler:(void (^)(UNNotificationPresentationOptions options))completionHandler {
    [[SMManager sharedInstance] willPresentNotification:notification withCompletionHandler:completionHandler];
}

+ (void)didReceiveNotificationResponse:(UNNotificationResponse *)response withCompletionHandler:(void(^)(void))completionHandler {
    [[SMManager sharedInstance] didReceiveNotificationResponse:response withCompletionHandler:completionHandler];
}

RCT_EXPORT_METHOD(getVersionLib:(RCTResponseSenderBlock)callback) {
    NSString *libraryVersion = [[SMManager sharedInstance] versionLib];
    callback(@[libraryVersion, [NSNull null]]);
}

RCT_EXPORT_METHOD(reloadSettings:(NSDictionary *)settings) {
    ClientSettings *clientSettings = [ClientSettings fromDictionary:settings];
    SMManagerSetting *managerSettings = [SMManagerSetting smManagerSettingsFrom:clientSettings];
    [[SMManager sharedInstance] reloadSetting:managerSettings];
}

RCT_EXPORT_METHOD(sendDeviceInfo:(NSString *)externalId) {
    SMDeviceInfos *deviceInfos = [SMDeviceInfos deviceInfosWithExternalId:externalId];
    [[SMManager sharedInstance] sendDeviceInfo:deviceInfos];
}

RCT_EXPORT_METHOD(enableInAppMessages:(BOOL)enabled) {
    [[SMManager sharedInstance] enableInAppMessage:enabled];
}

RCT_EXPORT_METHOD(applyLogLevel:(NSArray<NSNumber *> *)logLevels) {
    __block NSInteger requestedBitShiftedLogLevel = 0;
    for (NSNumber *logLevel in logLevels) {
        LogLevel plLogLevel = logLevel.integerValue;
        SMLogLevel smLogLevel = [[EnumMapper sharedEnumMapper] smLogLevelForLogLevel:plLogLevel];
        requestedBitShiftedLogLevel = requestedBitShiftedLogLevel | smLogLevel;
    }
    [[SMManager sharedInstance] applyLogLevel:(SMLogLevel) requestedBitShiftedLogLevel];
}

RCT_EXPORT_METHOD(currentAuthorisationStatus:(RCTResponseSenderBlock)callback) {
    SMLocationAuthorisationStatus smLocationAuthStatus = [[SMManager sharedInstance] currentAuthorisationStatus];
    LocationAuthorisationStatus status = [[EnumMapper sharedEnumMapper] locationAuthorisationStatusForSMLocationAuthorisationStatus:smLocationAuthStatus];
    callback(@[@(status), [NSNull null]]);
}

RCT_EXPORT_METHOD(requestLocationAuthorisation:(NSInteger)authorisationType) {
    SMLocationAuthorisationType smAuthType = [[EnumMapper sharedEnumMapper] smLocationAuthorisationTypeForLocationAuthorisationType:authorisationType];
    [[SMManager sharedInstance] requestLocationAuthorisation:smAuthType];
}

RCT_EXPORT_METHOD(isGeolocationEnabled:(RCTResponseSenderBlock)callback) {
    BOOL enabled = [[SMManager sharedInstance] isGeoLocationEnabled];
    callback(@[@(enabled), [NSNull null]]);
}

RCT_EXPORT_METHOD(sendEvent:(NSDictionary *)data successCallback:(RCTResponseSenderBlock)successCallback errorCallback:(RCTResponseSenderBlock)errorCallback) {
    Event *event = [Event fromDictionary:data];
    SMEvent *smEvent = [event smEventWithBlockSuccess:^(SMSuccess *success) {
        successCallback(@[success.messageSM, [NSNull null]]);
    } BlockFailure:^(SMFailure *failure) {
        errorCallback(@[failure.messageSM, [NSNull null]]);
    }];
    [[SMManager sharedInstance] sendSMEvent:smEvent];
}

RCT_EXPORT_METHOD(enableGeolocation:(BOOL)enable) {
    if (enable) {
        [[SMManager sharedInstance] enableGeoLocation];
    } else {

        [[SMManager sharedInstance] disableGeoLocation];
    }
}

RCT_EXPORT_METHOD(forceRemoteNotificationBackgroundFetchResult:(nonnull NSNumber *)remoteNotificationBackgroundFetchResult) {
    self.requestedForcedRemoteNotificationBackgroundFetchResult = @([[EnumMapper sharedEnumMapper] uiBackgroundFetchResultForBackgroundFetchResult:remoteNotificationBackgroundFetchResult.integerValue]);
}

RCT_EXPORT_METHOD(enableNotifications:(BOOL)enable) {
    if (enable) {
        [[SMManager sharedInstance] registerForRemoteNotification];
    } else {
        [[SMManager sharedInstance] unregisterForRemoteNotification];
    }
}

RCT_EXPORT_METHOD(displayLastReceivedRemotePushNotification) {
    [[SMManager sharedInstance] displayLastReceivedRemotePushNotification];
}

RCT_EXPORT_METHOD(getLastRemotePushNotification:(RCTResponseSenderBlock)callback) {
    NSDictionary *lastRemotePushNotification = [[SMManager sharedInstance] retrieveLastRemotePushNotification];
    NSDictionary *message = nil;
    if(lastRemotePushNotification) {
        message = @{
                    @"id" : lastRemotePushNotification[@"id"],
                    @"title" : lastRemotePushNotification[@"title"],
                    };
    }
    callback(@[message ?: [NSNull null], [NSNull null]]);
}

RCT_EXPORT_METHOD(displayNotification:(NSString *)notificationId) {
    [[SMManager sharedInstance] displayNotificationID:notificationId];
}

RCT_EXPORT_METHOD(subscribeToEvents) {
    [self _addOrReplaceObserverForSelector:@selector(_handleDidReceiveInAppMessage:) forName:kSMNotification_Event_DidReceiveInAppMessage];
    [self _addOrReplaceObserverForSelector:@selector(_handleButtonClicked:) forName:kSMNotification_Event_ButtonClicked];
    [self _addOrReplaceObserverForSelector:@selector(_handleWillDisplayNotification:) forName:kSMNotification_Event_WillDisplayNotification];
    [self _addOrReplaceObserverForSelector:@selector(_handleWillDismissNotification:) forName:kSMNotification_Event_WillDismissNotification];
    [self _addOrReplaceObserverForSelector:@selector(_handleDidReceiveRemoteNotification:) forName:kSMNotification_Event_DidReceiveRemoteNotification];
}

- (void)_addOrReplaceObserverForSelector:(SEL)selector forName:(NSString *)name {
    [[NSNotificationCenter defaultCenter] removeObserver:self name:name object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:selector name:name object:nil];
}

#pragma mark - Event Observation

- (void)_handleButtonClicked:(NSNotification*)notification {
    NSDictionary *dict = [notification userInfo];
    SMNotificationButtonData *btnData = dict[kSMNotification_Data_ButtonData];
    NSDictionary *data = @{
                           @"type": @([[EnumMapper sharedEnumMapper] notificationButtonTypeForSMNotificationButtonType:btnData.type]),
                           @"value": btnData.value ?: [NSNull null],
                           @"id": btnData.idButtonData ?: [NSNull null],
                           @"label": btnData.label ?: [NSNull null],
                           };
    [self _sendBroadcastEventResultWithData:data andType:BROADCAST_BUTTON_CLICKED];
}

- (void)_handleDidReceiveInAppMessage:(NSNotification*)notification {
    NSDictionary *dict = [notification userInfo];
    NSArray *inAppMessageData = dict[kSMNotification_Data_InAppMessage];
    NSDictionary *data = @{
                           @"messages": inAppMessageData ?: [NSNull null],
                           };
    [self _sendBroadcastEventResultWithData:data andType:BROADCAST_RECEIVED_IN_APP_MSG];
}

- (void)_handleDidReceiveRemoteNotification:(NSNotification*)notification {
    NSDictionary *dict = [notification userInfo];
    NSDictionary *notificationData = dict[kSMNotification_Data_RemoteNotification];
    NSDictionary *data = @{
                           @"pushId": notificationData[@"pushId"] ?: [NSNull null],
                           @"name": notificationData[@"name"] ?: [NSNull null],
                           };
    [self _sendBroadcastEventResultWithData:data andType:BROADCAST_RECEIVED_REMOTENOTIFICATION];
}

- (void)_handleWillDisplayNotification:(NSNotification*)notification {
    [self _sendBroadcastEventResultWithData:nil andType:BROADCAST_WILL_DISPLAY_NOTIFICATION];
}

- (void)_handleWillDismissNotification:(NSNotification*)notification {
    [self _sendBroadcastEventResultWithData:nil andType:BROADCAST_WILL_DISMISS_NOTIFICATION];
}

- (void)_sendBroadcastEventResultWithData:(NSDictionary *)data andType:(NSString *)type {
    [self sendEventWithName:type body:data ?: [NSNull null]];
}

-(NSArray<NSString *> *)supportedEvents {
    return @[
        BROADCAST_BUTTON_CLICKED,
        BROADCAST_RECEIVED_IN_APP_MSG,
        BROADCAST_WILL_DISPLAY_NOTIFICATION,
        BROADCAST_WILL_DISMISS_NOTIFICATION,
        BROADCAST_RECEIVED_REMOTENOTIFICATION,
        FETCHED_REMOTE_NOTIFICATION
     ];
}

- (dispatch_queue_t)methodQueue {
    return dispatch_get_main_queue();
}

#pragma mark - Dealloc

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

@end
