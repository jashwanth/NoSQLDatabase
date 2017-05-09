#pragma once
/////////////////////////////////////////////////////////////////////
// NoSqlDb.h - key/value pair in-memory database                   //
// ver 1.0                                                         //
// Application: An implementation of NoSQL database using templates//
// Platform:    Apple Macbbok pro, Win 8.1 Pro, Visual Studio 2015 //
// Author:      Jashwanth Reddy Gangula,Graduate student,		   //
//				Computer Engineering, Syracuse University          //
//              jgangula@syr.edu								   //
//Proffessor:						                               //
//Jim Fawcett, CSE687 - Object Oriented Design, Spring 2017        //
/////////////////////////////////////////////////////////////////////


 //* Operations :
 //*------------------ -
 //* NoSQL database constructed as part of this project is a key value 
 //* type database which is generalized for any 'Data' type using the power 
 //* tempalates in cpp
 //*
 //* This package provides a complete implementation of NoSQL Database.
 //* The prime functionalities are:
 //* 1. The Data type which the user wants to store is generic. 
 //* 2. The user can store elements of his custom type, Add keys to the store,
 //* Edit the metadata and Data of a key, Add or delete relations of an Element.
 //* 3. Persistance mechanism has been implemented. The store can be populated 
 //* from an xml and the store can be persisted to an xml using commands.
 //* 4. Wrapper Classes that implement the Ipersist interface are used to 
 // persist and restore the database content to and from XML.
 //* 4. Query mechanism has been implemented which enables the user to query on the
 //* database, querying on the keys filtered from a query, Union of multiple queries.
 //* XmlParser objects throw if given an invalid path to an XML file.

 //* Class operations:
 //* Element: It is the class which corresponds to every element in the store.
 //* NoSqlDB: It is the class which corresponds to the database store.
 //* ElementWrapper: This class provides a wrapper so that Element can be persisted 
 //* to the xml.
 //* DBWrapper: This class provides a wrapper so that the the store can be persisted 
 //* to the xml.


 //* Required Files :
 //*-------------- -
 //*-XmlDocument.h, XmlDocument.cpp,
 //*XmlElement.h, XmlElement.cpp
 //*CppProperties.h,CppProperties.cpp
 //*PersistHelp.h,PersistHelp.cpp
 //*StrHelper.h



 //* Maintenance History :
 //*--------------------
 //* Ver 1.0 - Febrauary 6, 2017


#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>
#include <regex>
#include <set>
#include <ctime>
#include "../CppProperties/CppProperties.h"
#include "../Persist/PersistHelp.h"
#include "../Utilities/StrHelper.h"

using Xml = std::string;
using StrData = std::string;  // added by me

typedef struct Widgetstruct
{
	Property<std::string> courseId;
	Property<std::string> courseName;
}WidgetStruct;

/////////////////////////////////////////////////////////////////////
// Element class represents a data record in our NoSql database
// - in our NoSql database that is just the value in a key/value pair
// - it needs to store child data, something for you to implement
//
template<typename Data>
class Element
{
public:
  using Name = std::string;
  using Category = std::string;
  using TimeDate = std::string;
  using Description = std::string;

  Property<Name> name;            // metadata
  Property<Category> category;    // metadata
  Property<TimeDate> timeDate;    // metadata
  Property<Data> data;            // data
  Property<Description> description;  // metadata 
  std::vector<std::string> children;
  //Property<Children> children;
								 
  std::string show();
  std::string showWidgetData();
};

//// Use this function to show the specific Data instanstiated by the 
// template for WidgetStruct memeber defined above
template<typename Data>
std::string Element<Data>::showWidgetData()
{
	std::ostringstream out;
	out.setf(std::ios::adjustfield, std::ios::left);
	WidgetStruct w = data;
	out << "\n    " << std::setw(8) << "name" << " : " << name;
	out << "\n    " << std::setw(8) << "category" << " : " << category;
	out << "\n    " << std::setw(8) << "timeDate" << " : " << timeDate;
	out << "\n    " << std::setw(8) << "Description" << " : " << description;
	out << "\n    " << std::setw(8) << "data" << " : ";
	out << "\n    " << std::setw(8) << "Course Code" << " : " <<  w.courseId;
	out << "\n    " << std::setw(8) << "Course Name" << " : " << w.courseName;
	out << "\n    " << std::setw(8) << "Children size" << " : " << children.size();
	for (unsigned int i = 0; i < children.size(); i++)
	{
		out << "\n    " << std::setw(8) << "Child  " << " : " << children[i];
	}
	out << "\n";
	return out.str();
}

