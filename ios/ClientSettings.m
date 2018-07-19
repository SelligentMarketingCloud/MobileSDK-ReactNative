#import "ClientSettings.h"
#import "LogLevel.h"
#import "ParsableObject.h"

@interface ClientSettings()

@property (nonatomic, strong) NSString *url;
@property (nonatomic, strong) NSString *clientId;
@property (nonatomic, strong) NSString *privateKey;
@property (nonatomic, strong) NSNumber *shouldClearBadge;
@property (nonatomic, strong) NSNumber *shouldDisplayRemoteNotification;
@property (nonatomic, strong) NSNumber *configureLocationServices;
@property (nonatomic, strong) NSNumber *clearCacheIntervalValue;
@property (nonatomic, strong) InAppMessageSettings *inAppMessageSettings;

@end

@implementation ClientSettings

+ (instancetype)fromDictionary:(NSDictionary *)dictionary {
    ClientSettings *clientSettings = [[ClientSettings alloc] init];
    clientSettings.url = dictionary[@"url"];
    clientSettings.clientId = dictionary[@"clientId"];
    clientSettings.privateKey = dictionary[@"privateKey"];
    clientSettings.shouldClearBadge = dictionary[@"shouldClearBadge"];
    clientSettings.shouldDisplayRemoteNotification = dictionary[@"shouldDisplayRemoteNotification"];
    clientSettings.configureLocationServices = dictionary[@"configureLocationServices"];
    clientSettings.clearCacheIntervalValue = dictionary[@"clearCacheIntervalValue"];
    clientSettings.inAppMessageSettings = [InAppMessageSettings fromDictionary:dictionary];
    return clientSettings;
}

@end
