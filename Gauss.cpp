#include<cassert>
#include<limits>  //for numeric_limits
#include<cstddef> //std::size_t
#include<fstream>
#include<iostream> 
#include<iomanip> 

typedef float Element_type;

class Matrix
{
    private:
	size_t mColCount;
	size_t mRowCount;
	Element_type * mData;
	
    public:
	void initialize( const std::size_t r, const std::size_t c )
	{
		mRowCount = r;
		mColCount = c;
		mData = new Element_type[r*c];
	}

	void setElement( const std::size_t i, const std::size_t j,const  Element_type  e)
	{
		mData[i* mColCount + j] = e;
	}
	
	Element_type & getElement( const std::size_t i , const std::size_t j) const
	{
		return mData[ i * mColCount + j ];
	}

	size_t getCol() const
	{
		return mColCount;
	}

	size_t getRow() const
	{
		return mRowCount;
	}
};

void readMatrix( Matrix & matrix, std::ifstream & like_pipe )
	{
	assert( like_pipe.is_open() );
	std::size_t r= std::numeric_limits<std::size_t>::max();
	like_pipe >> r;
	assert(r < std::numeric_limits<Element_type>::max() );
	assert(r > 0);
	assert( like_pipe.is_open() );
	std::size_t c = std::numeric_limits<std::size_t>::max();
	like_pipe >> c;
	assert(c < std::numeric_limits<Element_type>::max() );
	assert(c > 0);
	Element_type x = std::numeric_limits<Element_type>::max();
	matrix.initialize(r,c);
	for( std::size_t i = 0; i < r; ++i)
	{
		for( std::size_t j=0; j< c; ++j)
		{
			like_pipe>> x; 
			assert( x < std::numeric_limits<Element_type>::max());
			matrix.setElement(i,j,x);
		}
	}
}

Element_type myRound( Element_type var)
{
	Element_type value = (int)(var * 100000);
	return (Element_type)value/100000;
}

Element_type myAbs( Element_type var)
{
	if( var < 0)
	{		
	       	return (-1)*var;
	}
	else 
	{
		return var;
	}
}

void writeMatrix(const Matrix & matrix , std::ofstream & like_pipe)
{
	assert(like_pipe.good());
	like_pipe<< matrix.getRow() << " ";
	assert(like_pipe.good());
	like_pipe<< matrix.getCol() << std::endl;
	for(std::size_t i = 0; i < matrix.getRow(); ++i)
	{
		for( std::size_t j = 0; j< matrix.getCol(); ++j)
		{
		       like_pipe<< std::setw(12)<<  matrix.getElement(i,j) << std::endl; //OK version
		}
		like_pipe << std::endl;
	}	
}

void gaussMethod( Matrix & a, Matrix &b, Matrix &x)
{
	std::size_t single_col = 0;
	//pivotization()
	for( std::size_t i =0; i< a.getRow(); ++i)
	{
		for( std::size_t k = i+1; k<a.getRow(); ++k)
		{
			if( myAbs(a.getElement(i,i)) < myAbs(a.getElement(k,i)))
			{
				for( std::size_t j =0; j < a.getCol(); ++j)
				{
					Element_type temp_a = a.getElement(i,j);
					Element_type temp_b = b.getElement(i,single_col);
					a.setElement(i,j, a.getElement(k,j));
					b.setElement(i,single_col, b.getElement(k,single_col));
					a.setElement( k,j,temp_a);
					b.setElement( k,single_col,temp_b);
				}
			}
		}	
	}
	//elimination
	for( std::size_t i = 0; i < a.getRow(); ++i)
	{
		for(std::size_t k= i+1; k<a.getRow(); ++k)
		{
			Element_type temp_a = a.getElement(k,i) / a.getElement(i,i);
			Element_type temp_res_b = 0;
			temp_res_b = b.getElement( k, single_col) - temp_a*b.getElement(i,single_col);
			b.setElement(k,single_col, temp_res_b);
			for(std::size_t j = 0; j < a.getCol(); ++j)
			{
				Element_type temp_res_a = 0;
			        temp_res_a = a.getElement( k,j) - temp_a *a.getElement(i,j);
				a.setElement(k,j, temp_res_a);
			}	
		}
	}
	for(std::size_t i = 0; i < a.getRow(); ++i)
	{	
		for(std::size_t j=0; j < a.getCol(); ++j){
			std::cout<< a.getElement(i,j) << "  ";
		}
		std::cout<< b.getElement(i,single_col);
		std::cout<< "\n";
	}
	//back substitution
	
		std::cout << a.getRow() << " row" ;
		std::cout << a.getCol() << " col\n" ;	
		for(std::size_t i = a.getRow(); i > 0; --i) {// minus enq arel -1
		
			Element_type ele = b.getElement(i-1,0);
			for(std::size_t j=i; j < a.getCol(); ++j)
			{
				if(i !=j){
				ele -= a.getElement(i-1,j-1) * x.getElement(i,single_col);
				}
			}
			 ele = (b.getElement(i,single_col)-ele) / a.getElement(i-1,i-1);
			std::cout<< ele << "\n";
			x.setElement(i-1,single_col, ele);
		}
		
}		
	
int main()
{	
	Matrix a;
	Matrix b;
	Matrix x;
	std::ifstream A("A.txt"), B("B.txt");
	std::ofstream X("x.txt");
	readMatrix(a,A); 
	readMatrix(b,B);
	x.initialize(a.getRow(), b.getCol());
	gaussMethod( a, b, x);
	writeMatrix( x, X);
	return 0;
}
