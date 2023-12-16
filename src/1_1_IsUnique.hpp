#include <gtest/gtest.h>
#include <string>

bool isUnique(const std::string& input) {
    __int128_t mask = 0;
    for (const auto& c : input) {
        if (mask & (2 << c)) {
            return false;
        }
        mask |= (2 << c);
    }
    return true;
}

TEST(IsUniqueTest, UniqueString) {
    std::string input = "abcde";
    EXPECT_TRUE(isUnique(input));
}

TEST(IsUniqueTest, NonUniqueString) {
    std::string input = "hello";
    EXPECT_FALSE(isUnique(input));
}

TEST(IsUniqueTest, EmptyString) {
    std::string input = "";
    EXPECT_TRUE(isUnique(input)); // Assuming an empty string is considered unique
}

TEST(IsUniqueTest, SpecialCharacters) {
    std::string input = "!@#$%^&*()";
    EXPECT_TRUE(isUnique(input)); // Depends on your function's handling of special chars
}

TEST(IsUniqueTest, AllUniqueASCIICharacters) {
    std::string input = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#";
    EXPECT_TRUE(isUnique(input));
}

TEST(IsUniqueTest, RepeatedASCIICharacters) {
    std::string input = "aaBBccDD!!@@";
    EXPECT_FALSE(isUnique(input));
}

TEST(IsUniqueTest, ASCIIControlCharacters) {
    std::string input = std::string(1, char(0)) + std::string(1, char(1)) + "AB";
    EXPECT_TRUE(isUnique(input));
}

TEST(IsUniqueTest, MaxLengthASCIIString) {
    std::string input(1000, 'A'); // String of 1000 'A's
    EXPECT_FALSE(isUnique(input));
}

TEST(IsUniqueTest, NumericCharactersOnly) {
    std::string input = "1234567890";
    EXPECT_TRUE(isUnique(input));
}

TEST(IsUniqueTest, PunctuationCharacters) {
    std::string input = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
    EXPECT_TRUE(isUnique(input));
}

TEST(IsUniqueTest, MixedCharacterTypes) {
    std::string input = "a1!A2@b3#B4$c5%C6^";
    EXPECT_TRUE(isUnique(input));
}
