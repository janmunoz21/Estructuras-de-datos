/*************************************************************************
Autor: Jan Marco Muñoz Pineda
Fecha: 06/11/2024
Descripción: Algoritmo de Dijkstra
*************************************************************************/

#include <iostream>

using namespace std;

int main{
	int m_Matrix[6][6]= {{0, 1, 7, 6, 0, 0, 0}, {1, 0, 9, 0, 0, 3, 0}, {7, 9, 0, 0, 0, 0, 1}, {6, 0, 0, 0, 2, 0, 0}, {0, 0, 0, 2, 0, 0, 5},
	{0, 3, 0, 0, 0, 0, 5}, {0, 0, 1, 0, 5, 3, 0}}
}

template< class V, class C >
class Graph{
public:
	list< V > Preorder( int seed );
	list< V > Levels( int seed );
	protected:
	vector< V > m_Vertices;
	vector< vector< C > > m_Matrix;
	map< int, std::map< int, C > > m_Matrix;
};

template< class V, class C >
	list< V > Graph< V, C >::Levels( int seed ){
	list< V > res;
	vector< bool > marks( this->m_Vertices.size(),false );
	queue< int > q;
	q.push( seed );
	
	while( !q.empty() ){
		int n = q.front( );
		q.pop( );
		if( marks[ n ] )
		continue;
		marks[ n ] = true;
		res.push_back( this->m_Vertices[ n ] );
	
		for( int i = 0; i < this->m_Vertices.size( ); ++i ){
			if( this->m_Matrix.ElementExists( n, i ) )
			q.push( i );
		} // for
	
	} // while
	return( res );
}