template<typename Data>
std::string Element<Data>::show()
{
  // show children when you've implemented them

  std::ostringstream out;
  out.setf(std::ios::adjustfield, std::ios::left);
  out << "\n    " << std::setw(8) << "name" << " : " << name;
  out << "\n    " << std::setw(8) << "category" << " : " << category;
  out << "\n    " << std::setw(8) << "timeDate" << " : " << timeDate;
  out << "\n    " << std::setw(8) << "Description" << " : " << description;
  out << "\n    " << std::setw(8) << "data" << " : " << data;
  out << "\n    " << std::setw(8) << "Children size" << " : " << children.size();
  for (unsigned int i = 0; i < children.size(); i++)
  {
	  out << "\n    " << std::setw(8) << "Child  " << " : " << children[i];
  }
  out << "\n";
  return out.str();
}


/////////////////////////////////////////////////////////////////////
// NoSqlDb class is a key/value pair in-memory database
// - stores and retrieves elements
// - you will need to add query capability
//   That should probably be another class that uses NoSqlDb
//
template<typename Data>
class NoSqlDb
{
public:
  using Key = std::string;
  using Keys = std::vector<Key>;
  using UnionKeys = std::set<std::string>;

  Keys keys();
  bool save(Key key, Element<Data> elem);
  bool deleteKey(Element<Data> elem);
  void deleteChildFromParent(Key curKey);
  void addChildren(Key key1, Key key2);
  Keys getChildrenofElement(Key key1);
  Element<Data> value(Key key);
  void EditElementInstance(Key name, std::string data, std::string type);
  Keys MatchKeys(Key );
  Keys MatchKeys(Key, Keys);
  Keys MatchKeysWithSameCategory(Key categorystr);
  Keys MatchKeysWithSameCategory(Keys ,Key  categorystr);
  Keys MatchKeysWithSameData(Key datastr);
  time_t getEpochFromStringVector(Keys );
  time_t getEpochTimefromString(std::string str);
  Key convertEpochToString(void);
  Keys MatchKeysWithInTimeInterval(Keys input, std::string time1, std::string time2);
  Keys MatchKeysFromStartToCurrentTime(Keys input, std::string time1);
  UnionKeys FindUnionOfKeys(Keys k1, Keys k2);
  size_t count();
  int write = 0; /* this variable tells the number of writes after which the db should
				 be persisted to XML file */
private:
  
  using Item = std::pair<Key, Element<Data>>;
  
