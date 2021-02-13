/* FileBase.c is a program for 
   creating and managing custom database-like files.
   These databases can import various file types.
   The point is to store many files simultaneously in a single database file.

   Function overview:
   Import file
      * By pressing "1" and typing the filename or the filepath.
      * If two filepaths ends up in the same filename, it will assume it is
      * the same file, thus asking you to replace it.
   Search file
      * By pressing "2" and typing part of the filename.
      * A list of files containing this part is printed.
   Export file
      * By pressing "3" and typing filename existing in database.
      * The program asks you to type the filename for the exported file.
      * A new file is being created with the specified filename.
      * Note: You are responsible for assigning correct file extension.
   Delete file
      * By pressing "4" and typing filename existing in database.
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define BYTE_SIZE 512
#define NAME_SIZE 20
#define PATH_SIZE 50

struct file_data{
	int name_bytes;
	long total_bytes;
	char file_name[NAME_SIZE];
	char data[BYTE_SIZE];
};

// Function for debugging
void checking(long check_fd,int line){
	
	if(check_fd==-1){
		printf("error in line %d..\n",line);
		exit(1);
	}
}

// Function used in "Export" and "Delete"
// Copies contents of FD1 to FD2 per 512 bytes
void imp_to_exp(int fd1,int fd2,struct file_data info){
	int check_fd1,check_fd2;
	long counter=0;
	
	if(info.total_bytes<=BYTE_SIZE){
		do{
			check_fd1=read(fd1,info.data,info.total_bytes);
			checking(check_fd1,__LINE__);
			
			check_fd2=write(fd2,info.data,info.total_bytes);
			checking(check_fd2,__LINE__);
			
		}while(check_fd1 !=0 && check_fd1 !=info.total_bytes);
	}else{
		if(info.total_bytes/BYTE_SIZE==1){
			do{
				check_fd1=read(fd1,info.data,BYTE_SIZE);
				checking(check_fd1,__LINE__);
				
				check_fd2=write(fd2,info.data,check_fd1);
				checking(check_fd2,__LINE__);
				
			}while(check_fd2<BYTE_SIZE);
			do{
				check_fd1=read(fd1,info.data,(info.total_bytes-BYTE_SIZE));
				checking(check_fd1,__LINE__);
				
				check_fd2=write(fd2,info.data,check_fd1);
				checking(check_fd2,__LINE__);
				
			}while(check_fd1<(info.total_bytes-BYTE_SIZE) && check_fd1 != 0);
		}
		else{
			do{
				check_fd1=read(fd1,info.data,BYTE_SIZE);
				checking(check_fd1,__LINE__);
				
				check_fd2=write(fd2,info.data,check_fd1);
				checking(check_fd2,__LINE__);
				counter=counter+check_fd2;
				
			}while((counter+check_fd1)<info.total_bytes);
			
			do{
				check_fd1=read(fd1,info.data,(info.total_bytes%BYTE_SIZE));
				checking(check_fd1,__LINE__);
				
				check_fd2=write(fd2,info.data,check_fd1);
				checking(check_fd2,__LINE__);
				
			}while(check_fd1<(info.total_bytes%BYTE_SIZE)&& check_fd1 != 0);
		}
	}
	fsync(fd2);
	lseek(fd1,-info.total_bytes,SEEK_CUR);
}

void delete(int fd1,struct file_data info,char name[],char argv[]){

	long counter=0,ls,check,sum,bytes_calc,temp;
	int fd2,flag=0;
	char *name_fix;
	
	fd2=open(argv,O_RDWR,S_IRWXU);
	lseek(fd2,sizeof(long),SEEK_SET);
	
	counter=lseek(fd1,0,SEEK_END);
	checking(counter,__LINE__);
	
	if(counter==sizeof(long)){
		printf("empty base nothing to delete\n");
		return;
	}
	
	lseek(fd1,0,SEEK_SET);
	check=lseek(fd1,sizeof(long),SEEK_SET);
	checking(check,__LINE__);
	
	do{
		memset(info.file_name,' ',NAME_SIZE);
		check=read(fd1,&info.name_bytes,sizeof(int));
		checking(check,__LINE__);
					
		check=read(fd1,info.file_name,info.name_bytes);
		checking(check,__LINE__);
					
		name_fix=strchr(info.file_name,' ');
		if(name_fix!=NULL){
			*name_fix='\0';
		}
		
		check=read(fd1,&info.total_bytes,sizeof(long));
		checking(check,__LINE__);
		
 		ls=lseek(fd1,info.total_bytes,SEEK_CUR);
		checking(ls,__LINE__);
 		temp=ls;
		
 		ls=lseek(fd1,-info.total_bytes,SEEK_CUR);
		checking(ls,__LINE__);
		
		bytes_calc=info.name_bytes+sizeof(int)+info.total_bytes+sizeof(long);
		
		if(strcmp(info.file_name,name)==0){
 			check=lseek(fd1,info.total_bytes- bytes_calc,SEEK_CUR);
			checking(check,__LINE__);
			
			flag=1;
 			if(temp>=counter){
				check=lseek(fd2,bytes_calc,SEEK_CUR);
				checking(check,__LINE__);
				
 				check=ftruncate(fd2,counter-bytes_calc);
				checking(check,__LINE__);
 			}else{
				check=lseek(fd2,bytes_calc,SEEK_CUR);
				checking(check,__LINE__);
				do{
					memset(info.file_name,' ',NAME_SIZE);
					check=read(fd2,&info.name_bytes,sizeof(int));
					checking(check,__LINE__);
						
					check=read(fd2,info.file_name,info.name_bytes);
					checking(check,__LINE__);
						
					name_fix=strchr(info.file_name,' ');
					if(name_fix!=NULL){
						*name_fix='\0';
					}
					
					check=read(fd2,&info.total_bytes,sizeof(long));
					checking(check,__LINE__);
					
					sum=lseek(fd2,info.total_bytes,SEEK_CUR);
					checking(sum,__LINE__);
					
					check=lseek(fd2,-info.total_bytes,SEEK_CUR);
					checking(check,__LINE__);
					
					check=write(fd1,&info.name_bytes,sizeof(int));
					checking(check,__LINE__);
					
					check=write(fd1,info.file_name,info.name_bytes);
					checking(check,__LINE__);
					
					check=write(fd1,&info.total_bytes,sizeof(long));
					checking(check,__LINE__);
					
					imp_to_exp(fd2,fd1,info);
					
					check=lseek(fd2,info.total_bytes,SEEK_CUR);
					checking(check,__LINE__);
					
					fsync(fd1);
				}while(sum < counter);
			
				
				check=ftruncate(fd2,counter-bytes_calc);
				checking(check,__LINE__);
			}
		}
		ls=lseek(fd1,info.total_bytes,SEEK_CUR);
		checking(ls,__LINE__);
		temp=ls;
		memset(info.file_name,' ',NAME_SIZE);
		check=lseek(fd2,bytes_calc,SEEK_CUR);
		checking(check,__LINE__);
		
	}while(flag!=1 && counter != temp );
	
	if(flag !=1){
		printf("file is not imported\n");
	}
	
	lseek(fd1,0,SEEK_SET);
	close(fd2);
}


void import(int fd1,int fd2,struct file_data info,char argv[]){
	
	long check_fd1,check_fd2,flag=0;
	long counter=0,temp,ls;
	char name[NAME_SIZE],option,*name_fix;
	
	strcpy(name,info.file_name);
	
	counter=lseek(fd1,0,SEEK_END);
	checking(counter,__LINE__);
	
	lseek(fd1,0,SEEK_SET);
	check_fd1=lseek(fd1,sizeof(long),SEEK_SET);
	checking(check_fd1,__LINE__);

	do{
		if(counter==sizeof(long)){
			break;
		}
		memset(info.file_name,' ',NAME_SIZE);
		check_fd1=read(fd1,&info.name_bytes,sizeof(int));
		checking(check_fd1,__LINE__);
		
		check_fd1=read(fd1,info.file_name,info.name_bytes);
		checking(check_fd1,__LINE__);
			
		name_fix=strchr(info.file_name,' ');
		if(name_fix!=NULL){
			*name_fix='\0';
		}
			
		check_fd1=read(fd1,&info.total_bytes,sizeof(long));
		checking(check_fd1,__LINE__);
			
		if(strcmp(info.file_name,name)==0){
			do{
				flag=1;
				printf("This file already exists. Do you want to continue?(y/n): ");
				scanf(" %c",&option);
				
				if(option== 'y'){
					delete(fd1,info,name,argv);
					break;
				}
			}while(option != 'n');
		}
		ls=lseek(fd1,info.total_bytes,SEEK_CUR);
		checking(ls,__LINE__);
		temp=ls;
		
	}while(counter > temp &&flag!=1);
	check_fd1=lseek(fd1,0,SEEK_END);
	checking(check_fd1,__LINE__);
	
	if(flag==0||(flag==1 && option== 'y')){
		
		info.total_bytes= lseek(fd2, 0, SEEK_END);
		checking(info.total_bytes,__LINE__);
		
		check_fd2=lseek(fd2,0,SEEK_SET);
		checking(check_fd2,__LINE__);
		
		info.name_bytes=strlen(name);
		checking(info.name_bytes,__LINE__);
		
		check_fd1=write(fd1,&info.name_bytes,sizeof(int));
		checking(check_fd1,__LINE__);
		
		check_fd1=write(fd1,name,info.name_bytes);
		checking(check_fd1,__LINE__);
		
		check_fd1=write(fd1,&info.total_bytes,sizeof(long));
		checking(check_fd1,__LINE__);
		
		do{
			check_fd2=read(fd2,info.data,BYTE_SIZE);
			checking(check_fd2,__LINE__);
			
			check_fd1=write(fd1,info.data,check_fd2);
			checking(check_fd1,__LINE__);
		}while(check_fd2 !=0);
	}
	fsync(fd1);
}
void search(int fd1,struct file_data info,char name[]){
	
	char *name_fix;
	long temp,counter,check_fd1,ls;
	int flag=0;
	
	
	counter=lseek(fd1,0,SEEK_END);
	checking(counter,__LINE__);
	
	if(counter==sizeof(long)){
		printf("Database is empty \n");
		return;
	}
	
	check_fd1=lseek(fd1,0,SEEK_SET);
	checking(check_fd1,__LINE__);
	
	check_fd1=lseek(fd1,sizeof(long),SEEK_SET);
	checking(check_fd1,__LINE__);
	
	if(strcmp(name,"*")==0){
		do{
			memset(info.file_name,' ',NAME_SIZE);
			check_fd1=read(fd1,&info.name_bytes,sizeof(int));
			checking(check_fd1,__LINE__);
			
			check_fd1=read(fd1,info.file_name,info.name_bytes);
			checking(check_fd1,__LINE__);
	
			name_fix=strchr(info.file_name,' ');
			if(name_fix!=NULL){
				*name_fix='\0';
			}
			
			check_fd1=read(fd1,&info.total_bytes,sizeof(long));
			checking(check_fd1,__LINE__);
	
			printf("%s\n",info.file_name);
			
			ls=lseek(fd1,info.total_bytes,SEEK_CUR);
			checking(ls,__LINE__);
			temp=ls;
			
		}while(counter > temp);
	}
	else{
		do{
			memset(info.file_name,' ',NAME_SIZE);
			check_fd1=read(fd1,&info.name_bytes,sizeof(int));
			checking(check_fd1,__LINE__);
			
			check_fd1=read(fd1,info.file_name,info.name_bytes);
			checking(check_fd1,__LINE__);
			
			name_fix=strchr(info.file_name,' ');
			if(name_fix!=NULL){
				*name_fix='\0';
			}
			
			check_fd1=read(fd1,&info.total_bytes,sizeof(long));
			checking(check_fd1,__LINE__);
			
			if(strcmp(info.file_name,name)==0){
				printf("%s\n",info.file_name);
				flag=1;
			}
					
			if(name_fix != NULL){
				if(strcmp(name,(name_fix+1))==0){
					printf("%s\n",info.file_name);
				}
			}
			if(flag!=1){
				if(strstr(info.file_name,name)!=NULL){
					printf("%s\n",info.file_name);
				}
			}
			ls=lseek(fd1,info.total_bytes,SEEK_CUR);
			checking(ls,__LINE__);
			temp=ls;		
			flag=0;
			
		}while(counter > temp);
	}
	check_fd1=lseek(fd1,0,SEEK_SET);
	checking(check_fd1,__LINE__);
}

void export(int fd1,char name[],char dest[],struct file_data info){
	
	long counter,check_fd1,trunc,temp,ls;
	int fd2,flag=0;
	char option,*name_fix;
	
	counter=lseek(fd1,0,SEEK_END);
	checking(counter,__LINE__);
	if(counter==sizeof(long)){
		printf("Empty base cannot export\n");
		return;
	}
	
	check_fd1=lseek(fd1,0,SEEK_SET);
	checking(check_fd1,__LINE__);
	
	check_fd1=lseek(fd1,sizeof(long),SEEK_SET);
	checking(check_fd1,__LINE__);
	
	do{
		memset(info.file_name,' ',NAME_SIZE);
		check_fd1=read(fd1,&info.name_bytes,sizeof(int));
		checking(check_fd1,__LINE__);
		
		check_fd1=read(fd1,info.file_name,info.name_bytes);
		checking(check_fd1,__LINE__);
		
		name_fix=strchr(info.file_name,' ');
		if(name_fix!=NULL){
			*name_fix='\0';
		}
		
		check_fd1=read(fd1,&info.total_bytes,sizeof(long));
		checking(check_fd1,__LINE__);
		
		if(strcmp(info.file_name,name)==0){
			flag=1;
			fd2=open(dest,O_RDWR|O_APPEND,S_IRWXU);
			if(fd2==-1){
				fd2=open(dest,O_RDWR|O_APPEND|O_TRUNC|O_CREAT,S_IRWXU);
				checking(fd2,__LINE__);
				
				imp_to_exp(fd1,fd2,info);	
			}else{
				printf("The destination file already exists. Do you want to continue?(y/n):");
				scanf(" %c",&option);
				
				switch(option){
				
					case 'y':{
						trunc=ftruncate(fd2,0);
						if(trunc!=0){
							printf("error trunc\n");
							exit(1);
						}
						check_fd1=lseek(fd2,0,SEEK_SET);
						checking(check_fd1,__LINE__);
						
						imp_to_exp(fd1,fd2,info);
						break;
					}
					case 'n':
						break;
									
					default:{
						printf("Wrong choice\n");
						break;
					}
				}
			}
		}
		ls=lseek(fd1,info.total_bytes,SEEK_CUR);
		checking(ls,__LINE__);
		temp=ls;		
		memset(info.file_name,' ',NAME_SIZE);
		
	}while(counter != temp &&flag !=1);
				
	if(flag !=1){
		printf("The file you are looking for is not in database\n");
	}
	lseek(fd1,0,SEEK_SET);
	close(fd2);
}

// Function opening data base and checks for magic code
int base_open(char file_path[]){
	int fd;
	long magic_code,key;
	
	magic_code=57024;
	
	fd=open(file_path,O_RDWR,S_IRWXU);
	if(fd==-1){
		
		fd=open(file_path,O_RDWR|O_TRUNC|O_CREAT,S_IRWXU);
                
		if(fd==-1){
			printf("problem base_open\n");
			exit(1);
		}
		write(fd,&magic_code,sizeof(long));
		return fd;
	}
	else{
		read(fd,&key,sizeof(long));
		if(magic_code==key){
			return fd;
		}else{
			printf("This database is not mine\n");
			exit(1);
		}
	}
}



int main(int argc,char *argv[]){
	
	int fd1,fd2,option,flag=0;
 	char file_path[PATH_SIZE],*name_finder,*path,name[NAME_SIZE],dest[NAME_SIZE],choice;
	struct file_data info;
	
	
	memset(file_path,' ',PATH_SIZE);
	memset(info.file_name,' ',NAME_SIZE);
	memset(dest,' ',NAME_SIZE);
	
	fd1=base_open(argv[1]);
	checking(fd1,__LINE__);
	
	do{
		printf("\n1.import\n2.search\n3.export\n4.delete\n5.quit\n");
		scanf(" %d", &option);
		
		switch(option){
		
			case 1:{
				printf("Write the name of the file: ");
				scanf(" %50s",file_path);
				
				fd2=open(file_path,O_RDWR|O_APPEND,S_IRWXU);
				if(fd2==-1){
					printf("File doesn't exist\n");
					break;
				}
				
				name_finder=strrchr(file_path,'/');
				if(name_finder==NULL){
						
					path=strchr(file_path,' ');
					if(path !=NULL){
						*path='\0';
					}
						
					strcpy(info.file_name, file_path);
					path=strchr(info.file_name,' ');
					if(path !=NULL){
						*path='\0';
					}
					import(fd1,fd2,info,argv[1]);
				}
				if(name_finder !=NULL){
					path=strchr(name_finder,' ');
					if(path !=NULL){
						*path='\0';
					}
					strcpy(info.file_name,(name_finder+1));
					
					path=strchr(info.file_name,' ');
					if(path !=NULL){
						*path='\0';
					}
					
					import(fd1,fd2,info,argv[1]);
				}
				close(fd2);
				break;
			}
			case 2:{
				printf("Write the name of the file: ");
				scanf(" %20s",name);
				
				search(fd1, info,name);
				break;
			}
			case 3:{
				printf("Write the name of the file: ");
				scanf(" %20s",name);
				
				printf("Write the name of the destination file: ");
				scanf(" %50s",file_path);
				
				name_finder=strrchr(file_path,'/');
				if(name_finder==NULL){
					
					path=strchr(file_path,' ');
					if(path !=NULL){
						*path='\0';
					}
					export(fd1,name,file_path,info);
				}
				if(name_finder !=NULL){
					path=strchr(name_finder,' ');
					if(path !=NULL){
						*path='\0';
					}
					export(fd1,name,file_path,info);
				}
				break;
			}
			case 4:{
				printf("Write the name of the file: ");
				scanf(" %20s",name);
				delete(fd1,info,name,argv[1]);
				break;
			}
			case 5:{
				flag=1;
				break;
			}
			default:{
				printf("Wrong input do you want to exit?(y/n)\n");
				scanf(" %c",&choice);
				break;
			}
		}
	}while(choice!='y'&& flag!=1);	
	close(fd1);
	return 0;
}
