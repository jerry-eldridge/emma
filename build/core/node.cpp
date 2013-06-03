#include <iostream>
using namespace std;

#include <string>
#include <math.h>
#include "core/core.h"

ostream & operator <<(ostream &os, const Node &v)
{
	os << v.id << ",";
	os << "\"" << v.label << "\",";
	switch (v.box) {
		case none: 
			os << "\"none\"";
			break;
		case rectangle: 
			os << "\"rectangle\"";
			break;
		case circle: 
			os << "\"circle\"";
			break;
		case connection: 
			os << "\"connection\"";
			break;
		default:
			break;
	}

	return os;
}

istream& operator >>(istream &is, Node &v)
{
	char line[4096];
	is.getline(line, 4096);
	string s = line;
	int beg = 0;
	int pos = s.find(",",beg);
	string ss;
	ss = s.substr(beg,pos-beg);
	v.id = atoi(ss.c_str());

	int sbeg, spos;

	beg = pos+1;
	pos = s.find(",",beg);
	ss = s.substr(beg,pos-beg);
	sbeg = ss.find("\"",0) + 1;
	spos = ss.rfind("\"",ss.length());
	ss = ss.substr(sbeg,spos-sbeg);
	strcpy(v.label, ss.c_str());

	beg = pos+1;
	pos = s.find(",",beg);
	ss = s.substr(beg,pos-beg);
	beg = ss.find("\"",0) + 1;
	pos = ss.rfind("\"",ss.length());
	ss = ss.substr(beg,pos-beg);

	if (!strcmp(ss.c_str(),"none")) {
		v.box = none;
	} else if (!strcmp(ss.c_str(),"rectangle")) {
		v.box = rectangle;
	} else if (!strcmp(ss.c_str(),"circle")) {
		v.box = circle;
	} else if (!strcmp(ss.c_str(),"connection")) {
		v.box = connection;
	}

	return is;
}