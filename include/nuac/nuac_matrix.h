/*
opyright (c) 2012 Newton Kim (babynewton73@gmail.com)

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

   3. This notice may not be removed or altered from any source
   distribution.
*/

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
		void add(nuaMatrix& lval, nuaMatrix& rval);
		void substract(nuaMatrix& lval, nuaMatrix& rval);
		void multiply(nuaMatrix& lval, nuaMatrix& rval);
		void transpose(nuaMatrix& oval);
		void identify(void);
		void swap(const int orig, const int dest);
		void copy(nuaMatrix<T>& a);
		void subWithout(nuaMatrix<T>& a, const int row, const int col);
};

template <class T> nuaMatrix<T>::nuaMatrix():
	m_rows(0),
	m_cols(0),
	val(NULL)
{
};

template <class T> void nuaMatrix<T>::copy(nuaMatrix<T>& a) {
	m_rows = a.rows();
	m_cols = a.cols();
	allocate();
	for(int i = 0 ; i < m_rows ; i++)
		memcpy(val[i], a.val[i], sizeof(T) * m_cols);
};

template <class T> nuaMatrix<T>::~nuaMatrix()
{
	free_all();
};

template <class T> void nuaMatrix<T>::identify(void){
	if(!m_rows || !m_cols) throw "An empty matrix";
	if(m_rows != m_cols) throw "The matrix is not sqare";
	for(int i = 0 ; i < m_rows ; i++)
		for(int j = 0 ; j < m_cols ; j++)
			val[i][j] = (i == j) ? 1 : 0;
};

template <class T> void nuaMatrix<T>::free_all(void){
	if(!val) return;
	for(int i = 0 ; i < m_rows ; i++)
		if(val[i]) delete val[i];
	delete val;
	val = NULL;
};

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

template <class T> void nuaMatrix<T>::add(nuaMatrix& lval, nuaMatrix& rval){
	if(val) free_all();
	if(!lval.rows() || !lval.cols()) throw "lval is an empty matrix";
	if(!rval.rows() || !rval.cols()) throw "rval is an empty matrix";
	if(lval.cols() != rval.cols()) throw "Columns are not identical";
	if(lval.rows() != rval.rows()) throw "Rows are not identical";
	m_rows = lval.rows();
	m_cols = rval.cols();
	allocate();
	int cnt = lval.cols();
	for(int i = 0 ; i < m_rows ; i++){
		for(int j = 0 ; j < m_cols ; j++){
			val[i][j] = lval[i][j] + rval[i][j];
		}
	}
};

template <class T> void nuaMatrix<T>::substract(nuaMatrix& lval, nuaMatrix& rval){
	if(val) free_all();
	if(!lval.rows() || !lval.cols()) throw "lval is an empty matrix";
	if(!rval.rows() || !rval.cols()) throw "rval is an empty matrix";
	if(lval.cols() != rval.rows()) throw "Columns of lval and Rows of rval are not same";
	m_rows = lval.rows();
	m_cols = rval.cols();
	allocate();
	T value;
	for(int i = 0 ; i < m_rows ; i++){
		for(int j = 0 ; j < m_cols ; j++){
			val[i][j] = lval[i][j] - rval[i][j];
		}
	}
};

template <class T> void nuaMatrix<T>::multiply(nuaMatrix& lval, nuaMatrix& rval){
	if(val) free_all();
	if(!lval.rows() || !lval.cols()) throw "lval is an empty matrix";
	if(!rval.rows() || !rval.cols()) throw "rval is an empty matrix";
	if(lval.cols() != rval.rows()) throw "Columns of lval and Rows of rval are not same";
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
};

template <class T> void nuaMatrix<T>::transpose(nuaMatrix& oval){
	if(val) free_all();
	if(!oval.rows() || !oval.cols()) throw "val is an empty matrix";
	m_cols = oval.rows();
	m_rows = oval.cols();
	allocate();
	for(int i = 0 ; i < m_rows ; i++){
		for(int j = 0 ; j < m_cols ; j++){
			val[i][j] = oval[j][i];
		}
	}
};

template <class T> void nuaMatrix<T>::swap(const int orig, const int dest){
	if(orig < 0 || dest < 0 || orig >= m_rows || dest >= m_rows) throw "out of bound";
	T* tmp = val[orig];
	val[orig] = val[dest];
	val[dest] = tmp;
};

template <class T> void nuaMatrix<T>::subWithout(nuaMatrix<T>& a, const int row, const int col){
	if(a.rows() <= 1 || a.cols() <= 1) throw "Too small to get a sub matrix";
	if(row < 0 || col < 0 || row >= a.rows() || col >= a.cols()) throw "out of boundary";
	m_rows = a.rows() - 1;
	m_cols = a.cols() - 1;
	allocate();
	int sub_i = 0, sub_j = 0;
	for(int i = 0, sub_i = 0 ; i < a.rows() ; i++){
		if(i == row) continue;
		for(int j = 0, sub_j = 0 ; j < a.cols() ; j++){
			if(j == col) continue;
			val[sub_i][sub_j] = a[i][j];
			sub_j++;
		}
		sub_i++;
	}
};
#endif //__NUAC_MATRIX_H__
