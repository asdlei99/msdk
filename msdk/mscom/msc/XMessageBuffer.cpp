#include "StdAfx.h"
#include "XMessageBuffer.h"

/*
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
*/

/////////////////////////////////////////////////////////////////////////////
XMessageBuffer::XMessageBuffer()
	:m_xBuffer(),
	 m_dwPos(0)
{
}

/////////////////////////////////////////////////////////////////////////////
XMessageBuffer::XMessageBuffer(DWORD dwDataLen, BOOL& bResult)
	:m_xBuffer(dwDataLen + sizeof(XMessage), bResult),
	 m_dwPos(0)
{
}

/////////////////////////////////////////////////////////////////////////////
XMessageBuffer::~XMessageBuffer()
{
}

/////////////////////////////////////////////////////////////////////////////
XMessageBuffer* XMessageBuffer::Clone()
{
	BOOL bResult = FALSE;
	XMessageBuffer* lpXMessageBuffer = new XMessageBuffer(DataLen(), bResult);
	if (NULL == lpXMessageBuffer)
	{
		return NULL;
	}

	if (!bResult)
	{
		delete lpXMessageBuffer;
		return NULL;
	}

	::CopyMemory(lpXMessageBuffer->Buffer(), Buffer(), Len());
	return lpXMessageBuffer;
}

/////////////////////////////////////////////////////////////////////////////
XMessage* XMessageBuffer::Header()
{
	_ASSERT(m_xBuffer.Len() >= sizeof(XMessage));
	return (XMessage*)m_xBuffer.Buffer();
}

/////////////////////////////////////////////////////////////////////////////
LPBYTE XMessageBuffer::Data()
{
	return m_xBuffer.Buffer() + sizeof(XMessage);
}

/////////////////////////////////////////////////////////////////////////////
DWORD XMessageBuffer::DataLen()
{
	return m_xBuffer.Len() - sizeof(XMessage);
}

/////////////////////////////////////////////////////////////////////////////
LPBYTE XMessageBuffer::RestBuffer()
{
	return m_xBuffer.Buffer() + m_dwPos;
}

/////////////////////////////////////////////////////////////////////////////
DWORD XMessageBuffer::RestLen()
{
	return m_xBuffer.Len() - m_dwPos;
}

/////////////////////////////////////////////////////////////////////////////
LPBYTE XMessageBuffer::Buffer()
{
	return m_xBuffer.Buffer();
}

/////////////////////////////////////////////////////////////////////////////
DWORD XMessageBuffer::Len()
{
	return m_xBuffer.Len();
}

/////////////////////////////////////////////////////////////////////////////
DWORD XMessageBuffer::Pos()
{
	return m_dwPos;
}

/////////////////////////////////////////////////////////////////////////////
VOID XMessageBuffer::Pos(DWORD dwPos)
{
	m_dwPos = dwPos;
}

/////////////////////////////////////////////////////////////////////////////
VOID XMessageBuffer::ResetPos()
{
	m_dwPos = 0;
}

/////////////////////////////////////////////////////////////////////////////
VOID XMessageBuffer::Advance(DWORD dwDelta)
{
	m_dwPos += dwDelta;
	_ASSERT(m_dwPos <= m_xBuffer.Len());
}

/////////////////////////////////////////////////////////////////////////////
BOOL XMessageBuffer::IsFull()
{
	_ASSERT(m_dwPos <= m_xBuffer.Len());
	return m_dwPos == m_xBuffer.Len();
}

/////////////////////////////////////////////////////////////////////////////
BOOL XMessageBuffer::Alloc(DWORD dwDataLen)
{
	BOOL bResult = m_xBuffer.Alloc(dwDataLen + sizeof(XMessage));
	if (bResult)
	{
		m_dwPos = 0;
	}
	return bResult;
}

/////////////////////////////////////////////////////////////////////////////
BOOL XMessageBuffer::Realloc(DWORD dwDataLen)
{
	//Realloc��Ӱ��m_dwPos;
	return m_xBuffer.Realloc(dwDataLen + sizeof(XMessage));
}

/////////////////////////////////////////////////////////////////////////////
VOID XMessageBuffer::AttachBuffer(LPBYTE lpBuf, DWORD dwLen)
{
	m_xBuffer.AttachBuffer(lpBuf, dwLen);
	m_dwPos = 0;
}

/////////////////////////////////////////////////////////////////////////////
VOID XMessageBuffer::DettachBuffer(LPBYTE& lpBuf, DWORD& dwLen)
{
	m_xBuffer.DettachBuffer(lpBuf, dwLen);
	m_dwPos = 0;
}

/////////////////////////////////////////////////////////////////////////////
VOID XMessageBuffer::DettachBuffer()
{
	m_xBuffer.DettachBuffer();
	m_dwPos = 0;
}

/////////////////////////////////////////////////////////////////////////////