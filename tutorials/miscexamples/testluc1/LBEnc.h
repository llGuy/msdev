//
//  LBEnc.h
//  testluc1
//
//  Created by Brice Rosenzweig on 06/06/2017.
//  Copyright © 2017 Brice Rosenzweig. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef  unsigned char unchar_t;


@interface LBEnc : NSObject

// NSString * decode(unchar_t*p, size_t n);
-(NSString*)decode:(unchar_t*)p size:(size_t)n;

@end
