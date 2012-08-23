//
//  YAccount.m
//  contract-demo
//
//  Created by bryn austin bellomy on 8.20.12.
//  Copyright (c) 2012 robot bubble bath LLC. All rights reserved.
//

#import "YAccount.h"
#import "Contracts.h"


@implementation YAccount

@invariants (
  self.allDeposits != nil,
  self.balance >= 0
)



- (id) init {
  self = [super init];
  if (self) {
    _allDeposits = [NSMutableArray array];
  }
  return self;
}



- (NSUInteger) depositCount {
  @preconditions()
  @postconditions()
  
  return self.allDeposits.count;
}



- (NSUInteger) deposit: (NSUInteger) sum {
  @preconditions (
    sum >= 0
  )
  
  @freeze(_allDeposits, _balance)
  @postconditions (
    _allDeposits.count == [frozen(_allDeposits) count] + 1,
    _balance == [frozen(_balance) intValue] + sum + 1 // this postcondition is meant to fail
  )
  
  [self.allDeposits addObject: @(sum)];
  self.balance += sum;
  
  return self.balance;
}

@end






