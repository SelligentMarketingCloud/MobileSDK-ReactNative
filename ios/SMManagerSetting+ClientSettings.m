#import "SMManagerSetting+ClientSettings.h"
#import "SMManagerSettingIAM.h"
#import "ClientSettings.h"
#import "EnumMapper.h"

@implementation SMManagerSetting (ClientSettings)

+ (SMManagerSetting *)smManagerSettingsFrom:(ClientSettings *)clientSettings {
    SMManagerSetting *settings = [SMManagerSetting settingWithUrl:clientSettings.url ClientID:clientSettings.clientId PrivateKey:clientSettings.privateKey];
    [self _configureManagerSettings:settings withClientSettings:clientSettings];
    SMManagerSettingIAM *iamSettings = [self _iamManagerSettingsFor:clientSettings];
    if (iamSettings) {
        [settings configureInAppMessageServiceWithSetting:iamSettings];
    }
    return settings;
}

+ (void)_configureManagerSettings:(SMManagerSetting *)settings withClientSettings:(ClientSettings *)clientSettings {
    NSString *appGroupId = clientSettings.appGroupId;
    if(appGroupId) {
        if([appGroupId hasPrefix:@"group."]) {
            settings.appGroupId = appGroupId;
        } else {
            settings.appGroupId = [NSString stringWithFormat:@"group.%@", appGroupId];
        }
    }
    
    NSNumber *shouldClearBadgeAsNumber = clientSettings.shouldClearBadge;
    if(shouldClearBadgeAsNumber) {
        settings.shouldClearBadge = shouldClearBadgeAsNumber.boolValue;
    }
    
    NSNumber *shouldDisplayRemoteNotificationAsNumber = clientSettings.shouldDisplayRemoteNotification;
    if(shouldDisplayRemoteNotificationAsNumber) {
        settings.shouldDisplayRemoteNotification = shouldDisplayRemoteNotificationAsNumber.boolValue;
    }
    
    if(clientSettings.configureLocationServices.boolValue) {
        [settings configureLocationService];
    }
    
    NSNumber *clearCacheIntervalValueAsNumber = clientSettings.clearCacheIntervalValue;
    if(clearCacheIntervalValueAsNumber) {
        settings.clearCacheIntervalValue = [[EnumMapper sharedEnumMapper] smClearCacheForClearCacheInterval:clearCacheIntervalValueAsNumber.integerValue]; //((SMClearCache) );
    }
}

+ (SMManagerSettingIAM *)_iamManagerSettingsFor:(ClientSettings *)clientSettings {
    SMManagerSettingIAM *iamSettings = nil;
    if(clientSettings.inAppMessageSettings.shouldPerformBackgroundFetch && clientSettings.inAppMessageSettings.refreshType) {
        SMInAppRefreshType refreshType = [[EnumMapper sharedEnumMapper] smInAppRefreshTypeForInAppMessageRefreshType:clientSettings.inAppMessageSettings.refreshType.integerValue];
        iamSettings = [SMManagerSettingIAM settingWithRefreshType:refreshType ShouldPerformBackgroundFetch:clientSettings.inAppMessageSettings.shouldPerformBackgroundFetch.boolValue];
    } else if (clientSettings.inAppMessageSettings.shouldPerformBackgroundFetch) {
        iamSettings = [SMManagerSettingIAM settingWithBackgroundFetchOnly];
    } else if(clientSettings.inAppMessageSettings.refreshType){
        SMInAppRefreshType refreshType = [[EnumMapper sharedEnumMapper] smInAppRefreshTypeForInAppMessageRefreshType:clientSettings.inAppMessageSettings.refreshType.integerValue];
        iamSettings = [SMManagerSettingIAM settingWithRefreshType:refreshType];
    }
    return iamSettings;
}

@end
