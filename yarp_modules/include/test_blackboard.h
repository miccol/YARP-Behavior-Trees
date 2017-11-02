
#pragma once
#include <blackboard.h>
#include <iostream>
#include <stdio.h>
#include <rtf/TestCase.h>
#include <rtf/TestResult.h>
#include <rtf/TestResultCollector.h>
#include <rtf/ConsoleListener.h>
#include <rtf/TestAssert.h>

#include <rtf/dll/Plugin.h>
#include <rtf/TestAssert.h>
#include <rtf/TestCase.h>


using namespace RTF;


class BlackBoardTest : public TestCase {
public:
    BlackBoardTest();
    virtual ~BlackBoardTest();
    virtual bool setup(int argc, char **argv);
    virtual void tearDown();
    virtual void run();
};
