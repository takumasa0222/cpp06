#include "Base.hpp"
#include <ctime>
#include <cstdlib>
int main(void) {
    std::srand(std::time(NULL));
    Base *something = generate();
    identify(something);
    identify(*something);
    delete something;
    return 0;
}
