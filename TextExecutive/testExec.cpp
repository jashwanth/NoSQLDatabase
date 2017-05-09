#pragma once
/////////////////////////////////////////////////////////////////////
// TestExecutive.cpp -                   //
// ver 1.0                                                         //
// Application: A demonstration of implementation of NoSQL database//
//				using templates									   //
// Platform:    Apple Macbbok pro, Win 8.1 Pro, Visual Studio 2013 //
// Author:      Jashwanth Reddy Gangula,Graduate student,		   //
//				Computer Engineering, Syracuse University          //
//              jgangula@syr.edu								   //
//Proffessor:						                               //
//Jim Fawcett, CSE687 - Object Oriented Design, Spring 2017       //
/////////////////////////////////////////////////////////////////////
//* Opearations:
//* A Test Executive which will demonstrate all the requirements of the Project1


//* Required Files :
//*-------------- -
//* NoSqlDb.h,Utilities.h

//* Maintenance History :
//*--------------------
//* Ver 1.0 - Febrauary 6, 2017

#include "../NoSqlDb/NoSqlDb.h"
#include <fstream>
#include "../Utilities/Utilities.h"

using namespace std;
using StrData = std::string;
//using intData = int;
using Keys = NoSqlDb<StrData>::Keys;


void DemoWidgetDataType()
{
	WidgetStruct ws;
	ws.courseId = "CSE 687";
	ws.courseName = "Object Oriented Design";
	NoSqlDb<WidgetStruct> testDemo;
	Element<WidgetStruct> elem1, elem2, elem3, elem4;
	elem1.name = "OOD";
	elem1.category = "course information";
	elem1.data = ws;
	elem1.description = "Understand OOPS";
	elem1.children.clear();
	testDemo.save(elem1.name, elem1);
	elem2.name = "SMA";
	elem2.category = "course information";
	elem2.description = "Concept Documents and C#";
	ws.courseId = "CSE 681";
	ws.courseName = "Software Modelling & Analysis";
	elem2.data = ws;
	elem2.children.clear();
	testDemo.save(elem2.name, elem2);
	elem3.name = "DP";
	elem3.category = "course information";
	ws.courseId = "CSE 776";
	ws.courseName = "Design patterns";
	elem3.data = ws;
	elem3.description = "Presentations on Design Methods";
	elem3.children.clear();
	testDemo.save(elem3.name, elem3);
	testDemo.addChildren(elem3.name, elem1.name);
	testDemo.addChildren(elem3.name, elem2.name);
	Keys Widgetkeys = testDemo.keys();
	for (auto wkey : Widgetkeys)
	{
		Element<WidgetStruct> ews = testDemo.value(wkey);
		cout << ews.showWidgetData() << endl;
	}
}

void DemoShowDbContent(NoSqlDb<StrData> &db)
{
	Title("Display the elements of NoSql DB key/value pair");
	putLine();
	/*Title("Display of the Meta Data Information includes:");
	putLine();
	Title("Item name, Category name, Description name, TimeDate String, Child Keys, templatised Data type");*/
	vector<string> keys = db.keys();
	for (auto keyIterate : keys)
	{
		cout << "\n " << keyIterate << ":";
		std::cout << db.value(keyIterate).show();
	}
	Title("End of DB Display");
	putLine();
}

void checkforPersistence(NoSqlDb<StrData> &db)
{
	cout << "Number of Writes on the Database = " << db.write << endl;
	if (db.write % 3 == 0)
	{
		Title("Req6. Demonstarting the number of writes to persist the DB contents periodically for every 3 writes");
		putLine();
		db.write = 0;
		/* Number of writes is a multiple of 3 persisit the NoSqlDB contents to XML */
		ofstream ofs;
		DBWrapper dbw(db);
		ofs.open("../xmlpersist.txt");
		if (ofs.is_open())
		{
			string newContent = dbw.save();
			ofs << newContent << endl;
			std::cout << "New xml content is " << newContent << endl;
			ofs.close();
		}
		Title("End of Req6");
		putLine();
	}
}

void DemoReq10a()
{
	Title("Req10. Load the NoSql Database from the project package structure xml file");
	putLine();
	ifstream ifs;
	string myxmlbuf;
	ifs.open("../projpackage.txt");
	if (!ifs.is_open())
	{
		Title("Failed to open the project struct package xml file to load the NoSql Database");
		putLine();
		return;
	}
	string line;
	while (getline(ifs, line))
	{
		myxmlbuf += line;
	}
	ifs.close();
	cout << "XML Content is " << myxmlbuf << endl;
	DBWrapper dbw;
	dbw.restore(myxmlbuf);
	NoSqlDb<StrData> db = static_cast<NoSqlDb<StrData>>(dbw);
	DemoShowDbContent(db);
	Title("End of Req10");
	putLine();
}

