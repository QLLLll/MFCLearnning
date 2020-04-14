#pragma once
#include<afxwin.h>
#include<vector>
#import "../dll/msxml3.dll" named_guids
using namespace MSXML2;
using namespace std;

class CXmlHelper
{
public:
	CXmlHelper();
	~CXmlHelper();

	void  ReadXml(CString strXmlPath, MSXML2::IXMLDOMNodeListPtr &nodeList);
	void ReadNode(const MSXML2::IXMLDOMNodeListPtr &nodeList, vector<CString>&nodes);

private:
	MSXML2::IXMLDOMDocumentPtr   m_pDoc;
	MSXML2::IXMLDOMElementPtr   m_pDocRoot;
};

