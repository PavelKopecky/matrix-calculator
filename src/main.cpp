/**
* @author Pavel Kopecký <kopecp14@fit.cvut.cz>
* @date 29.04.2023
*/

#include <iostream>
#include "CInterface.h"

/**
 * Core of the calculator
 * Reads input until EOF is reached / exit is called
 * @return exit status
 */
int main () {
    CInterface interface;
    interface.run(std::cout, std::cin);
    return EXIT_SUCCESS;
}
