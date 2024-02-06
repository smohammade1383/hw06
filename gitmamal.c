#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
char gitmamaldirectory[2000];
char addressfile[1000];
char lastchange[200];
char lastadd[200];
char filename[100];
char username[100];
char email[100];
char mode[20];
int addnum;
int makan;
int x;
int existaddress;
char addedmemory[40][2000];
int commitarray[100];
char commitusername[100];
char commitemail[100];
char committime[100];
char commitmassage[100];
int commitnumstage;
int curcommit;
char tagname[100];
char taguser[100];
char tagdate[100];
char tagmassage[100];
struct stat fortime;
void last_modify(char* address);
void findfilename(char* address);
int found_gitmamal();
void run_init();
int search_commit(char* address);
void search_commit_information(int id);
void foundusername();
void foundemail();
int run_config(int argc,char* argv[]);
int run_alias(int argc,char* argv[]);
void create_branch(char* name);
int numcommit();
int run_add_file(char* address);
int run_add_folder(char* address);
int run_add_e(char* address);
int run_reset_file(char* address);
int run_reset_folder(char* address);
int datecom(char* date1,char* date2);
int run_reset_e(char* address);
int findfulladdress(char* name);
int run_commit(char* massage);
int statusidentifying(char* address);
int findintags(char* tagname,int* tagcommitid,int* overwrite);
int run_tag(char* tagname,char* tagmassage,int tagcommitid,int tagoverwrite);
char* deletenullspace(char* fordeletenullspace);
int isnullspace(char* line);
int run_diff(char* address1,char* address2,int begin1,int end1,int begin2,int end2);
int filenumline(char* address);
void last_modify(char* address){
    stat(address,&fortime);
    strftime(lastchange,100,"%d/%m/%Y/ %H/:%M:%S",localtime(&fortime.st_mtime));
}


void findfilename(char* address){
    int j=0;
    char token[100][100];
    char* tok=strtok(address,"/");
    while(tok!=NULL){
        strcpy(token[j],tok);
        j++;
        tok=strtok(NULL,"/");
    }
    strcpy(filename,token[j-1]);
}


int found_gitmamal(){
    //yaftan va zakhire address .gitmamal
    char tmpdir[2000];
    char workdirectory[2000];
    getcwd(workdirectory,sizeof(workdirectory));
    do{
        getcwd(tmpdir,sizeof(tmpdir));
        DIR* directory=opendir(".");
        struct dirent* x;
        while((x=readdir(directory))!=NULL){
            if((strcmp(x->d_name,".gitmamal")==0)&&(x->d_type==DT_DIR)){
                chdir(".gitmamal");
                getcwd(gitmamaldirectory,sizeof(gitmamaldirectory));
                chdir(workdirectory);
                //printf("%s\n",gitmamaldirectory);
                return 1;
            }
        }
        chdir("..");
        closedir(directory);
    }while(strcmp(tmpdir,"/")!=0);
    chdir(workdirectory);
    //printf(" aaaa %s\n",workdirectory);
    return 0;
}


void run_init(){
    //sakht .gitmamal dar workdirectory dar soorat adam vojood
    char address[2000];
    int exist=found_gitmamal();
    char workdirectory[2000];
    getcwd(workdirectory,sizeof(workdirectory));
    //printf("%s",workdirectory);
    if(exist==1){
        printf("you have already initialized");
        //printf("%s",getcwd(gitmamaldirectory,sizeof(gitmamaldirectory)));
    }
    else{
        strcpy(address,strcat(workdirectory,"/.gitmamal"));
        mkdir(address,0755);
        printf("%s",address);
        chdir(address);
        strcpy(gitmamaldirectory,address);
        //create_branch("master");
        FILE* file=fopen("branches.txt","w");
        fprintf(file,"master");
        fclose(file);
        mkdir("./configs",0755);
        //printf("aaaaaa");
        file=fopen("/Users/wishuwerehere/Desktop/global/projects.txt","a");
        fprintf(file,"%s\n",address);
        fclose(file);
        chdir(workdirectory); 
        //printf("%s",getcwd(workdirectory,sizeof(workdirectory)));       
    }
}


int search_commit(char* address){
    found_gitmamal();
    int a;
    x=0;
    char workdirectory[1000];
    char address1[1000];
    getcwd(workdirectory,sizeof(workdirectory));
    chdir(gitmamaldirectory);
    chdir("configs");
    FILE* commited=fopen("commited.txt","r");
    while(1){
        fgets(address1,1000,commited);
        address1[strlen(address1)-1]='\0';
        if(feof(commited))break;
        if(strcmp(address1,address)==0){
            fscanf(commited,"%d\n",&a);
            commitarray[x];
            x++;
       }
    }
    if(x==0)return 0;
    else{return 1;}
}


void search_commit_information(int id){
    char workdirectory[1000];
    char ids[10];
    getcwd(workdirectory,sizeof(workdirectory));
    found_gitmamal();
    chdir(gitmamaldirectory);
    sprintf(ids,"%d",id);
    chdir(ids);
    FILE* open=fopen("./information/username.txt","r");
    fgets(commitusername,1000,open);
    fclose(open);
    open=fopen("./information/email.txt","r");
    fgets(commitemail,100,open);
    fclose(open);
    open=fopen("./information/time.txt","r");
    fgets(committime,100,open);
    fclose(open);
    open=fopen("./information/massage.txt","r");
    fgets(commitmassage,1000,open);
    fclose(open);
    open=fopen("./information/stagenum.txt","r");
    fscanf(open,"%d",&commitnumstage);
    fclose(open);
    chdir(workdirectory);
}


void foundusername(){
    char workdirectory[1000];
    getcwd(workdirectory,sizeof(workdirectory));
    found_gitmamal();
    chdir(gitmamaldirectory);
    chdir("configs");
    FILE* user=fopen("username.txt","r");
    fscanf(user,"%s",username);
    fclose(user);
    chdir(workdirectory);
}


void foundemail(){
    char workdirectory[1000];
    getcwd(workdirectory,sizeof(workdirectory));
    found_gitmamal();
    chdir(gitmamaldirectory);
    chdir("configs");
    FILE* email1=fopen("email.txt","r");
    fscanf(email1,"%s",email);
    fclose(email1);
    chdir(workdirectory);
}


