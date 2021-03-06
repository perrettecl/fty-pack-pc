/*  ========================================================================
    Copyright (C) 2020 Eaton
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
    ========================================================================
*/
#include "examples/example7.h"
#include "examples/example8.h"
#include <catch2/catch.hpp>

TEST_CASE("Oneof serialization/deserialization")
{
    test7::Item origin;
    origin.name = "some name";
    origin.val1 = "some string";
    origin.val2 = 42;

    auto check = [](const test7::Item& item) {
        REQUIRE("some name" == item.name);
        REQUIRE(42 == item.val2);
        REQUIRE(item.val1.empty());
    };

    check(origin);

    SECTION("Serialization yaml")
    {
        std::string cnt = *pack::yaml::serialize(origin);
        REQUIRE(!cnt.empty());

        test7::Item restored;
        pack::yaml::deserialize(cnt, restored);

        check(restored);
    }

    SECTION("Serialization json")
    {
        std::string cnt = *pack::json::serialize(origin);
        REQUIRE(!cnt.empty());

        test7::Item restored;
        pack::json::deserialize(cnt, restored);

        check(restored);
    }

    SECTION("Serialization zconfig")
    {
        std::string cnt = pack::zconfig::serialize(origin);
        REQUIRE(!cnt.empty());

        test7::Item restored;
        pack::zconfig::deserialize(cnt, restored);

        check(restored);
    }

    SECTION("Serialization protobuf")
    {
        std::string cnt = pack::protobuf::serialize(origin);
        REQUIRE(!cnt.empty());

        test7::Item restored;
        pack::protobuf::deserialize(cnt, restored);

        check(restored);
    }
}

TEST_CASE("Oneof adv serialization/deserialization")
{
    test8::Item origin;
    origin.name = "some name";

    origin.val1.value1 = "some string";
    origin.val1.num1 = 42;

    origin.val2.value2 = "some string 2";
    origin.val2.num2 = 43;

    auto check = [](const test8::Item& item) {
        REQUIRE("some name" == item.name);
        REQUIRE(!item.val1.hasValue());
        REQUIRE(item.val2.hasValue());
        REQUIRE("some string 2" == item.val2.value2);
        REQUIRE(43 == item.val2.num2);
    };

    check(origin);

    SECTION("Serialization yaml")
    {
        std::string cnt = *pack::yaml::serialize(origin);
        REQUIRE(!cnt.empty());

        test8::Item restored;
        pack::yaml::deserialize(cnt, restored);

        check(restored);
    }

    SECTION("Serialization json")
    {
        std::string cnt = *pack::json::serialize(origin);
        REQUIRE(!cnt.empty());

        test8::Item restored;
        pack::json::deserialize(cnt, restored);

        check(restored);
    }

    SECTION("Serialization zconfig")
    {
        std::string cnt = pack::zconfig::serialize(origin);
        REQUIRE(!cnt.empty());

        test8::Item restored;
        pack::zconfig::deserialize(cnt, restored);

        check(restored);
    }

    SECTION("Serialization protobuf")
    {
        std::string cnt = pack::protobuf::serialize(origin);
        REQUIRE(!cnt.empty());

        test8::Item restored;
        pack::protobuf::deserialize(cnt, restored);

        check(restored);
    }
}