void DemoReq1()
{
	Title("Req1 . Implemented C++ using the facilities of the standard C++ Libraries and Visual Studio 2015");
	putLines(2);
}

void DemoReq2a()
{
	Title("Req2. Demonstarting the NoSql for widget type object which contains strings courseId and courseName");
	putLines(2);
	DemoWidgetDataType();
}

void DemoReq2bsub2(NoSqlDb<StrData> &db)
{
	Title("Req5. Persisting the NoSql DB to xmlpersist file");
	putLine();
	std::ofstream ofs;
	DBWrapper dbwrap(db);
	std::string xmlsaved = dbwrap.save();
	ofs.open("../xmlpersist.txt");
	if (ofs.is_open())
	{
		std::cout << "xmlpersist.xml is open for writing" << std::endl;
		ofs << xmlsaved;
		ofs.close();
	}
	cout << "XML Content is " << xmlsaved << endl;
	cout << "  Demonstarting the reversible i.e., reload the NoSqlDb from XML file second time " << endl;
	DBWrapper dbwrap2;
	dbwrap2.restore(dbwrap.save());
	NoSqlDb<StrData> dbReload = static_cast<NoSqlDb<StrData>>(dbwrap2);
	cout << "Display the reloaded database" << endl;
	DemoShowDbContent(dbReload);
	Title("End of Req5");
	putLine();

}

void DemoReq9a(NoSqlDb<StrData> &db)
{
	Title("Req8. Demonstarting Query on Query . i.e., run the query on the results returned by the previous query");
	putLine();
	cout << " Performing the filter of Query results on another Query" << endl;
	cout << " Performing the time interval query from 2012/2/6 12:00:00 to current Time on " << endl;
	cout << " Query results returned from the keys search match pattern query 'elem2' " << endl;
	Keys keys = db.MatchKeysFromStartToCurrentTime(db.MatchKeys("elem2"), "2012/2/6 12:00:00");
	for (auto keyIterate : keys)
	{
		cout << "\n Matched key is:" << keyIterate << endl << endl;
	}
	cout << " Performing the filter of Query results on another Query" << endl;
	cout << " Searching the NoSql DB for 'category' match pattern 'some random string' " 
		 << " on all the keys which match the pattern 'elem3' string  " << endl;
	keys = db.MatchKeysWithSameCategory(db.MatchKeys("elem3"), "some random string");
	Title("End of Req8");
	putLine();
	Title("Req9. Demonstrate the Union of Queries on two different Queries");
	putLine();
	cout << " Performing the union of keys with data match pattern:('new element') and keys match pattern('elem2') " << endl;
	std::set<std::string> myUnionSet = db.FindUnionOfKeys(db.MatchKeysWithSameData("new element"), db.MatchKeys("elem2"));
	for (auto myUnionIter : myUnionSet)
	{
		cout << "\n Matched key is: " << myUnionIter << endl;
	}
	Title("End of Req9");
	putLine();

}

void DemoReq7b(NoSqlDb<StrData> &db)
{
	cout << "Searching the database between the time intervals 2010/1/6 12:00:00 and 2017/3/20 18:47:56" << endl;
	Keys keys = db.MatchKeysWithInTimeInterval(db.keys(), "2010/1/6 12:00:00", "2017/3/20 18:47:56");
	for (auto keyIterate : keys)
	{
		cout << "\n Matched key is:" << keyIterate << endl;
	}
	
	cout << "Searching the database from the time 2017/2/6 18:47:56 to current time" << endl;
	keys = db.MatchKeysFromStartToCurrentTime(db.keys(), "2010/1/6 12:00:00");
	for (auto keyIterate : keys)
	{
		cout << "\n Matched key is:" << keyIterate << endl;
	}
}