int run_config(int argc,char* argv[]){
    char workdirectory[2000];
    getcwd(workdirectory,sizeof(workdirectory));
    found_gitmamal();
    if(strcmp(argv[2],"-global")==0){
        if(strcmp(argv[3],"user.name")){
            FILE* file=fopen("/Users/wishuwerehere/Desktop/global/projects.txt","r");
            while(!feof(file)){
                char address[2000];
                fgets(address,sizeof(address),file);
                address[strlen(address)-1]='\0';
                chdir(address);
                chdir("./configs");
                FILE* usernames=fopen("username.txt","w");
                fprintf(usernames,"%s",argv[4]);
                fclose(usernames);
            }
            fclose(file);
            chdir(workdirectory);
        }
        if(strcmp(argv[3],"user.email")){
            FILE* file=fopen("/Users/wishuwerehere/Desktop/global/projects.txt","r");
            while(!feof(file)){
                char address[2000];
                fgets(address,sizeof(address),file);
                address[strlen(address)-1]='\0';
                chdir(address);
                chdir("./configs");
                FILE* useremails=fopen("useremail.txt","w");
                fprintf(useremails,"%s",argv[4]);
                fclose(useremails);
            }
            fclose(file);
            chdir(workdirectory);
        }
        return 1;
    }
    else{
        if(found_gitmamal()==0){
        printf("please initialize first!");
        return 0;
        }
        else{
            if(strcmp(argv[2],"user.name")==0){
                chdir(gitmamaldirectory);
                chdir("./configs");
                FILE* file=fopen("usernames.txt","w");
                fprintf(file,"%s",argv[3]);
                fclose(file);
                chdir(workdirectory);
            //printf("%s",workdirectory);
                return 1;
            }
            else if(strcmp(argv[2],"user.email")==0){
                chdir(gitmamaldirectory);
                chdir("./configs");
                FILE* file=fopen("emails.txt","w");
                fprintf(file,"%s",argv[3]);
                fclose(file);
                chdir(workdirectory);
                return 1;
            }
        }
    }
}


int run_alias(int argc,char* argv[]){
    if(strcmp(argv[2],"-global")==0){
        char workdirectory[2000];
        getcwd(workdirectory,sizeof(workdirectory));
        FILE* file=fopen("Users/wishuwerehere/Desktop/global/projects.txt","a");
        while(!feof(file)){
            char address[2000];
            fgets(address,sizeof(address),file);
            address[strlen(address)-1]='\0';
            chdir(address);
            chdir("configs");
            FILE* alias=fopen("alias.txt","a");
            for(int i=6;i<strlen(argv[3]);i++)fprintf(alias,"%c",argv[3][i]);
            fprintf(alias,"\n");
            fprintf(alias,"%s\n",argv[4]);
            fclose(alias);
        }
        fclose(file);
        chdir(workdirectory);
        return 1;
    }
    else{
        if(found_gitmamal()==0){
            printf("please initialize first");
            return 0;
        }
        else{
            char workdirectory[2000];
            getcwd(workdirectory,sizeof(workdirectory));
            chdir("./.gitmamal/configs");
            FILE* alias=fopen("alias.txt","a");
            for(int i=6;i<strlen(argv[3]);i++)fprintf(alias,"%c",argv[3][i]);
            fprintf(alias,"\n");
            fprintf(alias,"%s\n",argv[4]);
            fclose(alias);
            chdir(workdirectory);
            return 1;
        }
    }
}


void create_branch(char* name){
    found_gitmamal();
    char workdirectory[2000];
    getcwd(workdirectory,sizeof(workdirectory));
    chdir(".gitmamal");
    mkdir(name,0755);
    FILE* status=fopen("status.txt","w");
    fclose(status);
    chdir(workdirectory);
}


int numcommit(){
    
    return curcommit;
}


int run_add_file(char* address){
    existaddress=0;
    makan=0;
    char workdirectory[2000];
    char address1[2000];
    found_gitmamal();
    getcwd(workdirectory,sizeof(workdirectory));
    last_modify(address);
    chdir(gitmamaldirectory);
    chdir("master");
    FILE* status=fopen("status.txt","r+");
    while(1){
        fgets(address1,2000,status);
        address1[strlen(address1)-1]='\0';
        if(feof(status))break;
        if(strcmp(address,address1)==0){
            makan=ftell(status);
            fgets(lastadd,200,status);
            fgets(mode,20,status);
            lastadd[strlen(lastadd)-1]='\0';
            mode[strlen(mode)-1]='\0';
            existaddress=1;
            if(strcmp(mode,"dd")==0){
                fclose(status);
                chdir(workdirectory);
                return -1;
            }
            FILE* checker=fopen(address,"r");
            if(checker!=NULL){
                if((strcmp(lastadd,lastchange)==0)&&(strcmp(mode,"se")==0)){
                    //printf("this file is existed and already added!");
                    chdir(workdirectory);
                    fclose(status);
                    fclose(checker);
                    return 0;
                }
                else{
                    FILE* status=fopen("status.txt","r+");
                    fseek(status,makan,SEEK_SET);
                    fprintf(status,"%s\n",lastchange);
                    fprintf(status,"se\n");
                    fclose(status);
                    strcpy(addedmemory[addnum],address);
                    addnum++;
                    findfilename(address);
                    char goal[100];
                    char command[100];
                    sprintf(goal,"%s/stagingarea/%s",gitmamaldirectory,filename);
                    sprintf(command,"copy %s %s",address,goal);
                    system(command);
                    fclose(status);
                    fclose(checker);
                    chdir(workdirectory);
                    return 1;
                }
            }
            else{
                if(strcmp(mode,"sd")==0){
                    fclose(status);
                    fclose(checker);
                    chdir(workdirectory);
                    return 0;
                }
                else{
                    FILE* status=fopen("status.txt","r+");
                    fseek(status,makan,SEEK_SET);
                    fprintf(status,"%s\n",lastchange);
                    fprintf(status,"sd\n");
                    fclose(checker);
                    fclose(status);
                    strcpy(addedmemory[addnum],address);
                    addnum++;
                    chdir(gitmamaldirectory);
                    chdir("stagingarea");
                    findfilename(address);
                    remove(filename);
                    chdir(workdirectory);
                    return 1;
                }
            }
        }
        if(existaddress==0){
            FILE* checker=fopen(address,"r");
            if(checker!=NULL){
                FILE* status=fopen("status.txt","a");
                fprintf(status,"%s\n",address);
                fprintf(status,"%s\n",lastchange);
                fprintf(status,"se\n");
                fclose(status);
                strcpy(addedmemory[addnum],address);
                addnum++;
                char goal[1000];
                char command[1000];
                findfilename(address);
                sprintf(goal,"%s/stagingarea/%s",gitmamaldirectory,filename);
                sprintf(command,"copy %s %s",address,goal);
                system(command);
                chdir(workdirectory);
                return 1;
            }
            else{
                fclose(checker);
                chdir(workdirectory);
                return -1;
            }
        }
    }
    chdir(workdirectory);
}


int run_add_folder(char* address){
    char workdirectory[2000];
    getcwd(workdirectory,sizeof(workdirectory));
    chdir(address);
    struct dirent* x;
    DIR* directory=opendir(".");
    while((x=readdir(directory))!=NULL){
        if(x->d_type!=DT_DIR){
            findfulladdress(x->d_name);
            run_add_file(addressfile);
        }
    }
    closedir(directory);
    chdir(workdirectory);
    return 1;
}


int run_add_e(char* address){
    char workdirectory[1000];
    getcwd(workdirectory,sizeof(workdirectory));
    char a[1000];
    strcpy(a,address);
    if(chdir(a)==0){
        run_add_folder(address);
        chdir(workdirectory);
        return 1;
    }
    else{
        int b=run_add_file(address);
        if(b==-1){
            printf("there is no such file!");
            return 0;
        }
    }
    return 1;
}


