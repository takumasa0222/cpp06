#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

#include <string>
#include <cstdlib>
#include <cerrno>
#include <climits>
#include <limits>

class ScalarConverter {
private:
    enum LiteralType
    {
        TYPE_CHAR,
        TYPE_INT,
        TYPE_FLOAT,
        TYPE_DOUBLE,
        TYPE_INVALID
    };

    ScalarConverter();
    ScalarConverter(const ScalarConverter& other);
    ScalarConverter& operator=(const ScalarConverter& other);
    ~ScalarConverter();
    static LiteralType detectType(const std::string& literal);

public: 
    static void convert(const std::string& literal);
};

#endif
