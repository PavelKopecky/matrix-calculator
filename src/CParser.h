/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz>
* @date 29.04.2023
*/

#pragma once
#include "CApplication.h"
#include "CAbstractNode.h"
#include "CMatrixPersistor.h"
#include "CRegister.h"
#include <string>

/**
 * Class which parses the expression received from the user
 */
class CParser {
public:

    CParser () = default;

    /**
     * Parses an expression from the user, either recognizes a function such "status" or an operation which
     * will be converted into AST. If the user wants the matrix to be saved, it will try to construct it and save it,
     * if the user does not wish the save the matrix, it will be print the result of the operation
     * @param expression expression to be parsed
     * @param app where to send the result
     * @return exit status indicating success/failure/other
     */
    int parse (const std::string & expression, CApplication & app, std::ostream & output, std::istream & input);

private:

    /**
     * Parses an expression expected to be an operation. It constructs the AST along the way, if the user entered an operation.
     * @param expression the expression to be parsed
     * @param app application to communicate with (e.g. save the matrix into)
     * @param output ostream to print results/additional queries into
     * @param input istream from which the user can enter additional info, if needed (to confirm a change, for instance)
     */
    void parse_operation(const std::string & expression, CApplication & app, std::ostream & output) const;

    /**
     * Creates correct matrices
     */
    CMatrixPersistor persistor;

    /**
     * Contains all operands
     */
    CRegister reg;
};
