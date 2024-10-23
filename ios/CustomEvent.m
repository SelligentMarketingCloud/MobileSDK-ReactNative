#import "CustomEvent.h"

@implementation CustomEvent

+ (instancetype) eventWithData:(NSDictionary*)data AndName:(NSString*)name AndType:(NSString*)type {
  return [[self alloc] initWithData:data AndName:name AndType: type];
}

- (instancetype) initWithData:(NSDictionary*)data AndName:(NSString*)name AndType:(NSString*)type {
  self = [super init];
  self.data = data;
  self.type = type;
  self.name = name;
    
  return self;
}

@end
