#include "gtest/gtest.h"
#include "../main/AuthenticationService.h"

class StubProfileDao : public ProfileDao {
public:
    std::string getPassword(const std::string userName) override {
        return password;
    }
    std::string password;
};

class StubRsaTokenDao : public RsaTokenDao {
public:
    std::string getRandom(std::string userName) override {
        return token;
    }
    std::string token;
};

class MockLogger : public Logger {
public:
    void log(const std::string& message) override {
        msg = message;
    }
    std::string msg;
};

namespace {

    TEST(AuthenticationService, IsValid) {
        StubProfileDao* stubProfileDao = new StubProfileDao();
        stubProfileDao->password = "91";
        StubRsaTokenDao* stubRsaTokenDao = new StubRsaTokenDao();
        stubRsaTokenDao->token = "000000";
        MockLogger* mockLogger = new MockLogger();
        AuthenticationService target = AuthenticationService(stubProfileDao, stubRsaTokenDao, mockLogger);

        bool actual = target.isValid("joey", "91000000");

        ASSERT_TRUE(actual);

        delete stubProfileDao;
        delete stubRsaTokenDao;
        delete mockLogger;
    }

    TEST(AuthenticationService, IsNotValid) {
        StubProfileDao* stubProfileDao = new StubProfileDao();
        stubProfileDao->password = "91";
        StubRsaTokenDao* stubRsaTokenDao = new StubRsaTokenDao();
        stubRsaTokenDao->token = "123456";
        MockLogger* mockLogger = new MockLogger();
        AuthenticationService target = AuthenticationService(stubProfileDao, stubRsaTokenDao, mockLogger);

        bool actual = target.isValid("joey", "91000000");

        ASSERT_FALSE(actual);

        delete stubProfileDao;
        delete stubRsaTokenDao;
        delete mockLogger;
    }

    TEST(AuthenticationService, LogMessageWhenNotValid) {
        StubProfileDao* stubProfileDao = new StubProfileDao();
        stubProfileDao->password = "91";
        StubRsaTokenDao* stubRsaTokenDao = new StubRsaTokenDao();
        stubRsaTokenDao->token = "123456";
        MockLogger* mockLogger = new MockLogger();
        AuthenticationService target = AuthenticationService(stubProfileDao, stubRsaTokenDao, mockLogger);

        bool actual = target.isValid("joey", "91000000");

        ASSERT_FALSE(actual);
        ASSERT_STREQ("login failed with userName: joey", mockLogger->msg.c_str());

        delete stubProfileDao;
        delete stubRsaTokenDao;
        delete mockLogger;
    }

}