int run_reset_file(char* address){
    char workdirectory[2000];
    char address1[1000];
    found_gitmamal();
    int a=statusidentifying(address);
    if(a==-1)return -1;
    if(existaddress==0){
        printf("the file is untracked!");
        return 1;
    }
    else{
        getcwd(workdirectory,sizeof(workdirectory));
        chdir(gitmamaldirectory);
        chdir("master");
        FILE* status=fopen("status.txt","r+");
        fseek(status,makan,SEEK_SET);
        fprintf(status,"%s\n",lastchange);
        fprintf(status,"u");
        fclose(status);
        chdir(gitmamaldirectory);
        chdir("stagingarea");
        findfilename(address);
        remove(filename);
        chdir(workdirectory);
        return 1;
    }
}


int run_reset_folder(char* address){
    char workdirectory[2000];
    getcwd(workdirectory,sizeof(workdirectory));
    chdir(address);
    struct dirent* x;
    DIR* directory=opendir(".");
    while((x=readdir(directory))!=NULL){
        if(x->d_type!=DT_DIR){
            findfulladdress(x->d_name);
            run_reset_file(addressfile);
        }
    }
    closedir(directory);
    chdir(workdirectory);
    return 1;
    
}


int datecom(char* date1,char* date2){
    int d1,d2,mo1,mo2,y1,y2,h1,h2,mi1,mi2,s1,s2;
    sscanf(date1,"%d/%d/%d %d:%d:%d",&d1,&mo1,&y1,&h1,&mi1,&s1);
    sscanf(date1,"%d/%d/%d %d:%d:%d",&d2,&mo2,&y2,&h2,&mi2,&s2);
    if(y1>y2)return 1;
    else if(y2>y1)return 0;
    else{
        if(mo1>mo2)return 1;
        else if(mo2>mo1)return 0;
        else{
            if(d1>d2)return 1;
            else if(d2>d1)return 0;
            else{
                if(h1>h2)return 1;
                else if(h2>h1)return 0;
                else{
                    if(mi1>mi2)return 1;
                    else if(mi2>mi1)return 0;
                    else{
                        if(s1>s2)return 1;
                        else if(s2>s1)return 0;
                    }
                }
            }
        }
    }
}


int run_reset_e(char* address){
    char workdirectory[1000];
    getcwd(workdirectory,sizeof(workdirectory));
    char a[1000];
    strcpy(a,address);
    if(chdir(a)==0){
        run_reset_folder(address);
        chdir(workdirectory);
        return 1;
    }
    else{
        int b=run_reset_file(address);
        if(b==-1){
            printf("there is no such file!");
            return 0;
        }
    }
    return 1;

}


void print_command(int argc,char* const argv[]){
    for(int i=0;i<argc;i++)fprintf(stdout,"%s",argv[i]);
    fprintf(stdout,"\n");
}


int findfulladdress(char* name){
    char workdirectory[1000];
    char address1[100];
    char lastadd1[100];
    char mode1[10];
    char name1[100];
    found_gitmamal();
    getcwd(workdirectory,sizeof(workdirectory));
    chdir(gitmamaldirectory);
    chdir("master");
    FILE* status=fopen("status.txt","r");
    while(1){
        fgets(address1,100,status);
        address1[strlen(address1)-1]='\0';
        fgets(lastadd1,100,status);
        fgets(mode1,10,status);
        if(feof(status))break;
        findfilename(address1);
        if(strcmp(filename,name)==0){
            strcpy(addressfile,address1);
            fclose(status);
            chdir(workdirectory);
            return 1;
        }
    }
    fclose(status);
    chdir(workdirectory);
    return 0;
}


int run_commit(char* massage){
    char workdirectory[1000];
    char address[1000];
    char lastadd1[100];
    char mode1[10];
    int num_stage=0;
    getcwd(workdirectory,sizeof(workdirectory));
    found_gitmamal();
    chdir(gitmamaldirectory);
    chdir("configs");
    int cur;
    FILE* curcommit=fopen("curcommit.txt","r");
    fscanf(curcommit,"%d",&cur);
    char curid[100];
    sprintf(curid,"%d",cur);
    fclose(curcommit);
    chdir("../master");
    FILE* status=fopen("status.txt","r");
    while(1){
        fgets(address,1000,status);
        if(feof(status))break;
        fgets(lastadd1,100,status);
        fgets(mode1,10,status);
        mode1[strlen(mode1)-1]='\0';
        if(strcmp(mode1,"sd")==0)num_stage++;
    }
    fclose(status);
    chdir(gitmamaldirectory);
    chdir("stagingarea");
    DIR* stagingarea=opendir(".");
    struct dirent* x;
    while((x=readdir(stagingarea))!=NULL){
        if((x->d_type)!=DT_DIR)num_stage++;
    }
    closedir(stagingarea);
    if(num_stage==0){
        printf("there is no file to commit!");
        chdir(workdirectory);
        return 0;
    }
    else{
        chdir(gitmamaldirectory);
        chdir("master");
        status=fopen("status.txt","r+");
        chdir("../configs");
        int num=numcommit();
        num++;
        FILE* file;
        file=fopen("./numcommit.txt", "w");
        fprintf(file,"%d",num);
        fclose(file);
        chdir(gitmamaldirectory);
        char id[10];
        sprintf(id,"%d",num);
        mkdir(id,0755);
        chdir(id);
        mkdir("information",0755);
        mkdir("files",0755);
        chdir("information");
        foundusername();
        foundemail();
        file=fopen("./branch.txt", "w");
        fprintf(file,"%s","master");
        fclose(file);
        file=fopen("./username.txt","w");
        fprintf(file,"%s",username);
        fclose(file);
        file=fopen("./email.txt","w");
        fprintf(file,"%s",email);
        fclose(file);
        file=fopen("./massage.txt","w");
        fprintf(file,"%s",massage);
        fclose(file);
        file=fopen("./stagenum.txt","w");
        fprintf(file,"%d",num_stage);
        fclose(file);
        file=fopen("./time.txt","w");
        stat("./time.txt",&fortime);
        char committime[100];
        strftime(committime,100,"%d/%m/%Y %H:%M:%S",localtime(&fortime.st_ctime));
        fprintf(file,"%s",committime);
        fclose(file);
        chdir(gitmamaldirectory);
        chdir(curid);
        chdir("files");
        DIR* curcommitfiles=opendir(".");
        while((x=readdir(curcommitfiles))!= NULL){
            if(x->d_type!=DT_DIR){
                char source[2000];
                char goal[2000];
                sprintf(source,"%s\\%s\\files\\%s",gitmamaldirectory,curid,x->d_name);
                sprintf(goal,"%s\\%s\\files\\%s",gitmamaldirectory,id,x->d_name);
                char command[4000];
                sprintf(command,"copy %s %s",source,goal);
                system(command);
            }
        }
        closedir(curcommitfiles);
        chdir(gitmamaldirectory);
        chdir("stagingarea");
        stagingarea=opendir(".");
        struct dirent* x;
        while((x=readdir(stagingarea))!=NULL){
            if(x->d_type!=DT_DIR){
                char source[2000];
                char goal[2000];
                sprintf(source,"%s\\stagingarea\\%s",gitmamaldirectory,x->d_name);
                sprintf(goal,"%s\\%s\\files\\%s",gitmamaldirectory,id,x->d_name);
                char command[4000];
                sprintf(command,"move %s %s",source,goal);
                system(command);
            }
        }
        closedir(stagingarea);
        chdir(gitmamaldirectory);
        chdir("master");
        FILE* status=fopen("status.txt","r");
        char address1[1000];
        while(1){
            fgets(address1,1000,status);
            makan=ftell(status);
            last_modify(address1);
            address1[strlen(address1)-1]='\0';
            last_modify(address1);
            fgets(lastadd,100,status);
            lastadd[strlen(lastadd)-1]='\0';
            fgets(mode,10,status);
            mode[strlen(mode)-1]='\0';
            fclose(status);
            if(feof(status))break;
            if((strcmp(mode,"sd")==0)||(strcmp(mode,"se")==0)&&(strcmp(lastchange,lastadd)==0)){
                FILE* checker=fopen(address1,"r");
                if(checker==NULL){
                    fclose(checker);
                    FILE* status=fopen("status.txt","r+");
                    fseek(status,makan,SEEK_SET);
                    fprintf(status,"%s\n",lastchange);
                    fprintf(status,"%s\n","dd");
                    fclose(status);
                    chdir(workdirectory);
                }
                else{
                    fclose(checker);
                    FILE* status=fopen("status.txt" , "r+");
                    fseek(status,makan,SEEK_SET);
                    fprintf(status,"%s\n",lastchange);
                    fprintf(status,"%s\n","ue");
                    fclose(status);
                    chdir(workdirectory);
                }
            }    
        }
        chdir(workdirectory);
        FILE* file1=fopen("./configs/curcommit.txt","w");
        fprintf(file1,"%d",num);
        fclose(file1);
        char a[2000];
        char b[2000];
        char command[4000];
        sprintf(a,"%s\\%s\\status.txt",gitmamaldirectory,"master");
        sprintf(b,"%s\\%s\\information\\status.txt",gitmamaldirectory,id);
        sprintf(command,"copy %s %s",a,b);
        system(command);
        printf("id : %d\n",num);
        printf("time : %s\n",committime);
        printf("massage : %s\n",massage);
        chdir(workdirectory);
        return 1;
    }
}