  std::unordered_map<Key,Element<Data>> store; 
};

  /////////////////////////////////////////////////////////////////////
  // Element Wrapper class that implements the IPersisit inteface for saving and
  // restoring the element.
  class ElementWrapper : public IPersist<Element<StrData> >
  {
  public:
	  ElementWrapper() {}
	  ElementWrapper(const Element<StrData>& elem) : elem_(elem) { }
	  ElementWrapper& operator=(const Element<StrData>& elem);
	  Xml save();
	  void restore(const Xml& xml);
	  operator Element<StrData>()
	  {
		  return elem_;
	  }
  private:
	  Element<StrData> elem_;
  };

  //////////////////////////////////////////////////////////////////////
  // Persist NoSQL DB using DBWrapper class
  class DBWrapper : public IPersist<NoSqlDb<StrData> >
  {
  public:
	  DBWrapper()
	  {}
	  DBWrapper(const NoSqlDb<StrData>& db) : db_(db) { }
	  DBWrapper& operator=(const NoSqlDb<StrData>& db);
	  Xml save();
	  void restore(const Xml& xml);
	  operator NoSqlDb<StrData>()
	  {
		  return db_;
	  }
  private:
	  NoSqlDb<StrData> db_;
  };

  template<typename Data>
  typename NoSqlDb<Data>::UnionKeys NoSqlDb<Data>::FindUnionOfKeys(Keys k1, Keys k2)
  {
	  UnionKeys myset;
	  myset.clear();
	  for (auto key : k1)
	  {
		  myset.insert(key);
	  }
	  for (auto key : k2)
	  {
		  myset.insert(key);
	  }
	  return myset;
  }

  template<typename Data>
  typename NoSqlDb<Data>::Keys NoSqlDb<Data>::MatchKeysFromStartToCurrentTime(Keys input, std::string time1)
  {
	  time_t startTime = getEpochTimefromString(time1);
	  time_t endTime = time(NULL);
	  time(&endTime);
	  Keys finalResult;
	  finalResult.clear();
	  try
	  {
		  for (Key str : input)
		  {
			  Element<Data> elemeget = value(str);
			  time_t elemeSaveTime = getEpochTimefromString(elemeget.timeDate);
			  if ((elemeSaveTime >= startTime) && (elemeSaveTime <= endTime))
			  {
				  finalResult.push_back(elemeget.name);
			  }
		  }
	  }
	  catch (exception e) {
		  cout << "Exception occured in the searching the keys in a given time interval " << endl;
	  }
	  if (finalResult.empty())
	  {
		  finalResult.push_back("NO Keys were found in the given time interval");
	  }
	  return finalResult;
  }

 template<typename Data>
 typename NoSqlDb<Data>::Keys NoSqlDb<Data>::MatchKeysWithInTimeInterval(Keys input, std::string time1, std::string time2)
 {
	 time_t startTime = getEpochTimefromString(time1);
	 time_t endTime = getEpochTimefromString(time2);
	 Keys finalResult;
	 finalResult.clear();
	 try
	 {
	   for (Key str : input)
	   {
		   Element<Data> elemeget = value(str);
		   time_t elemeSaveTime = getEpochTimefromString(elemeget.timeDate);
		   if ((elemeSaveTime >= startTime) && (elemeSaveTime <= endTime))
		   {
			   finalResult.push_back(elemeget.name);
		   }
	   }
	 }
	 catch (exception e) {
		 cout << "Exception occured in the searching the keys in a given time interval " << endl;
	 }
	 if (finalResult.empty())
	 {
		 finalResult.push_back("NO Keys were found in the given time interval");
	 }
	 return finalResult;
 }

template<typename Data>
typename NoSqlDb<Data>::Keys NoSqlDb<Data>::keys()
{
  Keys keys;
  for (Item item : store)
  {
    keys.push_back(item.first);
  }
  return keys;
}

template<typename Data>
typename NoSqlDb<Data>::Key NoSqlDb<Data>::convertEpochToString(void)
{
	Key result;
	result.clear();
	time_t now = time(0);
	struct tm timeInfo;
	time(&now);
	localtime_s(&timeInfo,&now);
	stringstream ss;
	ss.str("");
	// 2014/05/02 13:00:03
	ss << (timeInfo.tm_year + 1900) << "/" << (timeInfo.tm_mon + 1) << "/"
	   << (timeInfo.tm_mday) << " " << timeInfo.tm_hour << ":" << timeInfo.tm_min
	   << ":" << timeInfo.tm_sec;
	return ss.str();
}

template<typename Data>
typename NoSqlDb<Data>::Keys NoSqlDb<Data>::MatchKeysWithSameData(Key datastr)
{
	Keys keyList = keys();
	Keys finalResult;
	finalResult.clear();
	try
	{
		regex e("[a-zA-Z1-9 ]*(" + datastr + ")[a-zA-Z1-9 ]*");
		for (string str : keyList)
		{
			Element<Data> elemeget = value(str);
			string elemData = elemeget.data;
			if (regex_match(elemData, e))
			{
				finalResult.push_back(elemeget.name);
			}
		}
	}
	catch (exception e) {
		cout << "Exception occured in the pattern searching of Data with regular expression " << endl;
	}
	if (finalResult.empty())
	{
		finalResult.push_back("NO Data matches found");
	}
	return finalResult;
}

