//
//  ROXFlag.h
//  ROX
//
//  Created by Elad Cohen on 3/19/17.
//  Copyright © 2017 DeDoCo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ROXString.h"

/**
 This class is the API for flags that are controlled by the ROX server. Flags are assigned to an experiment, and their value is based on the  experiment container.
 */

@interface ROXFlag : ROXString
NS_ASSUME_NONNULL_BEGIN
/**
 a property to indicate if the flag is enabled or disabled.
 */
@property (readonly, nonatomic) BOOL isEnabled;

- (BOOL)isEnabled:(ROXDynamicPropertyContext*)context;

/**
 Executes the given block if the flag is enabled.
 
 @param codeBlock The block to invoke(synchronously) when the flag is enabled.
 */
- (void)enabled:(void (^)(void))codeBlock;

- (void)enabled:(void (^)(void))codeBlock context:(ROXDynamicPropertyContext*)context;

/**
 Executes the given block if the flag is disabled.
 
 @param codeBlock The block to invoke (synchronously) when the flag is disabled.
 */
- (void)disabled:(void (^)(void))codeBlock;

- (void)disabled:(void (^)(void))codeBlock context:(ROXDynamicPropertyContext*)context;

/**
 Executes one of the provided blocks based on the current state of the flag.
 
 @param enabledCodeBlock will get invoked (synchronously) if flag is enabled
 @param disabledCodeBlock will get invoked (synchronously) if flag is disabled
 */

- (void)enabled:(void (^)(void))enabledCodeBlock disabled:(void (^)(void))disabledCodeBlock;

- (void)enabled:(void (^)(void))enabledCodeBlock disabled:(void (^)(void))disabledCodeBlock context:(ROXDynamicPropertyContext*)context;

/**
 Forces the flag to return the specified value. This overrides any other evaluated value (for example, from an experiment, view controller, or default), and can only be changed by calling `forceValue:` again with a new value.
 
 @param value to force the sdk with
 */

- (void)forceValue:(BOOL)value;

/**
 Initialize a flag with a default boolean value
 
 @param defaultValue a default value for this flag
 */

- (instancetype)initWithDefault:(BOOL)defaultValue;

- (instancetype)initWithDefault:(BOOL)defaultValue freeze:(ROXFreeze)freeze;

@end
NS_ASSUME_NONNULL_END
