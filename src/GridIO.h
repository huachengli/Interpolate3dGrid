#ifndef _USER_GRIDIO_H
#define _USER_GRIDIO_H
#define _DBUG
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <dirent.h>
#include <string.h>
#include <sys/time.h>
#include "Form.h"

#define maxFileNameLength 1024
extern int nX,nY,nZ;
extern double Lambda;
extern int ndata;
extern int kMin;

int readDataSet(grid & _D,const char * _cname,int head,const char * _qname,int ndata);
int readDataSetDir(grid & _D,const char * dir_cname,int head,const char * dir_qname,int ndata);
int OutGrid(grid & _G,const char * _oname,int ndata);
void retype(double * pois);
int MyStop(node & _p,int type);
int ListDir(char * _dir,char (*_res)[MaxLen]);
void Over(FILE * fp,int n);
int ReadParam(char * sfile,_SETUP * s);
int getTime();
#endif