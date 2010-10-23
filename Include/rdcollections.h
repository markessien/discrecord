// ThunderWeather Template Library Version 1.0
// Copyright (C) 2001 Snoopstar.com
// All rights reserved.
//
// This file is a part of ThunderWeather Template Library
// The code and information is provided "as-is" without
// warranty of any kind, either expressed or implied.

#if _MSC_VER > 1000
#pragma once
#endif

#if defined(AN_UNDEFINED_SYMBOL)
#else

//#include "stdafx.h"

#define __AFX_H__
struct __POSITION { int unused; };
typedef __POSITION* POSITION;


#ifndef ASSERT_VALID
#define ASSERT_VALID _ASSERT
#endif 

#ifndef ASSERT
#define ASSERT _ASSERT
#endif

//Declarations and definitions for C++ memory allocation functions
//Contains the declarations for C++ memory allocation functions.

#ifndef _INC_NEW
#define _INC_NEW

		#ifdef  __cplusplus

		#ifndef _MSC_EXTENSIONS
		#include <new>
		#endif

		#if     !defined(_WIN32) && !defined(_MAC)
		#error ERROR: Only Mac or Win32 targets supported!
		#endif

		/* Define _CRTIMP */

		#ifndef _CRTIMP
		#ifdef  _DLL
		#define _CRTIMP __declspec(dllimport)
		#else   /* ndef _DLL */
		#define _CRTIMP
		#endif  /* _DLL */
		#endif  /* _CRTIMP */


		/* Define __cdecl for non-Microsoft compilers */

		#if     ( !defined(_MSC_VER) && !defined(__cdecl) )
		#define __cdecl
		#endif

		/* Define _CRTAPI1 (for compatibility with the NT SDK) */

		#ifndef _CRTAPI1
		#if	_MSC_VER >= 800 && _M_IX86 >= 300
		#define _CRTAPI1 __cdecl
		#else
		#define _CRTAPI1
		#endif
		#endif


		/* types and structures */

		#ifndef _SIZE_T_DEFINED
		typedef unsigned int size_t;
		#define _SIZE_T_DEFINED
		#endif

		#ifdef  _MSC_EXTENSIONS
		typedef void (__cdecl * new_handler) ();
		_CRTIMP new_handler __cdecl set_new_handler(new_handler);
		#endif


		#ifndef __PLACEMENT_NEW_INLINE
		#define __PLACEMENT_NEW_INLINE
		inline void *__cdecl operator new(size_t, void *_P)
				{return (_P); }
		#if     _MSC_VER >= 1200
		inline void __cdecl operator delete(void *, void *)
			{return; }
		#endif
		#endif


		/*
		 * new mode flag -- when set, makes malloc() behave like new()
		 */

		_CRTIMP int __cdecl _query_new_mode( void );
		_CRTIMP int __cdecl _set_new_mode( int );

		#ifndef _PNH_DEFINED
		typedef int (__cdecl * _PNH)( size_t );
		#define _PNH_DEFINED
		#endif

		_CRTIMP _PNH __cdecl _query_new_handler( void );
		_CRTIMP _PNH __cdecl _set_new_handler( _PNH );

		/*
		 * Microsoft extension:
		 *
		 * _NO_ANSI_NEW_HANDLER de-activates the ANSI new_handler. Use this special value
		 * to support old style (_set_new_handler) behavior.
		 */

		#ifndef _NO_ANSI_NH_DEFINED
		#define _NO_ANSI_NEW_HANDLER  ((new_handler)-1)
		#define _NO_ANSI_NH_DEFINED
		#endif

		#endif /* __cplusplus */

#endif /* _INC_NEW */

/////////////////////////////////////////////////////////////////////////////
// Low level sanity checks for memory blocks
BOOL AfxIsValidAddress(const void* lp,
		UINT nBytes, BOOL bReadWrite = TRUE);
// AfxIsValidAddress() returns TRUE if the passed parameter points
// to at least nBytes of accessible memory. If bReadWrite is TRUE,
// the memory must be writeable; if bReadWrite is FALSE, the memory
// may be const.

