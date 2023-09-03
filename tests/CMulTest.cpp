/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 06.05.2023
*/

#include <cassert>
#include "../src/CApplication.h"
#include "../src/CMultiply.h"
#include "../src/CMatrixPersistor.h"

int main () {

    CApplication app;
    CMatrixPersistor persistor;

    app.addMatrix('A', *persistor("[[2,1],[1,2]]"));
    app.addMatrix('B', *persistor("[[2,1,1],[1,2,0]]"));
    app.addMatrix('C', *persistor("[[0,0],[0,0]]"));
    app.addMatrix('D', *persistor("[[-2,1],[-1,2]]"));
    app.addMatrix('E', *persistor("[[1,0],[0,1]]"));
    app.addMatrix('F', *persistor("[[0,2,0],[0,0,3],[0,0,0]]"));
    app.addMatrix('G', *persistor("[[3,4],[1,2],[-0.4,1]]"));
    app.addMatrix('H', *persistor("[[-2,-1,2]]"));

    assert( *CMultiply().execute(*app.getCopy('A'), *app.getCopy('A')) == *persistor("[[5,4],[4,5]]"));
    assert( *CMultiply().execute(*app.getCopy('A'), *app.getCopy('C')) == *app.getCopy('C'));
    assert( *CMultiply().execute(*app.getCopy('B'), *app.getCopy('F')) == *persistor("[[0,4,3],[0,2,6]]"));
    assert( *CMultiply().execute(*app.getCopy('A'), *app.getCopy('D')) == *persistor("[[-5,4],[-4,5]]"));
    assert( *CMultiply().execute(*app.getCopy('D'), *app.getCopy('A')) == *persistor("[[-3,0],[0,3]]"));
    assert( *CMultiply().execute(*app.getCopy('A'), *app.getCopy('E')) == *app.getCopy('A'));
    assert( *CMultiply().execute(*app.getCopy('H'), *app.getCopy('G')) == *persistor("[[-7.8,-8]]"));

    bool exception = false;

    try {
        CMultiply().execute(*app.getCopy('B'), *app.getCopy('A'));
    } catch (...) {
        exception = true;
    }

    assert( exception );

    std::cout << "Multiplication: All asserts passed." << std::endl;

    return EXIT_SUCCESS;
}
