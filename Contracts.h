//
//  Contracts.h
//  ObjC-DesignByContract
//
//  Created by bryn austin bellomy on 8.20.12.
//  Based on code by Nicolas Roard ( http://www.roard.com/contracts ).
//  Copyright (c) 2012 robot bubble bath LLC. All rights reserved.
//

#import <objc/objc.h>
#import <Foundation/Foundation.h>
#import <BrynKit/Bryn.h>
#import "EXTScope.h"
#import "metamacros.h"


#define contract_assert(TEST) \
  if (!(TEST)) { \
	  BrynLog (COLOR_ERROR(@">>> ERROR ON ASSERT : \"%s\" is false "), #TEST); \
  	if (CONTRACTS_CURRENT_STATE == 1) \
  		BrynLog (COLOR_ERROR(@"+++ Problem occurred while veryfing preconditions of method ") @"[" COLOR_FUNC(@"%@") @"]", CONTRACTS_CURRENT_METHOD); \
  	if (CONTRACTS_CURRENT_STATE == 2) \
  		BrynLog (COLOR_ERROR(@"+++ Problem occurred while veryfing postconditions of method ") @"[" COLOR_FUNC(@"%@") @"]", CONTRACTS_CURRENT_METHOD); \
  	if (CONTRACTS_CURRENT_STATE == 3) \
  		BrynLog (COLOR_ERROR(@"+++ Problem occurred while veryfing invariants in method ") @"[" COLOR_FUNC(@"%@") @"]", CONTRACTS_CURRENT_METHOD); \
  	exit (-2); \
	}

#define contract_assert_iter(index, assertion) \
  contract_assert(assertion);

#define invariants(...) \
    class NSObject; \
	- (void) CONTRACT__invariants { \
		CONTRACTS_CURRENT_STATE = 3; \
		[super CONTRACT__invariants]; \
    metamacro_if_eq(1, metamacro_argcount(xyzzy, ## __VA_ARGS__)) \
      () \
      (metamacro_foreach(contract_assert_iter, , __VA_ARGS__)) \
    ; \
    BrynLog(COLOR_SUCCESS(@"Invariants OK"); \
  }


#define preconditions(...) \
  try {} @finally {} \
  CONTRACTS_CURRENT_STATE = 1; \
  CONTRACTS_CURRENT_METHOD = NSStringFromSelector (_cmd); \
  metamacro_if_eq(1, metamacro_argcount(xyzzy, ## __VA_ARGS__)) \
    () \
    (metamacro_foreach(contract_assert_iter, , __VA_ARGS__)) \
  ; \
  BrynLog(COLOR_SUCCESS(@"Preconditions OK for ") @"[" COLOR_FUNC(@"%@") @"]", CONTRACTS_CURRENT_METHOD); \
  [self CONTRACT__invariants]; \



#define postconditions(...) \
  try{} @finally{} \
  @onExit { \
    [self CONTRACT__invariants]; \
    CONTRACTS_CURRENT_STATE = 2; \
    metamacro_if_eq(1, metamacro_argcount(xyzzy, ## __VA_ARGS__)) \
      () \
      (metamacro_foreach(contract_assert_iter, , __VA_ARGS__)) \
    ; \
    BrynLog(COLOR_SUCCESS(@"Postconditions OK for ") @"[" COLOR_FUNC(@"%@") @"]", CONTRACTS_CURRENT_METHOD); \
  };



#define freeze(...) \
  try{} @finally{} \
  NSArray *keys = [@#__VA_ARGS__ componentsSeparatedByString:@", "]; \
  NSMutableDictionary* __CONTRACTS_FROZEN__ = nil; \
  if (keys.count == 1 && keys[0] == @"") __CONTRACTS_FROZEN__ = nil; \
  else { \
    NSDictionary *__CONTRACTS_FROZEN_TEMP__ = [self dictionaryWithValuesForKeys:keys]; \
    __CONTRACTS_FROZEN__ = [NSMutableDictionary dictionary]; \
    for (id key in __CONTRACTS_FROZEN_TEMP__) { \
      __CONTRACTS_FROZEN__[ key ] = [__CONTRACTS_FROZEN_TEMP__[ key ] copy]; \
    } \
  }

#define frozen(variable) \
  __CONTRACTS_FROZEN__[ @#variable ]
//  try {} @finally {} \


NSString* CONTRACTS_CURRENT_METHOD;
static int CONTRACTS_CURRENT_STATE;

@interface NSObject (CONTRACT) 
	- (void) CONTRACT__invariants;
@end 
@implementation NSObject (CONTRACT) 
	- (void) CONTRACT__invariants {}
@end 