int statusidentifying(char* address){
    found_gitmamal();
    char workdirectory[1000];
    getcwd(workdirectory,sizeof(workdirectory));
    chdir(gitmamaldirectory);
    chdir("master");
    FILE* status=fopen("status.txt","r");
    FILE* checker=fopen(address,"r+");
    existaddress=0;
    fclose(checker);
    last_modify(address);
    while(1){
        char address1[1000];
        fgets(address1,1000,status);
        address1[strlen(address1)-1]='\0';
        if(feof(status))break;
        if(strcmp(address,address1)==0){
            makan=ftell(status);
            fgets(lastadd,100,status);
            lastadd[strlen(lastadd)-1]='\0';
            fgets(mode,10,status);
            mode[strlen(mode)-1]='\0';
            if(strcmp("dd",mode)==0){
                fclose(status);
                chdir(workdirectory);
                return -1;
            }
            else{
                checker=fopen(address,"r+");
                if(checker!=NULL){
                    if((strcmp(lastchange,lastadd)==0)&&(strcmp(mode,"se")==0)){
                        fclose(checker);
                        fclose(status);
                        chdir(workdirectory);
                        return 1;
                    }
                    else{
                        fclose(status);
                        fclose(checker);
                        chdir(workdirectory);
                        return 0;
                    }
                }
                else{
                    if(strcmp(mode,"sd")==0){
                        fclose(status);
                        fclose(checker);
                        chdir(workdirectory);
                        return 1;
                    }
                    else{
                        fclose(status);
                        fclose(checker);
                        chdir(workdirectory);
                        return 0;
                    }
                }
            }
        }
        fclose(status);
        chdir(workdirectory);
        return 0;
    }
}


int run_status(){
    found_gitmamal();
    char path[1000];
    char workdirectory[1000];
    getcwd(workdirectory,sizeof(workdirectory));
    int lastcommit= numcommit();
    struct dirent* file;
    DIR* directory=opendir(".");
    while((file=readdir(directory))!=NULL){
        if((file->d_type)!=DT_DIR){
            sprintf(path,"%s/%s",workdirectory,file->d_name);
            


                

            
        }

    }

    

}


int findintags(char* tagname,int* tagcommitid,int* overwrite){
    char workdirectory[1000];
    getcwd(workdirectory,sizeof(workdirectory));
    found_gitmamal();
    chdir(gitmamaldirectory);
    chdir("configs");
    FILE* tags=fopen("tags.txt","r");
    int commitid;
    int s=0;
    char tagname1[1000];
    char taguser[1000];
    char tagdate[1000];
    char tagmassage[1000];
    int overwrite1;
    while(1){
        fgets(tagname1,2000,tags);
        fscanf(tags,"%d\n",&commitid);
        fgets(taguser,2000,tags);
        fgets(tagdate,2000,tags);
        fgets(tagmassage,2000,tags);
        fscanf(tags,"%d\n",&overwrite1);
        tagname[strlen(tagname)-1]='\0';
        taguser[strlen(taguser)-1]='\0';
        tagdate[strlen(tagdate)-1]='\0';
        tagmassage[strlen(tagmassage)-1]='\0';
        if(feof(tags))break;
        if(strcmp(tagname,tagname1)==0){
            s=1;
            break;
        }
    }
    fclose(tags);
    chdir(workdirectory);
    if(s==1){
        *(tagcommitid)=commitid;
        *(overwrite)=overwrite1;
        return 1;
    }
    else{
        return 0;
    }
}


