#include <stdio.h>
#include <stdarg.h>
#include <syslog.h>
#include <fcntl.h>
#define LOG_CTR
//#define LOG_FILE_CTR
#define LOG_FILE_MAX_SIZE (1024)
#define LOG_FILE_PATH "./v2x.log"

#ifdef LOG_FILE_CTR
#define LOG_I(fmt,args...) \
     do{ \
         printf("info|%s:%d:[%s]:"fmt, __FILE__, __LINE__, __func__, ## args); \
         LOG_WRITE_FILE(fmt,args); \
     }while(0)

#define LOG_E(fmt,args...) \
     do{ \
         printf("error|%s:%d:[%s]:"fmt, __FILE__, __LINE__, __func__, ## args); \ 
         LOG_WRITE_FILE(fmt,args); \
     }while(0)
#elif
#define LOG_I(fmt,args...) \
     do{ \
         printf("info|%s:%d:[%s]:"fmt, __FILE__, __LINE__, __func__, ## args); \
     }while(0)

#define LOG_E(fmt,args...) \
     do{ \
         printf("error|%s:%d:[%s]:"fmt, __FILE__, __LINE__, __func__, ## args); \ 
     }while(0)
#endif
#define LOG_D(fmt,args...) \
     do{ \
         printf("debug|%s:%d:[%s]:"fmt, __FILE__, __LINE__, __func__, ## args) \       
     }while(0)


int fd = -1;

void  LOG_INIT()
{
	if((access(LOG_FILE_PATH,F_OK))!=-1)   
    {   
		remove(fd);
    }   

#ifdef LOG_FILE_CTR
	fd =  open(LOG_FILE_PATH, O_RDWR|O_APPEND|O_CREAT|O_EXCL, S_IRWXU);
	if(-1 == fd)
	{
		sprintf(stderr, "v2x create v2x.log is failed!\n");
		return -1;
	}
#endif

}

void LOG_WRITE_FILE(const char *format, ...)
{
   va_list ap;
   struct stat buf;
   char cmdstr[32] = "echo > ";
   char log_buf[512] = {0};

   strcat(cmdstr, LOG_FILE_MAX_SIZE);
   va_start(ap, format);
   if(-1 != fd)
   {	
		fstat(fd, &buf);
		if(buf.st_size >= LOG_FILE_MAX_SIZE)
			return;
		//	system(cmdstr);
		vsnprintf (log_buf,512,format, ap);
		write(fd, log_buf, strlen(log_buf));
   }
	va_end(ap);
	return;
}

void LOG_FILE_CLOSE()
{	
	if(-1 == fd)
		return;

	close(fd);
}

int main()
{
	int a= 9;
	LOG_INIT();
	while(1)
	{
	LOG_I("sdfasdfasdfasfdsadf%d\n", a);
}	
	return 0;
}
