///////////////////////////////////////////////////////////////////////
// NoSqlDb.cpp - key/value pair in-memory database                   //
// ver 1.0                                                           //
// Application: An implementation of NoSQL database using templates  //
// Platform:    Apple Macbbok pro, Win 8.1 Pro, Visual Studio 2015   //
// Author:      Jashwanth Reddy Gangula,Graduate student,			 //
//				Computer Engineering, Syracuse University            //
//              jgangula@syr.edu								     //
//Proffessor:						                                 //
//Jim Fawcett, CSE687 - Object Oriented Design, Spring 2017          //
///////////////////////////////////////////////////////////////////////
//* Opearations:
//*	Implement definitions defined in heade file operations on the NoSqlDB
//* using the templates declared in the NoSqlDb.h

//* Required Files :
//*-------------- -
//* NoSqlDb.h, StrHelper.h

//* Maintenance History :
//*--------------------
//* Ver 1.0 - Febrauary 6, 2017

#include "NoSqlDb.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "../Utilities/StrHelper.h"

using namespace std;

#ifdef TEST_NOSQLDB

using intData = int;
using Key = NoSqlDb<StrData>::Key;
using Keys = NoSqlDb<StrData>::Keys;

void NoSqlDemoFunc1()
{
	NoSqlDb<StrData> db;

	Element<StrData> elem1;
	elem1.name = "elem1";
	elem1.category = "test";
	elem1.data = "elem1's StrData";
	elem1.description = "elem1 description data";
	elem1.children.clear();

	db.save(elem1.name, elem1);

	Element<StrData> elem2;
	elem2.name = "elem2";
	elem2.category = "test";
	elem2.data = "elem2's StrData";
	elem2.description = "elem2 description data";
	elem2.children.clear();
    db.save(elem2.name, elem2);

	Element<StrData> elem3;
	elem3.name = "elem3";
	elem3.category = "test";
	elem3.data = "elem3's StrData";
	elem3.description = "elem3 description data";
	elem3.children.clear();
	db.save(elem3.name, elem3);

	Element<StrData> elem4;
	elem4.name = "elem4";
	elem4.category = "test";
	elem4.data = "elem4's strData";
	elem4.description = "elem4 description data";
	elem4.children.clear();
	db.save(elem4.name, elem4);

	db.addChildren(elem1.name, elem2.name);
	db.addChildren(elem1.name, elem3.name);
	db.addChildren(elem3.name, elem4.name);

	std::cout << "\n  Retrieving elements from NoSqlDb<string>";
	std::cout << "\n ------------------------------------------\n";

	std::cout << "\n  size of db = " << db.count() << "\n";
	Keys keys = db.keys();
	for (Key key : keys)
	{
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
	}
	std::cout << "\n\n";

	DBWrapper dbwrap(db);
	// dbwrap.restore(dbwrap.save());
	std::string xmlsaved = dbwrap.save();
	std::ofstream ofs;
	ofs.open("../xmlpersist.txt");
	if (ofs.is_open())
	{
		std::cout << "xmlpersist.xml is open for writing" << std::endl;
		ofs << xmlsaved;
		ofs.close();
	}
}

void NoSqlDemoFunc2()
{
	std::cout << "\n  Creating and saving NoSqlDb elements with int data";
	std::cout << "\n ----------------------------------------------------\n";

	NoSqlDb<intData> idb;

	Element<intData> ielem1;
	ielem1.name = "elem1";
	ielem1.category = "test";
	ielem1.data = 1;
	idb.save(ielem1.name, ielem1);

	Element<intData> ielem2;
	ielem2.name = "elem2";
	ielem2.category = "test";
	ielem2.data = 2;
	idb.save(ielem2.name, ielem2);

	Element<intData> ielem3;
	ielem3.name = "elem3";
	ielem3.category = "test";
	ielem3.data = 3;
	idb.save(ielem3.name, ielem3);

	Element<intData> ielem4;
	ielem3.name = "elem4";
	ielem3.category = "test";
	ielem3.data = 4;
	idb.save(ielem3.name, ielem3);

	std::cout << "\n  Retrieving elements from NoSqlDb<int>";
	std::cout << "\n ---------------------------------------\n";

	std::cout << "\n  size of idb = " << idb.count() << "\n";
	Keys ikeys = idb.keys();
	for (Key key : ikeys)
	{
		std::cout << "\n  " << key << ":";
		std::cout << idb.value(key).show();
	}
	std::cout << "\n\n";
}

int main()
{
  std::cout << "\n  Demonstrating NoSql Helper Code";
  std::cout << "\n =================================\n";

  std::cout << "\n  Creating and saving NoSqlDb elements with string data";
  std::cout << "\n -------------------------------------------------------\n";

  NoSqlDemoFunc1();
  NoSqlDemoFunc2();  
}
#endif
/*----< overload insertion operator for std::string properties >---*/
std::ostream& operator<<(std::ostream& out, Property<std::string>& p)
{
	std::string temp = p;
	try {
		out << (temp).c_str();
	}
	catch (std::exception& ex)
	{
		std::cout << "\n  exception:\n  " << ex.what() << "\n";
	}
	return out;
}

/*----< overload insertion operator for std::string properties >---*/
std::ostream& operator<<(std::ostream& out, Property<const std::string>& p)
{
	std::string temp = p;
	try {
		out << (temp).c_str();
	}
	catch (std::exception& ex)
	{
		std::cout << "\n  exception:\n  " << ex.what() << "\n";
	}
	return out;
}

