#pragma once
#include<stack>

#define BinNodePosi(T) BinNode<T> *

using namespace std;

template<typename T>
struct BinNode
{
	T data;
	BinNodePosi( T ) parent;
	BinNodePosi( T ) lChild;
	BinNodePosi( T ) rChild;

	BinNode() : data( NULL ), parent( NULL ), lChild( NULL ), rChild( NULL ) {}
	BinNode( T e, BinNodePosi( T ) p ) : data( e ), parent( NULL ), lChild( NULL ), rChild( NULL ) {}

	BinNodePosi( T ) InsertAsLC( T const & e )
	{
		return lChild = new BinNode( e, this );
	}
	BinNodePosi( T ) InsertAsRC( T const & e )
	{
		return rChild = new BinNode( e, this );
	}
};


template<typename T>
void VisitAlongLeftBranch( BinNodePosi( T ) x, stack<BinNodePosi( T )> & s, void( *pf )(T & e) )
{
	while( x )
	{
		(*pf)(x->data);
		s.push( x->rChild );
		x = x->lChild;
	}
}
template<typename T>
void GoAlongLeftBranch( BinNodePosi( T ) x, stack < BinNodePosi( T ) > & s )
{
	while( x )
	{
		s.push( x );
		x = x->lChild;
	}
}

template<typename T>
class BinTree
{
public:
	BinNodePosi( T ) _root;

public:
	void TravPre( void( *pf )(T & e) )
	{
		stack<BinNodePosi( T )> s;
		auto x = _root;
		while( true )
		{
			VisitAlongLeftBranch( x, s, pf );
			if( s.empty() )	break;
			x = s.top();
			s.pop();
		}
	}

	void TravIn( void( *pf )(T & e) )
	{
		stack<BinNodePosi( T )> s;
		BinNodePosi(T) x = _root;
		while( true )
		{
			GoAlongLeftBranch( x, s );
			if( s.empty() )	break;
			x = s.top();
			s.pop();
			(*pf)(x->data);
			x = x->rChild;
		}
	}
};