int run_tag(char* tagname,char* tagmassage,int tagcommitid,int tagoverwrite){
    char workdirectory[1000];
    char tagname1[100];
    int tagcommitid1;
    int tagoverwrite1;
    char tagusername1[100];
    char tagdate1[100];
    char tagmassage1[100];
    getcwd(workdirectory,sizeof(workdirectory));
    int a=findintags(tagname,&tagcommitid,&tagoverwrite1);
    if(a==1){
        if(tagoverwrite1==0)printf("tag name already exist!");
        else{
            found_gitmamal();
            chdir(gitmamaldirectory);
            FILE* tags=fopen("./configs/tags.txt","r");
            FILE* tags1=fopen("./configs/tags1.txt","w");
            while(1){
                fgets(tagname,100,tags);
                tagname[strlen(tagname)-1]='\0';
                fscanf(tags,"%d\n",&tagcommitid1);
                fgets(tagusername1,100,tags);
                fgets(tagdate1,100,tags);
                fgets(tagmassage1,100,tags);
                fscanf(tags,"%d\n",&tagoverwrite1);
                if(strcmp(tagname,tagname1)==0){
                    fputs(tagname,tags1);
                    fprintf(tags1,"%d\n",tagcommitid);
                    foundusername();
                    fprintf(tags1,"%s\n",username);
                    stat("./configs/tags1.txt",&fortime);
                    char time[100];
                    strftime(time,100,"%d/%m/%Y %H:%M:%S",localtime(&fortime.st_ctime));
                    fprintf(tags1,"%s\n",time);
                    fprintf(tags1,"%s\n",tagmassage);
                    fprintf(tags1,"%d\n",tagoverwrite);
                }
                else{
                    fputs(tagname1,tags);
                    fprintf(tags1,"%d\n",tagcommitid1);
                    fprintf(tags1,"%s\n",tagusername1);
                    fprintf(tags1,"%s\n",tagdate1);
                    fprintf(tags1,"%s\n",tagmassage1);
                    fprintf(tags1,"%d\n",tagoverwrite1);
                }
            }
            fclose(tags);
            fclose(tags1);
            tags=fopen("./configs/tags.txt","w");
            tags1=fopen("./configs/tags1.txt","r");
            while(1){
                fgets(tagname1,100,tags1);
                fscanf(tags1,"%d\n",&tagcommitid1);
                fscanf(tags1,"%s\n",tagusername1);
                fscanf(tags1,"%s\n",tagdate1);
                fscanf(tags1,"%s\n",tagmassage1);
                fscanf(tags1,"%d\n",&tagoverwrite1);
                if(feof(tags1))break;
                fputs(tagname1,tags);
                fprintf(tags,"%d\n",tagcommitid1);
                fprintf(tags,"%s\n",tagusername1);
                fprintf(tags,"%s\n",tagdate1);
                fprintf(tags,"%s\n",tagmassage1);
                fprintf(tags,"%d\n",tagoverwrite1);    
            }
            fclose(tags);
            fclose(tags1);
            chdir(workdirectory);
            remove("./configs/tags1.txt");
        }
    }
    else{
        found_gitmamal();
        chdir(gitmamaldirectory);
        FILE* tags=fopen("./configs/tags.txt","a");
        fputs(tagname,tags);
        fprintf(tags,"%d\n",tagcommitid);
        FILE* tagnamef=fopen("./configs/tagname.txt","a");
        fprintf(tagnamef,"%s\n",tagname);
        fclose(tagnamef);
        foundusername();
        fprintf(tags,"%s\n",username);
        FILE* nowtime=fopen("nowtime.txt","w");
        stat("./configs/nowtime.txt",&fortime);
        char time[100];
        strftime(time,100,"%d/%m/%Y %H:%M:%S",localtime(&fortime.st_ctime));
        fprintf(tags,"%s\n",time);
        fclose(nowtime);
        fprintf(tags,"%s\n",tagmassage);
        fprintf(tags,"%d\n",tagoverwrite);
        fclose(tags);
        chdir(workdirectory);
    }
    return 0;
}


char* deletenullspace(char* fordeletenullspace){
    int i=0;
    char* fordeletenullspace1=(char*)malloc(strlen(fordeletenullspace1)*sizeof(char));
    strcpy(fordeletenullspace1,fordeletenullspace);
    int tool=strlen(fordeletenullspace1);
    while(*(fordeletenullspace1+i)!='\0'){
        if((*(fordeletenullspace1+i)==' ')&&(*(fordeletenullspace1+i+1)==' ')){
            for(int j=i;j<tool;j++){
                *(fordeletenullspace1+j)=*(fordeletenullspace1+j+1);
            }
            tool--;
        }
        else{i++;}
    }
    return fordeletenullspace1;
}


int isnullspace(char* line){
    int i=0;
    while(*(line+i)!='\0'){
        if(*(line+i)!=' ')return 0;
        else{i++;}
    }
    return 1;
}


int run_diff(char* address1,char* address2,int begin1,int end1,int begin2,int end2){
    char line1[1000];
    char line2[1000];
    char line11[1000];
    char line22[1000];
    char line111[100][1000];
    char line222[100][1000];
    strcpy(line1,"");
    strcpy(line2,"");
    int i=0,j=0;
    FILE* file1=fopen(address1,"r");
    FILE* file2=fopen(address2,"r");
    while(1){
        if((feof(file1))&&(line1[0]!='\n'))return 0;
        fgets(line1,1000,file1);
        //printf("%s\n",line11);
        i++;
        line1[strlen(line1)-1]='\0';
        strcpy(line11,deletenullspace(line1));
        if(isnullspace(line1)==1)continue;
        while(1){
            if((feof(file2))&&(line2[0]!='\n'))return 0;
            fgets(line2,1000,file2);
            j++;
            line2[strlen(line2)-1]='\0';
            strcpy(line22,deletenullspace(line2));
            if(isnullspace(line2)==1)continue;
            //printf("%s\n%s",line11,line22);
            if((i>=begin1)&&(i<=end1)&&(j>=begin2)&&(j<=end2)&&(strcmp(line11,line22)!=0)){
                int x=0,y=0;
                char* tok=strtok(line11," ");
                while(tok!=NULL){
                    strcpy(line111[x],tok);
                    x++;
                    tok=strtok(NULL," ");
                }
                //printf("%s",line111[x-1]);
                char* tok1=strtok(line22," ");
                while(tok1!=NULL){
                    strcpy(line222[y],tok1);
                    y++;
                    tok1=strtok(NULL," ");
                }
                if(x==y){
                    int s=0;
                    int t;
                    for(int k=0;k<x;k++){
                        if(strcmp(line111[k],line222[k])!=0){
                            s++;
                            t=k;
                        }
                    }
                    //printf("%d %d %d %d ",s,x,y,t);
                    if(s==1){
                        printf("<<<<<<<<<<\n%s-%d\n","ssss.txt",i);
                        for(int k=0;k<x;k++){
                            if(k==t){
                                if(t!=x-1){
                                    printf(">>%s<< ",line111[k]);
                                }
                                else{printf(">>%s<<\n",line111[k]);}
                            }
                            else if((k==x-1)&&(k!=t))printf("%s\n",line111[k]);
                            else{printf("%s ",line111[k]);}   
                        }
                        printf("%s-%d\n","dddd.txt",j);
                        for(int k=0;k<x;k++){
                            if(k==t){
                                if(t!=x-1){
                                    printf(">>%s<< ",line222[k]);
                                }
                                else{printf(">>%s<<\n",line222[k]);}
                            }
                            else if((k==x-1)&&(k!=t))printf("%s\n",line222[k]);
                            else{printf("%s ",line222[k]);}
                        }
                        printf(">>>>>>>>>>\n");
                    
                    }
                    else{
                    printf("<<<<<<<<<<\n%s-%d\n%s\n%s-%d\n%s\n>>>>>>>>>>\n","ssss.txt",i,line1,"dddd.txt",j,line2);
                    }
                }
            }
            break;
        }        
    }
    fclose(file1);
    fclose(file2);
}


