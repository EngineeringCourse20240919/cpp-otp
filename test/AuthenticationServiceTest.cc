#include "gtest/gtest.h"
#include "../main/AuthenticationService.h"
#include "gmock/gmock.h"

class GStubProfileDao : public ProfileDao {
public:
    MOCK_METHOD(std::string, getPassword, (const std::string));
};

class GStubRsaTokenDao : public RsaTokenDao {
public:
    MOCK_METHOD(std::string, getRandom, (std::string));
};

class GMockLogger : public Logger {
public:
    MOCK_METHOD(void, log, (const std::string&));
};

namespace {

    TEST(AuthenticationService, IsValid) {
        GStubProfileDao* stubProfileDao = new GStubProfileDao();
        ON_CALL(*stubProfileDao, getPassword(::testing::_)).WillByDefault(::testing::Return("91"));
        GStubRsaTokenDao* stubRsaTokenDao = new GStubRsaTokenDao();
        ON_CALL(*stubRsaTokenDao, getRandom(::testing::_)).WillByDefault(::testing::Return("000000"));
        GMockLogger* mockLogger = new GMockLogger();
        AuthenticationService target = AuthenticationService(stubProfileDao, stubRsaTokenDao, mockLogger);

        bool actual = target.isValid("joey", "91000000");

        ASSERT_TRUE(actual);

        delete stubProfileDao;
        delete stubRsaTokenDao;
        delete mockLogger;
    }

    TEST(AuthenticationService, IsNotValid) {
        GStubProfileDao* stubProfileDao = new GStubProfileDao();
        ON_CALL(*stubProfileDao, getPassword(::testing::_)).WillByDefault(::testing::Return("91"));
        GStubRsaTokenDao* stubRsaTokenDao = new GStubRsaTokenDao();
        ON_CALL(*stubRsaTokenDao, getRandom(::testing::_)).WillByDefault(::testing::Return("123456"));
        GMockLogger* mockLogger = new GMockLogger();
        AuthenticationService target = AuthenticationService(stubProfileDao, stubRsaTokenDao, mockLogger);

        bool actual = target.isValid("joey", "91000000");

        ASSERT_FALSE(actual);

        delete stubProfileDao;
        delete stubRsaTokenDao;
        delete mockLogger;
    }

    TEST(AuthenticationService, LogMessageWhenNotValid) {
        GStubProfileDao* stubProfileDao = new GStubProfileDao();
        ON_CALL(*stubProfileDao, getPassword(::testing::_)).WillByDefault(::testing::Return("91"));
        GStubRsaTokenDao* stubRsaTokenDao = new GStubRsaTokenDao();
        ON_CALL(*stubRsaTokenDao, getRandom(::testing::_)).WillByDefault(::testing::Return("123456"));
        GMockLogger* mockLogger = new GMockLogger();
        EXPECT_CALL(*mockLogger, log(::testing::Eq("login failed with userName: joey"))).Times(1);
        AuthenticationService target = AuthenticationService(stubProfileDao, stubRsaTokenDao, mockLogger);

        bool actual = target.isValid("joey", "91000000");

        ASSERT_FALSE(actual);

        delete stubProfileDao;
        delete stubRsaTokenDao;
        delete mockLogger;
    }

}