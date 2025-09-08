//
//  ROXCore SDK version {{lib_version}}, Build {{build}}
//
//  Copyright (c) 2017 rollout.io. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "ROXOptions.h"
#import "ROXFlag.h"
#import "ROXInt.h"
#import "ROXDouble.h"
#import "ROXBaseContainer.h"
#import "ROXString.h"
#import "ROXFreeze.h"
#import "ROXFetcherResult.h"
#import "ROXReportingValue.h"
#import "ROXFlagsOverrides.h"
#import "ROXErrorHandling.h"
#import "ROXDynamicAPI.h"
#import "ROXDynamicPropertiesRule.h"

#define ROX ROXCore

typedef NS_ENUM(NSUInteger, ROXCoreState) {
    ROXCoreState_Idle = 0,
    ROXCoreState_SettingUp,
    ROXCoreState_Set,
    ROXCoreState_ShuttingDown,
    ROXCoreState_Corrupted
};

/**
 `ROXCore` class is an objc class that acts as a facade interface for the ROX SDK
 - You use this class for the following:
 
    - Initialize ROX SDK using `+setupWithKey:` (legacy singleton mode)
    - Create new ROX SDK instances using `+instanceWithSDKKey:` (multi-instance mode)
    - Register container instances using `+register:` or `-registerContainer:withNamespace:`
    - Load custom properties with `setCustomPropertyKey:value: methods`
    - Present the flags view controller with `+flagsViewController`

 
 */
@interface ROXCore : NSObject

/**
 * The SDK key associated with this `ROXCore` instance.
 */
@property (nonatomic, readonly) NSString *sdkKey;

/**
 * Creates a new `ROXCore` instance for the given `sdkKey` or returns an existing one.
 *
 * @param sdkKey The SDK key to associate with this instance
 * @return A `ROXCore` instance associated with the given `sdkKey`.
 */
+ (instancetype)instanceWithSDKKey:(NSString *)sdkKey;


/**
 * Returns the current SDK key being used by the singleton instance.
 * This is used for backward compatibility with the legacy singleton pattern.
 *
 * @return The current `sdkKey` or `nil` if no instance has been initialized.
 */
+ (NSString *)currentSDKKey;

/**
 * Initializes a new `ROXCore` instance with the given SDK key.
 *
 * @param sdkKey The SDK key to associate with this instance
 * @return A new `ROXCore` instance.
 */
- (instancetype)initWithSDKKey:(NSString *)sdkKey;

/**
 * Sets up this `ROXCore` instance with the given options.
 *
 * @param options The options to use for setup
 * @param platformVersion The platform version (e.g., "iOS", "Swift")
 * @param languageVersion The language version (e.g., "1.0.0")
 */
- (void)setupWithOptions:(ROXOptions *)options platformVersion:(NSString *)platformVersion languageVersion:(NSString *)languageVersion;

/**
 * Sets up this `ROXCore` instance with the given options.
 * Uses default platform and language versions.
 *
 * @param options The options to use for setup
 */
- (void)setupWithOptions:(ROXOptions *)options;

/**
 * Sets up this ROXCore instance with the given options and version information.
 * Uses the SDK key that was set during initialization.
 *
 * @param options The options to use for setup.
 * @param platformVersion The platform version.
 * @param languageVersion The language version.
 */
- (void)setupInstance:(ROXOptions * _Nonnull)options platformVersion:(NSString* _Nullable)platformVersion languageVersion:(NSString* _Nullable)languageVersion NS_SWIFT_NAME(setupInstance(options:platformVersion:languageVersion:));

/**
 * Sets a variant for the given key in this instance's repository.
 *
 * @param variant The variant to set
 * @param key The key to associate with the variant
 */
- (void)setVariant:(ROXString *)variant forKey:(NSString *)key;

/**
 * Registers a container with this `ROXCore` instance.
 *
 * @param container The container to register
 * @param namespace The namespace to register the container with
 */
- (void)registerContainer:(id)container withNamespace:(NSString *)namespace;

/**
 * Fetches the latest configuration for this ROXCore instance.
 */
- (void)fetch;

/**
 * Sets a custom string property for this `ROXCore` instance.
 *
 * @param value The string value
 * @param key The property key
 */
- (void)setCustomStringProperty:(NSString *)value forKey:(NSString *)key;

/**
 * Sets a custom boolean property for this `ROXCore` instance.
 *
 * @param value The boolean value
 * @param key The property key
 */
