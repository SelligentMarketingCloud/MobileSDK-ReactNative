#import <Foundation/Foundation.h>
#import "ParsableObject.h"
#import "EventType.h"

@interface Event : NSObject<ParsebleObject>

@property (nonatomic, readonly) EventType type;
@property (nonatomic, strong, readonly) NSString *email;
@property (nonatomic, strong, readonly) NSDictionary *data;
@property (nonatomic, readonly) BOOL shouldCache;

@end
