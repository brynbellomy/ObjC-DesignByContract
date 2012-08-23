//
//  YAccount.h
//  contract-demo
//
//  Created by bryn austin bellomy on 8.20.12.
//  Copyright (c) 2012 robot bubble bath LLC. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface YAccount : NSObject

@property (nonatomic, strong, readwrite) NSMutableArray *allDeposits;
@property (nonatomic, assign, readwrite) NSUInteger balance;

- (NSUInteger) deposit: (NSUInteger) sum;
- (NSUInteger) depositCount; // number of deposits made since opening

@end