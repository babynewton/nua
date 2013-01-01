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
