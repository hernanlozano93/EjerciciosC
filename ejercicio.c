#include <iostream>
#include <string>
#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <time.h>
#include <stdint.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>

char* size(char* storage, long double size, int8_t precision)
{
    static const char* units[10]={"bytes","Kb","Mb","Gb","Tb","Pb","Eb","Zb","Yb","Bb"};
    char format[10];

    int i= 0;

    while (size>1024)
        {
            size = size /1024;
            i++;
        }

    snprintf(format, 10, "%%.%dLf%%s", precision);
    snprintf(storage, 32, format, size, units[i]);

    return storage;
}

std::string extractFile(const char *filename, size_t bufferSize=512)
{
    int fd = open(filename, O_RDONLY);
    std::string output;

    if (fd==-1)
        return "";      /* error opening */

    char *buffer = (char*)malloc(bufferSize);
    if (buffer==NULL)
        return "";      /* Can't allocate memory */

    int datalength;
    while ((datalength = read(fd, buffer, bufferSize)) > 0)
        output.append(buffer, datalength);

    close(fd);
    return output;
}

int main(int argc, char *argv[])
{
	struct utsname unameInfo;
	struct sysinfo si;
	string cpuinfo = extractFile("/proc/cpuinfo");
    char* tokenized;
    char* ptrptr;
	tokenized=strtok_r((char*)cpuinfo.c_str(), "\n", &ptrptr);
   
    if (uname(&unameInfo)==-1)
    {
            fprintf (stdout, "ERROR\n");
            exit(-1);          
    }
		
	int arg;
	for(arg=1; arg<argc; arg++)
	{
		if(argv[arg][0] == '-')
		{	
			if((argv[arg]+1)[0] == 's')
			{	
				printf("\n MEMORIA: \n");
				printf ("Unidad de memoria: %d (%s)\n", si.mem_unit, size(temp, si.mem_unit, 3 ));
				printf ("RAM total: %ld (%s)\n", si.totalram, size(temp, si.totalram*si.mem_unit, 3));
				printf ("RAM free: %ld (%s)\n", si.freeram, size(temp, si.freeram*si.mem_unit, 3));
				printf ("RAM compartida: %ld (%s)\n", si.sharedram, size(temp, si.sharedram*si.mem_unit, 3));
				printf ("RAM buffers: %ld (%s)\n", si.bufferram, size(temp, si.bufferram*si.mem_unit, 3));
				printf ("RAM usada: %ld (%s)\n", si.totalram - si.freeram - si.bufferram,
                    size(temp, (si.totalram - si.freeram - si.bufferram)*si.mem_unit, 3));
				printf("\n CPU: \n");
				    while (tokenized)
					{
						char name[64];
						char value[1024];
						memset(value, '\0', 1024);
						sscanf (tokenized, "%[^\t:] : %[^\t\n]", name, value);
						//cout << "["<<name<<"]" << " = " << value << "\n";
						printf("[", name, "] = ", value, " \n");
						tokenized = strtok_r(NULL, "\n", &ptrptr);
					};
				printf("\n SYSTEMA: \n");
				printf ("Sistemqa: %s\n", unameInfo.sysname);
				printf ("Equipo: %s\n", unameInfo.nodename);
				printf ("Kernel: %s\n", unameInfo.release);
				printf ("Version: %s\n", unameInfo.version);
				printf ("Arquitectura: %s\n \n", unameInfo.machine);
				
			}else if((argv[arg]+1)[0] == 'f')
			{
				printf("\n Las opciones pertinentes para argumento -f: \n");
			}
		}else{
				printf("Argumento -s o -f requerido");
		}
	}
	exit(0);
}