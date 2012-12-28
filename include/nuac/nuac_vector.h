#ifndef __NUAC_VECTOR_H__
#define __NUAC_VECTOR_H__

template <class T> class nuaVector{
	private:
		const T* line;
	public:
		const int len;
		nuaVector(const T* _line, const int _len);
		T& operator [](const int index);
};

template <class T> nuaVector<T>::nuaVector(const T* _line, const int _len):
	line(_line),
	len(_len)
{
};

template <class T> T& nuaVector<T>::operator [](const int index){
	if(len <= index) throw "out of boundary";
	return (T&)line[index];
};
#endif //__NUAC_VECTOR_H__
