#import <Foundation/Foundation.h>
#import "ParsableObject.h"

@interface InAppMessageSettings : NSObject<ParsebleObject>

@property (nonatomic, strong, readonly) NSNumber *refreshType;
@property (nonatomic, strong, readonly) NSNumber *shouldPerformBackgroundFetch;

@end
