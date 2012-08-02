#import <Foundation/Foundation.h>

#define FACT(TEST) if (!(TEST)) { \
	NSLog (@">>> ERROR ON ASSERT : \"%s\" is false (l. %d file %s)", #TEST, __LINE__, __FILE__); \
	if (CONTRACTS_CURRENT_STATE == 1) \
		NSLog (@"+++ Problem occurred while veryfing preconditions of method \"%@\"", CONTRACTS_CURRENT_METHOD); \
	if (CONTRACTS_CURRENT_STATE == 2) \
		NSLog (@"+++ Problem occurred while veryfing postconditions of method \"%@\"", CONTRACTS_CURRENT_METHOD); \
	if (CONTRACTS_CURRENT_STATE == 3) \
		NSLog (@"+++ Problem occurred while veryfing invariants in method \"%@\"", CONTRACTS_CURRENT_METHOD); \
	exit (-2); \
	}

#define FACT_MSG(TEST,MSG) if (!(TEST)) { \
	NSLog (@">>> ERROR ON FACT : \"%s\" is false (l. %d file %s)", #TEST, __LINE__, __FILE__); \
	NSLog (@"+++ Reason : %s", MSG); \
	if (CONTRACTS_CURRENT_STATE == 1) \
		NSLog (@"+++ Problem occurred while veryfing preconditions of method \"%@\"", CONTRACTS_CURRENT_METHOD); \
	if (CONTRACTS_CURRENT_STATE == 2) \
		NSLog (@"+++ Problem occurred while veryfing postconditions of method \"%@\"", CONTRACTS_CURRENT_METHOD); \
	if (CONTRACTS_CURRENT_STATE == 3) \
		NSLog (@"+++ Problem occurred while veryfing invariants in method \"%@\"", CONTRACTS_CURRENT_METHOD); \
	exit (-2); \
	}

#define INVARIANTS(asserts) \
	- (void) invariants { \
		CONTRACTS_CURRENT_STATE = 3; \
		[super invariants]; \
		asserts;\
	}

#define REQUIRE(asserts) \
	CONTRACTS_CURRENT_STATE = 1; \
	asserts;
#define ENSURE(asserts) \
	CONTRACTS_CURRENT_STATE = 2; \
	asserts;

#define BEGIN_CONTRACT(name) \
extern NSString* CONTRACTS_CURRENT_METHOD; \
extern int CONTRACTS_CURRENT_STATE; \
	@interface name (name ## Contract) \
		- (void) invariants; \
	@end \
	@implementation name (name ## Contract) \
		- (void) invariants { \
			[super invariants]; } \
	@end \
	@interface name ## Contract : name {} \
	   	- (void) invariants; \
	@end \
	@implementation name ## Contract 

#define END_CONTRACT 	     @end	

#define APPLY_CONTRACT(name) \
		[name ## Contract poseAsClass: [name class]]; 

#define VERIFY(code) { \
	NSMutableDictionary* __OLD_DATA_VALUES__ = [NSMutableDictionary new]; \
	[CONTRACTS_CURRENT_METHOD release]; \
	CONTRACTS_CURRENT_METHOD = NSStringFromSelector (_cmd); \
	[self invariants]; \
	code; \
	[self invariants]; \
	[__OLD_DATA_VALUES__ release]; \
	return Result; \
}

#define VERIFY_PROC(code) { \
	NSMutableDictionary* __OLD_DATA_VALUES__ = [NSMutableDictionary new]; \
	[CONTRACTS_CURRENT_METHOD release]; \
	CONTRACTS_CURRENT_METHOD = NSStringFromSelector (_cmd); \
	[self invariants]; \
	code; \
	[self invariants]; \
	[__OLD_DATA_VALUES__ release]; \
}

#define ROLE(msg) // Role : msg 
#define RETURN(msg) // Return : msg 
#define MODIFY(variable) [__OLD_DATA_VALUES__ setObject: [[self valueForKey: @#variable] copy] forKey: @#variable];
#define CODE(method) [super method]
#define NAME(msg) // Name : msg
#define OLD(variable) [__OLD_DATA_VALUES__ valueForKey: @#variable]

NSString* CONTRACTS_CURRENT_METHOD;
static int CONTRACTS_CURRENT_STATE;

@interface NSObject (CONTRACT) 
	- (void) invariants; 
@end 
@implementation NSObject (CONTRACT) 
	- (void) invariants {} 
@end 
