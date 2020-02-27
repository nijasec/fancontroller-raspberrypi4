#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define HIGHTEMP 62
#define LOWTEMP 47
#define OUT "out"
#define IN "in"
int opengpio(char *pin)
{
 int fd = open("/sys/class/gpio/export", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/export");
        return -1;
    }

    if (write(fd, pin,2) != 2) {
        perror("Error writing to /sys/class/gpio/export");
        return -1;
    }

    close(fd);
return 0;
}
int closegpio(char *pin)
{

int fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/unexport");
      return -1;
    }

    if (write(fd, pin, 2) != 2) {
        perror("Error writing to /sys/class/gpio/unexport");
        return -1;
    }

    close(fd);
return 0;

}
int setgpiodirection(char *pin,char *dir,int len)
{
char path[100];
sprintf(path,"/sys/class/gpio/gpio%s/direction",pin);
 int fd = open(path, O_WRONLY);
    if (fd == -1) {
        perror("Unable to open...direction");
        return -1;
    }

    if (write(fd, dir, len) != 3) {
        perror("Error writing to /.../direction");
       return -1;
    }

    close(fd);
return 0;
}
int gpiowrite(char *pin,char *value)
{
char path[100];
sprintf(path,"/sys/class/gpio/gpio%s/value",pin);

 int fd  = open(path, O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/gpio../value");
       return -1;
    }
write(fd, value, 1);
close(fd);
return 0;

}
int gpioread(char *pin)
{
char path[100];
char value[2];
sprintf(path,"/sys/class/gpio/gpio%s/value",pin);
printf("%s\n",path);
 int fd  = open(path, O_RDONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/gpio../value");
       return -1;
    }
read(fd, value, 1);
close(fd);
return atoi(value);
}

int gettemp()
{
//char p[1000];
//sprintf(p,"paste");
const char *p="cat /sys/class/thermal/thermal_zone*/temp";

FILE *fp=popen(p,"r");
if(fp==NULL)
exit(0);
char msg[100];
fgets(msg,sizeof(msg),fp);


fclose(fp);

return atoi(msg); 
}
int main()
{

 char *fan="17";
printf("Automatic fan control\n");
printf("***********************\n\n");
printf("Current CPU temperature is:%d degree C\n",gettemp()/1000);
opengpio(fan);
setgpiodirection(fan,"out",3);


int temp;
while(1){

temp=gettemp()/1000;
if(temp>HIGHTEMP && gpioread(fan)!=1)
{
gpiowrite(fan,"1");
printf("temp is %d turning on the fan\n",temp);
}
else if(temp < LOWTEMP && gpioread(fan)!=0)
{
gpiowrite(fan,"0");
printf("temp is %d turning off the fan\n",temp);
}
sleep(5);

}
printf("%d",temp);
return 0;

}
