/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 07.05.2023
*/

#include <cassert>
#include "../src/CApplication.h"
#include "../src/CTranspose.h"
#include "../src/CMatrixPersistor.h"

int main () {

    CApplication app;
    CMatrixPersistor persistor;


    app.addMatrix('A', *persistor("[[2,1],[1,2]]"));
    app.addMatrix('B', *persistor("[[2,1,1],[1,2,0]]"));
    app.addMatrix('C', *persistor("[[0,0],[0,0]]"));
    app.addMatrix('D', *persistor("[[-2,1,-1,2]]"));
    app.addMatrix('E', *persistor("[[1,0],[0,1]]"));
    app.addMatrix('F', *persistor("[[0,2,0],[0,0,3],[0,0,0]]"));
    app.addMatrix('G', *persistor("[[1,0,0,0],[0,4,0,0],[0,0,0,0],[0,0,0,1]]"));


    assert( *CTranspose().execute(*app.getCopy('A')) == *app.getCopy('A'));
    assert( *CTranspose().execute(*app.getCopy('B')) == *persistor("[[2,1],[1,2],[1,0]]"));
    assert( *CTranspose().execute(*app.getCopy('C')) == *app.getCopy('C'));
    assert( *CTranspose().execute(*app.getCopy('D')) == *persistor("[[-2],[1],[-1],[2]]"));
    assert( *CTranspose().execute(*CTranspose().execute(*app.getCopy('D'))) == *app.getCopy('D'));
    assert( *CTranspose().execute(*app.getCopy('E')) == *app.getCopy('E'));
    assert( *CTranspose().execute(*app.getCopy('F')) == *persistor("[[0,0,0],[2,0,0],[0,3,0]]"));
    assert( *CTranspose().execute(*CTranspose().execute(*app.getCopy('F'))) == *app.getCopy('F'));
    assert( *CTranspose().execute(*app.getCopy('G')) == *app.getCopy('G'));
    assert( *CTranspose().execute(*CTranspose().execute(*app.getCopy('G'))) == *app.getCopy('G'));

    std::cout << "Transposition: All asserts passed." << std::endl;

    return EXIT_SUCCESS;
}