int filenumline(char* address){
    char line[1000];
    int i=0;
    FILE* address1=fopen(address,"r");
    while(feof(address1)==0){
        fgets(line,1000,address1);
        i++;
    }
    return i;
}

int main(int argc,char* argv[]){
    printf("aaaaa");
    if(argc==1){
        printf("please enter a valid command");
        return 0;
    }
    else if(strcmp(argv[1],"init")==0){
            run_init();
            return 0;
    }
    int a=found_gitmamal();
    if(a==0){
        printf("you have to initialize first!");
        return 0;
    }
    else if(strcmp(argv[1],"config")==0){
        a=found_gitmamal();
        if(a==0){
            printf("you have to initialize first");
            return 0;
        }
        else if((strncmp(argv[2],"alias.",6)==0)||(strncmp(argv[3],"alias.",6)==0)){
            int n=3,k=0;
            if(strcmp(argv[2],"-global")==0)n=4;
            if(strncmp(argv[n],"gitmamal config -global user.name",31)==0)k=1;
            else if(strncmp(argv[n],"gitmamal config -global user.email",32)==0)k=1;
            else if(strncmp(argv[n],"gitmamal config user.name",23)==0)k=1;
            else if(strncmp(argv[n],"gitmamal config user.email",24)==0)k=1;
            else if(strncmp(argv[n],"gitmamal config -global alias.",28)==0)k=1;
            else if(strncmp(argv[n],"gitmamal config -global alias.",28)==0)k=1;
            else if(strncmp(argv[n],"gitmamal init",11)==0)k=1;
            else if(strncmp(argv[n],"gitmamal add",10)==0)k=1;
            else if(strncmp(argv[n],"gitmamal reset",12)==0)k=1;
            else if(strncmp(argv[n],"gitmamal commit",13)==0)k=1;
            else if(strncmp(argv[n],"gitmamal status",13)==0)k=1;
            else if(strncmp(argv[n],"gitmamal branch",13)==0)k=1;
            else if(strncmp(argv[n],"gitmamal checkout",15)==0)k=1;
            else if(strncmp(argv[n],"gitmamal set",10)==0)k=1;
            else if(strncmp(argv[n],"gitmamal replace",14)==0)k=1;
            else if(strncmp(argv[n],"gitmamal remove",13)==0)k=1;
            else if(strncmp(argv[n],"gitmamal log",10)==0)k=1;
            if(k==0){
                printf("plese inter a valid command!");
                return 0;
            }
            else{
                run_alias(argc,argv);
                return 0;
            }   
        }
        run_config(argc,argv);
        return 0;
    }
    else if(strcmp(argv[1],"add")==0){
        a=found_gitmamal();
        if(a==0){
            printf("you have to initialize first!");
            return 0;
        }
        if(argc<3){
            printf("please inter a valid command!");
            return 0;
        }
        else if(argc==3){
            if((strcmp(argv[2],"-f")==0)||(strcmp(argv[2],"-n")==0)){
                printf("please inter a valid command!");
                return 0;
            }
            else{
                for(int i=0;i<strlen(argv[2]);i++){
                    if(argv[2][i]=='*'){
                        printf("there is no such word!");
                        return 0;
                    }
                }
                addnum=0;
                run_add_e(argv[2]);
                if(addnum!=0){
                    char workdirectory[1000];
                    getcwd(workdirectory,sizeof(workdirectory));
                    found_gitmamal();
                    chdir(gitmamaldirectory);
                    chdir("configs");
                    FILE* adds=fopen("adds.txt","w");
                    fprintf(adds,"%s\n",argv[2]);
                    fclose(adds);
                    chdir(workdirectory);
                }
                return 0;
            }
        }
        else if(strcmp(argv[2],"-n")==0){
            if(strcmp(argv[3],"1")!=0){
                printf("please inter a valid command!");
                return 0;
            }
            else{
                found_gitmamal();
                char workdirectory[1000];
                char address1[1000];
                int what=0;
                getcwd(workdirectory,sizeof(workdirectory));
                chdir(gitmamaldirectory);
                chdir("master");
                FILE* status=fopen("status.txt","r");
                chdir(workdirectory);
                DIR* directory=opendir(workdirectory);
                struct dirent* pp;
                while((pp=readdir(directory))!=NULL){
                    if(pp->d_type!=DT_DIR){
                        char help[1000];
                        strcpy(help,workdirectory);
                        strcat(help,"/");
                        strcat(help,pp->d_name);
                        last_modify(help);
                        while(1){
                            char address1[1000];
                            fgets(address1,1000,status);
                            address1[strlen(address1)-1]='\0';
                            if(feof(status))break;
                            if(strcmp(help,address1)==0){
                                fgets(lastadd,100,status);
                                lastadd[strlen(lastadd)-1]='\0';
                                fgets(mode,10,status);
                                mode[strlen(mode)-1]='\0';
                                FILE* checker=fopen(help,"r+");
                                if(checker!=NULL){
                                    if((strcmp(lastchange,lastadd)==0)&&(strcmp(mode,"se")==0)){
                                        fclose(checker);
                                        fclose(status);
                                        what=1;
                                    }
                                }
                                else{
                                    if(strcmp(mode,"sd")==0){
                                        fclose(status);
                                        fclose(checker);
                                        what=1;
                                    }
                                }
                            }
                            if(what==1){
                                printf("%s : staged",pp->d_name);
                            }
                            else{
                                printf("%s : unstaged",pp->d_name);
                            }
                        }                        
                    }
                    if(pp->d_type == DT_DIR){
                        if((strcmp(pp->d_name,".gitmamal")==0)||(strcmp(pp->d_name,".")==0)||(strcmp(pp->d_name,"..")==0))continue;
                        int stage=1;
                        DIR* directory1=opendir(pp->d_name);
                        struct dirent* pp1;
                        while((pp1=readdir(directory1))!=NULL){
                            if(pp1->d_type =! DT_DIR){
                                char help[1000];
                                strcpy(help,workdirectory);
                                strcat(help,"/");
                                strcat(help,pp->d_name);
                                strcat(help,"/");
                                strcat(help,pp1->d_name);
                                int o=statusidentifying(help);
                                if(o!=1){
                                    stage=0;
                                    break;
                                }
                            }
                        }
                        if(stage==0){
                            printf("%s : unstage",pp1->d_name);
                        }
                        else{
                            printf("%s : stage",pp1->d_name);
                        }
                        closedir(directory1);
                        chdir(workdirectory);
                    }
                }
                fclose(status);
                closedir(directory);
                return 0;
            }
        }
        else if(strcmp(argv[2],"-f")==0){
            char workdirectory[1000];
            getcwd(workdirectory,sizeof(workdirectory));
            for(int i=3;i<argc;i++){
                run_add_e(argv[i]);
            }
            //for reset undo
            if(addnum!=0){
                found_gitmamal();
                chdir(gitmamaldirectory);
                chdir("configs");
                FILE* adds=fopen("adds.txt","w");
                for(int i=0;i<addnum;i++){
                    fprintf(adds,"%s\n",addedmemory[i]);
                }
                fclose(adds);
                chdir(workdirectory);
            }
        }
        else{
            for(int i=2;i<argc;i++){
                run_add_e(argv[i]);
            }
            return 0;
        }
        return 0;
    }
    else if(strcmp(argv[1],"reset")==0){
        int a=found_gitmamal();
        if(argc<3){
            printf("please inter a valid command!");
            return 0;
        }
        else{
            if(a==0){
                printf("you have to initialize first");
                return 0;
            }
            else if(argc==3){
                if(strcmp(argv[2],"-f")==0){
                    printf("please inter a valid command");
                    return 0;
                }
                else if(strcmp(argv[2],"undo")==0){
                    char workdirectory[1000];
                    char address[100];
                    getcwd(workdirectory,sizeof(workdirectory));
                    chdir(gitmamaldirectory);
                    chdir("configs");
                    FILE* adds=fopen("adds.txt","r");
                    while(1){
                        fgets(address,1000,adds);
                        address[strlen(address)-1]='\0';
                        if(feof(adds))break;
                        run_reset_e(address);
                    }
                    chdir(workdirectory);
                    fclose(adds);
                    return 0;
                }
                else{
                    int s=0;
                    for(int i=0;i<strlen(argv[2]);i++){
                        if(argv[2][i]=='*'){
                            s=1;
                            break;
                        }
                    }
                    if(s==1){
                        printf("there is no such word!");
                        return 0;
                    }
                    run_reset_e(argv[2]);
                    return 0;
                }
            }
            else if(strcmp(argv[2],"-f")==0){
                for(int i=3;i<argc;i++){
                    run_reset_e(argv[i]);
                }
                return 0;
            }
            else{
                for(int i=2;i<argc;i++){
                    run_reset_e(argv[i]);
                }
                return 0;
            }
        }
    }
    else if(strcmp(argv[1],"commit")==0){
        if(argc!=4){
            printf("please inter a valid command!");
            return 0;
        }
        else if(strcmp(argv[2],"-s")==0){
            char workdirectory[1000];
            getcwd(workdirectory,sizeof(workdirectory));
            found_gitmamal();
            FILE* shortcuts=fopen("./configs/shortcuts.txt","r");
            char shortcutname[100];
            char shortcutmass[100];
            int k=0;
            while(1){
                fgets(shortcutname,100,shortcuts);
                fgets(shortcutmass,100,shortcuts);
                if(feof(shortcuts))break;
                shortcutname[strlen(shortcutname)-1]='\0';
                shortcutmass[strlen(shortcutmass)-1]='\0';
                if(strcmp(argv[3],shortcutname)==0){
                    k=1;
                    break;
                }
            }
            if(k==0){
                printf("the shortcut name does'nt exist");
            }
            else{
                run_commit(shortcutmass);
                chdir(workdirectory);
            }
        }
        else if(strcmp(argv[2],"-m")){
            if(strlen(argv[3])>72)printf("the commit massage is too long!");
            else{
                run_commit(argv[3]);
                return 0;
            }
        }
        else{
            printf("please inter a valid command!");
            return 0;
        }
    }
    else if(strcmp(argv[1],"set")==0){
        if(argc!=6)printf("please inter a valid command!");
        else if((strcmp(argv[2],"-m")!=0)||(strcmp(argv[4],"-s")!=0))printf("please inter a valid command!");
        else{
            char workdirectory[1000];
            char shortcutname[100];
            char shortcutmass[200];
            getcwd(workdirectory,sizeof(workdirectory));
            found_gitmamal();
            chdir(gitmamaldirectory);
            FILE* shortcuts=fopen("./configs/shortcuts.txt","r");
            while(1){
                fgets(shortcutname,100,shortcuts);
                fgets(shortcutmass,200,shortcuts);
                shortcutname[strlen(shortcutname)-1]='\0';
                if(feof(shortcuts))break;
                if(strcmp(shortcutname,argv[5])==0){
                    printf("the shortcut massage is already exist!");
                    fclose(shortcuts);
                    return 0;
                }
            }
            fclose(shortcuts);
            shortcuts=fopen("./configs/shortcuts.txt","a");
            fprintf(shortcuts,"%s\n",argv[5]);
            fprintf(shortcuts,"%s\n",argv[3]);
            chdir(workdirectory);
        }
        return 0;
    }
    else if(strcmp(argv[1],"replace")==0){
        if(argc!=6)printf("please inter a valid command!");
        else if((strcmp(argv[2],"-m")!=0)||(strcmp(argv[4],"-s")!=0))printf("please inter a valid command!");
        else{
            char workdirectory[1000];
            getcwd(workdirectory,sizeof(workdirectory));
            found_gitmamal();
            chdir(gitmamaldirectory);
            FILE* shortcuts=fopen("./configs/shortcuts.txt","r");
            int k = 0;
            char shortcutname[100];
            char shortcutmass[200];
            while(1) {
                fgets(shortcutname,100,shortcuts);
                fgets(shortcutmass,100,shortcuts);
                if(feof(shortcuts)) break;
                shortcutname[strlen(shortcutname)-1]='\0';
                if(strcmp(argv[5],shortcutname)==0){
                    k = 1;
                    break;
                }
            }
            fclose(shortcuts);
            if(k==0)printf("the shortcut name does not exist!");
            else {
                shortcuts=fopen("./configs/shortcuts.txt","r");
                FILE* shortcuts1=fopen("./configs/shortcuts1.txt","w");
                while(1) {
                    fgets(shortcutname,100,shortcuts);
                    fputs(shortcutname,shortcuts1);
                    fgets(shortcutmass,200,shortcuts);
                    if(feof(shortcuts1))break;
                    shortcutname[strlen(shortcutname)-1]='\0';
                    if(strcmp(argv[5],shortcutname)==0){
                        fprintf(shortcuts1,"%s\n",argv[3]);
                    }
                    else{fputs(shortcutmass,shortcuts1);}
                }
                fclose(shortcuts);
                fclose(shortcuts1);
                shortcuts=fopen("./configs/shortcuts.txt","w");
                shortcuts1=fopen("./configs/shortcuts1.txt","r");
                while(1) {
                    fgets(shortcutname,100,shortcuts1);
                    fgets(shortcutmass,200,shortcuts1);
                    if(feof(shortcuts1))break;
                    fprintf(shortcuts,"%s\n",shortcutname);
                    fprintf(shortcuts,"%s\n",shortcutmass);
                }
                fclose(shortcuts);
                fclose(shortcuts1);
                remove("./config1/shortcuts.txt");
            }
            chdir(workdirectory);
        }
        return 0;
    }
    else if(strcmp(argv[1],"remove")==0){
        if(argc!=4)printf("please inter a valid command!");
        else if(strcmp(argv[2],"-s")!=0)printf("please inter a valid command!");
        else{
            char workdirectory[1000];
            getcwd(workdirectory,sizeof(workdirectory));
            found_gitmamal();
            chdir(gitmamaldirectory);
            FILE* shortcuts=fopen("./configs/shortcuts.txt","r");
            int k = 0;
            char shortcutname[100];
            char shortcutmass[200];
            while(1) {
                fgets(shortcutname,100,shortcuts);
                fgets(shortcutmass,100,shortcuts);
                if(feof(shortcuts)) break;
                shortcutname[strlen(shortcutname)-1]='\0';
                if(strcmp(argv[3],shortcutname)==0){
                    k = 1;
                    break;
                }
            }
            fclose(shortcuts);
            if(k==0)printf("the shortcut name does not exist!");
            else {
                FILE* shortcuts=fopen("./configs/shortcuts.txt","r");
                FILE* shortcuts1=fopen("./configs/shortcuts1.txt","w");
                while(1) {
                    fgets(shortcutname,100,shortcuts1);
                    fgets(shortcutmass,200,shortcuts1);
                    if(feof(shortcuts1))break;
                    shortcutname[strlen(shortcutname)-1]='\0';
                    if(strcmp(argv[3],shortcutname)!=0){
                        fprintf(shortcuts1,"%s\n",shortcutname);
                        fprintf(shortcuts1,"%s\n",shortcutmass);
                    }                                             
                }
                fclose(shortcuts);
                fclose(shortcuts1);
                shortcuts=fopen("./configs/shortcuts.txt","w");
                shortcuts1=fopen("./configs/shortcuts1.txt","r");
                while(1) {
                    fgets(shortcutname,100,shortcuts1);
                    fgets(shortcutmass,200,shortcuts1);
                    if(feof(shortcuts1))break;
                    fprintf(shortcuts,"%s\n",shortcutname);
                    fprintf(shortcuts,"%s\n",shortcutmass);
                }
                fclose(shortcuts);
                fclose(shortcuts1);
                remove("./config1/shortcuts.txt");
            }
            chdir(workdirectory);
        }
        return 0;
    }
    else if(strcmp(argv[1],"log")==0){
        char workdirectory[1000];
        getcwd(workdirectory,sizeof(workdirectory));
        found_gitmamal();
        chdir(gitmamaldirectory);
        FILE* lastcommits=fopen("./configs/numcommit.txt","r");
        fscanf(lastcommits,"%d",&curcommit);
        fclose(lastcommits);
        chdir(workdirectory);
        if(argc==2){
            for(int i=curcommit;i>0;i--){
                search_commit_information(i);
                printf("commit time : %s",committime);
                printf("commit massage : %s",commitmassage);
                printf("commit username : %s",commitusername);
                printf("commit id : %d",curcommit);
                printf("commit branch : master");
                printf("commited file number : %d",commitnumstage);
            }
        }
        else if((argc==4)&&(strcmp(argv[2],"-n")==0)){
            int r;
            sscanf(argv[3],"%d",&r);
            for(int i=curcommit;i>curcommit-r;i--){
                search_commit_information(i);
                printf("commit time : %s",committime);
                printf("commit massage : %s",commitmassage);
                printf("commit username : %s",commitusername);
                printf("commit id : %d",curcommit);
                printf("commit branch : master");
                printf("commited file number : %d",commitnumstage);
            }
        }
        else if((argc==4)&&(strcmp(argv[2],"-author")==0)){
            int k=0;
            for(int i=curcommit;i>0;i--){
                search_commit_information(i);
                if(strcmp(commitusername,argv[3])==0){
                    k=1;
                    printf("commit time : %s",committime);
                    printf("commit massage : %s",commitmassage);
                    printf("commit username : %s",commitusername);
                    printf("commit id : %d",curcommit);
                    printf("commit branch : master");
                    printf("commited file number : %d",commitnumstage);
                }
                if(k==0)printf("there is no commit with this username!");   
            }
        }
        else if((argc==4)&&(strcmp(argv[2],"-since")==0)){
            int k=0;
            for(int i=curcommit;i>0;i--){
                search_commit_information(i);
                if(datecom(committime,argv[3])==1){
                    k=1;
                    printf("commit time : %s",committime);
                    printf("commit massage : %s",commitmassage);
                    printf("commit username : %s",commitusername);
                    printf("commit id : %d",curcommit);
                    printf("commit branch : master");
                    printf("commited file number : %d",commitnumstage);
                }
            }
            if(k==0)printf("there is no commit with this condition!");
        }
        else if((argc==4)&&(strcmp(argv[2],"-before")==0)){
            int k=0;
            for(int i=curcommit;i>0;i--){
                search_commit_information(i);
                if(datecom(committime,argv[3])==0){
                    k=1;
                    printf("commit time : %s",committime);
                    printf("commit massage : %s",commitmassage);
                    printf("commit username : %s",commitusername);
                    printf("commit id : %d",curcommit);
                    printf("commit branch : master");
                    printf("commited file number : %d",commitnumstage);
                }
            }
            if(k==0)printf("there is no commit with this condition!");
        }
        else if(strcmp(argv[2],"-search")==0){
            int k=0;
            for(int i=curcommit;i>0;i--){
                search_commit_information(i);
                if(strstr(commitmassage,argv[3])!=NULL){
                    k=1;
                    printf("commit time : %s",committime);
                    printf("commit massage : %s",commitmassage);
                    printf("commit username : %s",commitusername);
                    printf("commit id : %d",curcommit);
                    printf("commit branch : master");
                    printf("commited file number : %d",commitnumstage);
                }
            }
            if(k==0)printf("there is no commit with this condition!");
        }
    }
    else if(strcmp(argv[1],"diff")==0){
        if((argc==5)&&(strcmp(argv[2],"-f")==0)){
            run_diff(argv[3],argv[4],1,filenumline(argv[3]),1,filenumline(argv[4]));
        }
    }
    
    else if(strcmp(argv[1],"tag")==0){
        char workdirectory[1000];
        getcwd(workdirectory,sizeof(workdirectory));
        int a=found_gitmamal();
        if(a==0){
            printf("please initialize first!");
            return 0;
        }
        else{
            if(argc==2){
                char tag[100][100];
                    int s=0;
                    int i=0;
                    chdir(gitmamaldirectory);
                    FILE* tags=fopen("./configs/tagname.txt","r");
                    if(tags== NULL)printf("there are no tags!");
                    else{
                        while(1){
                            fgets(tagname,1000,tags);
                            if(feof(tags))break;
                            tagname[strlen(tagname)-1]='\0';
                            strcpy(tag[i],tagname);
                            i++;
                        }
                        for(int j=0;j<i;j++){
                            for(int k=j;k<i;k++){
                                if(strcmp(tag[i],tag[j])>0){
                                    char h[100];
                                    strcpy(h,tag[i]);
                                    strcpy(tag[i],tag[j]);
                                    strcpy(tag[j],h);
                            }
                        }
                    }
                    for(int j=0;j<i;j++){
                        printf("%s\n",tag[i]);
                    }
                }
                fclose(tags);
                chdir(workdirectory);
            }
            else if(argc==4){
                if(strcmp(argv[2],"show")==0){
                    
                }
            }

        }

    }
}
