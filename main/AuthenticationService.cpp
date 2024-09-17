//
// Created by Joseph Yao on 2018/7/31.
//

#include <string>
#include "AuthenticationService.h"
#include "ProfileDao.h"
#include "RsaTokenDao.h"

bool AuthenticationService::isValid(const std::string userName, const std::string password) {
    auto passwordFromDao = profileDao->getPassword(userName);

    auto randomCode = rsaTokenDao->getRandom(userName);

    auto validPassword = passwordFromDao + randomCode;
    auto isValid = password == validPassword;

    if (isValid) {
        return true;
    } else {
        logger->log("login failed with userName: " + userName);
        return false;
    }
}

AuthenticationService::AuthenticationService(ProfileDao *profileDao, RsaTokenDao *rsaTokenDao, Logger *logger) : profileDao(profileDao), rsaTokenDao(rsaTokenDao), logger(logger) {

}
