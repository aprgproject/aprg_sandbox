#include <boost/locale.hpp>

#include <gtest/gtest.h>

#include <ctime>
#include <iostream>

using namespace boost::locale;
using namespace std;

TEST(LocaleTest, LocaleTest)
{
    generator gen;
    locale loc=gen("");
    // Create system default locale

    locale::global(loc);
    // Make it system global

    cout.imbue(loc);
    // Set as default locale for output

    cout << format("Today {1,date} at {1,time} we had run our first localization example") % time(0) << "\n";

    cout << "This is how we show numbers in this locale " << as::number << 103.34 << "\n";
    cout << "This is how we show currency in this locale " << as::currency << 103.34 << "\n";
    cout << "This is typical date in the locale "<<as::date << std::time(0) << "\n";
    cout << "This is typical time in the locale "<<as::time << std::time(0) << "\n";
    cout << "This is upper case "<<to_upper("Hello World!") << "\n";
    cout << "This is lower case "<<to_lower("Hello World!") << "\n";
    cout << "This is title case "<<to_title("Hello World!") << "\n";
    cout << "This is fold case "<<fold_case("Hello World!") << "\n";
}
