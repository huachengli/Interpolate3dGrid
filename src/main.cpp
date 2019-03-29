#include "Form.h"
#include "GridIO.h"
#include "Divide.h"
#include <string.h>
#include <vector>
#include "Interpolate.h"
#include <omp.h>

// Pgrid HashMap[(nX+1)*(nY+1)*(nZ+1)];



int main()
{
    getTime();
    _SETUP s;
    char sfile[MaxLen] = "setup.inf";
    int OutNum = ReadParam(sfile,&s);
    omp_set_num_threads(s.Nthread);
#ifdef _DBUG
    fprintf(stdout,"ihead: %d,ohead: %d\n",s.ihead,s.ohead);
#endif
    grid DataSet;
    grid DataOut;

    ndata = s.ndata;
    nX = s.nX;
    nY = s.nY;
    nZ = s.nZ;
    kMin = s.Kmin;
    Lambda = s.Lambda;

    Pgrid * HashMap = (Pgrid *) malloc(sizeof(Pgrid)*(nX+1)*(nY+1)*(nZ+1));
    
    DataSet.clear();
    DataOut.clear();

    
    int error1 = readDataSetDir(DataSet,s.DataSetPath,s.ihead,s.DataSetQPath,ndata);

    if(0==error1)
    {
        fprintf(stdout,"Cannot open INPUT\n");
        fprintf(stdout,"EXIT with IOERROR\n");
        return 0;
    }

#ifdef _DBUG
        fprintf(stdout,"INPUT(n) : %d\n",DataSet.size());
#endif

    double pMax[PDIM],pMin[PDIM];
    double Scaler[PDIM];
    CheckInterval(pMax,pMin,DataSet);
    GetScaler(pMax,pMin,Scaler);

#ifdef _DBUG
    for(int k=0;k<PDIM;k++)
        fprintf(stdout,"pMin : %-20f,Scaler : %-20f,pMax : %-20f\n",pMin[k],Scaler[k],pMax[k]);
    fprintf(stdout,"\n");
#endif

    InitHashMap(HashMap,(nX+1)*(nY+1)*(nZ+1));
    BuildHashMap(HashMap,DataSet,Scaler,pMin);

#ifdef _DBUG
    double dMin[DDIM], dMax[DDIM];
    CheckIntervalData(dMax,dMin,DataSet,ndata);
    for(int k=0;k<ndata;k++)
        fprintf(stdout,"dMin:%-20f dMax:%-20f\n",dMin[k],dMax[k]);
#endif

#ifdef _DBUG
    double hMin[DDIM], hMax[DDIM];
    int PgridSum = CheckIntervalHashMap(HashMap,hMax,hMin,ndata,(nX+1)*(nY+1)*(nZ+1));
    for(int k=0;k<ndata;k++)
        fprintf(stdout,"hMin:%-20f hMax:%-20f\n",hMin[k],hMax[k]);
    fprintf(stdout,"there are %d Points in HashMap!\n",PgridSum);
    fprintf(stdout,"\n");
#endif


    #pragma omp parallel for
    for(int k=0;k<OutNum;k++)
    {
        int check = InterOneBlock(HashMap,pMin,Scaler,s.DataOutCoor,s.OutList[k],s.DataOutPath,s.ohead);
#ifdef _DBUG
        fprintf(stdout,"In %dth file,%d points error![%s:%s]\n",k,check,s.DataOutCoor,s.OutList[k]);
#endif
    }
    
    free(HashMap);
    getTime();
    return 0;

}
