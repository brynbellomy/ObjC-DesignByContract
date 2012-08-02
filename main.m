#import <Foundation/Foundation.h>
#import "Account.h"

#define __CONTRACTS__

#ifdef __CONTRACTS__
        #import "Contracts.h"
        #import "Account+Contract.h"
#else
        #define APPLY_CONTRACT(c)
#endif

int main (int argc, const char * argv[]) {

    	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];

        APPLY_CONTRACT (Account);

        id plop = [[Account alloc] init];

	NSLog (@"number of deposits : %d", [plop depositCount]);
	[plop deposit: 42];
	NSLog (@"number of deposits : %d", [plop depositCount]);
	
        [plop release];

    return 0;
}
