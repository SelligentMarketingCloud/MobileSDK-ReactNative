#import "SMManagerSetting.h"

@class ClientSettings;

@interface SMManagerSetting (ClientSettings)

+ (SMManagerSetting *)smManagerSettingsFrom:(ClientSettings *)clientSettings;

@end
