#include <iostream>
#include "VsssUFES.h"

void VsssUFES::greet() {
    std::cout << "Hello, " << name << ", your name has " << getNameLength() << " chars." << std::endl;
}

int VsssUFES::getNameLength() {
    return name.length();
}