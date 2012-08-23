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


#define contract_assert(TEST) if (!(TEST)) { \
	BrynLog (XCODE_COLORS_FG(255, 0, 0) @">>> ERROR ON ASSERT : \"%s\" is false (l. %d file %s)" XCODE_COLORS_RESET, #TEST, __LINE__, __FILE__); \
	if (CONTRACTS_CURRENT_STATE == 1) \
		BrynLog (XCODE_COLORS_FG(255, 0, 0) @"+++ Problem occurred while veryfing preconditions of method \"%@\"" XCODE_COLORS_RESET, CONTRACTS_CURRENT_METHOD); \
	if (CONTRACTS_CURRENT_STATE == 2) \
		BrynLog (XCODE_COLORS_FG(255, 0, 0) @"+++ Problem occurred while veryfing postconditions of method \"%@\"" XCODE_COLORS_RESET, CONTRACTS_CURRENT_METHOD); \
	if (CONTRACTS_CURRENT_STATE == 3) \
		BrynLog (XCODE_COLORS_FG(255, 0, 0) @"+++ Problem occurred while veryfing invariants in method \"%@\"" XCODE_COLORS_RESET, CONTRACTS_CURRENT_METHOD); \
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
    BrynLog(XCODE_COLORS_FG(0, 255, 0) @"Invariants OK" XCODE_COLORS_RESET); \
  }


#define preconditions(...) \
  try {} @finally {} \
  CONTRACTS_CURRENT_STATE = 1; \
  CONTRACTS_CURRENT_METHOD = NSStringFromSelector (_cmd); \
  metamacro_if_eq(1, metamacro_argcount(xyzzy, ## __VA_ARGS__)) \
    () \
    (metamacro_foreach(contract_assert_iter, , __VA_ARGS__)) \
  ; \
  BrynLog(XCODE_COLORS_FG(0, 255, 0) @"Preconditions OK for [%@]" XCODE_COLORS_RESET, CONTRACTS_CURRENT_METHOD); \
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
    BrynLog(XCODE_COLORS_FG(0, 255, 0) @"Postconditions OK for [%@]" XCODE_COLORS_RESET, CONTRACTS_CURRENT_METHOD); \
  };




#define freeze(...) \
  try{} @finally{} \
  NSArray *keys = [@#__VA_ARGS__ componentsSeparatedByString:@", "]; \
  NSMutableDictionary* __OLD_DATA_VALUES__ = nil; \
  if (keys.count == 1 && keys[0] == @"") __OLD_DATA_VALUES__ = nil; \
  else { \
    NSMutableDictionary *temp = [[self dictionaryWithValuesForKeys:keys] mutableCopy]; \
    __OLD_DATA_VALUES__ = [NSMutableDictionary dictionary]; \
    for (id key in temp) { \
      __OLD_DATA_VALUES__[ key ] = [temp[ key ] copy]; \
    } \
  }

#define frozen(variable) \
  __OLD_DATA_VALUES__[ @#variable ]
//  try {} @finally {} \


NSString* CONTRACTS_CURRENT_METHOD;
static int CONTRACTS_CURRENT_STATE;

@interface NSObject (CONTRACT) 
	- (void) CONTRACT__invariants;
@end 
@implementation NSObject (CONTRACT) 
	- (void) CONTRACT__invariants {}
@end 



//#define BEGIN_CONTRACT(name) \
//extern NSString* CONTRACTS_CURRENT_METHOD; \
//extern int CONTRACTS_CURRENT_STATE; \
//@interface name (name ## Contract) \
//- (void) invariants; \
//@end \
//@implementation name (name ## Contract) \
//- (void) invariants { \
//[super invariants]; } \
//@end \
//@interface name ## Contract : name {} \
//- (void) invariants; \
//@end \
//@implementation name ## Contract


//#define END_CONTRACT 	     @end

//#define APPLY_CONTRACT(name) \
//		[name ## Contract poseAsClass: [name class]];
//performSelector:@selector(poseAsClass:) withObject:[name class]];
//poseAsClass: [name class]];


//#define ContractWithReturn(code) \
//  { \
//    NSMutableDictionary* __OLD_DATA_VALUES__ = [NSMutableDictionary new]; \
//    CONTRACTS_CURRENT_METHOD = NSStringFromSelector (_cmd); \
//    [self invariants]; \
//    code; \
//    [self invariants]; \
//    return __RETURN_VALUE__; \
//  }
//
//#define Contract(code) \
//    NSMutableDictionary* __OLD_DATA_VALUES__ = [NSMutableDictionary new]; \
//    CONTRACTS_CURRENT_METHOD = NSStringFromSelector (_cmd); \
//    [self invariants]; \
//    code; \
//    [self invariants];
//[self trackValues:__VA_ARGS__, nil];

//#define VERIFY(selectorName, code) CONTRACT__##selectorName  { \
//NSMutableDictionary* __OLD_DATA_VALUES__ = [NSMutableDictionary new]; \
//CONTRACTS_CURRENT_METHOD = NSStringFromSelector (_cmd); \
//[self invariants]; \
//code; \
//[self invariants]; \
//return __RETURN_VALUE__; \
//}
//
//#define VERIFY_PROC(selectorName, code) CONTRACT__##selectorName { \
//NSMutableDictionary* __OLD_DATA_VALUES__ = [NSMutableDictionary new]; \
//CONTRACTS_CURRENT_METHOD = NSStringFromSelector (_cmd); \
//[self invariants]; \
//code; \
//[self invariants]; \
//NSLog(@"%d", __OLD_DATA_VALUES__.count); \
//}




