/*
Hazırlayacak olduğunuz program çalıştırıldıktan sonra program
sonlandırılıncaya kadar mouse ekran koordinatlarını okuyarak kullanıcı tarafından belirlenen
dosyaya bilgilerin aktarımını yapmalıdır. Program koordinat bilgileri ile birlikte dosyaya
timestamp bilgiside yazmalıdır.

Örnek çalıştırma : C:\user\unalc> ./mouse_event event_file

Örnek çıktı dosyası :
    timestamp        x  y
04.08.2021 15:42:00 134 89
04.08.2021 15:42:03 45 178

g++ mouse_event.c -o mouse_event -Wall -lX11
sudo mouse_event > evet_file
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <err.h>
#include <time.h>

#include <X11/Xlib.h>

int main(int argc, char** argv)
{

    int left, middle, right;
    signed char x, y;
    FILE *fp;

    Display *dpy;
    Window root, child;
    int rootX, rootY, winX, winY;
    unsigned int mask;
    int width, height, snum;

    int fd, bytes;
    unsigned char data[3];

    time_t rawtime;
    struct tm * timeinfo;

    const char *pDevice = "/dev/input/mice";

    if(!(dpy = XOpenDisplay(NULL)))
                errx(1, "cannot open display '%s'", XDisplayName(0));

    XQueryPointer(dpy,DefaultRootWindow(dpy),&root,&child,
                &rootX,&rootY,&winX,&winY,&mask); 

    snum = DefaultScreen(dpy);
    width = DisplayWidth(dpy, snum);
    height = DisplayHeight(dpy, snum);

    // Open Mouse
    fd = open(pDevice, O_RDWR);
    if(fd == -1)
    {
        printf("ERROR Opening %s\n", pDevice);
        return -1;
    }
    
    // Open File
    fp = fopen("out.txt", "w+");

    while(1)
    {
        // Set Current Time
        time ( &rawtime );
        timeinfo = localtime ( &rawtime );

        // Read Mouse     
        bytes = read(fd, data, sizeof(data));

        if(bytes > 0)
        {
            left = data[0] & 0x1;
            right = data[0] & 0x2;
            middle = data[0] & 0x4;

            x = data[1];
            y = data[2];
            
            rootX += x;
            if (rootX < 0)
                rootX = 0;
            
            if (rootX > width)
                rootX = width;

            rootY += y;            
            if (rootY < 0)
                rootY = 0;
            
            if (rootY > height)
                rootY = height;

            printf ( "%02d.%02d.%02d %02d:%02d:%02d %d %d\n", 
                timeinfo->tm_mday,
                timeinfo->tm_mon,
                timeinfo->tm_year,
                timeinfo->tm_hour,
                timeinfo->tm_min,
                timeinfo->tm_sec,
                rootX, 
                rootY );

            fprintf(fp, "%02d.%02d.%02d %02d:%02d:%02d %d %d\n", 
                timeinfo->tm_mday,
                timeinfo->tm_mon,
                timeinfo->tm_year,
                timeinfo->tm_hour,
                timeinfo->tm_min,
                timeinfo->tm_sec,
                rootX, 
                rootY );

            //printf("x=%d, y=%d, left=%d, middle=%d, right=%d\n", rootX, rootY, left, middle, right);
        
        }   
    }

    fclose(fp);
    return 0; 
}