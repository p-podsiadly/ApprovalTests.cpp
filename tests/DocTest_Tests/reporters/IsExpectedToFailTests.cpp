#include "doctest/doctest.h"
#include "ApprovalTests.hpp"
#include "FakeReporter.h"

using namespace ApprovalTests;

TEST_CASE("Reporter is not run when isExpectedToFail is set")
{
    TestInfo::getCurrent().isExpectedToFail = true;

    FakeReporter reporter;
    REQUIRE_THROWS_AS(Approvals::verify(21, reporter), ApprovalMismatchException);

    REQUIRE_FALSE(reporter.called);
}

TEST_CASE("isExpectedToFail is set to false")
{
    const auto& testInfo = TestInfo::getCurrent();

    REQUIRE_FALSE(testInfo.isExpectedToFail);
}

TEST_CASE("isExpectedToFail is set to true for \"should_fail\" tests" *
          doctest::should_fail())
{
    const auto& testInfo = TestInfo::getCurrent();

    if (testInfo.isExpectedToFail != true)
    {
        // Failing assert would be ignored
        std::abort();
    }

    FAIL("The test is marked as \"should_fail\" so it must contain this (failing) "
         "assertion");
}

TEST_CASE("isExpectedToFail is set to true for \"may_fail\" tests" * doctest::may_fail())
{
    const auto& testInfo = TestInfo::getCurrent();

    if (testInfo.isExpectedToFail != true)
    {
        // Failing assert would be ignored
        std::abort();
    }
}