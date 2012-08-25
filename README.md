# // objective-c design by contract

the macros herein are based on a set of macros devised by [nicolas roard](http://roard.com) quite a while back.  i was mega-stoked when i came across them, but it turned out that they weren't ARC-compatible.  so i rewrote them and added a lil' flair of my own.

# how

there are four pseudo-keywords defined in `Contracts.h`:

- `@invariants`
- `@preconditions`
- `@postconditions`
- `@freeze`
- `frozen` (note that this one lacks that stylish ampersand... just couldn't get that going, unfortunately)

### an example class implementation

a typical class implementation will look like this:

```objective-c
@implementation MyClass

@invariants (
  _yungWeezy != nil,
  _flavaFlav > 7,
  [_compton shouldntBeMessedWith] == YES
)

// ...

@end
```

note the `@invariants ( ... )` block, which for stylistic purposes ought to go at the top of your `@implementation` section.  you can simply provide a list of comma-separated expressions that evaluate to a boolean, and these will be checked a bunch automatically as you call methods on your class.


### an example method implementation

your methods will need to look something like this:

```objective-c
- (NSUInteger) recalculateNumberOfProblems:(BOOL)aBitchIsOne
                               newProblems:(NSArray *)newProblems {
  @preconditions (
    _money > 0,
    _problems != nil,
    _problems.count > 0,
    (newProblems != nil
        ? newProblems.count > 0
        : YES /* pass-through */ )
  )

  @freeze(_money, _problems)
  @postconditions(
    (aBitchIsOne
        ? self.money == 0
        : self.money < [frozen(_money) unsignedIntegerValue]),

    (newProblems != nil
        ? self.problems.count > [frozen(_problems) count]
        : self.problems.count == [frozen(_problems) count])
  )

  /** begin method body **/
  if (newProblems != nil) {
    [self.problems addObjectsFromArray:newProblems];
    self.money = [self recalculateMoney];
  }

  if (aBitchIsOne) {
    self.money = 0;
  }

  return (self.money * kMoneyProblemsMultiplier) + (aBitchIsOne ? 1 : 0);
}
```

a few things to take note of here:

- `@freeze` stores the value of a property/ivar on the object so that you can write postconditions about how it should've changed during the execution of the method body.
- `@freeze`'s internal machinery uses key/value stuff to store these values, so any scalar value is going to get encoded as an Objective-C object.  that's why you see `[frozen(_money) unsignedIntegerValue]` instead of just `frozen(_money)`.
- i'm pretty sure it's a good idea to use `self.x` in your `@postconditions` block rather than simply `_x`.  why?  because `@postconditions` defines an Objective-C block that gets executed upon leaving the method's scope.  i can't recall the specifics of how blocks copy the values of properties/ivars referenced in their block bodies, but just in case they copy the actual ivars instead of taking an automatic, silent reference to `self`, it'd be a good idea to reference the ivar via `self`.  otherwise, the copy of the ivar/property that the `@postconditions` block has access to will be from the very beginning of the method's execution, where `@postconditions` is defined, rather than the value upon exiting the method.


# authors & contributors

- bryn austin bellomy < <bryn.bellomy@gmail.com> >
- nicolas roard < <nicolas@roard.com> >

# license (MIT)

Copyright (c) 2012 bryn austin bellomy, robot bubble bath LLC ([robotbubblebath.com](http://robotbubblebath.com))

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