void ElementWrapper::restore(const Xml& xml)
{
	try
	{
		XmlDocument doc(xml);
		std::vector<SPtr> Element = doc.elements("element").select();
		elem_.children.clear();
		/* remove the extra for loops to reduce cyclomatic complexity */
		for (auto pElem : Element)
		{
			if (pElem->value().compare("key") == 0)
				elem_.name = trim(pElem->children()[0]->value());
			else if (pElem->value().compare("value") == 0)
			{
				std::vector<SPtr> valChild = pElem->children();
				for (auto pElem2 : valChild)
				{
					if (pElem2->value().compare("description") == 0)
						elem_.description = trim(pElem2->children()[0]->value());
					else if (pElem2->value().compare("time") == 0)
						elem_.timeDate = trim(pElem2->children()[0]->value());
					else if (pElem2->value().compare("category") == 0)
						elem_.category = trim(pElem2->children()[0]->value());
					else if (pElem2->value().compare("data") == 0)
						elem_.data = trim(pElem2->children()[0]->value());
					else if (pElem2->value().compare("children") == 0)
					{
						std::vector<SPtr> pElem3 = pElem2->children();
						for (auto pElem4 : pElem3)
							if (pElem4->value().compare("key") == 0)
								elem_.children.push_back(trim(pElem4->children()[0]->value()));
					}
				}
			}
		}
	}
	catch (std::exception& ex)
	{
		std::cout << "\n something bad happened in restoring the element ";
		std::cout << "\n " << ex.what();
	}
}

ElementWrapper & ElementWrapper::operator=(const Element<StrData>& elem)
{
	elem_ = elem;
	return *this;
}

ElementWrapper::Xml ElementWrapper::save()
{
	SPtr pRoot = makeTaggedElement("element");
	SPtr pNameElem = makeTaggedElement("key");
	SPtr pTextElem1 = makeTextElement(elem_.name);
	pNameElem->addChild(pTextElem1);
	pRoot->addChild(pNameElem);
	SPtr pvalElem = makeTaggedElement("value");
	SPtr pcategoryElem = makeTaggedElement("category");
	SPtr pTextElem2 = makeTextElement(elem_.category);
	pcategoryElem->addChild(pTextElem2);
	pvalElem->addChild(pcategoryElem);
	SPtr ptimeElem = makeTaggedElement("time");
	SPtr pTextElem3 = makeTextElement(elem_.timeDate);
	ptimeElem->addChild(pTextElem3);
	pvalElem->addChild(ptimeElem);
	SPtr pdescElem = makeTaggedElement("description");
	SPtr pTextElem4 = makeTextElement(elem_.description);
	pdescElem->addChild(pTextElem4);
	pvalElem->addChild(pdescElem);
	SPtr pdataElem = makeTaggedElement("data");
	SPtr pTextElem5 = makeTextElement(elem_.data);
	pdataElem->addChild(pTextElem5);
	pvalElem->addChild(pdataElem);
	SPtr pchildElem = makeTaggedElement("children");
	std::vector<std::string>::iterator it = elem_.children.begin();
	for (it; it != elem_.children.end(); it++)
	{
		SPtr pChildKey = makeTaggedElement("key");
		SPtr pTextElem6 = makeTextElement(*it);
		pChildKey->addChild(pTextElem6);
		pchildElem->addChild(pChildKey);
	}

	pvalElem->addChild(pchildElem);
	pRoot->addChild(pvalElem);
	return pRoot->toString();
}

DBWrapper& DBWrapper::operator=(const NoSqlDb<StrData>& db)
{
	db_ = db;
	return *this;
}

DBWrapper::Xml DBWrapper::save()
{
	XmlDocument doc;
	// make and add root element to doc
	SPtr root = makeTaggedElement("store");
	doc.docElement() = root;

	/*Use keys of key for now just use iterator */
	std::vector<std::string> getKeys = db_.keys();
	std::vector<std::string>::iterator it = getKeys.begin();
	for (it; it != getKeys.end(); it++)
	{
		Element<StrData> elem = db_.value(*it);
		ElementWrapper ew(elem);
		SPtr textElem = makeTextElement(ew.save());
		//	ew.restore(ew.save());
		root->addChild(textElem);
	}

	//// make Property<int> wint element and add to root
	//int wintValue = static_cast<Widget>(*this).wint;
	//std::string wintStr = Convert<int>::toString(wintValue);
	//SPtr pWintElem = makeTaggedElement("wint");
	//pWintElem->addChild(makeTextElement(wintStr));
	//root->addChild(pWintElem);
	//	restore(doc.toString());
	return doc.toString();
}

void DBWrapper::restore(const Xml& xml)
{
	try
	{
		XmlDocument doc(xml);
		std::vector<SPtr> childElem = doc.elements("store").select();
		for (auto pElem : childElem)
		{
			if (pElem->value().compare("element") == 0)
			{
				//	cout << "Element found in the datastore " << endl;
				ElementWrapper ew;
				ew.restore(pElem->toString());
				Element<StrData> restoreElem = static_cast<Element<StrData>>(ew);
				//restoreElem = ew.operator Element<StrData>();
				db_.save(restoreElem.name, restoreElem);
			}
		}
	}
	catch (std::exception& ex)
	{
		std::cout << "\n something bad happened in restroing the database ";
		std::cout << "\n " << ex.what();
	}
}
