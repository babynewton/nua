#ifndef __NUAC_MATRIX_H__
#define __NUAC_MATRIX_H__

template <class T> class nuaMatrix{
	private:
		int m_rows;
		int m_cols;
		T** val;
	public:
		const int rows(){return m_rows;}
		const int cols(){return m_cols;}
		nuaMatrix():
			m_rows(0),
			m_cols(0)
		{}
		nuaMatrix(const int _rows, const int _cols):
			m_rows(_rows),
			m_cols(_cols)
		{}


};
template <class T> class nuaMatrixFactory{
	public:
	static nuaMatrix<T>* create(const int rows, const int cols){
		nuaMatrix<T>* ret = new nuaMatrix<T>(rows, cols);
		return ret;
	}
	static nuaMatrix<T>* multiplicate(nuaMatrix<T>* lval, nuaMatrix<T>* rval){
		int rows = 0, cols = 0;
		//TODO:validity test for production operatoin
		//TODO:production of lval and rval
		nuaMatrix<T>* ret = new nuaMatrix<T>(rows, cols);
		return ret;
	}
};
#endif //__NUAC_MATRIX_H__