inline BOOL AfxIsValidAddress(const void* lp, UINT nBytes,
	BOOL bReadWrite)
{
	// simple version using Win-32 APIs for pointer validation.
	return (lp != NULL && !IsBadReadPtr(lp, nBytes) &&
		(!bReadWrite || !IsBadWritePtr((LPVOID)lp, nBytes)));
}

	template<class TYPE>
	inline void ConstructElements(TYPE* pElements, int nCount)
	{
		_ASSERT(nCount == 0 ||
			AfxIsValidAddress(pElements, nCount * sizeof(TYPE)));

		// first do bit-wise zero initialization
		memset((void*)pElements, 0, nCount * sizeof(TYPE));

		// then call the constructor(s)
		for (; nCount--; pElements++)
			::new((void*)pElements) TYPE;
	}

	template<class TYPE>
	inline void  DestructElements(TYPE* pElements, int nCount)
	{
	//	_ASSERT(nCount == 0 ||
	//		AfxIsValidAddress(pElements, nCount * sizeof(TYPE)));

		// call the destructor(s)
		for (; nCount--; pElements++)
			pElements->~TYPE();
	}

	template<class TYPE>
	inline void CopyElements(TYPE* pDest, const TYPE* pSrc, int nCount)
	{
		ASSERT(nCount == 0 ||
			AfxIsValidAddress(pDest, nCount * sizeof(TYPE)));
		ASSERT(nCount == 0 ||
			AfxIsValidAddress(pSrc, nCount * sizeof(TYPE)));

		// default is element-copy using assignment
		while (nCount--)
			*pDest++ = *pSrc++;
	}


	template<class TYPE, class ARG_TYPE>
	BOOL CompareElements(const TYPE* pElement1, const ARG_TYPE* pElement2)
	{
		ASSERT(AfxIsValidAddress(pElement1, sizeof(TYPE), FALSE));
		ASSERT(AfxIsValidAddress(pElement2, sizeof(ARG_TYPE), FALSE));

		return *pElement1 == *pElement2;
	}

	template<class ARG_KEY>
	inline UINT HashKey(ARG_KEY key)
	{
		// default identity hash - works for most primitive values
		return ((UINT)(void*)(DWORD)key) >> 4;
	}
#endif // an undefined

/////////////////////////////////////////////////////////////////////////////
#ifndef __AFXPLEX_H__
#define __AFXPLEX_H__

	#ifdef _AFX_PACKING
	#pragma pack(push, _AFX_PACKING)
	#endif

	#ifdef AFX_COLL_SEG
	#pragma code_seg(AFX_COLL_SEG)
	#endif

#if defined(AN_UNDEFINED_SYMBOL)
#else
	struct CPlex     // warning variable length structure
	{
		CPlex* pNext;
	#if (_AFX_PACKING >= 8)
		DWORD dwReserved[1];    // align on 8 byte boundary
	#endif
		// BYTE data[maxNum*elementSize];

		void* data() { return this+1; }

		static CPlex* PASCAL Create(CPlex*& head, UINT nMax, UINT cbElement)
		{
				_ASSERT(nMax > 0 && cbElement > 0);
				CPlex* p = (CPlex*) new BYTE[sizeof(CPlex) + nMax * cbElement];
						// may throw exception
				p->pNext = head;
				head = p;  // change head (adds in reverse order for simplicity)
				return p;
		}
				// like 'calloc' but no zero fill
				// may throw memory exceptions

		void FreeDataChain()       // free this one and links
		{
				CPlex* p = this;
				while (p != NULL)
				{
					BYTE* bytes = (BYTE*) p;
					CPlex* pNext = p->pNext;
					delete[] bytes;
					p = pNext;
				}
		}
	};

	#ifdef AFX_COLL_SEG
	#pragma code_seg()
	#endif

	#ifdef _AFX_PACKING
	#pragma pack(pop)
	#endif
