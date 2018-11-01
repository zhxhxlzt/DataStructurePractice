#pragma once
typedef int Rank;
#define DEFAULT_CAPACITY 3

template< typename T >
class Vector
{
public:
	//���캯��
	//����Ϊc�� ��ģΪs�� ����Ԫ�س�ʼ��Ϊv
	Vector( int c = DEFAULT_CAPACITY, int s = 0, T *v = 0 )
	{
		_elem = new T[_capacity = c];
		for( _size = 0; _size < s; _elem[_size++] = v );
	}
	//�������帴��
	Vector( T const *A, Rank n )
	{
		CopyFrom( A, 0, n );
	}
	//���临��
	Vector( T const *A, Rank lo, Rank hi )
	{
		CopyFrom( A, lo, hi );
	}
	//�������帴��
	Vector( Vector<T> const &V )
	{
		CopyFrom( V._elem, 0, V._size );
	}
	//����
	Vector( Vector<T> const &V, Rank lo, Rank hi )
	{
		CopyFrom( V._elem, lo, hi );
	}
	//��������
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
	//����ȥ��
	int Uniquify()
	{
		int old_size = _size;
		Rank s = 0, f = 0;	//s�����һ�����ظ�Ԫ��λ�ã�f��������������
		while( ++f < _size )
		{
			if( _elem[s] != _elem[f] )
			{
				_elem[++s] = _elem[f];//��f��Ԫ�ظ��Ƶ�s+1������Ч��ɾ��(s,f)�����ظ�Ԫ��
			}
		}
		_size = s + 1;
		return old_size - _size;
	}
	//����ָ�����
	void Traverse( void( *visit )(T&) )
	{
		Rank r = 0;
		while( r < _size ) (*visit)(_elem[r++]);
	}
	//Ԫ�����ͣ�����()����
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
		if( _size < _capacity ) return;//��������
		if( _capacity < DEFAULT_CAPACITY ) _capacity = DEFAULT_CAPACITY;//С����С����

		T *old = _elem;
		_elem = new T[_capacity <<= 1];//�����ӱ�
		
		for( int i = 0; i < _size; _elem[i++] = old[i] );

		delete[] old;//�ͷ�ԭ�ռ�
	}
	void Shrink()
	{
		if( _capacity < DEFAULT_CAPACITY << 1 ) return;	//���ź���С����default�ռ��С
		if( _size << 2 > _capacity ) return; //��25%Ϊ���ݽ���

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