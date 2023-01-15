#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "program.hpp"


class MockParser : public ParserInterface {
public:
    MOCK_METHOD(std::unique_ptr<GrammarRule>, parse, (const std::string& request), (override));
};


class MockInterpreter : public InterpreterInterface {
public:
    MOCK_METHOD(void, execute, (Assignment& assignment), (override));
    MOCK_METHOD(void, execute, (Pipe& assignment), (override));
    MOCK_METHOD(void, execute, (SelfProcessCommand& buildInCommand), (override));
};


TEST(ProgramTest, TestParsesProperString) {
    MockParser parser;
    MockInterpreter interpreter;
    auto program = Program(parser, interpreter);
    std::string parseable_string = "this is some command";

    EXPECT_CALL(parser, parse(parseable_string)).Times(1);
    program.execute(parseable_string);
}
