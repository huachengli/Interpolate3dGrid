
#ifndef _USER_DIVIDE_H
#define _USER_DIVIDE_H
#include <iostream>
#include <algorithm>
#include "Form.h"
#include "GridIO.h"



void CheckRange(double * rng,grid & v);
void CheckInterval(double * pMax,double * pMin,grid & v);
void CheckIntervalData(double * pMax,double * pMin,grid & v,int ndata);
int ReDirection(node & point,const double * _Scaler,const double * _pMin);
int BuildHashMap(Pgrid * _H,grid & _D,const double * _Scaler,const double * _pMin);
int CheckIntervalHashMap(Pgrid * _H,double * pMax,double *pMin,int ndata,int Hsize);
int ADDR(int Idx,int Idy,int Idz);

inline void InitHashMap(Pgrid * _H,int Len)
{
    for(int k=0;k<Len;k++)
        _H[k].clear();
}

inline void GetScaler(const double * _pMax,const double * _pMin,double * _Scaler)
{
    _Scaler[X] = (_pMax[X]-_pMin[X])/(nX-1);
    _Scaler[Y] = (_pMax[Y]-_pMin[Y])/(nY-1);
    _Scaler[Z] = (_pMax[Z]-_pMin[Z])/(nZ-1);
}

#endif