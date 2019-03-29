#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <stdlib.h>
#define MaxLen 200

int ListDir(const char * _dir,char (*_res)[MaxLen])
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
};

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
    
    if(NULL!=fp)
        fclose(fp);
    return ListDir(s->DataSetPath,s->OutList);

}

int main()
{
    char dir[100] = "/public/scratch_pbspku/zhuodang/coord_49nodes/";
    char set[100] = "setup.inf";

    _SETUP s;
    int INDEX = ReadParam(set,&s);
    
    fprintf(stdout,"%d\n",INDEX); 
    for(int k=0;k<INDEX;k++)
        fprintf(stdout,"%s\n",s.OutList[k]);  
    fprintf(stdout,"%lf\n",s.Lambda); 
    fprintf(stdout,"%s\n",s.DataSetPath); 
    return 0;

}

// int main()
// {
//     DIR *dirp; 
//     char res[100][100];
//     int INDEX = 0;
//     char dir[100] = "/public/scratch_pbspku/zhuodang/coord_49nodes/";
//     struct dirent *dp;
//     dirp = opendir(dir); 
//     while ((dp = readdir(dirp)) != NULL) 
//     {
//         if(dp->d_name[0]=='.')
//             continue;
//         strcpy(res[INDEX],dir);
//         strcat(res[INDEX++],dp->d_name);
//     }
//     fprintf(stdout,"%d\n",INDEX); 
//     for(int k=0;k<INDEX;k++)
//         fprintf(stdout,"%s\n",res[k]);     
//     (void) closedir(dirp);
//     return 0;
// }


// #include <stdio.h>
// #include <sys/types.h>
// #include <regex.h>
// int main(void)
// {
//     int status = 0, i = 0;
//     int flag = REG_EXTENDED;
//     regmatch_t pmatch[1];
//     const size_t nmatch = 1;
//     regex_t reg;
//     const char pattern[50] = "^\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*$";
//     char buf[50] = "123456789@qq.com";//success
//     // char *buf = "###270401@163.com";//error
//     regcomp(&reg, pattern, flag);
//     status = regexec(&reg, buf, nmatch, pmatch, 0);
//     if(status == REG_NOMATCH)
//     {
//         printf("no match\n");
//     }
//     else if(status == 0)
//     {
//         printf("match success\n");
//         for(i = pmatch[0].rm_so; i < pmatch[0].rm_eo; i++){
//         putchar(buf[i]);
//     }
//     putchar('\n');
//     }
//     regfree(&reg);

//     return 0;
// }