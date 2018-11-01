#pragma once
typedef int Rank;
#define DEFAULT_CAPACITY 3

template< typename T >
class Vector
{
public:
	//构造函数
	//容量为c， 规模为s， 所有元素初始化为v
	Vector( int c = DEFAULT_CAPACITY, int s = 0, T *v = 0 )
	{
		_elem = new T[_capacity = c];
		for( _size = 0; _size < s; _elem[_size++] = v );
	}
	//数组整体复制
	Vector( T const *A, Rank n )
	{
		CopyFrom( A, 0, n );
	}
	//区间复制
	Vector( T const *A, Rank lo, Rank hi )
	{
		CopyFrom( A, lo, hi );
	}
	//向量整体复制
	Vector( Vector<T> const &V )
	{
		CopyFrom( V._elem, 0, V._size );
	}
	//区间
	Vector( Vector<T> const &V, Rank lo, Rank hi )
	{
		CopyFrom( V._elem, lo, hi );
	}
	//析构函数
	~Vector() { delete[] _elem; }
	Rank Size() const
	{
		return _size;
	}
	bool Empty() const
	{
		return 0 == _size;
	}
	int Disordered() const
	{
		int n = 0, i = 0;
		while( ++i < _size )
		{
			if( _elem[i - 1] > _elem[i] ) n++;
		}
		return n;
	}
	Rank Find( T const &e ) const
	{
		return Find( e, 0, _size );
	}
	Rank Find( T const &e, Rank lo, Rank hi ) const
	{
		while( (lo < hi--) && (e != _elem[hi]) );

		return hi;
	}
	Rank Search( T const &e ) const
	{
		return (0 >= _size) ? -1, Search( e, 0, _size );
	}
	Rank Search( T const &e, Rank lo, Rank hi ) const;

	T& operator[]( Rank r ) const
	{
		return &_elem[r];
	}
	Vector<T>& operator= ( Vector<T> const &v )
	{
		if( v == this ) { return *this; }
		if( _elem ) delete[] _elem;
		CopyFrom( v._elem, 0, v.Size() );
		return *this;
	}
	T Remove( Rank r )
	{
		T t = _elem[r];
		Remove( r, r + 1 );
		return t;
	}
	int Remove( Rank lo, Rank hi )
	{
		if( lo >= hi ) return 0;
		while( hi < _size )
		{
			_elem[lo++] = _elem[hi++];
		}
		_size = lo;
		Shrink();
		return hi - lo;
	}
	Rank Insert( Rank r, T const &e )
	{
		Expand();
		for( int i = _size; i > r; _elem[i--] = _elem[i - 1] );

		_elem[r] = e;
		_size++;
		return r;
	}
	Rank Insert( T const &e )
	{
		return Insert( _size, e );
	}
	void Sort( Rank lo, Rank hi );
	void Sort() { Sort( 0, _size ); }
	int Deduplicate()
	{
		int old_size = _size;
		Rank i = 1;
		while( i < _size )
		{
			Find( _elem[i], 0, i ) ? ++i : Remove( i );
		}
		return old_size - _size;
	}
	//有序去重
	int Uniquify()
	{
		int old_size = _size;
		Rank s = 0, f = 0;	//s：最后一个不重复元素位置，f：遍历整个数组
		while( ++f < _size )
		{
			if( _elem[s] != _elem[f] )
			{
				_elem[++s] = _elem[f];//将f处元素复制到s+1处，等效于删除(s,f)区间重复元素
			}
		}
		_size = s + 1;
		return old_size - _size;
	}
	//函数指针遍历
	void Traverse( void( *visit )(T&) )
	{
		Rank r = 0;
		while( r < _size ) (*visit)(_elem[r++]);
	}
	//元素类型，重载()遍历
	template< typename VST >
	void Traverse( VST &visit )
	{
		Rank r = 0;
		while( r < _size ) 
			visit( _elem[r++] );
	}

private:
	Rank _size;
	int _capacity;
	T *_elem;

protected:
	void CopyFrom( T const *A, Rank lo, Rank hi )
	{
		_elem = new T[_capacity = 2 * (hi - lo)];
		_size = 0;
		while( lo < hi )
			_elem[_size++] = A[lo++];
	}
	void Expand()
	{
		if( _size < _capacity ) return;//无须扩容
		if( _capacity < DEFAULT_CAPACITY ) _capacity = DEFAULT_CAPACITY;//小于最小容量

		T *old = _elem;
		_elem = new T[_capacity <<= 1];//容量加倍
		
		for( int i = 0; i < _size; _elem[i++] = old[i] );

		delete[] old;//释放原空间
	}
	void Shrink()
	{
		if( _capacity < DEFAULT_CAPACITY << 1 ) return;	//绽放后最小大于default空间大小
		if( _size << 2 > _capacity ) return; //以25%为缩容界限

		T *old = _elem;
		_elem = new T[_capacity >>= 1];
		
		for( int i = 0; i < _size; _elem[i++] = old[i] );

		delete[] old;
	}
	bool Bubble( Rank lo, Rank hi );
	void BubbleSort( Rank lo, Rank hi );
	Rank Max( Rank lo, Rank hi );
	void SelectionSort( Rank lo, Rank hi );
	void Merge( Rank lo, Rank mi, Rank hi );
	void MergeSort( Rank lo, Rank hi );
	Rank Partition( Rank lo, Rank hi );
	void QuickSort( Rank lo, Rank hi );
	void HeapSort( Rank lo, Rank hi );
};