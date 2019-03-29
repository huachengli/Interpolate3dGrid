
#include "Interpolate.h"


double Kernel(double x)
{
    return exp(-0.05*x*x);
}


int InterBox(const Pgrid & Box,node & _p,double & weight,int ndata)
{
    double tmp;
    for(int k=0;k<Box.size();k++)
    {
        tmp = Kernel(NDist(*Box[k],_p));
        weight += tmp;
        for(int i=0;i<ndata;i++)
        {
            _p.data[i] += tmp*Box[k]->data[i];
        }
    }
    return Box.size();
}

int NeribInterk(const Pgrid * _H,node & _p,double & weight,int ndata,int d,int * _I)
{
    int count = 0;
    for(int i=-d;i<=d;i++)
    {
        for(int j=-d;j<=d;j++)
        {
            for(int k=-d;k<=d;k++)
            {
                if(abs(i)!=d && abs(j)!=d && abs(k)!=d)
                    continue;
                int _OFFSET = ADDR(_I[X]+i,_I[Y]+j,_I[Z]+k);
                if(_OFFSET!=-1 && 0!=i && 0!=j && 0!=k)
                {
                    count += InterBox(_H[_OFFSET],_p,weight,ndata);
                } 
            }
        }
    }
    return count;
}


int NeribInter(const Pgrid * _H,node & _p,const double * _Scaler,const double * _pMin,int ndata)
{
    int INDEX[PDIM];
    double weight = 0.0;
    int count = 0;
    
    for(int k=0;k<PDIM;k++)
    {
        INDEX[k] = (int) floor((_p.pois[k]-_pMin[k])/_Scaler[k]);
    }

    int _OFFSET = ADDR(INDEX[X],INDEX[Y],INDEX[Z]);

    if(_OFFSET!=-1)
    {
        count += InterBox(_H[_OFFSET],_p,weight,ndata);
        count += NeribInterk(_H,_p,weight,ndata,1,INDEX);
    }       

    for(int k = 2;k<MaxDepth;k++)
    {
        if(count < kMin)
            count += NeribInterk(_H,_p,weight,ndata,k,INDEX);
        else
            break;
    }

    if(0==count)
    {
        MyStop(_p,1);
        return 0;
    }

    if(weight > 1e-7)
    {
//        fprintf(stdout,"%d : %d : %f : %f\n",_OFFSET,count,_p.data[0],weight);
        for(int k=0;k<ndata;k++)
        {
            _p.data[k]  = _p.data[k]/weight;
        }
        return count;
    }
    else
        return 0;
}


int InterOneBlock(const Pgrid * _H,const double * _pMin,const double * _Scaler,const char * _path,const char * _name,const char * _outpath,int head)
{
    grid DataOut;
    DataOut.clear();

    char tmp[MaxLen];
    strcpy(tmp,_path);
    strcat(tmp,_name);
    readDataSet(DataOut,tmp,head,NULL,0);

    int NeedExtrapolation = 0;
    for(auto it = DataOut.begin();it!=DataOut.end();it++)
    {
        NeedExtrapolation += (int) 0==NeribInter(_H,*it,_Scaler,_pMin,ndata);
    }

    char otmp[MaxLen];
    strcpy(otmp,_outpath);
    strcat(otmp,_name);
    OutGrid(DataOut,otmp,ndata);

    return NeedExtrapolation;
}