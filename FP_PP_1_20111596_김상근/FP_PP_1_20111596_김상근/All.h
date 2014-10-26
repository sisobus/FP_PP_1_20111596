#ifndef __ALL_H__
#define __ALL_H__

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cctype>
#include <bitset>
#include <deque>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <fstream>
#include <sstream>
#include <climits>
#include <iostream>
#include "delim.h"
#include "buffile.h"
#include "iobuffer.h"
#include "recfile.h"
#include "varlen.h"
using namespace std;

#define MP make_pair
#define FOR(x,b,e) for(int (x)=(b);(x)<=(e);++(x))
#define FORD(x,b,e) for(int (x)=(b);(x)>=(e);--(x))
#define REP(x,n) for(int (x)=0;(x)<(n);++(x))
#define REPD(x,n) for(int (x)=(n)-1;(x)>=0;--(x))
#define ALL(c) (c).begin(),(c).end()
#define SIZE(x) (int)(x).size()
#define ROUNDING(x, dig) (floor((x) * pow(10, dig) + 0.11f) / pow(10, dig))
#define PB push_back
#define ST first
#define ND second

typedef pair<int,int> ii;
typedef long long ll;

#define MAX_READ_LINE_LENGTH 128
//string getReadLine(FILE * fp,char *s) {
//	fgets(s,MAX_READ_LINE_LENGTH,fp);
//
//	while ( s[strlen(s)-1] == '\r' || s[strlen(s)-1] == '\n' ) 
//		s[strlen(s)-1] = 0;
//
//	return string(s);
//}

#endif
