#include <iostream>
#include <thread>
#include <utility>
#include <algorithm>
#include <chrono>
#include "gtest/gtest.h"

#include "ContactDetails.hpp"
#include "User.hpp"
#include "Wallet.hpp"

namespace demystify
{
namespace unittest
{

transactional::Wallet ttWallet;

personal::User tttUser("Username");
personal::ContactDetails tContactDetails;
    
TEST(GenericFactory, Test_UserAsJSON)
{
    using namespace std;

    tContactDetails.setAddress("Femi Str");
    tContactDetails.setCity("Femi City");
    tContactDetails.setState("Femi State");
    tContactDetails.setPostalCode(12121);
    tContactDetails.setPhone(2983987982);
    
    ttWallet.setBalance(123423);
    tttUser.setWallet(ttWallet);
    tttUser.setContactDetails(tContactDetails);
    tttUser.setLastLogin(Datable());

    auto ttJSON = tttUser.UserAsJSON();
    ASSERT_TRUE(ttJSON.at("username").serialize() == ('\"' + tttUser.getUsername() + '\"'));
    ASSERT_TRUE(ttJSON.at("enabled").as_bool() == tttUser.isEnabled());
    ASSERT_TRUE(ttJSON.at("contactDetails").at("address").serialize() == ('\"' + tContactDetails.getAddress() + '\"'));
    ASSERT_TRUE(ttJSON.at("contactDetails").at("city").serialize() == ('\"' + tContactDetails.getCity() + '\"'));
    ASSERT_TRUE(ttJSON.at("contactDetails").at("state").serialize() == ('\"' + tContactDetails.getState() + '\"'));
    ASSERT_TRUE(ttJSON.at("contactDetails").at("postalCode").as_number().to_uint32() == tContactDetails.getPostalCode());
    ASSERT_TRUE(ttJSON.at("contactDetails").at("phone").as_number().to_uint32() == tContactDetails.getPhone());
    ASSERT_TRUE(ttJSON.at("wallet").at("balance").as_number().to_uint32() == ttWallet.getBalance());
    ASSERT_TRUE(ttJSON.at("creditPoint").at("totalPoints").as_number().to_uint32() == tttUser.getCreditPoint().getPoint());
    ASSERT_TRUE(ttJSON.at("creditPoint").at("pointLeftToSpend").as_number().to_uint32() == tttUser.getCreditPoint().pointLeftToSpend());
}

} // namespace unittest
} // namespace demystify