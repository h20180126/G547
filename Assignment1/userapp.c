#include <stdio.h> 
#include<stdlib.h>
#include<fcntl.h>
#include <unistd.h>
#include<sys/types.h>
#include<stdint.h>

#define adxl_x "/dev/adxl_x"
#define adxl_y "/dev/adxl_y"
#define adxl_z "/dev/adxl_z"

int main()

{ 
  int fd,fd1,fd2,n,i;
  uint16_t read_buff;
  int ch;
 do
 {
  printf(" Enter which axis data do you want\n1 for xaxis\n2 for yaxis \n3 for zaxis\n4 for allaxis data\n");
  
  scanf("%d",&n);
  if(n>4)
  {
   printf("enter valid selection\n");
   exit;
  }
  if(n==1)
  {
  fd=open(adxl_x, O_RDWR);//OPEN FOR READING AND WRITING 
  
  if(fd  == -1)
  {
  
    printf("file %s does not exit or provide permission to access file as sudo chmod 777 /dev/adxl_*\n",adxl_x);
    exit(-1);
  }
  
  read(fd,&read_buff,sizeof(read_buff));
  printf("accelerometer xais value device data read is %d\n ",read_buff);
  }
  
  if(n==2)
  {
  fd=open(adxl_y , O_RDWR);//OPEN FOR READING AND WRITING 
  
  if(fd  == -1)
  {
  
    printf("file %s does not exit or provide permission to access file as sudo chmod 777 /dev/adxl_*\n",adxl_x);
    exit(-1);
  }
  
  read(fd,&read_buff,sizeof(read_buff));
  printf("accelerometer yaxis value device data read is %d\n",read_buff);
  }
  if(n==3)
  {
  fd=open(adxl_z, O_RDWR);//OPEN FOR READING AND WRITING for read only use O_RDONLY
  
  if(fd  == -1)
  {
  
    printf("file %s does not exit or provide permission to access file as sudo chmod 777 /dev/adxl_*\n",adxl_z);
    exit(-1);
  }
  
  read(fd,&read_buff,sizeof(read_buff));
  printf("accelerometer zaxis value device data read is %d\n",read_buff);
  }
  if(n==4)
  {
  fd=open(adxl_x, O_RDWR);//OPEN FOR READING AND WRITING for read only use O_RDONLY
  
  if(fd  == -1)
  {
  
    printf("file %s does not exit or provide permission to access file as sudo chmod 777 /dev/adxl_*\n",adxl_x);
    exit(-1);
  }
  
  read(fd,&read_buff,sizeof(read_buff));
  printf("accelerometer xaxis value device data read is %d\n",read_buff);
  close(fd);
  
  
  fd1=open(adxl_y , O_RDWR);//OPEN FOR READING AND WRITING for read only use O_RDONLY
  
  if(fd1  == -1)
  {
  
    printf("file %s does not exit or provide permission to access file as sudo chmod 777 /dev/adxl_*\n",adxl_y);
    exit(-1);
  }
  
  read(fd1,&read_buff,sizeof(read_buff));
  printf("accelerometer yaxis value device data read is %d\n",read_buff);
   close(fd1);
  
  fd2=open(adxl_z, O_RDWR);//OPEN FOR READING AND WRITING for read only use O_RDONLY
  
  if(fd1  == -1)
  {
  
    printf("file %s does not exit or provide permission to access file as sudo chmod 777 /dev/adxl_*\n",adxl_z);
    exit(-1);
  }
  
  read(fd,&read_buff,sizeof(read_buff));
  printf("accelerometer zaxis value device data read is %d\n",read_buff);
  close(fd2);
  
  }
  
  close(fd);
  printf("enter 1 to take further values  and any key to exit\n"); 
  scanf("%d",&ch);
  }while(ch==1);  
  
  return 0;
}
