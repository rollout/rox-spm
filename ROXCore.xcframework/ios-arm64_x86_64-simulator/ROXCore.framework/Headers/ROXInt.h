//
//  ROXInt.h
//  ROX
//
//  Created by Elad Cohen on 23/12/2019.
//  Copyright © 2019 DeDoCo. All rights reserved.
//

#import <ROXCore/ROXCore.h>
#import "ROXDynamicPropertiesRule.h"

NS_ASSUME_NONNULL_BEGIN

@interface ROXInt : ROXString

/**
 Forces the flag to return the specified value. This overrides any other evaluated value (for example, from an experiment, view controller, or default), and can only be changed by calling `forceValue:` again with a new value.
 
 @param value to force the sdk with
 */

- (void)forceValue:(int)value;

- (int)value;

- (int)value:(ROXDynamicPropertyContext* _Nullable)context;

- (instancetype)initWithDefault:(int)defaultValue;

- (instancetype)initWithDefault:(int)defaultValue variations:(nonnull NSArray<NSNumber*> *)variations;

- (instancetype)initWithDefault:(int)defaultValue variations:(nonnull NSArray<NSNumber *> *)variations freeze:(ROXFreeze)freeze;

@end

NS_ASSUME_NONNULL_END
