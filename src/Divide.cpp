#include "Divide.h"

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))


extern int nX,nY,nZ;
extern double Lambda;
extern int ndata;

void CheckRange(double * rng,grid & v)
{
    rng[2*X-1] = v[0].pois[X];
    rng[2*X]   = v[0].pois[X];
    rng[2*Y-1] = v[0].pois[Y];
    rng[2*Y]   = v[0].pois[Y];
    rng[2*Z-1] = v[0].pois[Z];
    rng[2*Z]   = v[0].pois[Z];
    for(auto it=v.begin();it!=v.end();it++)
    {
        rng[2*X-1] = MIN(it->pois[X],rng[2*X-1]);
        rng[2*X]   = MAX(it->pois[X],rng[2*X]);
        rng[2*Y-1] = MIN(it->pois[Y],rng[2*Y-1]);
        rng[2*Y]   = MAX(it->pois[Y],rng[2*Y]);
        rng[2*Z-1] = MIN(it->pois[Z],rng[2*Z-1]);
        rng[2*Z]   = MAX(it->pois[Z],rng[2*Z]);
    }
}

void CheckInterval(double * pMax,double * pMin,grid & v)
{
    for(int k=0;k<PDIM;k++)
    {
        pMin[k] = v[0].pois[k];
        pMax[k] = v[0].pois[k];
    }
    
    for(auto it=v.begin();it!=v.end();it++)
    {
        for(int k=0;k<PDIM;k++)
        {
            pMax[k] = MAX(pMax[k],it->pois[k]);
            pMin[k] = MIN(pMin[k],it->pois[k]);
        }
    }
}

void CheckIntervalData(double * pMax,double * pMin,grid & v,int ndata)
{
    for(int k=0;k<ndata;k++)
    {
        pMin[k] = v[0].data[k];
        pMax[k] = v[0].data[k];
    }
    
    for(auto it=v.begin();it!=v.end();it++)
    {
        for(int k=0;k<ndata;k++)
        {
            pMax[k] = MAX(pMax[k],it->data[k]);
            pMin[k] = MIN(pMin[k],it->data[k]);
        }
    }
}

int BuildHashMap(Pgrid * _H,grid & _D,const double * _Scaler,const double * _pMin)
{
    int Escape = 0;
    for(int k=0;k<_D.size();k++)
    {
        int Idp = ReDirection(_D[k],_Scaler,_pMin);
        if(Idp >=0 && Idp <= nX*nY*nZ)
        {
            _H[Idp].push_back(&_D[k]);
        }
        else
            Escape ++;
    }
    return Escape;
}

int ReDirection(node & point,const double * _Scaler,const double * _pMin)
{
    int INDEX[PDIM];
    for(int k=0;k<PDIM;k++)
    {
        INDEX[k] = (int) floor((point.pois[k]-_pMin[k])/_Scaler[k]);
    }
    return INDEX[Z] + INDEX[Y]*nZ + INDEX[X]*nY*nZ;
}


int ADDR(int Idx,int Idy,int Idz)
{
    if(Idx<=nX && Idy<=nY && Idz<=nZ && Idx>=0 && Idy>=0 && Idz >=0)
    {
        return Idz + Idy*nZ + Idx*nY*nZ;
    }
    else
        return -1;
}

int CheckIntervalHashMap(Pgrid * _H,double * pMax,double *pMin,int ndata,int Hsize)
{
    int count = 0;
    for(int k=0;k<Hsize;k++)
    {
        for(auto it=_H[k].begin();it!=_H[k].end();it++)
        {
            if(0==count)
            {
                for(int j=0;j<ndata;j++)
                {
                    pMax[j] = pMin[j] = (*it)->data[j];
                }
            }
            else
            {
                for(int j=0;j<ndata;j++)
                {
                    pMax[j] = MAX(pMax[j],(*it)->data[j]);
                    pMin[j] = MIN(pMin[j],(*it)->data[j]);
                }
            }
        }
        count += _H[k].size();
    }
    return count;
}





