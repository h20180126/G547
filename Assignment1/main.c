#include<linux/init.h>
#include<linux/module.h>
#include<linux/version.h>
#include<linux/kernel.h>
#include<linux/types.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/device.h>
#include<linux/cdev.h>
#include <linux/uaccess.h>
#include<linux/random.h>

static dev_t first;//variable for device number
static struct cdev c_dev1;
static struct class *cls;
static dev_t second;//variable for device number
static struct cdev c_dev2;
static dev_t third;//variable for device number
static struct cdev c_dev3;
static dev_t first1;
int ret;
int x;
uint16_t val;
uint16_t getrand(void){
	uint16_t retval;
	get_random_bytes(&retval, 2);
	return retval;
}

//step 4: Driver callback functions
 static int my_openx(struct inode *i,struct file *f)
 { 
     printk(KERN_INFO "x device file : open()\n");
     return 0;
 
 }
 
 static int my_closex(struct inode *i,struct file *f)
 { 
        printk(KERN_INFO "x device file: close()\n");
        return 0;
 
 }
 static int my_openy(struct inode *i,struct file *f)
 { 
     printk(KERN_INFO "y device file : open()\n");
     return 0;
 
 }
 
 static int my_closey(struct inode *i,struct file *f)
 { 
        printk(KERN_INFO "y device file: close()\n");
        return 0;
 
 }
 static int my_openz(struct inode *i,struct file *f)
 { 
     printk(KERN_INFO "z device file : open()\n");
     return 0;
 
 }
 
 static int my_closez(struct inode *i,struct file *f)
 { 
        printk(KERN_INFO "z device file: close()\n");
        return 0;
 
 }
 static ssize_t my_readx(struct file *f,char __user *buf,size_t len,loff_t *off)
{
  printk(KERN_INFO "myadxl:data is read from xaxisread()\n");
  val=((getrand())&(0x03ff));
  printk(KERN_INFO "%d\n",val);
  copy_to_user(buf,&val,sizeof(val));
return 0;
}
static ssize_t my_ready(struct file *f,char __user *buf,size_t len,loff_t *off)
{
   printk(KERN_INFO "myadxl:data is read from yaxisread()\n");
   val=(getrand())&(0x03ff);
   printk(KERN_INFO "%d\n",val);
   copy_to_user(buf,&val,sizeof(val));
return 0;
}
static ssize_t my_readz(struct file *f,char __user *buf,size_t len,loff_t *off)
{
  printk(KERN_INFO "myadxl:data is read from zaxis read()\n");
  val=(getrand())&(0x03ff);
  printk(KERN_INFO "%d\n",val);
  copy_to_user(buf,&val,sizeof(val));
return 0;
}
ssize_t my_write(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
 printk(KERN_INFO "myadxl:write()\n");
 return 0;
}

static struct file_operations fops1 =
{
 .owner=THIS_MODULE,
 .open=my_openx,
 .release=my_closex,
 .read=my_readx,
 .write=my_write
};
static struct file_operations fops2 =
{
 .owner=THIS_MODULE,
 .open=my_openy,
 .release=my_closey,
 .read=my_ready,
 .write=my_write
};
static struct file_operations fops3 =
{
 .owner=THIS_MODULE,
 .open=my_openz,
 .release=my_closez,
 .read=my_readz,
 .write=my_write
};
                         
 // static char *mystr ="hi friends";
  //static int a =1234;
 // module_param(mystr,charp,0);
 // module_param(a,int,0);
 // MODULE_PARM_DESC(a,"GANTA");
   
                         
static int __init mychar_init(void)

{
  printk(KERN_INFO "my adxl driver registered\n\n");
  
 //step1: reserve <major,minor>
 
 if(alloc_chrdev_region(&first1,0,3,"adxlxaxis")<0)
 {
  return -1;
  
 }
 
       first=MKDEV(MAJOR(first1), MINOR((first1)+0));
       second=MKDEV(MAJOR(first1), MINOR((first1)+1));
       third=MKDEV(MAJOR(first1), MINOR((first1)+2));
 // step 2 creation of device file
 if((cls=class_create(THIS_MODULE,"chardrv1"))==NULL)
 { class_destroy(cls);
   unregister_chrdev_region(first,1);
   return -1;
 }
 
 
 
 
 if(device_create(cls,NULL,first,NULL,"adxl_x")==NULL)
 {
printk(KERN_INFO "<MAJOR, MINOR> <%d %d>\n",MAJOR(first) ,MINOR(first));
return 0;
}

 if(device_create(cls,NULL,second,NULL,"adxl_y")==NULL)
 {
printk(KERN_INFO "<MAJOR, MINOR> <%d %d>\n",MAJOR(second) ,MINOR(second));
return 0;
}

 
 if(device_create(cls,NULL,third,NULL,"adxl_z")==NULL)
 {
printk(KERN_INFO "<MAJOR, MINOR> <%d %d>\n",MAJOR(third) ,MINOR(third));
return 0;
}
 // step 3 link fops and cdev to the device node
 cdev_init(&c_dev1,&fops1);
 if(cdev_add(&c_dev1,first,1)==1)
 {
   device_destroy(cls,first);
   class_destroy(cls);
   unregister_chrdev_region(first,1);
   
   return -1;
   }
   
   cdev_init(&c_dev2,&fops2);
 if(cdev_add(&c_dev2,second,1)==1)
 {
   device_destroy(cls,second);
   class_destroy(cls);
   unregister_chrdev_region(second,1);
   
   return -1;
   }
   
   cdev_init(&c_dev3,&fops3);
 if(cdev_add(&c_dev3,third,1)==1)
 {
   device_destroy(cls,third);
   class_destroy(cls);
   unregister_chrdev_region(third,1);
   
   return -1;
   }
   return 0;
   }


static void __exit mychar_exit(void)
{  
   cdev_del(&c_dev1);
   device_destroy(cls,first);
   class_destroy(cls);
   unregister_chrdev_region(first,1);
   cdev_del(&c_dev2);
   device_destroy(cls,second);
   class_destroy(cls);
   unregister_chrdev_region(second,1);
   cdev_del(&c_dev3);
   device_destroy(cls,third);
   unregister_chrdev_region(third,1);
   printk(KERN_INFO "Bye :accelerometer adxl  unregistered\n\n");
   
 
 }
 module_init(mychar_init);
 module_exit(mychar_exit);
 MODULE_LICENSE("GPL");
 MODULE_AUTHOR("Krishna Chaithanya<h20180120@goa.bits-pilani.ac.in>");
 MODULE_DESCRIPTION("adxl driver");


