#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <string>
#include <iomanip>

struct	Matrix
{
	int* m_array;
	int n_rows;
	int n_colu;
	int num_m;
	Matrix(const unsigned int M, const unsigned int K)
	{
		n_rows = M;
		n_colu = K;
		m_array = new int[M * K];
	}

	int getNumOfColumns()const
	{
		return n_colu;
	}

	int getNumOfRows()const
	{
		return n_rows;
	}

	int getNumOfMatrix()const
	{
		return num_m;
	}

	int & operator() (const unsigned int i, const unsigned int j)const
	{
		return m_array[i * getNumOfColumns() + j];
	}

	~Matrix(){
		delete[] m_array;
	}	
};

struct	fileReader
{
private:	
	const char* f_name;
	std::ifstream fs;
	unsigned int row_n;
	unsigned int column_n;
public:	
	char c;
	fileReader(const char* fn):f_name(fn)
	{
		fs.open(f_name, std::ios::in);
		assert(fs.is_open() && "File opening");
		if(!(fs >> row_n && fs >> c && fs >> column_n))
		{
			std::cout<< "Cannot read matrix dimensios";
		}
	}

	bool read(int& x)
	{
		if(fs >> x)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool readchar(char& c)
	{
		if(fs >> c)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	int matrix_rows_num()
	{
		return row_n;
	}

	int matrix_column_num()
	{
		return column_n;
	}

	~fileReader()
	{
		fs.close();
	}
};

bool ReadMatrix(Matrix& a, fileReader& ra)
{
	char c;
	if(ra.readchar(c) && ra.read(a.num_m) && ra.readchar(c))
	{
		for(int i = 0; i < a.getNumOfRows(); i++)
		{
			for(int j = 0; j < a.getNumOfColumns(); j++)
			{	
				int x = 0;		
				if(ra.read(x))
				{
					a(i,j)=x;
				}
				else
				{
					return false;
				}
			}
		}
	}
	else
	{
		return false;
	}
}

struct fileWriter
{
	const char* f_name;
	std::ofstream fs;
	fileWriter(const char* fn):f_name(fn)
	{
		fs.open(f_name, std::ios::out);
		assert(fs.is_open() && "File opening");
	}
	void writeint(int& x)
	{
		fs<<x;
	}
	void writestring(std::string& str)
	{
		fs<<str;
	}
	~fileWriter()
	{
		fs.close();
	}
};

/*void writeMatrix(const Matrix& m, fileWriter& w){
	for(std::size_t i = 0; i < m.getNumOfRows(); ++i) {
		for(std::size_t j = 0; j < m.getNumOfColumns(); ++j) {
			w <<  m(i, j);
		}
		w << std::endl;
	}
}*/	

void mult(const Matrix& a,const Matrix& x,Matrix& c) {
	for(int i = 0; i < a.getNumOfRows(); ++i) {
		int S = 0;
		for(int j = 0; j < a.getNumOfColumns(); ++j) {
			S = S + a(i, j) * x(i,0);
			std::cout << S << std::endl;
		}
		c(i,0) = S;
		std::cout << c(i,0) << std::endl;
	//	if(c (i,0) == b(i, 0) {
	//		cout << "a == b"<< std::endl;
	//	}else{
//			std::cout << "a!= b" << std::endl;
				
//		}
	}	
}


void Writer(int& num,int& nnum, fileWriter& w) {
	std::string str = "number of wrong rows = ";
	std::string str2 = "number of right rows = ";
	std::string s = "\n";
	if(nnum != 0) {
		w.writestring(str2);
		w.writeint(nnum);
		w.writestring(s);

	}else{
		w.writestring(str);
		w.writeint(num);
		w.writestring(s);
	}
}

void Write(int& count, fileWriter& w, int& cou) {
	int flag = 1;
	std::string str = "mismatch row = ";
	std::string mis = "match row = ";
	std::string str1 = "\n";
	std::string str2 = " : ";
	if(flag ==0){
		
	w.writestring(str);
	w.writeint(cou);
	w.writestring(str2);
	w.writeint(count);
	w.writestring(str1);
	}else{
	w.writestring(mis);
	w.writeint(cou);
	w.writestring(str2);
	w.writeint(count);
	w.writestring(str1);
	}

}	

void check(const Matrix& c, const Matrix& b, int count,int num) {
	int flag = 1;
	for(int i = 0; i < c.getNumOfRows(); i++) {
		for(int j = 0; j < c.getNumOfColumns(); ++j) {
			if(c(i,0) != b(i,0)) {
				flag = 0;
				 count++;
				 num = c.getNumOfRows();
				 std::cout<< c(i,0);
				continue;
			}else{
				flag = 1;
				count++;
				std::cout<< c(i,0) << std::endl;	
				int nnum = c.getNumOfRows();
				continue;
			}	
		}
	}	
				
}	

int main()
{
	int count = 0;
	int cou = 0;
	int M = 0;
	int K = 0;
	int S = 0;
	Matrix a(M,K), b(M,S), x(M,S), c(M, S);
	fileReader ra("A.txt"),B("B.txt"),X("x.txt");
        fileWriter  w("log.txt");
	ReadMatrix(a,ra);
        ReadMatrix(b,B);
        ReadMatrix(x,X);
		int num = 0;
		mult(a,x,c);
		check(c,b,count,num);
		Writer(num,num, w);
		cou++;
	Write(count,w, cou);
	
return 0;
}
