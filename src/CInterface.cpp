/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 22.05.2023
*/

#include "CInterface.h"

void CInterface::run(std::ostream & output, std::istream & input) {

    output << "\n\n\n!------------------------------------ MATRIX CALCULATOR! ------------------------------------!\n"
                 "!               Enter \"HELP\" for a quick guide on how to use this calculator.                !\n\n";

    std::string expression;

    while (true) {

        std::getline(input, expression);

        if (expression.empty()) continue;
        else if (std::cin.eof()) {
            break;
        } else {
            try {
                if (!m_Parser.parse(expression, m_App, output, input)) break;
            } catch (const std::exception & ex) {
                output << ex.what() << std::endl;
            }
        }
    }
}
