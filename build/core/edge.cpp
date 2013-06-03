#include <iostream>
using namespace std;

#include <math.h>
#include "core/core.h"

ostream & operator <<(ostream &os, const Edge &e)
{
	os << e.i << "," << e.j << ",";
	os << "\"" << e.label << "\",";
	os << "\"" << e.inlabel << "\",";
	os << "\"" << e.outlabel << "\"";

	return os;
}

istream& operator >>(istream &is, Edge &e)
{
	char line[4096];
	is.getline(line, 4096);
	string s = line;
	int beg = 0;
	int pos = s.find(",",beg);
	string ss;
	ss = s.substr(beg,pos-beg);
	e.i = atoi(ss.c_str());
	beg = pos+1;
	pos = s.find(",",beg);
	ss = s.substr(beg,pos-beg);
	e.j = atoi(ss.c_str());

	int sbeg, spos;

	beg = pos+1;
	pos = s.find(",",beg);
	ss = s.substr(beg,pos-beg);
	sbeg = ss.find("\"",0) + 1;
	spos = ss.rfind("\"",ss.length());
	ss = ss.substr(sbeg,spos-sbeg);
	strcpy(e.label, ss.c_str());

	beg = pos+1;
	pos = s.find(",",beg);
	ss = s.substr(beg,pos-beg);
	sbeg = ss.find("\"",0) + 1;
	spos = ss.rfind("\"",ss.length());
	ss = ss.substr(sbeg,spos-sbeg);
	strcpy(e.inlabel, ss.c_str());

	beg = pos+1;
	pos = s.find(",",beg);
	ss = s.substr(beg,pos-beg);
	sbeg = ss.find("\"",0) + 1;
	spos = ss.rfind("\"",ss.length());
	ss = ss.substr(sbeg,spos-sbeg);
	strcpy(e.outlabel, ss.c_str());

	return is;
}