- (void)setCustomBooleanProperty:(BOOL)value forKey:(NSString *)key;

/**
 * Sets a custom int property for this `ROXCore` instance.
 *
 * @param value The int value
 * @param key The property key
 */
- (void)setCustomIntProperty:(int)value forKey:(NSString *)key;

/**
 * Sets a custom double property for this `ROXCore` instance.
 *
 * @param value The double value
 * @param key The property key
 */
- (void)setCustomDoubleProperty:(double)value forKey:(NSString *)key;

/**
 * Shuts down this `ROXCore` instance.
 */
- (void)shutdown;

/**
 Loads the SDK, usually called as part of `-[AppDelegate application:didFinishLaunchingWithOptions:]`
 
 Checks if a cached experimentation container exists, and loads a container.
 
 Executes an async network call to fetch the experiment container from the ROX server and calculates experiments and target groups.
 
 @param roxKey The app key (taken from ROX dashboard)
 */
+(void)setupWithKey:(NSString* _Nonnull)roxKey;


+ (BOOL) isUUIDKey:(NSString* _Nonnull)key;
/**
 Loads the SDK, usually called as part of `-[AppDelegate application:didFinishLaunchingWithOptions:]`
 
 Checks if a cached experimentation container exists, and loads a container.
 
 Executes an async network call to fetch the experiment container from the ROX server and calculates experiments and target groups.
 
 @param roxKey The app key (taken from ROX dashboard)
 @param options setup options
 */
+(void)setupWithKey:(NSString * _Nonnull)roxKey options:(ROXOptions * _Nonnull)options;

+(void)setupWithKey:(NSString * _Nonnull)roxKey options:(ROXOptions * _Nonnull)options platformVersion:(NSString* _Nullable)platformVersion languageVersion:(NSString* _Nullable)languageVersion;

+(ROXCoreState)state;

+(void)shutdown;

/**
 Register a container instance to the ROX system.
 - @param namespace The namespace to register the container with (all flags/configuration will be prefixed with the namespace).
 - @param container The instance to register, this instance's values are fetched at `+setupWithKey:`, or when the app goes into foreground.
 - @note This method should be called **only once** for a given namespace.
 */
+(void) register:(NSString * _Nonnull)namespace container:(ROXBaseContainer * _Nonnull)container;

/**
  Register a container in the default namespace.
 */
+(void) register:(ROXBaseContainer * _Nonnull)container;

+(void) handleNamespace:(NSString * _Nonnull)namespace;

/**
 Unfreeze the state of all flags in code
 
 When a flag is accessed in code, its value is frozen in the app until the next time the app enters the foreground. Calling this function unfreezes all flags, so subsequent evaluations return the most up-to-date values.
 
 @see [Flags Consistency](https://support.rollout.io/docs/flags-consistency)
 
 */
+(void) unfreeze;
+(void) unfreezeNamespace:(NSString* _Nonnull)ns;

/**
 A view to control feature flags values locally on a mobile device or simulator.
 
 ROX ViewController allows developers, QA, or internal employees (depending on policy) to view, disable, enable, and reset the state of their flags locally on the device. The functions return a view controller that can be loaded into the view hierarchy for test devices upon shake, or by triggering an existing debug view in the app.
 
 @see [How to set up flagsviewController](https://support.rollout.io/docs/flags-override-view).
 
 @return A `UViewController` which shows the local feature flags and provides an interface to turn them on or off.
 */
+ (UIViewController* _Nonnull)flagsViewController;

/**
 Sets a custom property value that can be used when creating target groups.
 
 @see [Creating a target group](https://support.rollout.io/docs/creating-target-groups)
 
 @param key The name of the custom property
 @param value The value of the custom property
 
 */
+(void) setCustomStringProperty:(NSString* _Nonnull)value forKey:(NSString* _Nonnull)key;

/**
 Sets a custom property value that can be used when creating target groups.
 
 @see [Creating a target group](https://support.rollout.io/docs/creating-target-groups)
 
 @param key  The name of the custom property
 @param block This block will get invoked when trying to evaluate the value of the property.
 
 */
+(void) setCustomComputedStringProperty:(NSString* _Nullable (^_Nonnull)(NSString* _Nonnull, ROXDynamicPropertyContext* _Nonnull))block forKey:(NSString* _Nonnull)key;

/**
 Sets a custom property value that can be used when creating target groups.
 
 @see [Creating a target group](https://support.rollout.io/docs/creating-target-groups)
 
 @param key The name of the custom property
 @param value The value of the custom property
 
 */
