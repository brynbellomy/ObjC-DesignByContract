#import <Foundation/Foundation.h>

@interface Account : NSObject
{
	NSMutableArray* AllDeposits;
	int balance; // current balance
}
- (int) depositCount; // number of deposits made since opening
- (void) deposit: (int) sum; // add sum to the 
- (int) balance;
@end
