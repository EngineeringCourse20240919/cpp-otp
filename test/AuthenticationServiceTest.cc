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

namespace {

    TEST(AuthenticationService, IsValid) {
        StubProfileDao* stubProfileDao = new StubProfileDao();
        stubProfileDao->password = "91";
        StubRsaTokenDao* stubRsaTokenDao = new StubRsaTokenDao();
        stubRsaTokenDao->token = "000000";
        AuthenticationService target = AuthenticationService(stubProfileDao, stubRsaTokenDao);

        bool actual = target.isValid("joey", "91000000");

        ASSERT_TRUE(actual);
    }

    TEST(AuthenticationService, IsNotValid) {
        StubProfileDao* stubProfileDao = new StubProfileDao();
        stubProfileDao->password = "91";
        StubRsaTokenDao* stubRsaTokenDao = new StubRsaTokenDao();
        stubRsaTokenDao->token = "123456";
        AuthenticationService target = AuthenticationService(stubProfileDao, stubRsaTokenDao);

        bool actual = target.isValid("joey", "91000000");

        ASSERT_FALSE(actual);
    }

}