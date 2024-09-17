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
        return false;
    }
}

AuthenticationService::AuthenticationService(ProfileDao *profileDao, RsaTokenDao *rsaTokenDao) : profileDao(profileDao), rsaTokenDao(rsaTokenDao) {

}
