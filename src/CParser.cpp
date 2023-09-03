/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz>
* @date 29.04.2023
*/

#include "CParser.h"
#include "CApplication.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstring>

int CParser::parse(const std::string &expression, CApplication & app, std::ostream & output, std::istream & input) {

    //user wants to exit the app
    if (!strcasecmp(expression.c_str(), "exit")) {
        if (!app.saved()) {
            std::string command;

            output << "Data is not saved, enter \"yes\" to exit:\n";
            std::getline(input, command);

            //wait for user confirmation
            if (!command.empty() && !strcasecmp(command.c_str(), "yes")) {
                output << "Closing application." << std::endl;
                return 0;
            } else {
                output << "Aborted.\n";
                return 1;
            }
        }
        output << "Closing application." << std::endl;
        return 0;

    //user wants to display the 'HELP' text
    } else if (!strcasecmp(expression.c_str(), "help")) {

        std::ifstream helpText;
        helpText.open("assets/help.txt");

        while (helpText.peek() != EOF) {
            std::string inputLine;
            std::getline(helpText, inputLine);
            output << inputLine << std::endl;
        }

        output << std::endl;
        return 1;

    //print all matrices in the app
    } else if (!strcasecmp(expression.c_str(), "status")){
        app.print(output);
        return 1;

    } else {

        std::istringstream expr(expression);
        std::string command;
        expr >> command;

        //user wants to load matrices from a file
        if (!strcasecmp(command.c_str(), "load")) {
            std::string fileName;
            command.clear();
            expr >> fileName >> command;
            if (fileName.empty() || !command.empty()) throw std::invalid_argument("ERROR: Syntax error.");
            else {
                if (!app.saved()) {
                    output << "Data is not saved, enter \"yes\" to continue:\n";
                    std::getline(input, command);

                    if (!command.empty() && !strcasecmp(command.c_str(), "yes")) {
                        app.loadFromFile(fileName);
                        output << "File loaded successfully.\n";
                    } else output << "Aborted.\n";
                }
                else {
                    app.loadFromFile(fileName);
                    output << "File loaded successfully.\n";
                }
            }

        //user wants to save the matrices inside the app into a file
        } else if (!strcasecmp(command.c_str(), "save")) {
            std::string fileName;
            command.clear();
            expr >> fileName >> command;
            if (fileName.empty() || !command.empty()) throw std::invalid_argument("ERROR: Syntax error.");
            else {
                app.saveToFile(fileName);
                output << "Calculator saved successfully.\n";
                return 1;
            }
        } else if (!strcasecmp(command.c_str(), "rm")) {
        std::string matrixName;
        command.clear();
        expr >> matrixName >> command;
        if (!command.empty() || matrixName.size() != 1) throw std::invalid_argument("ERROR: Syntax error.");
        else {
            app.remove(matrixName[0]);
            output << "Matrix removed.\n";
            return 1;
        }
    } else parse_operation(expression, app, output); //user most likely entered an expression, parse it
        return 1;
    }
}

