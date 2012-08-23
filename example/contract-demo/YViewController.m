//
//  YViewController.m
//  contract-demo
//
//  Created by bryn austin bellomy on 8.20.12.
//  Copyright (c) 2012 robot bubble bath LLC. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "YViewController.h"
#import "YAccount.h"

@interface YViewController ()
@end

@implementation YViewController

- (void)viewDidLoad
{
  [super viewDidLoad];
  
  YAccount *account = [[YAccount alloc] init];
  
	NSLog (@"number of deposits: %d", [account depositCount]);
	[account deposit: 42];
	NSLog (@"number of deposits: %d", [account depositCount]);
}

@end
