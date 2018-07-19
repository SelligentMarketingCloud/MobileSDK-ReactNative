#import "InAppMessageSettings.h"

@interface InAppMessageSettings()

@property (nonatomic, strong) NSNumber *refreshType;
@property (nonatomic, strong) NSNumber *shouldPerformBackgroundFetch;

@end

@implementation InAppMessageSettings

+ (instancetype)fromDictionary:(NSDictionary *)dictionary {
    InAppMessageSettings *inAppMessageSettings = [[InAppMessageSettings alloc] init];
    inAppMessageSettings.shouldPerformBackgroundFetch = dictionary[@"shouldPerformBackgroundFetch"];
    inAppMessageSettings.refreshType = dictionary[@"inAppMessageRefreshType"];
    return inAppMessageSettings;
}

@end
