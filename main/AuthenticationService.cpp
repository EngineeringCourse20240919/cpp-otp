//
// Created by Joseph Yao on 2018/7/31.
//

#include <string>
#include "AuthenticationService.h"
#include "ProfileDao.h"
#include "RsaTokenDao.h"

bool AuthenticationService::isValid(const std::string userName, const std::string password) {
    ProfileDao profileDao;
    auto passwordFromDao = profileDao.getPassword(userName);

    RsaTokenDao rsaToken;
    auto randomCode = rsaToken.getRandom(userName);

    auto validPassword = passwordFromDao + randomCode;
    auto isValid = password == validPassword;

    if (isValid) {
        return true;
    } else {
        return false;
    }
}
