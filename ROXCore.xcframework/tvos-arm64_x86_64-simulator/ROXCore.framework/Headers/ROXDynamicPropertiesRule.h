//
//  ROXDynamicPropertiesRule.h
//  ROX
//
//  Created by Andrew Anisimov on 10.06.2021.
//  Copyright © 2021 DeDoCo. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NSObject* _Nullable (^ROXDynamicPropertyContext)(NSString* _Nonnull propName);
typedef NSObject* _Nullable (^ROXDynamicPropertiesRule)(NSString* _Nonnull propName, ROXDynamicPropertyContext _Nonnull context);
