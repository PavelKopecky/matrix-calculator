/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 14.05.2023
*/

#include <cassert>
#include "../src/CApplication.h"
#include "../src/CMerge.h"
#include "../src/CMatrixPersistor.h"

int main () {

    CApplication app;
    CMatrixPersistor persistor;

    app.addMatrix('A', *persistor("[[2,1],[1,2]]"));
    app.addMatrix('B', *persistor("[[1,0,0],[1,0,0]]"));
    app.addMatrix('C', *persistor("[[1,0,0],[1,1,0],[1,1,1]]"));
    app.addMatrix('D', *persistor("[[0,7],[1.2,0],[4,7]]"));
    app.addMatrix('E', *persistor("[[1,4,8,11],[17,80,0,5]]"));
    app.addMatrix('F', *persistor("[[0,0,0],[0,0,0],[0,0,0]]"));
    app.addMatrix('G', *persistor("[[1,0,0],[0,1,0]]"));
    app.addMatrix('H', *persistor("[[0,0,1]]"));
    app.addMatrix('I', *persistor("[[1,0],[0,4],[0,0],[0,0]]"));
    app.addMatrix('J', *persistor("[[0,0],[0,0],[1,0],[0,0]]"));


    assert( *CMerge().execute(*app.getCopy('A'), *app.getCopy('A')) == *persistor("[[2,1,2,1],[1,2,1,2]]"));
    assert( *CMerge().execute(*app.getCopy('A'), *app.getCopy('B')) == *persistor("[[2,1,1,0,0],[1,2,1,0,0]]"));
    assert( *CMerge().execute(*app.getCopy('B'), *app.getCopy('A')) == *persistor("[[1,0,0,2,1],[1,0,0,1,2]]"));
    assert( *CMerge().execute(*app.getCopy('B'), *app.getCopy('C')) == *persistor("[[1,0,0],[1,0,0],[1,0,0],[1,1,0],[1,1,1]]"));
    assert( *CMerge().execute(*app.getCopy('A'), *app.getCopy('D')) == *persistor("[[2,1],[1,2],[0,7],[1.2,0],[4,7]]"));
    assert( *CMerge().execute(*app.getCopy('B'), *app.getCopy('E')) == *persistor("[[1,0,0,1,4,8,11],[1,0,0,17,80,0,5]]"));
    assert( *CMerge().execute(*app.getCopy('B'), *app.getCopy('F')) == *persistor("[[1,0,0],[1,0,0],[0,0,0],[0,0,0],[0,0,0]]"));
    assert( *CMerge().execute(*app.getCopy('G'), *app.getCopy('H')) == *persistor("[[1,0,0],[0,1,0],[0,0,1]]"));
    assert ( *CMerge().execute(*app.getCopy('I'), *app.getCopy('J')) == *persistor("[[1,0,0,0],[0,4,0,0],[0,0,1,0],[0,0,0,0]]"));

    uint32_t exceptionsThrown = 0;

    try  {
        CMerge().execute(*app.getCopy('A'), *app.getCopy('C'));
    } catch (...) {
        exceptionsThrown++;
    }

    try  {
        CMerge().execute(*app.getCopy('C'), *app.getCopy('A'));
    } catch (...) {
        exceptionsThrown++;
    }

    try  {
        CMerge().execute(*app.getCopy('E'), *app.getCopy('C'));
    } catch (...) {
        exceptionsThrown++;
    }

    try  {
        CMerge().execute(*app.getCopy('F'), *app.getCopy('A'));
    } catch (...) {
        exceptionsThrown++;
    }

    assert( exceptionsThrown == 4 );

    std::cout << "Merge: All asserts passed." << std::endl;

    return EXIT_SUCCESS;
}
