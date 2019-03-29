#ifndef _USER_FORM_H
#define _USER_FORM_H

#include <math.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string.h>
#define PDIM 3
#define DDIM 5
#define X 0
#define Y 1
#define Z 2
#define Radius 1000.0
#define MaxLen 200



class node
{
public:
    double pois[PDIM];
    double data[DDIM];
    int ndata;
    node(const double * _p,const double * _d,int _n):ndata(_n)
    {
        for(int k=0;k<PDIM;k++)
        {
            pois[k] = _p[k];
        }
        for(int k=0;k<_n;k++)
        {
            data[k] = _d[k];
        }
    }

    node(double x = 0.0)
    {
        memset(pois,x,sizeof(pois));
        memset(data,x,sizeof(data));
    }

    friend double NDist(const node & x,const node & y)
    {
        double tmp = 0;
        for(int k=0;k<DDIM;k++)
            tmp += (x.pois[k]-y.pois[k])*(x.pois[k]-y.pois[k]);
        return sqrt(tmp);
    }

};

struct _SETUP
{
    int Nthread;
    char DataSetPath[MaxLen];
    char DataSetQPath[MaxLen];
    char DataOutCoor[MaxLen];
    char DataOutPath[MaxLen];
    char OutList[MaxLen][MaxLen];
    int ndata;
    int Kmin;
    double Lambda;
    int nX;
    int nY;
    int nZ;
    int ihead;
    int ohead;
};


typedef std::vector<node>  grid;
typedef std::vector<node*> Pgrid;

#endif