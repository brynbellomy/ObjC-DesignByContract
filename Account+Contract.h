#import "Contracts.h"
#import "Account.h"

BEGIN_CONTRACT (Account)

	INVARIANTS (
		FACT (AllDeposits != nil);
		FACT (balance >= 0);
	)

	- (int) depositCount VERIFY ( 
		int Result = [super depositCount]; // call the method
	)

	- (void) deposit: (int) sum VERIFY_PROC (
		NSLog (@"deposit %d", sum);
		REQUIRE (
			FACT (sum >= 0);
		)
		MODIFY (AllDeposits);
		MODIFY (balance);
		[super deposit: sum]; // call the method
		ENSURE (
			NSLog (@"Alldeposits count: %d", [AllDeposits count]);
			NSLog (@"OLD Alldeposits count: %d", [OLD(AllDeposits) count]);
			FACT ([AllDeposits count] == [OLD(AllDeposits) count] + 1);
			FACT (balance == [OLD (balance) intValue]+ sum);
		)
	)

END_CONTRACT
