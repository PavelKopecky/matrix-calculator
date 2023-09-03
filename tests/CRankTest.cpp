/**
* @author Pavel Kopecky <kopecp14@fit.cvut.cz> 
* @date 12.05.2023
*/


#include <cassert>
#include "../src/CApplication.h"
#include "../src/CMatrixRank.h"
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
    app.addMatrix('J', *persistor("[[0,0],[0,0]]"));
    app.addMatrix('K', *persistor("[[3],[9.731],[307812]]"));
    app.addMatrix('L', *persistor("[[3,9,307812]]"));

    assert( CMatrixRank().execute(*app.getCopy('A'))->get(0,0) == 2 );
    assert( CMatrixRank().execute(*app.getCopy('B'))->get(0,0) == 1 );
    assert( CMatrixRank().execute(*app.getCopy('C'))->get(0,0) == 2 );
    assert( CMatrixRank().execute(*app.getCopy('D'))->get(0,0) == 3 );
    assert( CMatrixRank().execute(*app.getCopy('E'))->get(0,0) == 3 );
    assert( CMatrixRank().execute(*app.getCopy('F'))->get(0,0) == 1 );
    assert( CMatrixRank().execute(*app.getCopy('G'))->get(0,0) == 2 );
    assert( CMatrixRank().execute(*app.getCopy('H'))->get(0,0) == 3 );
    assert( CMatrixRank().execute(*app.getCopy('I'))->get(0,0) == 2 );
    assert( CMatrixRank().execute(*app.getCopy('J'))->get(0,0) == 0 );
    assert( CMatrixRank().execute(*app.getCopy('K'))->get(0,0) == 1 );
    assert( CMatrixRank().execute(*app.getCopy('L'))->get(0,0) == 1 );

    std::cout << "Matrix Rank: All asserts passed." << std::endl;

    return EXIT_SUCCESS;
}
