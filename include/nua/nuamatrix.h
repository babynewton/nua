#ifndef __NUAC_MATRIX_H__
#define __NUAC_MATRIX_H__

template <class T> class nuaMatrix{
	private:
		int m_rows;
		int m_cols;
		T** val;
		void allocate(void);
		void free_all(void);
	public:
		const int rows(){return m_rows;}
		const int cols(){return m_cols;}
		nuaMatrix();
		~nuaMatrix();
		nuaMatrix(const int _rows, const int _cols);
		T* operator [](const int index);
		bool multiply(nuaMatrix& lval, nuaMatrix& rval);
};

template <class T> nuaMatrix<T>::nuaMatrix():
	m_rows(0),
	m_cols(0),
	val(NULL)
{
};

template <class T> nuaMatrix<T>::~nuaMatrix()
{
	free_all();
};

template <class T> void nuaMatrix<T>::free_all(void){
	if(!val) return;
	for(int i = 0 ; i < m_rows ; i++)
		if(val[i]) delete val[i];
	delete val;
	val = NULL;
}

template <class T> void nuaMatrix<T>::allocate(void){
	if(!m_rows || !m_cols) return;
	val = new T*[m_rows];
	for(int i = 0 ; i < m_rows ; i++)
		val[i] = new T[m_cols];
};

template <class T> nuaMatrix<T>::nuaMatrix(const int _rows, const int _cols):
	m_rows(_rows),
	m_cols(_cols),
	val(NULL)
{
	allocate();
};

template <class T> T* nuaMatrix<T>::operator [](const int index){
	if(index >= m_rows) return NULL;
	return val[index];
};

template <class T> bool nuaMatrix<T>::multiply(nuaMatrix& lval, nuaMatrix& rval){
	if(val) free_all();
	if(!lval.rows() || !lval.cols()) return false;
	if(!rval.rows() || !rval.cols()) return false;
	if(lval.cols() != rval.rows()) return false;
	m_rows = lval.rows();
	m_cols = rval.cols();
	allocate();
	int cnt = lval.cols();
	T value;
	for(int i = 0 ; i < m_rows ; i++){
		for(int j = 0 ; j < m_cols ; j++){
			value = 0;
			for(int k = 0 ; k < cnt ; k++){
				value += lval[i][k] * rval[k][j];
			}
			val[i][j] = value;
		}
	}
	return true;
};
#endif //__NUAC_MATRIX_H__
