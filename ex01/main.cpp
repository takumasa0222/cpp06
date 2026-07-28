#include "Serializer.hpp"
#include <iostream>

int main() {
    Data *data = new Data();
    data->name = "test";
    data->value = 42;
    std::cout << "data address: " << data << std::endl;
    std::cout << "data name: " << data->name << std::endl;
    std::cout << "data value: " << data->value << std::endl;
    uintptr_t serializedValue = Serializer::serialize(data);
    std::cout << "serializedValue: " << serializedValue << std::endl;
    Data *desirialized = Serializer::deserialize(serializedValue);
    std::cout << "desirialized address: " << desirialized << std::endl;
    std::cout << "desirialized name: " << desirialized->name << std::endl;
    std::cout << "data desirialized: " << desirialized->value << std::endl;
    if (desirialized == data)
        std::cout << "desizialized and data has same pointer" << std::endl;
    else
        std::cout << "desizialized and data has different pointer" << std::endl;
    delete data;
    return 0;
}
