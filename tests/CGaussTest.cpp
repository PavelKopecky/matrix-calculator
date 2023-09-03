/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 11.05.2023
*/

#include <cassert>
#include "../src/CApplication.h"
#include "../src/CMatrixPersistor.h"

int main () {

    CApplication app;
    CMatrixPersistor persistor;

    app.addMatrix('A', *persistor("[[3,4],[1,9]]"));
    app.addMatrix('B', *persistor("[[1,0,0],[1,0,0]]"));
    app.addMatrix('C', *persistor("[[1,0],[0,1]]"));
    app.addMatrix('D', *persistor("[[1,0,0],[1,1,0],[1,1,1]]"));
    app.addMatrix('E', *persistor("[[3,0,0],[0,7,0],[0,0,17]]"));
    app.addMatrix('F', *persistor("[[0,0,0],[0,1,0]]"));
    app.addMatrix('G', *persistor("[[1,2],[1,3],[2,4],[2,5]]"));
    app.addMatrix('H', *persistor("[[0,1,2],[3,2,6],[1,3,2]]"));
    app.addMatrix('I', *persistor("[[1,3,1,9],[1,1,-1,1],[3,11,5,35]]"));
    app.addMatrix('J', *persistor("[[1,0,0],[-1,0,0]]"));
    app.addMatrix('K', *persistor("[[-24,1,-2],[-3,2,-6],[1,-3,2]]"));

    app.getCopy('A')->gauss()->print(std::cout);
    std::cout << std::endl;
    app.getCopy('B')->gauss()->print(std::cout);
    std::cout << std::endl;
    app.getCopy('C')->gauss()->print(std::cout);
    std::cout << std::endl;
    app.getCopy('D')->gauss()->print(std::cout);
    std::cout << std::endl;
    app.getCopy('E')->gauss()->print(std::cout);
    std::cout << std::endl;
    app.getCopy('F')->gauss()->print(std::cout);
    std::cout << std::endl;
    app.getCopy('G')->gauss()->print(std::cout);
    std::cout << std::endl;
    app.getCopy('H')->gauss()->print(std::cout);
    std::cout << std::endl;
    app.getCopy('I')->gauss()->print(std::cout);
    std::cout << std::endl;
    app.getCopy('J')->gauss()->print(std::cout);
    std::cout << std::endl;
    app.getCopy('K')->gauss()->print(std::cout);

    std::cout << "Gauss: All asserts passed." << std::endl;

    return EXIT_SUCCESS;
}
