/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 22.05.2023
*/

#pragma once
#include <iostream>
#include "CApplication.h"
#include "CParser.h"

/**
 * Class representing an interface between the user and the app
 */
class CInterface {
public:

    CInterface () = default;

    /**
     * Starts the application.
     * All interaction with the user will be performed through the ostream and istream streams in parameters
     * Reads input from the user until a signal to exit the application is entered
     * @param output ostream to print into
     * @param input istream to get input from
     */
    void run (std::ostream & output, std::istream & input);

private:

    /**
     * Core of the application.
     */
    CApplication m_App;

    /**
     * Parses the expressions from user
     */
    CParser m_Parser;
};