template<typename Data>
typename NoSqlDb<Data>::Keys NoSqlDb<Data>::MatchKeysWithSameCategory(Keys input, Key keystr)
{
	Keys keyList = input;
	Keys finalResult;
	finalResult.clear();
	try
	{
		regex e("[a-z1-9 ]*(" + keystr + ")[a-z1-9 ]*");

		for (string str : keyList)
		{
			Element<Data> elemeget = value(str);
			string category = elemeget.category;
			if (regex_match(category, e))
			{
				finalResult.push_back(elemeget.name);
			}
		}
	}
	catch (exception e) {
		cout << "Exception occured in the pattern searching of category with regular expression " << endl;
	}

	if (finalResult.empty())
	{
		finalResult.push_back("NO category matches found");
	}
	return finalResult;
}
template<typename Data>
typename NoSqlDb<Data>::Keys NoSqlDb<Data>::MatchKeysWithSameCategory(Key keystr)
{
	Keys keyList = keys();
	Keys finalResult;
	finalResult.clear();
	try
	{
		regex e("[a-z1-9 ]*(" + keystr + ")[a-z1-9 ]*");
		
		for (string str : keyList)
		{
			Element<Data> elemeget = value(str);
			string category = elemeget.category;
			if (regex_match(category, e))
			{
				finalResult.push_back(elemeget.name);
			}
		}
	}
	catch (exception e) {
		cout << "Exception occured in the pattern searching of category with regular expression " << endl;
	}

	if (finalResult.empty())
	{
		finalResult.push_back("NO category matches found");
	}
	return finalResult;
}

template<typename Data>
time_t NoSqlDb<Data>::getEpochFromStringVector(Keys myVector) 
{
	struct tm t = { 0 };  // Initalize to all 0's
	t.tm_year = stoi(myVector.at(0)) - 1900;  // This is year-1900, so 112 = 2012
	t.tm_mon = stoi(myVector.at(1))-1; // month from 0-11 so substract 1 
	t.tm_mday = stoi(myVector.at(2));
	t.tm_hour = stoi(myVector.at(3));
	t.tm_min = stoi(myVector.at(4));
	t.tm_sec = stoi(myVector.at(5));
	time_t timeSinceEpoch = mktime(&t);
	return timeSinceEpoch;
}

template<typename Data>
time_t NoSqlDb<Data>::getEpochTimefromString(std::string str) 
{
	// 2014/05/02 13:00:03
	// the format of the string is expected to be year/month/day 24hr:60min:60sec
	std::vector<std::string> wholevector;  
	std::istringstream iss(str);
	for (std::string s; iss >> str; ) {
		wholevector.push_back(str);
	}

	std::string Date = wholevector.at(0);
	std::string Time = wholevector.at(1);
	std::string word;
	stringstream stream(Date);
	vector<std::string> result;
	while (getline(stream, word, '/')) {
		result.push_back(word);
	}

	string word1;
	stringstream stream1(Time);
	vector<string> TimeVector;
	while (std::getline(stream1, word1, ':')) {
		//cout << word << "\n";
		result.push_back(word1);
	}
	
	return getEpochFromStringVector(result);
}

template<typename Data>
typename NoSqlDb<Data>::Keys NoSqlDb<Data>::MatchKeys(Key keystr)
{
	Keys keyList = keys();
	Keys matchedKeys;
	try 
	{
		regex e("[a-z1-9 ]*(" + keystr + ")[a-z1-9 ]*");

		for (string str : keyList) {
			if (regex_match(str, e)) {
				matchedKeys.push_back(str);
			}
		}
	}
	catch (exception e) {
		cout << "Exception Occured" << endl;
		cout << "The pattern you are searching has some error" << endl;
	}
	if (!(matchedKeys.empty())) {
		return matchedKeys;
	}
	else {
		cout << "No keys are fetched matching the pattern" << endl;
		return keyList;
	}


}

template<typename Data>
typename NoSqlDb<Data>::Keys NoSqlDb<Data>::MatchKeys(Key keystr,Keys keyList)
{
	Keys matchedKeys;
	try
	{
		regex e("[a-z1-9 ]*(" + keystr + ")[a-z1-9 ]*");

		for (string str : keyList) {
			if (regex_match(str, e)) {
				matchedKeys.push_back(str);
			}
		}
	}
	catch (exception e) {
		cout << "Exception Occured" << endl;
		cout << "The pattern you are searching has some error" << endl;
	}
	if (!(matchedKeys.empty())) {
		return matchedKeys;
	}
	else {
		cout << "No keys are fetched matching the pattern" << endl;
		return keyList;
	}
}