+(void) setCustomBooleanProperty:(BOOL)value forKey:(NSString*_Nonnull)key;

/**
 Sets a custom property value that can be used when creating target groups.
 
 @see [Creating a target group](https://support.rollout.io/docs/creating-target-groups)
 
 @param key  The name of the custom property
 @param block this block will get invoked when trying to evaluate the value of the property
 
 */
+(void) setCustomComputedBooleanProperty:(BOOL (^_Nullable)(NSString* _Nullable, ROXDynamicPropertyContext* _Nonnull))block forKey:(NSString*_Nonnull)key;

/**
 Sets a custom property value that can be used when creating target groups.
 
 @see [Creating a target group](https://support.rollout.io/docs/creating-target-groups)
 
 @param key The name of the custom property
 @param value The value of the custom property
 
 */
+(void) setCustomIntProperty:(int)value forKey:(NSString* _Nullable)key;

/**
 Sets a custom property value that can be used when creating target groups.
 
 @see [Creating a target group](https://support.rollout.io/docs/creating-target-groups)
 
 @param key  The name of the custom property
 @param block this block will get invoked when trying to evaluate the value of the property
 
 */
+(void) setCustomComputedIntProperty:(int (^_Nonnull)(NSString* _Nonnull, ROXDynamicPropertyContext* _Nonnull))block forKey:(NSString*_Nonnull)key;

/**
 Sets a custom property value that can be used when creating target groups.
 
 @see [Creating a target group](https://support.rollout.io/docs/creating-target-groups)
 
 @param key The name of the custom property
 @param value The value of the custom property
 
 */
+(void) setCustomDoubleProperty:(double)value forKey:(NSString* _Nonnull)key;

/**
 Sets a custom property value that can be used when creating target groups.
 
 @see [Creating a target group](https://support.rollout.io/docs/creating-target-groups)
 
 @param key  The name of the custom property
 @param block this block will get invoked when trying to evaluate the value of the property
 
 */
+(void) setCustomComputedDoubleProperty:(double (^_Nonnull)(NSString* _Nonnull, ROXDynamicPropertyContext* _Nonnull))block forKey:(NSString*_Nonnull)key;

/**
 Sets a custom property value that can be used when creating target groups.
 
 @see [Creating a target group](https://support.rollout.io/docs/creating-target-groups)
 
 @param key The name of the custom property
 @param value The value of the custom property
 
 */
+(void) setCustomSemverProperty:(NSString*_Nonnull)value forKey:(NSString* _Nonnull)key;

/**
 Sets a custom property value that can be used when creating target groups.
 
 @see [Creating a target group](https://support.rollout.io/docs/creating-target-groups)
 
 @param key  The name of the custom property
 @param block this block will get invoked when trying to evaluate the value of the property
 
 */
+(void) setCustomComputedSemverProperty:(NSString* _Nullable (^_Nonnull)(NSString* _Nonnull, ROXDynamicPropertyContext* _Nonnull))block forKey:(NSString*_Nonnull)key;

/**
 @param key The name of the custom property
 @param value The value of the custom property
 
 */
+ (void)setCustomDateTimeProperty:(NSDate *_Nullable)value forKey:(NSString *_Nullable)key;
/**
 @param key  The name of the custom property
 @param block this block will get invoked when trying to evaluate the value of the property
 
 */
+ (void)setCustomComputedDateTimeProperty:(NSDate *_Nullable(^_Nullable)(NSString* _Nullable flagName, ROXDynamicPropertyContext* _Nullable context))block forKey:(NSString *_Nullable)key;

/**
  Sets a dynamic property context that will be used as a default for each flag evaluation.
 */
+(void) setGlobalDynamicPropertyContext:(ROXDynamicPropertyContext* _Nullable)context;

/**
 :nodoc:
 */
+(void) setVariant:(ROXString*_Nonnull)variant forKey:(NSString*_Nonnull)key;
/**
 :nodoc:
 */
+(ROXString*_Nullable) variantWithKey:(NSString*_Nonnull)key;

/**
 :nodoc:
 */
+(void)fetch;

+ (ROXFlagsOverrides*_Nonnull)overrides;
+ (ROXDynamicAPI*_Nonnull)dynamicAPI;
+ (NSArray<ROXString*>*_Nonnull)flags;

/**
 :nodoc:
 */
+(void)setUserspaceUnhandledErrorHandler:(ROXUserspaceUnhandledErrorHandler _Nonnull)handler;

@end

