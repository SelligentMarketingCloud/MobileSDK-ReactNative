#import <Foundation/Foundation.h>

@interface CustomEvent : NSObject

@property(nonatomic) NSString *_Nonnull name;
@property(nonatomic) NSString *_Nonnull type;
@property(nonatomic) NSDictionary *_Nullable data;

+ (instancetype _Nonnull) eventWithData:(NSDictionary*_Nullable)data AndName:(NSString*_Nonnull)name AndType:(NSString*_Nonnull)type;

@end