template<typename Data>
typename NoSqlDb<Data>::Keys NoSqlDb<Data>::getChildrenofElement(Key key1)
{
	Keys keys;
	if (store.find(key1) != store.end())
	{
		Element<StrData> curElem = store[key1];
		for (size_t i = 0; i < curElem.children.size(); i++)
		{
			keys.push_back(curElem.children[i]);
		}
	}
	return keys;
}

template<typename Data>
bool NoSqlDb<Data>::save(Key key, Element<Data> elem)
{
  if (store.find(key) != store.end())
  {
	  //	return false;
	  store.erase(store.find(key));
  }
 // time_t now = time(0);
 // struct tm* timeInfo;
 //// string trimLine = ctime(&now);
 // time(&now);
 // /*char result[30];
 // ctime_s(result, sizeof(result), &now);
 // trimLine.copy(result, 0, 30);*/
 //// trimLine.pop_back();
 // //  trimLine.erase(trimLine.length() - 1, 1);
 // timeInfo = localtime(&now);
 // stringstream ss;
 // ss.str("");
 // // 2014/05/02 13:00:03
 // ss << (timeInfo->tm_year + 1900) << "/" << (timeInfo->tm_mon + 1) << "/"
	// << (timeInfo->tm_mday) << " " << timeInfo->tm_hour << ":" << timeInfo->tm_min
	// << ":" << timeInfo->tm_sec;
  elem.timeDate = convertEpochToString();
  store[key] = elem;
  write++;
  return true;
}

template<typename Data>
Element<Data> NoSqlDb<Data>::value(Key key)
{
  if (store.find(key) != store.end())
    return store[key];
  return Element<Data>();
}

template<typename Data>
size_t NoSqlDb<Data>::count()
{
  return store.size();
}

template <typename Data>
void NoSqlDb<Data>::deleteChildFromParent(Key curKey)
{
	std::unordered_map<Key, Element<Data>>::iterator it1 = store.begin();
	for (it1; it1 != store.end(); it1++)
	{
		vector<string>::iterator it2 = it1->second.children.begin();
		for (it2; it2 != it1->second.children.end(); it2++)
		{
			if ((*it2) == curKey)
			{
				cout << "Removing the child " << curKey << " from the parent " << it1->first << endl;
				it1->second.children.erase(it2);
				break;
			}
		}
	}
}

template <typename Data>
bool NoSqlDb<Data>::deleteKey(Element<Data> elem)
{
	if (store.find(elem.name) == store.end())
	{
		cout << "Failed to find the key " << endl;
		return false;
	}
	deleteChildFromParent(elem.name);
	store.erase(elem.name);
	write++;
	return true;
}

template <typename Data>
void NoSqlDb<Data>::addChildren(Key elem1, Key elem2)
{
	if (store.find(elem1) == store.end())
	{
		cout << "Parent Element not found in the datastore" << endl;
		return;
	}

	if (store.find(elem2) == store.end())
	{
		cout << "Child Element not found in the datastore" << endl;
		return;
	}

	unordered_map<Key, Element<Data> >::iterator it = store.find(elem1);
	it->second.children.push_back(elem2);
	write++;
	//	cout << "Added child " << elem2 << " to Parent " << elem1;

}

template <typename Data>
void NoSqlDb<Data>::EditElementInstance(Key name, std::string data, std::string type)
{
	try
	{
		if (store.find(name) != store.end()) {
			Element<Data> element = value(name);
			if (type.compare("description") == 0) {
				element.description = data;
				write++;
			}
			else if (type.compare("category") == 0) {
				element.category = data;
				write++;
			}
			else if (type.compare("data") == 0) {
				element.data = data;
				write++;
			}
			else if (type.compare("timeDate") == 0) {
				element.timeDate = data;
				write++;
			}
			else if (type.compare("element") == 0)
			{
				/* Replace the entire element content */
				ElementWrapper ewr;
				ewr.restore(data);
				store[name] = static_cast<Element<StrData>>(ewr);
				write++;
				return;
			}
			else
			{
				cout << "The type of metadata to be edited is invalid string type " << endl;
			}
			store[name] = element;
		}
	}
	catch (exception e) {
		cout << "An exception occured in editing the element instance" << endl;
	}
}

