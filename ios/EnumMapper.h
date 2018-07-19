#import <UIKit/UIKit.h>
#import "LogLevel.h"
#import "InAppMessageRefreshType.h"
#import "LocationAuthorisationStatus.h"
#import "LocationAuthorisationType.h"
#import "ClearCacheInterval.h"
#import "SMLocationAuthorisationType.h"
#import "SMLog.h"
#import "SMClearCache.h"
#import "SMInAppRefreshType.h"
#import "BackgroundFetchResult.h"
#import "SMNotificationButtonType.h"
#import "NotificationButtonType.h"

@interface EnumMapper : NSObject

+ (instancetype)sharedEnumMapper;
- (SMLogLevel)smLogLevelForLogLevel:(LogLevel)logLevel;
- (LogLevel)logLevelForSMLogLevel:(SMLogLevel)smLogLevel;

- (SMClearCache)smClearCacheForClearCacheInterval:(ClearCacheInterval)clearCacheInterval;
- (SMClearCache)clearCacheIntervalForSMClearCache:(SMClearCache)smClearCache;

- (SMInAppRefreshType)smInAppRefreshTypeForInAppMessageRefreshType:(InAppMessageRefreshType)inAppMessageRefreshType;
- (InAppMessageRefreshType)inAppMessageRefreshTypeForSMInAppRefreshType:(SMInAppRefreshType)smInAppRefreshType;

- (SMLocationAuthorisationStatus)smLocationAuthorisationStatusForLocationAuthorisationStatus:(LocationAuthorisationStatus)locationAuthorisationStatus;
- (LocationAuthorisationStatus)locationAuthorisationStatusForSMLocationAuthorisationStatus:(SMLocationAuthorisationStatus)smLocationAuthorisationType;

- (SMLocationAuthorisationType)smLocationAuthorisationTypeForLocationAuthorisationType:(LocationAuthorisationType)locationAuthorisationType;
- (LocationAuthorisationType)locationAuthorisationTypeForSMLocationAuthorisationType:(SMLocationAuthorisationType)smLocationAuthorisationType;

- (UIBackgroundFetchResult)uiBackgroundFetchResultForBackgroundFetchResult:(BackgroundFetchResult)backgroundFetchResult;
- (BackgroundFetchResult)backgroundFetchResultForUIBackgroundFetchResult:(UIBackgroundFetchResult)uiBackgroundFetchResult;

- (SMNotificationButtonType)smNotificationButtonTypeForNotificationButtonType:(NotificationButtonType)notificationButtonType;
- (NotificationButtonType)notificationButtonTypeForSMNotificationButtonType:(SMNotificationButtonType)smNotificationButtonType;

@end
