#include "ScalarConverter.hpp"

ScalarConverter::LiteralType
ScalarConverter::detectType(const std::string& literal)
{
    if (isFloatPseudoLiteral(input))
        return TYPE_FLOAT;
    if (isDoublePseudoLiteral(input))
        return TYPE_DOUBLE;
    if (isCharLiteral(input))
        return TYPE_CHAR;
    if (isIntLiteral(input))
        return TYPE_INT;
    if (isFloatLiteral(input))
        return TYPE_FLOAT;
    if (isDoubleLiteral(input))
        return TYPE_DOUBLE;
    return TYPE_INVALID;
}

bool isFloatPseudoLiteral(const std::string& input)
{
    return (
        input == "nanf"
        || input == "+inff"
        || input == "-inff"
    );
}

bool isDoublePseudoLiteral(const std::string& input)
{
    return (
        input == "nan"
        || input == "+inf"
        || input == "-inf"
    );
}

bool isCharLiteral(const std::string& input)
{
    return (
        input.length() == 1
        && !std::isdigit(static_cast<unsigned char>(input[0]))
    );
}

bool isIntLiteral(const std::string& input)
{
    if (input.empty())
        return false;
    std::size_t i = 0;
    if (input[i] == '+' || input[i] == '-')
    {
        ++i;
        if (i == input.length())
            return false;
    }
    while (i < input.length())
    {
        if (!std::isdigit(static_cast<unsigned char>(input[i])))
            return false;
        ++i;
    }
    return true;
}

bool isFloatLiteral(const std::string& input)
{
    if (input.length() < 4)
        return false;
    if (input[input.length() - 1] != 'f')
        return false;
    std::size_t i = 0;
    bool hasDot = false;
    bool hasDigitBeforeDot = false;
    bool hasDigitAfterDot = false;
    if (input[i] == '+' || input[i] == '-')
        ++i;
    for (; i < input.length() - 1; ++i)
    {
        if (input[i] == '.')
        {
            if (hasDot)
                return false;

            hasDot = true;
        }
        else if (std::isdigit(static_cast<unsigned char>(input[i])))
        {
            if (!hasDot)
                hasDigitBeforeDot = true;
            else
                hasDigitAfterDot = true;
        }
        else
        {
            return false;
        }
    }

    return hasDot && hasDigitBeforeDot && hasDigitAfterDot;
}

bool isDoubleLiteral(const std::string& input)
{
    if (input.empty())
        return false;
    std::size_t i = 0;
    bool hasDot = false;
    bool hasDigitBeforeDot = false;
    bool hasDigitAfterDot = false;
    if (input[i] == '+' || input[i] == '-')
    {
        ++i;

        if (i == input.length())
            return false;
    }

    for (; i < input.length(); ++i)
    {
        if (input[i] == '.')
        {
            if (hasDot)
                return false;

            hasDot = true;
        }
        else if (std::isdigit(static_cast<unsigned char>(input[i])))
        {
            if (!hasDot)
                hasDigitBeforeDot = true;
            else
                hasDigitAfterDot = true;
        }
        else
        {
            return false;
        }
    }
    return hasDot && hasDigitBeforeDot && hasDigitAfterDot;
}

void ScalarConverter::convert(const std::string& input)
{
    LiteralType type = detectType(input);
    switch (type)
    {
        case TYPE_CHAR:
            convertFromChar(input);
            break;

        case TYPE_INT:
            convertFromInt(input);
            break;

        case TYPE_FLOAT:
            convertFromFloat(input);
            break;

        case TYPE_DOUBLE:
            convertFromDouble(input);
            break;

        default:
            std::cout << "Invalid literal" << std::endl;
            break;
    }
}