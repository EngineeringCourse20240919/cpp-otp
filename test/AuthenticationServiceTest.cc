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

class AuthenticationServiceTest : public ::testing::Test {
protected:
    GStubProfileDao* stubProfileDao;
    GStubRsaTokenDao* stubRsaTokenDao;
    GMockLogger *mockLogger;
    AuthenticationService* target;

    void SetUp() override {
        stubProfileDao = new GStubProfileDao();
        stubRsaTokenDao = new GStubRsaTokenDao();
        mockLogger = new GMockLogger();
        target = new AuthenticationService(stubProfileDao, stubRsaTokenDao, mockLogger);
    }

    void TearDown() override {
        delete stubProfileDao;
        delete stubRsaTokenDao;
        delete mockLogger;
        delete target;
    }

    void givenPassword(const std::string& password) {
        ON_CALL(*stubProfileDao, getPassword(::testing::_)).WillByDefault(::testing::Return(password));
    }

    void givenRandom(const std::string& random) {
        ON_CALL(*stubRsaTokenDao, getRandom(::testing::_)).WillByDefault(::testing::Return(random));
    }
};

    TEST_F(AuthenticationServiceTest, IsValid) {
        givenPassword("91");
        givenRandom("000000");

        bool actual = target->isValid("joey", "91000000");

        ASSERT_TRUE(actual);
    }

    TEST_F(AuthenticationServiceTest, IsNotValid) {
        givenPassword("91");
        givenRandom("123456");

        bool actual = target->isValid("joey", "91000000");

        ASSERT_FALSE(actual);
    }

    TEST_F(AuthenticationServiceTest, LogMessageWhenNotValid) {
        givenPassword("91");
        givenRandom("123456");
        EXPECT_CALL(*mockLogger, log(::testing::Eq("login failed with userName: joey"))).Times(1);

        bool actual = target->isValid("joey", "91000000");

        ASSERT_FALSE(actual);
    }

}