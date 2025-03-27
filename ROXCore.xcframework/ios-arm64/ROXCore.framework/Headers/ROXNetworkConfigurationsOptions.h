//
//  RoxNetworkConfigurationsOptions.h
//  ROX
//
//  Created by asaf meir on 02/03/2023.
//  Copyright © 2023 DeDoCo. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ROXNetworkConfigurationsOptions : NSObject <NSCopying>

@property (nonatomic, copy) NSString * _Nullable getConfigApiEndpoint;

@property (nonatomic, copy) NSString * _Nullable getConfigCloudEndpoint;

@property (nonatomic, copy) NSString * _Nullable sendStateApiEndpoint;

@property (nonatomic, copy) NSString * _Nullable sendStateCloudEndpoint;

@property (nonatomic, copy) NSString * _Nullable analyticsEndpoint;

@property (nonatomic, copy) NSString * _Nullable pushNotificationEndpoint;

@end
