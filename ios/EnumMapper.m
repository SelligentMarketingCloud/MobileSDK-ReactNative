#import "EnumMapper.h"

@implementation EnumMapper {
    NSDictionary *_logLevelEnumMapping;
    NSDictionary *_clearCacheIntervalEnumMapping;
    NSDictionary *_inAppRefreshTypeEnumMapping;
    NSDictionary *_remoteMessageDisplayTypeEnumMapping;
    NSDictionary *_locationAuthorisationStatusMapping;
    NSDictionary *_locationAuthorisationTypeMapping;
    NSDictionary *_backgroundFetchResult;
    NSDictionary *_notificationButtonTypeMapping;
}

+ (instancetype)sharedEnumMapper {
    static EnumMapper *sharedSDKEnumMapper = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedSDKEnumMapper = [[self alloc] init];
    });
    return sharedSDKEnumMapper;
}

- (instancetype)init {
    if (self = [super init]) {
        _logLevelEnumMapping = @{
                                 @(llNone) : @(kSMLogLevel_None),
                                 @(llInfo) : @(kSMLogLevel_Info),
                                 @(llWarning) : @(kSMLogLevel_Warning),
                                 @(llError) : @(kSMLogLevel_Error),
                                 @(llHTTPCall) : @(kSMLogLevel_HTTPCall),
                                 @(llLocation) : @(kSMLogLevel_Location),
                                 @(llAll) : @(kSMLogLevel_All),
                                 };
        _clearCacheIntervalEnumMapping = @{
                                           @(cciAuto) : @(kSMClearCache_Auto),
                                           @(cciNone) : @(kSMClearCache_None),
                                           @(cciWeek) : @(kSMClearCache_Week),
                                           @(cciMonth) : @(kSMClearCache_Month),
                                           @(cciQuarter) : @(kSMClearCache_Quarter),
                                           };
        _inAppRefreshTypeEnumMapping = @{
                                         @(iamrtNone) : @(kSMIA_RefreshType_None),
                                         @(iamrtMinute) : @(kSMIA_RefreshType_Minutely),
                                         @(iamrtHour) : @(kSMIA_RefreshType_Hourly),
                                         @(iamryDay ) : @(kSMIA_RefreshType_Daily),
                                         };
        _remoteMessageDisplayTypeEnumMapping = @{
            @(rmdtAutomatic) : @(kSMRemoteMessageDisplayType_Automatic),
            @(rmdtNone) : @(kSMRemoteMessageDisplayType_None),
            @(rmdtNotification) : @(kSMRemoteMessageDisplayType_Notification),
        };
        _backgroundFetchResult = @{
                                   @(bfrNewData) : @(UIBackgroundFetchResultNewData),
                                   @(bfrNoData) : @(UIBackgroundFetchResultNoData),
                                   @(bfrFailed) : @(UIBackgroundFetchResultFailed),
                                   };
        _notificationButtonTypeMapping = @{
                @(nbtUnknown) : @(kSMNotificationButtonType_Unknown),
                @(nbtSimple) : @(kSMNotificationButtonType_Simple),
                @(nbtOpenPhoneCall) : @(kSMNotificationButtonType_OpenPhoneCall),
                @(nbtOpenSms) : @(kSMNotificationButtonType_OpenSms),
                @(nbtOpenMail) : @(kSMNotificationButtonType_OpenMail),
                @(nbtOpenBrowser) : @(kSMNotificationButtonType_OpenBrowser),
                @(nbtOpenApplication) : @(kSMNotificationButtonType_OpenApplication),
                @(nbtRateApplication) : @(kSMNotificationButtonType_RateApplication),
                @(nbtCustomActionBroadcastEvent) : @(kSMNotificationButtonType_CustomActionBroadcastEvent),
                @(nbtReturn_Text) : @(kSMNotificationButtonType_Return_Text),
                @(nbtReturn_Photo) : @(kSMNotificationButtonType_Return_Photo),
                @(nbtReturn_TextAndPhoto) : @(kSMNotificationButtonType_Return_TextAndPhoto),
                @(nbtPassbook) : @(kSMNotificationButtonType_Passbook)
        };
    }
    return self;
}

- (SMLogLevel)smLogLevelForLogLevel:(LogLevel)logLevel {
    return (SMLogLevel) ((NSNumber *) _logLevelEnumMapping[@(logLevel)]).integerValue;
}

- (LogLevel)logLevelForSMLogLevel:(SMLogLevel)smLogLevel {
    return (LogLevel) ((NSNumber *)[_logLevelEnumMapping allKeysForObject:@(smLogLevel)].firstObject).integerValue;
}

- (SMClearCache)smClearCacheForClearCacheInterval:(ClearCacheInterval)clearCacheInterval {
    return (SMClearCache) ((NSNumber *)_clearCacheIntervalEnumMapping[@(clearCacheInterval)]).integerValue;
}

- (SMClearCache)clearCacheIntervalForSMClearCache:(SMClearCache)smClearCache {
    return (SMClearCache) ((NSNumber *)[_clearCacheIntervalEnumMapping allKeysForObject:@(smClearCache)].firstObject).integerValue;
}

- (SMInAppRefreshType)smInAppRefreshTypeForInAppMessageRefreshType:(InAppMessageRefreshType)inAppMessageRefreshType {
    return (SMInAppRefreshType) ((NSNumber *)_inAppRefreshTypeEnumMapping[@(inAppMessageRefreshType)]).integerValue;
}

- (InAppMessageRefreshType)inAppMessageRefreshTypeForSMInAppRefreshType:(SMInAppRefreshType)smInAppRefreshType {
    return (InAppMessageRefreshType) ((NSNumber *)[_inAppRefreshTypeEnumMapping allKeysForObject:@(smInAppRefreshType)].firstObject).integerValue;
}

-(SMRemoteMessageDisplayType)smRemoteMessageDisplayTypeForRemoteMessageDisplayType:(RemoteMessageDisplayType)remoteMessageDisplayType {
    return (SMRemoteMessageDisplayType) ((NSNumber *)_remoteMessageDisplayTypeEnumMapping[@(remoteMessageDisplayType)]).integerValue;
}

- (UIBackgroundFetchResult)uiBackgroundFetchResultForBackgroundFetchResult:(BackgroundFetchResult)backgroundFetchResult {
    return (UIBackgroundFetchResult) ((NSNumber *)_backgroundFetchResult[@(backgroundFetchResult)]).integerValue;
}

- (BackgroundFetchResult)backgroundFetchResultForUIBackgroundFetchResult:(UIBackgroundFetchResult)uiBackgroundFetchResult {
    return (BackgroundFetchResult) ((NSNumber *)[_backgroundFetchResult allKeysForObject:@(uiBackgroundFetchResult)].firstObject).integerValue;
}

- (SMNotificationButtonType)smNotificationButtonTypeForNotificationButtonType:(NotificationButtonType)notificationButtonType {
    return (SMNotificationButtonType) ((NSNumber *)_notificationButtonTypeMapping[@(notificationButtonType)]).integerValue;
}

- (NotificationButtonType)notificationButtonTypeForSMNotificationButtonType:(SMNotificationButtonType)smNotificationButtonType {
    return (NotificationButtonType) ((NSNumber *)[_notificationButtonTypeMapping allKeysForObject:@(smNotificationButtonType)].firstObject).integerValue;
}


@end
