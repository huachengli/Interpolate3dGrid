
#ifndef _USER_INTERPOLATE_H
#define _USER_INTERPOLATE_H
#include "Form.h"
#include "GridIO.h"
#include "Divide.h"
#define MaxDepth 5


double Kernel(double x);
int InterBox(const Pgrid & Box,node & _p,double & weight,int ndata);
int NeribInterk(const Pgrid * _H,node & _p,double & weight,int ndata,int _d,int * _I);
int NeribInter(const Pgrid * _H,node & _p,const double * scaler,const double * _pMin,int ndata);
int InterOneBlock(const Pgrid * _H,const double * _pMin,const double * _Scaler,const char * _path,const char * _name,const char * _outpath,int head);

#endif