/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

bool suite_BreakoutTestSuite_init = false;
#include "C:\Users\jongo\CS4850\project-breakout-breakout-milestone1\test\Breakout.cxxtest.hpp"

static BreakoutTestSuite suite_BreakoutTestSuite;

static CxxTest::List Tests_BreakoutTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_BreakoutTestSuite( "test/Breakout.cxxtest.hpp", 8, "BreakoutTestSuite", suite_BreakoutTestSuite, Tests_BreakoutTestSuite );

static class TestDescription_suite_BreakoutTestSuite_testBlockManager : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_BreakoutTestSuite_testBlockManager() : CxxTest::RealTestDescription( Tests_BreakoutTestSuite, suiteDescription_BreakoutTestSuite, 20, "testBlockManager" ) {}
 void runTest() { suite_BreakoutTestSuite.testBlockManager(); }
} testDescription_suite_BreakoutTestSuite_testBlockManager;

static class TestDescription_suite_BreakoutTestSuite_testGameStateManager : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_BreakoutTestSuite_testGameStateManager() : CxxTest::RealTestDescription( Tests_BreakoutTestSuite, suiteDescription_BreakoutTestSuite, 40, "testGameStateManager" ) {}
 void runTest() { suite_BreakoutTestSuite.testGameStateManager(); }
} testDescription_suite_BreakoutTestSuite_testGameStateManager;

static class TestDescription_suite_BreakoutTestSuite_testBall : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_BreakoutTestSuite_testBall() : CxxTest::RealTestDescription( Tests_BreakoutTestSuite, suiteDescription_BreakoutTestSuite, 60, "testBall" ) {}
 void runTest() { suite_BreakoutTestSuite.testBall(); }
} testDescription_suite_BreakoutTestSuite_testBall;

