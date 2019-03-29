#include "GridIO.h"

char tmpc[1024];
char tmpq[1024];


int ndata = 1;
int nX = 100;
int nY = 100;
int nZ = 100;
int kMin = 27;
double Lambda = 0.05;

int readDataSetDir(grid & _D,const char * dir_cname,int head,const char * dir_qname,int ndata)
{
#ifdef _DBUG_GRID
    fprintf(stdout,"%s\n",dir_qname);
#endif

    struct dirent *dp = NULL;
    DIR *dirp; 
    dirp = opendir(dir_cname);
    int count = 0;

    while ((dp = readdir(dirp)) != NULL) 
    {
        if(dp->d_name[0]=='.')
            continue;
        strcpy(tmpc,dir_cname);
        strcpy(tmpq,dir_qname);
        strcat(tmpc,dp->d_name);
        strcat(tmpq,dp->d_name);
#ifdef _DBUG_GRID
        fprintf(stdout,"%s,%s\n",tmpc,tmpq);
#endif        
        readDataSet(_D,tmpc,head,tmpq,ndata);

        count ++;
    }      
    closedir(dirp);
    return count; 
}



int readDataSet(grid & _D,const char * _cname,int head,const char * _qname,int ndata)
{
    node tmp(0.0);
    FILE * cfp = fopen(_cname,"r");
    FILE * qfp = NULL; 
    if(ndata>0)
        qfp = fopen(_qname,"r");
    
    if(NULL==cfp)
    {
        fprintf(stdout,"openfile failed![%s]\n",_cname);
        return 0;
    }

    if(head > 0)
    {
        char buf[1024];
        for(int k=0;k<head;k++)
        {
            fgets(buf,sizeof(buf),cfp);
        }
    }
    
#ifdef _DBUG_GRID
        fprintf(stdout,"##:%d",_D.size());
#endif 

#ifdef _DBUG_GRID
        fprintf(stdout,"%d,%s\n",ndata+head,_qname);
#endif 

    while(EOF!=fscanf(cfp,"%lf %lf %lf",&tmp.pois[X],&tmp.pois[Y],&tmp.pois[Z]))
    {
        retype(tmp.pois);
        for(int k=0;k<ndata;k++)
        {
            fscanf(qfp,"%lf",&tmp.data[k]);
        }
        _D.push_back(tmp);
    }

    if(NULL!=cfp)
        fclose(cfp);
    if(NULL!=qfp)
        fclose(qfp);
    return 1;
}

int OutGrid(grid & _G,const char * _oname,int ndata)
{
    FILE * ofp = fopen(_oname,"w");
    if(NULL==ofp)
    {
        fprintf(stdout,"cannot open outputfile!\n");
        fprintf(stdout,"EXIT WITH Write Error!\n");
        return 0;
    }

    for(grid::iterator it=_G.begin();it!=_G.end();it++)
    {
        fprintf(ofp,"%lf %lf %lf",it->pois[X],it->pois[Y],it->pois[Z]);
        for(int k=0;k<ndata;k++)
        {
            fprintf(ofp," %lf ",it->data[k]);
        }
        fprintf(ofp,"\n");
    }
    fclose(ofp);
    return 1;
}

void retype(double * pois)
{
    double _z = pois[Z]*cos(pois[X]);
    double _y = pois[Z]*sin(pois[X])*cos(pois[Y]);
    double _x = pois[Z]*sin(pois[X])*sin(pois[Y]);

    pois[Z] = Radius*_z;
    pois[Y] = Radius*_y;
    pois[X] = Radius*_x;

}

int MyStop(node & _p,int type)
{
    return 0;
}


int ListDir(char * _dir,char (*_res)[MaxLen])
{
    DIR *dirp; 
    int INDEX = 0;
    struct dirent *dp;
    memset(_res,'\0',sizeof(_res));
    dirp = opendir(_dir); 
    while ((dp = readdir(dirp)) != NULL) 
    {
        if(dp->d_name[0]=='.')
            continue;
        strcpy(_res[INDEX++],dp->d_name);
    }   
    (void) closedir(dirp);
    return INDEX;
}

void Over(FILE * fp,int n)
{
    char buf[1024];
    for(int k=0;k<n;k++)
    {
        fgets(buf,sizeof(buf),fp);
    }
}

int ReadParam(char * sfile,_SETUP * s)
{
    FILE * fp = fopen(sfile,"r");
    if(NULL==fp)
    {
        fprintf(stdout,"Can not open sfile\n");
        fprintf(stdout,"EXIT WITH SETUPERROR\n");
        return 1;
    }
    Over(fp,5);
    fscanf(fp,"%d\n",&s->Nthread);
    Over(fp,1);
    fscanf(fp,"%s\n",&s->DataSetPath);
    Over(fp,1);
    fscanf(fp,"%s\n",&s->DataSetQPath);
    Over(fp,1);
    fscanf(fp,"%s\n",&s->DataOutCoor);
    Over(fp,1);
    fscanf(fp,"%s\n",&s->DataOutPath);
    Over(fp,1);
    fscanf(fp,"%d %lf %d\n",&s->ndata,&s->Lambda,&s->Kmin);
    Over(fp,1);
    fscanf(fp,"%d %d %d\n",&(s->nX),&(s->nY),&(s->nZ));
    Over(fp,1);
    fscanf(fp,"%d %d\n",&s->ihead,&s->ohead);

    if(NULL!=fp)
        fclose(fp);
    return ListDir(s->DataOutCoor,s->OutList);

}

int getTime()
{
    int ret = -1;
    struct timeval stuTimeVal;
    memset(&stuTimeVal,0,sizeof(struct timeval));
    ret = gettimeofday(&stuTimeVal,NULL);
    if(0 == ret)
    {
        printf("\n tv_sec[%lu] tv_usec[%lu]\n",stuTimeVal.tv_sec , stuTimeVal.tv_usec);
    }
    return 0;
}
