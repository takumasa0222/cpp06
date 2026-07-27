#include "ScalarConverter.hpp"

enum LiteralType
{
    TYPE_CHAR,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_PSEUDO,
    TYPE_INVALID
};

static bool isCharLiteral(const std::string& input);
static bool isIntLiteral(const std::string& input);
static bool isDecimalLiteral(const std::string& literal, bool hasFloatSuffix);

static LiteralType detectType(const std::string& literal);
static bool isPseudoLiteral(const std::string& literal)
{
    return literal == "nan"
        || literal == "nanf"
        || literal == "+inf"
        || literal == "+inff"
        || literal == "-inf"
        || literal == "-inff";
}

static LiteralType detectType(const std::string& literal)
{
    if (isPseudoLiteral(literal))
        return TYPE_PSEUDO;

    if (isCharLiteral(literal))
        return TYPE_CHAR;

    if (isIntLiteral(literal))
        return TYPE_INT;

    if (isDecimalLiteral(literal, true))
        return TYPE_FLOAT;

    if (isDecimalLiteral(literal, false))
        return TYPE_DOUBLE;

    return TYPE_INVALID;
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
        ++i;
    if (i == input.length())
            return false;
    while (i < input.length())
    {
        if (!std::isdigit(static_cast<unsigned char>(input[i])))
            return false;
        ++i;
    }
    return true;
}

static bool isDecimalLiteral(const std::string& literal, bool hasFloatSuffix)
{
    if (literal.empty())
        return false;
    std::size_t end = literal.length();
    if (hasFloatSuffix)
    {
        if (literal[end - 1] != 'f')
            return false;
        --end;
    }
    std::size_t i = 0;
    if (i < end && (literal[i] == '+' || literal[i] == '-'))
        ++i;
    if (i == end)
        return false;
    bool hasDot = false;
    bool hasDigitBeforeDot = false;
    bool hasDigitAfterDot = false;
    while (i < end)
    {
        if (literal[i] == '.')
        {
            if (hasDot)
                return false;
            hasDot = true;
        }
        else if (std::isdigit(static_cast<unsigned char>(literal[i])))
        {
            if (hasDot)
                hasDigitAfterDot = true;
            else
                hasDigitBeforeDot = true;
        }
        else
            return false;
        ++i;
    }
    return hasDot && hasDigitBeforeDot && hasDigitAfterDot;
}

static bool parseValue(const std::string& literal, LiteralType type, double& value)
{
    if (type == TYPE_CHAR)
    {
        char original = literal[0];
        value = static_cast<double>(original);
        return true;
    }
    std::string numberPart = literal;
    if (type == TYPE_FLOAT)
        numberPart.erase(numberPart.length() - 1);
    const char* start = numberPart.c_str();
    char* end = NULL;
    errno = 0;
    double parsed = std::strtod(start, &end);
    if (end == start || *end != '\0' || errno == ERANGE)
        return false;
    if (type == TYPE_INT 
        && parsed >= static_cast<double>(std::numeric_limits<int>::min())
        && parsed <= static_cast<double>(std::numeric_limits<int>::max()))
    {
        int original = static_cast<int>(parsed);
        value = static_cast<double>(original);
    }
    else if (type == TYPE_FLOAT
        && parsed >= -static_cast<double>(std::numeric_limits<float>::max())
        && parsed <= static_cast<double>(std::numeric_limits<float>::max()))
    {
        float original = static_cast<float>(parsed);
        value = static_cast<double>(original);
    }
    else
    {
        value = parsed;
    }
    return true;
}


static double truncateTowardZero(double value)
{
    if (value < 0.0)
        return std::ceil(value);
    return std::floor(value);
}

static void printChar(double value)
{
    double truncated = truncateTowardZero(value);

    if (truncated < static_cast<double>(std::numeric_limits<char>::min())
        || truncated > static_cast<double>(std::numeric_limits<char>::max()))
    {
        std::cout << "char: impossible" << std::endl;
        return;
    }

    char converted = static_cast<char>(value);

    if (!std::isprint(static_cast<unsigned char>(converted)))
    { 
        std::cout << "char: Non displayable" << std::endl; 
        return;
    }

    std::cout << "char: '" << converted << "'" << std::endl;
}

static void printInt(double value)
{
    double truncated = truncateTowardZero(value);

    if (truncated < static_cast<double>( std::numeric_limits<int>::min())
        || truncated > static_cast<double>( std::numeric_limits<int>::max()))
    {
        std::cout << "int: impossible" << std::endl;
        return;
    }
    std::cout << "int: " << static_cast<int>(value) << std::endl;
}
static void printFloatingValue(const char* label, double value, int precision, const char* suffix)
{
    std::ios::fmtflags oldFlags = std::cout.flags();
    std::streamsize oldPrecision = std::cout.precision();
    std::cout.unsetf(std::ios::floatfield);
    std::cout << label;

    if (value == std::floor(value))
        std::cout << std::fixed << std::setprecision(1);
    else
        std::cout << std::setprecision(precision);
    std::cout << value << suffix << std::endl;
    std::cout.flags(oldFlags);
    std::cout.precision(oldPrecision);
}

static void printFloat(double value)
{
    if (value < -static_cast<double>( std::numeric_limits<float>::max() )
        || value > static_cast<double>( std::numeric_limits<float>::max()))
    {
        std::cout << "float: impossible" << std::endl;
        return;
    }
    float converted = static_cast<float>(value);

    printFloatingValue("float: ", static_cast<double>(converted), std::numeric_limits<float>::digits10 + 1, "f");
}
static void printDouble(double value, LiteralType sourceType)
{
    int precision = std::numeric_limits<double>::digits10 + 1;
    if (sourceType == TYPE_FLOAT)
        precision = std::numeric_limits<float>::digits10 + 1;
    printFloatingValue("double: ", value, precision, "");
}
static void printConversions(double value, LiteralType sourceType)
{
    printChar(value);
    printInt(value);
    printFloat(value);
    printDouble(value, sourceType);
}

static void printPseudoLiteral(const std::string& literal)
{
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;

    if (literal == "nan" || literal == "nanf")
    {
        std::cout << "float: nanf" << std::endl;
        std::cout << "double: nan" << std::endl;
    }
    else if (literal == "+inf" || literal == "+inff")
    {
        std::cout << "float: +inff" << std::endl;
        std::cout << "double: +inf" << std::endl;
    }
    else
    {
        std::cout << "float: -inff" << std::endl;
        std::cout << "double: -inf" << std::endl;
    }
}

static void printAllImpossible()
{
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;
    std::cout << "float: impossible" << std::endl;
    std::cout << "double: impossible" << std::endl;
}

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter &source)
{
    (void)source;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &source)
{
    (void)source;
    return *this;
}

ScalarConverter::~ScalarConverter() {}
void ScalarConverter::convert(const std::string& literal)
{
    LiteralType type = detectType(literal);
    if (type == TYPE_INVALID)
    {
        std::cout << "Invalid literal" << std::endl;
        return;
    }
    if (type == TYPE_PSEUDO)
    {
        printPseudoLiteral(literal);
        return;
    }
    double value;
    if (!parseValue(literal, type, value))
    {
        printAllImpossible();
        return;
    }
    printConversions(value, type);
}