#import "Event.h"

@interface Event()

@property (nonatomic) EventType type;
@property (nonatomic, strong) NSString *email;
@property (nonatomic, strong) NSDictionary *data;
@property (nonatomic) BOOL shouldCache;

@end

@implementation Event

+ (instancetype)fromDictionary:(NSDictionary *)dictionary{
    Event *event = [[Event alloc] init];
    EventType type = (EventType) [dictionary[@"type"] integerValue];
    event.type = type;
    event.email = dictionary[@"email"];
    event.data = dictionary[@"data"];
    event.shouldCache = [dictionary[@"shouldCache"] boolValue];
    return event;
}

@end