void DemoReq7a(NoSqlDb<StrData> &db)
{
	Title("Req7.Demonstrating the support of queries");
	putLine();
	cout << "Req7b. Get all the children of element1 " << endl;
	Keys keys = db.getChildrenofElement("elem1");
	for (auto keyIterate : keys)
	{
		cout << "\n key is:" << keyIterate << endl;
	}

	cout << "Req7c. Searching for all the keys which match the pattern 'elem2' string " << endl;
	keys = db.MatchKeys("elem2");
	for (auto keyIterate : keys)
	{
		cout << "\n Matched key is:" << keyIterate << endl;
	}

	cout << "Req 7d.searching for 'some random string' match pattern inside keys which default to all keys  " << endl;
	keys = db.MatchKeys("some random string");
	for (auto keyIterate : keys)
	{
		cout << "\n Matched key is:" << keyIterate << endl;
	}

	cout << "Searching the NoSql DB for category match pattern 'te' " << endl;
	keys = db.MatchKeysWithSameCategory("te");
	for (auto keyIterate : keys)
	{
		cout << "\n Matched key is:" << keyIterate << endl;
	}

	cout << "Searching the NoSql DB for data template match pattern of  'new element' string" << endl;
	keys = db.MatchKeysWithSameData("new element");
	for (auto keyIterate : keys)
	{
		cout << "\n Matched key is:" << keyIterate << endl;
	}
	DemoReq7b(db);
	Title("End of Req7");
	putLine();
	DemoReq9a(db);
	DemoReq10a();
}

void DemoReq3a(NoSqlDb<StrData> &db)
{
	Title("Req3. Demo the addition/deletion of key value pair from DB");
	putLine();
	cout << "Deleting the element element3 from the datastore " << endl;
	db.deleteKey(db.value("elem3"));
	checkforPersistence(db);
	DemoShowDbContent(db);
	Title("End of Req3");
	putLine();
}

void DemoReq4a(NoSqlDb<StrData> &db)
{
	Title("Req4. Demonstrate the Editing of metadata, child relations , replace element with new instance");
	putLine();
	Element<StrData> elem = db.value("elem1");
	elem.description = "change element description";
	cout << "changing the element1 description to: " << elem.description << endl;
	elem.category = " change element category";
	cout << "changing the element1 category to: " << elem.description << endl;
	elem.data = "new element data";
	cout << "changing the element1 data to: " << elem.data << endl;
	ElementWrapper ewr(elem);
	cout << "changing the entire element instance " << endl;
	db.EditElementInstance("elem1", ewr.save(), "element");
	checkforPersistence(db);
	cout << "New Element1 instance is: " << endl;
	cout << db.value("elem1").show() << endl;

	cout << "Demostrate the editing of description field " << endl;
	elem.description = "changing only the description second time";
	db.EditElementInstance("elem1", elem.description, "description");
	checkforPersistence(db);
	cout << db.value("elem1").show() << endl;

	cout << "Demonstrate the editing of category field " << endl;
	elem.category = "changing the category second time";
	db.EditElementInstance("elem1", elem.category, "category");
	checkforPersistence(db);
	cout << db.value("elem1").show() << endl;

	cout << "Demonstrate addition of elem4 as child of elem1" << endl;
	db.addChildren(elem.name, "elem4");
	checkforPersistence(db);
	cout << db.value("elem1").show() << endl;
	Title("End of Req4");
	putLine();

}

void DemoReq2bsub1(string xmlLoad)
{
	cout << "XML Content is " << xmlLoad << endl;
	DBWrapper dbw;
	dbw.restore(xmlLoad);
	NoSqlDb<StrData> db = static_cast<NoSqlDb<StrData>>(dbw);
	
	cout << endl << "Loading the database from XML file xmlpersist" << endl;
	DemoShowDbContent(db);
	DemoReq2bsub2(db);
	DemoReq3a(db);
	DemoReq4a(db);
//	db.deleteKey(db.value("elem3"));

	DemoReq7a(db);
	
	/*ofs.open("../xmlpersist.txt");
	if (ofs.is_open())
	{
	string newContent = dbw.save();
	ofs << newContent << endl;
	std::cout << "New xml content is " << newContent << endl;
	ofs.close();
	}*/
}

void DemoReq2b()
{
	ifstream ifs;
	string myxmlbuf;
	ifs.open("../xmlpersist.txt");
	if (!ifs.is_open())
	{
		Title("Failed to open the xmlpersist xml file to load the NoSql Database");
		putLine();
		Title("Retry opening the file . Run the program again");
		putLine();
		return;
	}
	string line;
	while (getline(ifs, line))
	{
		myxmlbuf += line;
	}
	ifs.close();
	DemoReq2bsub1(myxmlbuf);
}

int main()
{
	try
	{ 
	  Title("Req 11. Starting the Test Executive to demonstrate Requirements 2 to 9");
	  putLine();
	  DemoReq1();
	  DemoReq2a();
	  DemoReq2b();
	  Title("Req12: All the string match pattern is implemeted using Regex Library of C++");
	  putLine();
	  Title("End of Test Executive . It has demonstarted all the requirements 1-12");
	  putLine();
	  getchar();
	}
	catch (exception e)
	{
		Title("Exception caught in the main function");
		putLine();
	}
}