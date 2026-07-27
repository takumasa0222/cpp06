#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

#include <string>
#include <cstdlib>
#include <cerrno>
#include <climits>
#include <limits>
#include <iostream>
#include <iomanip>
#include <cmath>

class ScalarConverter {
private:
    ScalarConverter();
    ScalarConverter(const ScalarConverter& other);
    ScalarConverter& operator=(const ScalarConverter& other);
    ~ScalarConverter();

public: 
    static void convert(const std::string& literal);
};

#endif