#endif // and undfined
#endif //__AFXPLEX_H__

	// forward declarations
	class COleVariant;
	struct tagVARIANT;

	/////////////////////////////////////////////////////////////////////////////
	// CArray<TYPE, ARG_TYPE>

	template<class TYPE, class ARG_TYPE>
	class CArray
	{
	public:
	// Construction
		CArray();

	// Attributes
		int GetSize() const;
		int GetUpperBound() const;
		void SetSize(int nNewSize, int nGrowBy = -1);

	// Operations
		// Clean up
		void FreeExtra();
		void RemoveAll();

		// Accessing elements
		TYPE GetAt(int nIndex) const;
		void SetAt(int nIndex, ARG_TYPE newElement);
		TYPE& ElementAt(int nIndex);

		// Direct Access to the element data (may return NULL)
		const TYPE* GetData() const;
		TYPE* GetData();

		// Potentially growing the array
		void SetAtGrow(int nIndex, ARG_TYPE newElement);
		int Add(ARG_TYPE newElement);
		int Append(const CArray& src);
		void Copy(const CArray& src);

		// overloaded operator helpers
		TYPE operator[](int nIndex) const;
		TYPE& operator[](int nIndex);

		// Operations that move elements around
		void InsertAt(int nIndex, ARG_TYPE newElement, int nCount = 1);
		void RemoveAt(int nIndex, int nCount = 1);
		void InsertAt(int nStartIndex, CArray* pNewArray);

	// Implementation
	protected:
		TYPE* m_pData;   // the actual array of data
		int m_nSize;     // # of elements (upperBound - 1)
		int m_nMaxSize;  // max allocated
		int m_nGrowBy;   // grow amount

	public:
		~CArray();
	//	void Serialize(CArchive&);
	#ifdef _DEBUG
	//	void Dump(CDumpContext&) const;
		void AssertValid() const;
	#endif
	};

	/////////////////////////////////////////////////////////////////////////////
	// CArray<TYPE, ARG_TYPE> inline functions

	template<class TYPE, class ARG_TYPE>
	inline int CArray<TYPE, ARG_TYPE>::GetSize() const
		{ return m_nSize; }
	template<class TYPE, class ARG_TYPE>
	inline int CArray<TYPE, ARG_TYPE>::GetUpperBound() const
		{ return m_nSize-1; }
	template<class TYPE, class ARG_TYPE>
	inline void CArray<TYPE, ARG_TYPE>::RemoveAll()
		{ SetSize(0, -1); }
	template<class TYPE, class ARG_TYPE>
	inline TYPE CArray<TYPE, ARG_TYPE>::GetAt(int nIndex) const
		{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
			return m_pData[nIndex]; }
	template<class TYPE, class ARG_TYPE>
	inline void CArray<TYPE, ARG_TYPE>::SetAt(int nIndex, ARG_TYPE newElement)
		{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
			m_pData[nIndex] = newElement; }
	template<class TYPE, class ARG_TYPE>
	inline TYPE& CArray<TYPE, ARG_TYPE>::ElementAt(int nIndex)
		{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
			return m_pData[nIndex]; }
	template<class TYPE, class ARG_TYPE>
	inline const TYPE* CArray<TYPE, ARG_TYPE>::GetData() const
		{ return (const TYPE*)m_pData; }
	template<class TYPE, class ARG_TYPE>
	inline TYPE* CArray<TYPE, ARG_TYPE>::GetData()
		{ return (TYPE*)m_pData; }
	template<class TYPE, class ARG_TYPE>
	inline int CArray<TYPE, ARG_TYPE>::Add(ARG_TYPE newElement)
		{ int nIndex = m_nSize;
			SetAtGrow(nIndex, newElement);
			return nIndex; }
	template<class TYPE, class ARG_TYPE>
	inline TYPE CArray<TYPE, ARG_TYPE>::operator[](int nIndex) const
		{ return GetAt(nIndex); }
	template<class TYPE, class ARG_TYPE>
	inline TYPE& CArray<TYPE, ARG_TYPE>::operator[](int nIndex)
		{ return ElementAt(nIndex); }

	/////////////////////////////////////////////////////////////////////////////
	// CArray<TYPE, ARG_TYPE> out-of-line functions

	template<class TYPE, class ARG_TYPE>
	CArray<TYPE, ARG_TYPE>::CArray()
	{
		m_pData = NULL;
		m_nSize = m_nMaxSize = m_nGrowBy = 0;
	}

	template<class TYPE, class ARG_TYPE>
	CArray<TYPE, ARG_TYPE>::~CArray()
	{
		ASSERT_VALID(this);

		if (m_pData != NULL)
		{
			DestructElements<TYPE>(m_pData, m_nSize);
			delete[] (BYTE*)m_pData;
		}
	}

	template<class TYPE, class ARG_TYPE>
	void CArray<TYPE, ARG_TYPE>::SetSize(int nNewSize, int nGrowBy)
	{
		ASSERT_VALID(this);
		ASSERT(nNewSize >= 0);

		if (nGrowBy != -1)
			m_nGrowBy = nGrowBy;  // set new size

		if (nNewSize == 0)
		{
			// shrink to nothing
			if (m_pData != NULL)
			{
				DestructElements<TYPE>(m_pData, m_nSize);
				delete[] (BYTE*)m_pData;
				m_pData = NULL;
			}
			m_nSize = m_nMaxSize = 0;
		}
		else if (m_pData == NULL)
		{
			// create one with exact size
	#ifdef SIZE_T_MAX
			ASSERT(nNewSize <= SIZE_T_MAX/sizeof(TYPE));    // no overflow
	#endif
			m_pData = (TYPE*) new BYTE[nNewSize * sizeof(TYPE)];
			ConstructElements<TYPE>(m_pData, nNewSize);
			m_nSize = m_nMaxSize = nNewSize;
		}
		else if (nNewSize <= m_nMaxSize)
		{
			// it fits
			if (nNewSize > m_nSize)
			{
				// initialize the new elements
				ConstructElements<TYPE>(&m_pData[m_nSize], nNewSize-m_nSize);
			}
			else if (m_nSize > nNewSize)
			{
				// destroy the old elements
				DestructElements<TYPE>(&m_pData[nNewSize], m_nSize-nNewSize);
			}
			m_nSize = nNewSize;
		}
		else
		{
			// otherwise, grow array
			int nGrowBy = m_nGrowBy;
			if (nGrowBy == 0)
			{
				// heuristically determine growth when nGrowBy == 0
				//  (this avoids heap fragmentation in many situations)
				nGrowBy = m_nSize / 8;
				nGrowBy = (nGrowBy < 4) ? 4 : ((nGrowBy > 1024) ? 1024 : nGrowBy);
			}
			int nNewMax;
			if (nNewSize < m_nMaxSize + nGrowBy)
				nNewMax = m_nMaxSize + nGrowBy;  // granularity
			else
				nNewMax = nNewSize;  // no slush

			ASSERT(nNewMax >= m_nMaxSize);  // no wrap around
	#ifdef SIZE_T_MAX
			ASSERT(nNewMax <= SIZE_T_MAX/sizeof(TYPE)); // no overflow
	#endif
			TYPE* pNewData = (TYPE*) new BYTE[nNewMax * sizeof(TYPE)];

			// copy new data from old
			memcpy(pNewData, m_pData, m_nSize * sizeof(TYPE));

			// construct remaining elements
			ASSERT(nNewSize > m_nSize);
			ConstructElements<TYPE>(&pNewData[m_nSize], nNewSize-m_nSize);

			// get rid of old stuff (note: no destructors called)
			delete[] (BYTE*)m_pData;
			m_pData = pNewData;
			m_nSize = nNewSize;
			m_nMaxSize = nNewMax;
		}
	}

	template<class TYPE, class ARG_TYPE>
	int CArray<TYPE, ARG_TYPE>::Append(const CArray& src)
	{
		ASSERT_VALID(this);
		ASSERT(this != &src);   // cannot append to itself

		int nOldSize = m_nSize;
		SetSize(m_nSize + src.m_nSize);
		CopyElements<TYPE>(m_pData + nOldSize, src.m_pData, src.m_nSize);
		return nOldSize;
	}

	template<class TYPE, class ARG_TYPE>
	void CArray<TYPE, ARG_TYPE>::Copy(const CArray& src)
	{
		ASSERT_VALID(this);
		ASSERT(this != &src);   // cannot append to itself

		SetSize(src.m_nSize);
		CopyElements<TYPE>(m_pData, src.m_pData, src.m_nSize);
	}

	template<class TYPE, class ARG_TYPE>
	void CArray<TYPE, ARG_TYPE>::FreeExtra()
	{
		ASSERT_VALID(this);

		if (m_nSize != m_nMaxSize)
		{
			// shrink to desired size
	#ifdef SIZE_T_MAX
			ASSERT(m_nSize <= SIZE_T_MAX/sizeof(TYPE)); // no overflow
	#endif
			TYPE* pNewData = NULL;
			if (m_nSize != 0)
			{
				pNewData = (TYPE*) new BYTE[m_nSize * sizeof(TYPE)];
				// copy new data from old
				memcpy(pNewData, m_pData, m_nSize * sizeof(TYPE));
			}

			// get rid of old stuff (note: no destructors called)
			delete[] (BYTE*)m_pData;
			m_pData = pNewData;
			m_nMaxSize = m_nSize;
		}
	}

	template<class TYPE, class ARG_TYPE>
	void CArray<TYPE, ARG_TYPE>::SetAtGrow(int nIndex, ARG_TYPE newElement)
	{
		ASSERT_VALID(this);
		ASSERT(nIndex >= 0);

		if (nIndex >= m_nSize)
			SetSize(nIndex+1, -1);
		m_pData[nIndex] = newElement;
	}

	template<class TYPE, class ARG_TYPE>
	void CArray<TYPE, ARG_TYPE>::InsertAt(int nIndex, ARG_TYPE newElement, int nCount /*=1*/)
	{
		ASSERT_VALID(this);
		ASSERT(nIndex >= 0);    // will expand to meet need
		ASSERT(nCount > 0);     // zero or negative size not allowed

		if (nIndex >= m_nSize)
		{
			// adding after the end of the array
			SetSize(nIndex + nCount, -1);   // grow so nIndex is valid
		}
		else
		{
			// inserting in the middle of the array
			int nOldSize = m_nSize;
			SetSize(m_nSize + nCount, -1);  // grow it to new size
			// destroy intial data before copying over it
			DestructElements<TYPE>(&m_pData[nOldSize], nCount);
			// shift old data up to fill gap
			memmove(&m_pData[nIndex+nCount], &m_pData[nIndex],
				(nOldSize-nIndex) * sizeof(TYPE));

			// re-init slots we copied from
			ConstructElements<TYPE>(&m_pData[nIndex], nCount);
		}

		// insert new value in the gap
		ASSERT(nIndex + nCount <= m_nSize);
		while (nCount--)
			m_pData[nIndex++] = newElement;
	}

	template<class TYPE, class ARG_TYPE>
	void CArray<TYPE, ARG_TYPE>::RemoveAt(int nIndex, int nCount)
	{
		ASSERT_VALID(this);
		ASSERT(nIndex >= 0);
		ASSERT(nCount >= 0);
		ASSERT(nIndex + nCount <= m_nSize);

		// just remove a range
		int nMoveCount = m_nSize - (nIndex + nCount);
		DestructElements<TYPE>(&m_pData[nIndex], nCount);
		if (nMoveCount)
			memmove(&m_pData[nIndex], &m_pData[nIndex + nCount],
				nMoveCount * sizeof(TYPE));
		m_nSize -= nCount;
	}

	template<class TYPE, class ARG_TYPE>
	void CArray<TYPE, ARG_TYPE>::InsertAt(int nStartIndex, CArray* pNewArray)
	{
		ASSERT_VALID(this);
		ASSERT(pNewArray != NULL);
		ASSERT_VALID(pNewArray);
		ASSERT(nStartIndex >= 0);

		if (pNewArray->GetSize() > 0)
		{
			InsertAt(nStartIndex, pNewArray->GetAt(0), pNewArray->GetSize());
			for (int i = 0; i < pNewArray->GetSize(); i++)
				SetAt(nStartIndex + i, pNewArray->GetAt(i));
		}
	}

	#ifdef _DEBUG
	template<class TYPE, class ARG_TYPE>
	void CArray<TYPE, ARG_TYPE>::AssertValid() const
	{
		CObject::AssertValid();

		if (m_pData == NULL)
		{
			ASSERT(m_nSize == 0);
			ASSERT(m_nMaxSize == 0);
		}
		else
		{
			ASSERT(m_nSize >= 0);
			ASSERT(m_nMaxSize >= 0);
			ASSERT(m_nSize <= m_nMaxSize);
			ASSERT(AfxIsValidAddress(m_pData, m_nMaxSize * sizeof(TYPE)));
		}
	}
	#endif //_DEBUG

	/////////////////////////////////////////////////////////////////////////////
	// CList<TYPE, ARG_TYPE>

	template<class TYPE, class ARG_TYPE>
	class CList
	{
	protected:
		struct CNode
		{
			CNode* pNext;
			CNode* pPrev;
			TYPE data;
		};
	public:
	// Construction
		CList(int nBlockSize = 10);

	// Attributes (head and tail)
		// count of elements
		int GetCount() const;
		BOOL IsEmpty() const;

		// peek at head or tail
		TYPE& GetHead();
		TYPE GetHead() const;
		TYPE& GetTail();
		TYPE GetTail() const;

	// Operations
		// get head or tail (and remove it) - don't call on empty list !
		TYPE RemoveHead();
		TYPE RemoveTail();

		// add before head or after tail
		POSITION AddHead(ARG_TYPE newElement);
		POSITION AddTail(ARG_TYPE newElement);

		// add another list of elements before head or after tail
		void AddHead(CList* pNewList);
		void AddTail(CList* pNewList);

		// remove all elements
		void RemoveAll();

		// iteration
		POSITION GetHeadPosition() const;
		POSITION GetTailPosition() const;
		TYPE& GetNext(POSITION& rPosition); // return *Position++
		TYPE GetNext(POSITION& rPosition) const; // return *Position++
		TYPE& GetPrev(POSITION& rPosition); // return *Position--
		TYPE GetPrev(POSITION& rPosition) const; // return *Position--

		// getting/modifying an element at a given position
		TYPE& GetAt(POSITION position);
		TYPE GetAt(POSITION position) const;
		void SetAt(POSITION pos, ARG_TYPE newElement);
		void RemoveAt(POSITION position);

		// inserting before or after a given position
		POSITION InsertBefore(POSITION position, ARG_TYPE newElement);
		POSITION InsertAfter(POSITION position, ARG_TYPE newElement);

		// helper functions (note: O(n) speed)
		POSITION Find(ARG_TYPE searchValue, POSITION startAfter = NULL) const;
			// defaults to starting at the HEAD, return NULL if not found
		POSITION FindIndex(int nIndex) const;
			// get the 'nIndex'th element (may return NULL)

	// Implementation
	protected:
		CNode* m_pNodeHead;
		CNode* m_pNodeTail;
		int m_nCount;
		CNode* m_pNodeFree;
		struct CPlex* m_pBlocks;
		int m_nBlockSize;

		CNode* NewNode(CNode*, CNode*);
		void FreeNode(CNode*);

	public:
		~CList();
	//	void Serialize(CArchive&);
	#ifdef _DEBUG
	//	void Dump(CDumpContext&) const;
		void AssertValid() const;
	#endif
	};

	/////////////////////////////////////////////////////////////////////////////
	// CList<TYPE, ARG_TYPE> inline functions

	template<class TYPE, class ARG_TYPE>
	inline int CList<TYPE, ARG_TYPE>::GetCount() const
		{ return m_nCount; }
	template<class TYPE, class ARG_TYPE>
	inline BOOL CList<TYPE, ARG_TYPE>::IsEmpty() const
		{ return m_nCount == 0; }
	template<class TYPE, class ARG_TYPE>
	inline TYPE& CList<TYPE, ARG_TYPE>::GetHead()
		{ ASSERT(m_pNodeHead != NULL);
			return m_pNodeHead->data; }
	template<class TYPE, class ARG_TYPE>
	inline TYPE CList<TYPE, ARG_TYPE>::GetHead() const
		{ ASSERT(m_pNodeHead != NULL);
			return m_pNodeHead->data; }
	template<class TYPE, class ARG_TYPE>
	inline TYPE& CList<TYPE, ARG_TYPE>::GetTail()
		{ ASSERT(m_pNodeTail != NULL);
			return m_pNodeTail->data; }
	template<class TYPE, class ARG_TYPE>
	inline TYPE CList<TYPE, ARG_TYPE>::GetTail() const
		{ ASSERT(m_pNodeTail != NULL);
			return m_pNodeTail->data; }
	template<class TYPE, class ARG_TYPE>
	inline POSITION CList<TYPE, ARG_TYPE>::GetHeadPosition() const
		{ return (POSITION) m_pNodeHead; }
	template<class TYPE, class ARG_TYPE>
	inline POSITION CList<TYPE, ARG_TYPE>::GetTailPosition() const
		{ return (POSITION) m_pNodeTail; }
	template<class TYPE, class ARG_TYPE>
	inline TYPE& CList<TYPE, ARG_TYPE>::GetNext(POSITION& rPosition) // return *Position++
		{ CNode* pNode = (CNode*) rPosition;
			_ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
			rPosition = (POSITION) pNode->pNext;
			return pNode->data; }
	template<class TYPE, class ARG_TYPE>
	inline TYPE CList<TYPE, ARG_TYPE>::GetNext(POSITION& rPosition) const // return *Position++
		{ CNode* pNode = (CNode*) rPosition;
			ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
			rPosition = (POSITION) pNode->pNext;
			return pNode->data; }
	template<class TYPE, class ARG_TYPE>
	inline TYPE& CList<TYPE, ARG_TYPE>::GetPrev(POSITION& rPosition) // return *Position--
		{ CNode* pNode = (CNode*) rPosition;
			ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
			rPosition = (POSITION) pNode->pPrev;
			return pNode->data; }
	template<class TYPE, class ARG_TYPE>
	inline TYPE CList<TYPE, ARG_TYPE>::GetPrev(POSITION& rPosition) const // return *Position--
		{ CNode* pNode = (CNode*) rPosition;
			ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
			rPosition = (POSITION) pNode->pPrev;
			return pNode->data; }
	template<class TYPE, class ARG_TYPE>
	inline TYPE& CList<TYPE, ARG_TYPE>::GetAt(POSITION position)
		{ CNode* pNode = (CNode*) position;
			ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
			return pNode->data; }
	template<class TYPE, class ARG_TYPE>
	inline TYPE CList<TYPE, ARG_TYPE>::GetAt(POSITION position) const
		{ CNode* pNode = (CNode*) position;
			ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
			return pNode->data; }
	template<class TYPE, class ARG_TYPE>
	inline void CList<TYPE, ARG_TYPE>::SetAt(POSITION pos, ARG_TYPE newElement)
		{ CNode* pNode = (CNode*) pos;
			ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
			pNode->data = newElement; }

	template<class TYPE, class ARG_TYPE>
	CList<TYPE, ARG_TYPE>::CList(int nBlockSize)
	{
		_ASSERT(nBlockSize > 0);

		m_nCount = 0;
		m_pNodeHead = m_pNodeTail = m_pNodeFree = NULL;
		m_pBlocks = NULL;
		m_nBlockSize = nBlockSize;
	}

	template<class TYPE, class ARG_TYPE>
	void CList<TYPE, ARG_TYPE>::RemoveAll()
	{
		_ASSERT(this);

		// destroy elements
		CNode* pNode;
		for (pNode = m_pNodeHead; pNode != NULL; pNode = pNode->pNext)
			DestructElements<TYPE>(&pNode->data, 1);

		m_nCount = 0;
		m_pNodeHead = m_pNodeTail = m_pNodeFree = NULL;
		m_pBlocks->FreeDataChain();
		m_pBlocks = NULL;
	}

	template<class TYPE, class ARG_TYPE>
	CList<TYPE, ARG_TYPE>::~CList()
	{
		RemoveAll();
		_ASSERT(m_nCount == 0);
	}

	/////////////////////////////////////////////////////////////////////////////
	// Node helpers
	//
	// Implementation note: CNode's are stored in CPlex blocks and
	//  chained together. Free blocks are maintained in a singly linked list
	//  using the 'pNext' member of CNode with 'm_pNodeFree' as the head.
	//  Used blocks are maintained in a doubly linked list using both 'pNext'
	//  and 'pPrev' as links and 'm_pNodeHead' and 'm_pNodeTail'
	//   as the head/tail.
	//
	// We never free a CPlex block unless the List is destroyed or RemoveAll()
	//  is used - so the total number of CPlex blocks may grow large depending
	//  on the maximum past size of the list.
	//

	template<class TYPE, class ARG_TYPE>
	CList<TYPE, ARG_TYPE>::CNode*
	CList<TYPE, ARG_TYPE>::NewNode(CList::CNode* pPrev, CList::CNode* pNext)
	{
		if (m_pNodeFree == NULL)
		{
			// add another block
			CPlex* pNewBlock = CPlex::Create(m_pBlocks, m_nBlockSize,
					 sizeof(CNode));

			// chain them into free list
			CNode* pNode = (CNode*) pNewBlock->data();
			// free in reverse order to make it easier to debug
			pNode += m_nBlockSize - 1;
			for (int i = m_nBlockSize-1; i >= 0; i--, pNode--)
			{
				pNode->pNext = m_pNodeFree;
				m_pNodeFree = pNode;
			}
		}
		_ASSERT(m_pNodeFree != NULL);  // we must have something

		CList::CNode* pNode = m_pNodeFree;
		m_pNodeFree = m_pNodeFree->pNext;
		pNode->pPrev = pPrev;
		pNode->pNext = pNext;
		m_nCount++;
		_ASSERT(m_nCount > 0);  // make sure we don't overflow

		ConstructElements<TYPE>(&pNode->data, 1);
		return pNode;
	}

	template<class TYPE, class ARG_TYPE>
	void CList<TYPE, ARG_TYPE>::FreeNode(CList::CNode* pNode)
	{
		DestructElements<TYPE>(&pNode->data, 1);
		pNode->pNext = m_pNodeFree;
		m_pNodeFree = pNode;
		m_nCount--;
		ASSERT(m_nCount >= 0);  // make sure we don't underflow

		// if no more elements, cleanup completely
		if (m_nCount == 0)
			RemoveAll();
	}

	template<class TYPE, class ARG_TYPE>
	POSITION CList<TYPE, ARG_TYPE>::AddHead(ARG_TYPE newElement)
	{
		ASSERT_VALID(this);

		CNode* pNewNode = NewNode(NULL, m_pNodeHead);
		pNewNode->data = newElement;
		if (m_pNodeHead != NULL)
			m_pNodeHead->pPrev = pNewNode;
		else
			m_pNodeTail = pNewNode;
		m_pNodeHead = pNewNode;
		return (POSITION) pNewNode;
	}

	template<class TYPE, class ARG_TYPE>
	POSITION CList<TYPE, ARG_TYPE>::AddTail(ARG_TYPE newElement)
	{
		_ASSERT(this);

		CNode* pNewNode = NewNode(m_pNodeTail, NULL);
		pNewNode->data = newElement;
		if (m_pNodeTail != NULL)
			m_pNodeTail->pNext = pNewNode;
		else
			m_pNodeHead = pNewNode;
		m_pNodeTail = pNewNode;
		return (POSITION) pNewNode;
	}

	template<class TYPE, class ARG_TYPE>
	void CList<TYPE, ARG_TYPE>::AddHead(CList* pNewList)
	{
		ASSERT_VALID(this);

		ASSERT(pNewList != NULL);
		ASSERT_VALID(pNewList);

		// add a list of same elements to head (maintain order)
		POSITION pos = pNewList->GetTailPosition();
		while (pos != NULL)
			AddHead(pNewList->GetPrev(pos));
	}

	template<class TYPE, class ARG_TYPE>
	void CList<TYPE, ARG_TYPE>::AddTail(CList* pNewList)
	{
		ASSERT_VALID(this);
		ASSERT(pNewList != NULL);
		ASSERT_VALID(pNewList);

		// add a list of same elements
		POSITION pos = pNewList->GetHeadPosition();
		while (pos != NULL)
			AddTail(pNewList->GetNext(pos));
	}

	template<class TYPE, class ARG_TYPE>
	TYPE CList<TYPE, ARG_TYPE>::RemoveHead()
	{
		ASSERT_VALID(this);
		ASSERT(m_pNodeHead != NULL);  // don't call on empty list !!!
		ASSERT(AfxIsValidAddress(m_pNodeHead, sizeof(CNode)));

		CNode* pOldNode = m_pNodeHead;
		TYPE returnValue = pOldNode->data;

		m_pNodeHead = pOldNode->pNext;
		if (m_pNodeHead != NULL)
			m_pNodeHead->pPrev = NULL;
		else
			m_pNodeTail = NULL;
		FreeNode(pOldNode);
		return returnValue;
	}

	template<class TYPE, class ARG_TYPE>
	TYPE CList<TYPE, ARG_TYPE>::RemoveTail()
	{
		ASSERT_VALID(this);
		ASSERT(m_pNodeTail != NULL);  // don't call on empty list !!!
		ASSERT(AfxIsValidAddress(m_pNodeTail, sizeof(CNode)));

		CNode* pOldNode = m_pNodeTail;
		TYPE returnValue = pOldNode->data;

		m_pNodeTail = pOldNode->pPrev;
		if (m_pNodeTail != NULL)
			m_pNodeTail->pNext = NULL;
		else
			m_pNodeHead = NULL;
		FreeNode(pOldNode);
		return returnValue;
	}

	template<class TYPE, class ARG_TYPE>
	POSITION CList<TYPE, ARG_TYPE>::InsertBefore(POSITION position, ARG_TYPE newElement)
	{
		ASSERT_VALID(this);

		if (position == NULL)
			return AddHead(newElement); // insert before nothing -> head of the list

		// Insert it before position
		CNode* pOldNode = (CNode*) position;
		CNode* pNewNode = NewNode(pOldNode->pPrev, pOldNode);
		pNewNode->data = newElement;

		if (pOldNode->pPrev != NULL)
		{
			ASSERT(AfxIsValidAddress(pOldNode->pPrev, sizeof(CNode)));
			pOldNode->pPrev->pNext = pNewNode;
		}
		else
		{
			ASSERT(pOldNode == m_pNodeHead);
			m_pNodeHead = pNewNode;
		}
		pOldNode->pPrev = pNewNode;
		return (POSITION) pNewNode;
	}

	template<class TYPE, class ARG_TYPE>
	POSITION CList<TYPE, ARG_TYPE>::InsertAfter(POSITION position, ARG_TYPE newElement)
	{
		ASSERT_VALID(this);

		if (position == NULL)
			return AddTail(newElement); // insert after nothing -> tail of the list

		// Insert it before position
		CNode* pOldNode = (CNode*) position;
		ASSERT(AfxIsValidAddress(pOldNode, sizeof(CNode)));
		CNode* pNewNode = NewNode(pOldNode, pOldNode->pNext);
		pNewNode->data = newElement;

		if (pOldNode->pNext != NULL)
		{
			ASSERT(AfxIsValidAddress(pOldNode->pNext, sizeof(CNode)));
			pOldNode->pNext->pPrev = pNewNode;
		}
		else
		{
			ASSERT(pOldNode == m_pNodeTail);
			m_pNodeTail = pNewNode;
		}
		pOldNode->pNext = pNewNode;
		return (POSITION) pNewNode;
	}

	template<class TYPE, class ARG_TYPE>
	void CList<TYPE, ARG_TYPE>::RemoveAt(POSITION position)
	{
		ASSERT_VALID(this);

		CNode* pOldNode = (CNode*) position;
		ASSERT(AfxIsValidAddress(pOldNode, sizeof(CNode)));

		// remove pOldNode from list
		if (pOldNode == m_pNodeHead)
		{
			m_pNodeHead = pOldNode->pNext;
		}
		else
		{
			ASSERT(AfxIsValidAddress(pOldNode->pPrev, sizeof(CNode)));
			pOldNode->pPrev->pNext = pOldNode->pNext;
		}
		if (pOldNode == m_pNodeTail)
		{
			m_pNodeTail = pOldNode->pPrev;
		}
		else
		{
			ASSERT(AfxIsValidAddress(pOldNode->pNext, sizeof(CNode)));
			pOldNode->pNext->pPrev = pOldNode->pPrev;
		}
		FreeNode(pOldNode);
	}

	template<class TYPE, class ARG_TYPE>
	POSITION CList<TYPE, ARG_TYPE>::FindIndex(int nIndex) const
	{
		ASSERT_VALID(this);

		if (nIndex >= m_nCount || nIndex < 0)
			return NULL;  // went too far

		CNode* pNode = m_pNodeHead;
		while (nIndex--)
		{
			ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
			pNode = pNode->pNext;
		}
		return (POSITION) pNode;
	}

	template<class TYPE, class ARG_TYPE>
	POSITION CList<TYPE, ARG_TYPE>::Find(ARG_TYPE searchValue, POSITION startAfter) const
	{
		ASSERT_VALID(this);

		CNode* pNode = (CNode*) startAfter;
		if (pNode == NULL)
		{
			pNode = m_pNodeHead;  // start at head
		}
		else
		{
			ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
			pNode = pNode->pNext;  // start after the one specified
		}

		for (; pNode != NULL; pNode = pNode->pNext)
			if (CompareElements<TYPE>(&pNode->data, &searchValue))
				return (POSITION)pNode;
		return NULL;
	}
#ifdef _DEBUG
	template<class TYPE, class ARG_TYPE>
	void CList<TYPE, ARG_TYPE>::AssertValid() const
	{
		CObject::AssertValid();

		if (m_nCount == 0)
		{
			// empty list
			ASSERT(m_pNodeHead == NULL);
			ASSERT(m_pNodeTail == NULL);
		}
		else
		{
			// non-empty list
			ASSERT(AfxIsValidAddress(m_pNodeHead, sizeof(CNode)));
			ASSERT(AfxIsValidAddress(m_pNodeTail, sizeof(CNode)));
		}
	}
#endif //_DEBUG