void CParser::parse_operation(const std::string & expression, CApplication & app, std::ostream & output) const {

    std::istringstream expr(expression);
    std::string operand;

    CAbstractNode * leftNode = nullptr;
    CAbstractNode * rightNode = nullptr;
    CAbstractNode * helperNode = nullptr;

    /** needs to be initialized, expected to be overwritten later, '_' is not a valid name for a matrix anyway*/
    char lastMatrix = '_';

    while (expr && expr.peek() != EOF && expr.peek() != '\n') {

        if (!(expr >> operand) || operand.empty()) break;

        switch (reg.contains(operand)) {

            //a unary operator was entered
            case -1 : {
                if (helperNode != nullptr) {
                    CAbstractNode * newNode(new CAbstractNode(reg.getUnary(operand)));
                    newNode->leftNode = helperNode;
                    helperNode = newNode;
                    lastMatrix = '_';
                } else if (rightNode != nullptr) {
                    CAbstractNode * newNode(new CAbstractNode(reg.getUnary(operand)));
                    newNode->leftNode = rightNode;
                    rightNode = newNode;
                    lastMatrix = '_';
                } else {
                    delete helperNode;
                    delete rightNode;
                    delete leftNode;
                    throw std::invalid_argument("ERROR: Syntax error.");
                }
                break;
            }

            //a binary operator was entered
            case 1 : {
                if (helperNode != nullptr && rightNode != nullptr) {
                    CAbstractNode * newNode(new CAbstractNode(reg.getBinary(operand)));
                    newNode->rightNode = helperNode;
                    newNode->leftNode = rightNode;
                    rightNode = newNode;
                    helperNode = nullptr;
                    lastMatrix = '_';
                } else if (rightNode != nullptr && leftNode != nullptr) {
                    CAbstractNode * newNode(new CAbstractNode(reg.getBinary(operand)));
                    newNode->rightNode = rightNode;
                    newNode->leftNode = leftNode;
                    rightNode = newNode;
                    leftNode = nullptr;
                    lastMatrix = '_';
                } else {
                    delete helperNode;
                    delete rightNode;
                    delete leftNode;
                    throw std::invalid_argument("ERROR: Syntax error.");
                }
                break;
            }

            //an error occurred, or a matrix (explicit/name) was entered
            case 0 : {

                //name of a matrix entered - needs to be a letter
                if (operand.length() == 1 && ((operand[0] >= 'A' && operand[0] <= 'Z') || (operand[0] >= 'a' && operand[0] <= 'z'))) {

                    if (rightNode != nullptr && leftNode != nullptr) {

                        if (helperNode == nullptr && app.contains(operand[0])) {
                            helperNode = new CAbstractNode(app.getCopy(operand[0]));
                        } else {
                            delete helperNode;
                            delete rightNode;
                            delete leftNode;
                            throw std::invalid_argument("ERROR: Syntax error.");
                        }
                    }
                    else if (app.contains(operand[0])) {
                        lastMatrix = operand[0];
                        leftNode = rightNode;
                        rightNode = new CAbstractNode(app.getCopy(operand[0]));
                    } else { //user most likely wants to create a new matrix, signalized by op =
                        char sign;
                        if (!(expr >> sign) || sign != '=' ||
                            leftNode != nullptr || rightNode == nullptr || helperNode != nullptr) {
                            delete helperNode;
                            delete rightNode;
                            delete leftNode;
                            throw std::invalid_argument("ERROR: Syntax error.");
                        }

                        //only whitespace can follow the =
                        while (expr >> sign) {
                            if (sign != '\n' && sign != ' ' && sign != '\t') {
                                delete helperNode;
                                delete rightNode;
                                delete leftNode;
                                throw std::invalid_argument("ERROR: Syntax error.");
                            }
                        }

                        try {
                            app.addMatrix(operand[0], *rightNode->evaluate());
                            output << "Matrix added successfully\n";
                        } catch (const std::exception & ex) {
                            output << ex.what() << std::endl;
                        }

                        delete helperNode;
                        delete rightNode;
                        delete leftNode;
                        return;
                    }

                } else if (!operand.empty() && operand[0] == '[') {

                    /**
                     * Keep reading the expression until you find two consecutive ']' -- a full matrix can be formed
                     * If no two consecutive ']' are found, throw an exception
                     */
                    while ( expr && expr.peek() != EOF &&
                            (operand[operand.size() - 1] != ']' || operand[operand.size() - 2] != ']')) {

                        std::string newPart;
                        expr >> newPart;
                        operand += newPart;
                    }

                    if ((operand[operand.size() - 1] != ']' || operand[operand.size() - 2] != ']')) {
                        delete helperNode;
                        delete rightNode;
                        delete leftNode;
                        throw std::invalid_argument("ERROR: Syntax error.");
                    }

                    if (rightNode != nullptr && leftNode != nullptr) {
                        if (helperNode == nullptr) {
                            helperNode = new CAbstractNode(persistor(std::move(operand)));
                        } else {
                            delete helperNode;
                            delete rightNode;
                            delete leftNode;
                            throw std::invalid_argument("ERROR: Syntax error.");
                        }
                    }
                    else {
                        leftNode = rightNode;
                        rightNode = new CAbstractNode(persistor(std::move(operand)));
                    }

                } else if (!operand.empty() && operand[0] == '=') {

                    char sign;

                    //'_' indicated that a matrix was not the last input, therefore we detect a syntax error
                    //leftNode contains what should be saved into the new matrix
                    if (rightNode == nullptr || leftNode == nullptr || helperNode != nullptr || lastMatrix == '_') {
                        delete helperNode;
                        delete rightNode;
                        delete leftNode;
                        throw std::invalid_argument("ERROR: Syntax error.");
                    }

                    while (expr >> sign) {
                        if (sign != '\n' && sign != ' ' && sign != '\t') {
                            delete helperNode;
                            delete rightNode;
                            delete leftNode;
                            throw std::invalid_argument("ERROR: Syntax error.");
                        }
                    }

                    //lastMatrix contains the name of the last matrix entered, which is in the rightNode

                    try {
                        app.addMatrix(lastMatrix, *leftNode->evaluate());
                        output << "Original matrix overwritten, new matrix added successfully\n";
                    } catch (const std::exception & ex) {
                        output << ex.what() << std::endl;
                    }

                    delete helperNode;
                    delete rightNode;
                    delete leftNode;
                    return;
                } else {
                    delete helperNode;
                    delete rightNode;
                    delete leftNode;
                    throw std::invalid_argument("ERROR: Syntax error.");
                }
                break;
            }

            default : break;
        }
    }

    //not a complete expression
    if (rightNode == nullptr || leftNode != nullptr || helperNode != nullptr) {
        delete helperNode;
        delete rightNode;
        delete leftNode;
        throw std::invalid_argument("ERROR: Syntax error.");
    }

    //user does not want to save the result - print it
    try {
        rightNode->evaluate()->print(output);
    } catch (const std::exception & ex) {
        output << ex.what() << std::endl;
    }

    delete helperNode;
    delete rightNode;
    delete leftNode;
}
