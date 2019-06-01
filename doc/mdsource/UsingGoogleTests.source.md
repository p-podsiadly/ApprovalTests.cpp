<a id="top"></a>

# Using Approval Tests With Google Tests

<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Contents**

- [Getting Started With Google Test](#getting-started-with-google-test)
  - [Starter Project](#starter-project)
  - [New Project](#new-project)
  - [Existing Project - no main()](#existing-project---no-main)
  - [Existing Project - with your main()](#existing-project---with-your-main)
- [Customizing Google Tests Approval File Names](#customizing-google-tests-approval-file-names)
  - [Customizing](#customizing)
    - [Custom Suffixes](#custom-suffixes)
    - [Custom Anything](#custom-anything)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->


## Getting Started With Google Test

The [Google Test](https://github.com/google/googletest) test framework works well with Approval Tests.

This section describes the various ways of using Approval Tests with Google Test.

### Starter Project

We haven't yet provided a Starter Project for using Approval Tests with Google Tests.

This is partly based on the assumption that anyone already using Google Tests will have their own project set up, and anyone else would probably use Catch 2 instead.
 
If it would be helpful for us to such a Starter Project, please let us know, via the contact details in [Contributing to ApprovalTests.cpp](/doc/Contributing.md#top). 


### New Project

Create a file `main.cpp` and add just the following two lines:

snippet: googletest_main

### Existing Project - no main()

Google Test has a `gtest_main` library that provides a `main()` function, and then runs all your tests.

If your existing Google Test application uses the `gtest_main` library, Approval Tests will not be able to obtain the names to use output files. You will then see the help message shown in [Troubleshooting](/doc/Troubleshooting.md#top).

To fix this, please add a new `main.cpp`, as shown in the previous section.


### Existing Project - with your main()

If you have an existing Google Test-based test program that provides its own `main()`, you won't be able to use the approach above.

Instead, you should make the following additions to your own source file that contains `main()`.  

snippet: googletest_existing_main

## Customizing Google Tests Approval File Names

Most testing frameworks have two pieces of naming information: `SourceFileName` and `test_name`.

Google Tests has an additional piece of information: `test_case_name`.
 
snippet: googletest_name_parts

With Google Tests, this will result in Approvals creating output files beginning with: 
`SourceFileName.test_case_name.test_name`

Very often, the `SourceFileName` and the `test_case_name` are redundant, meaning that what you would like is `SourceFileName.test_case_name.test_name`

By default, Approval Tests will do this if `test_case_name` is completely contained within `SourceFileName`, meaning it is a sub-string.

### Customizing

If this is not enough, Approvals allows for customisation, in two ways.

**Note:** to be able to add these pieces of code outside of a function, you need to hold on to the result as a variable. This variable is not used, it is only there to allow the method to execute.

**Note:** using these customisations inside a Google `TEST` or `TEST_F`, is too late for that test: they won't take effect until the next executed test.

#### Custom Suffixes

For example, if you are Google test fixtures, you might have a lot of class names of the format `TestClassNameFixture`. You can tell Approval Tests that these are the same by adding the following to your main:

snippet: googletest_customize_suffix

#### Custom Anything

If you have something more unique, you can write a function that will match if the test case name and the source file names should be considered equal.

For example, let's say you want a special tag `IgnoreThis` to indicate a that a TestCaseName should be ignored, when determining the names of output files.

So:

snippet: googletest_customize_test

Would produce an output file beginning with:

snippet: googletest_customize_test_name

You could achieve this by registering a function pointer like this:

Or by using a lambda like this:

snippet: googletest_customize_lambda 


---

[Back to User Guide](/doc/README.md#top)