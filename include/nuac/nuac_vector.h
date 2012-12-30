#ifndef __NUAC_VECTOR_H__
#define __NUAC_VECTOR_H__

template <class T> class nuaVector{
	private:
		bool m_doFree;
		T* m_line;
		int m_len;
	public:
		unsigned int len(void);
		nuaVector();
		nuaVector(T* _line, const int _len);
		~nuaVector();
		T& operator [](const int index);
		void renew(const int size);
		void resize(const int size);
};

template <class T> nuaVector<T>::nuaVector():
	m_line(NULL),
	m_len(0),
	m_doFree(false)
{
};

template <class T> nuaVector<T>::nuaVector(T* _line, const int _len):
	m_line(_line),
	m_len(_len),
	m_doFree(false)
{
};

template <class T> nuaVector<T>::~nuaVector()
{
	if(m_doFree) delete m_line;
};

template <class T> T& nuaVector<T>::operator [](const int index){
	if(m_len <= index) throw "out of boundary";
	return (T&)m_line[index];
};

template <class T> unsigned int nuaVector<T>::len(void){
	return m_len;
};

template <class T> void nuaVector<T>::renew(const int size){
	resize(size);
	memset(m_line, 0, sizeof(T) * m_len);
};

template <class T> void nuaVector<T>::resize(const int size){
	if(m_len != size){
		if(m_doFree) delete m_line;
		m_line = new T [size];
		m_doFree = true;
		m_len = size;
	}
};
#endif //__NUAC_VECTOR_H__

