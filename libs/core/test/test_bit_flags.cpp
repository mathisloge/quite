// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <boost/ut.hpp>
#include <quite/core/bit.hpp>
#include <quite/core/bit_flags.hpp>
#include <quite/core/bit_flags_fmt.hpp>

using namespace boost::ut;
using namespace quite;
using namespace std::literals::string_view_literals;

enum class TestFlags : uint8_t
{
    none = 0,
    read = bit(0),
    write = bit(1),
    execute = bit(2),
    admin = bit(3),
};

static suite<"BitFlags"> _ = [] {
    "default_constructor"_test = [] {
        BitFlags<TestFlags> flags;
        expect(!flags) << "default constructed flags should be false";
        expect(that % flags.to_raw() == 0U);
    };

    "single_flag_constructor"_test = [] {
        BitFlags<TestFlags> flags(TestFlags::read);
        expect(flags) << "flags with value should be true";
        expect(flags.is_set(TestFlags::read));
        expect(!flags.is_set(TestFlags::write));
    };

    "initializer_list_constructor"_test = [] {
        BitFlags<TestFlags> flags{TestFlags::read, TestFlags::write};
        expect(flags.is_set(TestFlags::read));
        expect(flags.is_set(TestFlags::write));
        expect(!flags.is_set(TestFlags::execute));
    };

    "set_and_unset"_test = [] {
        BitFlags<TestFlags> flags;
        flags.set(TestFlags::read);
        expect(flags.is_set(TestFlags::read));

        flags.set(TestFlags::write);
        expect(flags.is_set(TestFlags::read));
        expect(flags.is_set(TestFlags::write));

        flags.unset(TestFlags::read);
        expect(!flags.is_set(TestFlags::read));
        expect(flags.is_set(TestFlags::write));
    };

    "clear"_test = [] {
        BitFlags<TestFlags> flags{TestFlags::read, TestFlags::write, TestFlags::execute};
        expect(flags);

        flags.clear();
        expect(!flags);
        expect(!flags.is_set(TestFlags::read));
        expect(!flags.is_set(TestFlags::write));
        expect(!flags.is_set(TestFlags::execute));
    };

    "or_operator"_test = [] {
        BitFlags<TestFlags> flags1(TestFlags::read);
        BitFlags<TestFlags> flags2(TestFlags::write);

        auto result = flags1 | flags2;
        expect(result.is_set(TestFlags::read));
        expect(result.is_set(TestFlags::write));

        auto result2 = flags1 | TestFlags::execute;
        expect(result2.is_set(TestFlags::read));
        expect(result2.is_set(TestFlags::execute));
    };

    "and_operator"_test = [] {
        BitFlags<TestFlags> flags1{TestFlags::read, TestFlags::write};
        BitFlags<TestFlags> flags2{TestFlags::write, TestFlags::execute};

        auto result = flags1 & flags2;
        expect(!result.is_set(TestFlags::read));
        expect(result.is_set(TestFlags::write));
        expect(!result.is_set(TestFlags::execute));
    };

    "xor_operator"_test = [] {
        BitFlags<TestFlags> flags1{TestFlags::read, TestFlags::write};
        BitFlags<TestFlags> flags2{TestFlags::write, TestFlags::execute};

        auto result = flags1 ^ flags2;
        expect(result.is_set(TestFlags::read));
        expect(!result.is_set(TestFlags::write));
        expect(result.is_set(TestFlags::execute));
    };

    "compound_assignment_operators"_test = [] {
        BitFlags<TestFlags> flags(TestFlags::read);

        flags |= TestFlags::write;
        expect(flags.is_set(TestFlags::read));
        expect(flags.is_set(TestFlags::write));

        flags &= TestFlags::read;
        expect(flags.is_set(TestFlags::read));
        expect(!flags.is_set(TestFlags::write));

        flags |= TestFlags::execute;
        flags ^= TestFlags::read;
        expect(!flags.is_set(TestFlags::read));
        expect(flags.is_set(TestFlags::execute));
    };

    "not_operator"_test = [] {
        BitFlags<TestFlags> flags(TestFlags::read);
        auto inverted = ~flags;

        expect(!inverted.is_set(TestFlags::read));
        expect(inverted.is_set(TestFlags::write));
        expect(inverted.is_set(TestFlags::execute));
        expect(inverted.is_set(TestFlags::admin));
    };

    "equality_operators"_test = [] {
        BitFlags<TestFlags> flags1{TestFlags::read, TestFlags::write};
        BitFlags<TestFlags> flags2{TestFlags::read, TestFlags::write};
        BitFlags<TestFlags> flags3(TestFlags::read);

        expect(flags1 == flags2);
        expect(flags1 != flags3);
    };

    "from_raw_to_raw"_test = [] {
        constexpr uint8_t raw_value = 0b0101;
        auto flags = BitFlags<TestFlags>::from_raw(raw_value);

        expect(that % flags.to_raw() == raw_value);
        expect(flags.is_set(TestFlags::read));
        expect(!flags.is_set(TestFlags::write));
        expect(flags.is_set(TestFlags::execute));
    };

    "formatting"_test = [] {
        BitFlags<TestFlags> flags{TestFlags::read, TestFlags::execute};
        auto formatted = std::format("{}", flags);

        expect(that % formatted == "00000101"sv) << "should format as binary string";
    };

    "bool_conversion"_test = [] {
        BitFlags<TestFlags> empty_flags;
        BitFlags<TestFlags> set_flags(TestFlags::read);

        expect(!static_cast<bool>(empty_flags));
        expect(static_cast<bool>(set_flags));

        if (set_flags)
        {
            expect(true);
        }
        else
        {
            expect(false) << "should be truthy when flags are set";
        }
    };
};
