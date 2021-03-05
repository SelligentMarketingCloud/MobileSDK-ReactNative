#import <Foundation/Foundation.h>
#import "ParsableObject.h"
#import "InAppMessageSettings.h"

@interface ClientSettings : NSObject<ParsebleObject>

@property (nonatomic, strong, readonly) NSString *url;
@property (nonatomic, strong, readonly) NSString *clientId;
@property (nonatomic, strong, readonly) NSString *privateKey;
@property (nonatomic, strong, readonly) NSString *appGroupId;
@property (nonatomic, strong, readonly) NSNumber *shouldClearBadge;
@property (nonatomic, strong, readonly) NSNumber *shouldDisplayRemoteNotification;
@property (nonatomic, strong, readonly) NSNumber *configureLocationServices;
@property (nonatomic, strong, readonly) NSNumber *clearCacheIntervalValue;
@property (nonatomic, strong, readonly) InAppMessageSettings *inAppMessageSettings;

@end



