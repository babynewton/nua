#ifndef __NUAC_DETERMINANT_H__
#define __NUAC_DETERMINANT_H__

#define NUAC_ACCELERATE_BY_CRAMERS_RULE

template <class T> class nuaLaplaceDeterminant{
	public:
		T determinant(nuaMatrix<T>& a);
};

template <class T> T nuaLaplaceDeterminant<T>::determinant(nuaMatrix<T>& a){
	if(a.rows() != a.cols()) throw "The matrix is not square";
	if(a.rows() == 0) throw "The matrix is empty";
#ifdef NUAC_ACCELERATE_BY_CRAMERS_RULE
	if(a.rows() == 3) return a[0][0] * a[1][1] * a[2][2]
					+ a[0][1] * a[1][2] * a[2][0]
					+ a[0][2] * a[1][0] * a[2][1]
					- a[0][2] * a[1][1] * a[2][0]
					- a[0][0] * a[1][2] * a[2][1]
					- a[0][1] * a[1][0] * a[2][2];
	if(a.rows() == 2) return a[0][0] * a[1][1] - a[0][1] * a[1][0];
#endif //NUAC_ACCELERATE_BY_CRAMERS_RULE
	if(a.rows() == 1) return a[0][0];
	int max_zeros = 0, least_row = 0;
	for(int i = 0 ; i < a.rows() ; i++){
		int zeros = 0;
		for(int j = 0 ; j < a.cols() ; j++) if(a[i][j] == 0 || a[i][j] == 1) zeros++;
		if(zeros > max_zeros) least_row = i;
	}
	T det = 0;
	for(int j = 0 ; j < a.cols() ; j++){
		if(a[least_row][j] == 0) continue;
		nuaMatrix<T> sub;
		sub.subWithout(a, least_row, j);
		T cdet = determinant(sub);
		if(cdet == 0) continue;
		T sgn = ((least_row + j) % 2) ? -a[least_row][j] : a[least_row][j];
		det += sgn * cdet;
	}
	return det;
};

#endif //__NUAC_DETERMINANT_H__
