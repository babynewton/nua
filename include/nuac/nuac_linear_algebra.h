#ifndef __NUAC_LINEAR_ALGEBRA_H__
#define __NUAC_LINEAR_ALGEBRA_H__

template <class T> class nuaGaussJordan{
	private:
		nuaVector<unsigned int> pivot;
		void findMax(nuaMatrix<T>& a, T& val, int& row, int& col);
		T abs(T& v);
	public:
		void invert(nuaMatrix<T>& a, nuaMatrix<T>& b);
};

template <class T> T nuaGaussJordan<T>::abs(T& v){
	return (v >= 0) ? v : -v;
};

template <class T> void nuaGaussJordan<T>::findMax(nuaMatrix<T>& a, T& val, int& row, int& col){
	val = 0;
	T v;
	for(int i = 0 ; i < a.rows() ; i++){
		if(pivot[i] != 1){
			for(int j = 0 ; j < a.cols() ; j++){
				if(pivot[j] == 0){
					v = abs(a[i][j]);
					if(v >= val){
						val = v;
						row = i;
						col = j;
					}
				} else if(pivot[j] > 1) {
					throw "The matrix is singular.";
				}
			}
		}
	}
	pivot[col]++;
};

template <class T> void nuaGaussJordan<T>::invert(nuaMatrix<T>& _a, nuaMatrix<T>& b){
	nuaMatrix<T> a(_a);
	pivot.renew(a.cols());
	for(int cnt = 0 ; cnt < a.rows() ; cnt++){
		T val;
		int row, col;
		findMax(a, val, row, col);
		if(val == 0) throw "The matrix is singular";
		if(row != col) {
			a.swap(row, col);
			b.swap(row, col);
		}
		T inv = 1 / val;
		for(int j = 0 ; j < a.cols() ; j++) a[col][j] *= inv;
		for(int j = 0 ; j < b.cols() ; j++) b[col][j] *= inv;
		a[col][col] = 1;
			
		for(int i = 0 ; i < a.rows() ; i++){
			T factor = a[i][col];
			if(i != col){
				for(int j = 0 ; j < a.cols() ; j++) a[i][j] -= a[col][j] * factor;
				for(int j = 0 ; j < b.cols() ; j++) b[i][j] -= b[col][j] * factor;
			}
		}
	}
};

#endif //__NUAC_LINEAR_ALGEBRA_H__
