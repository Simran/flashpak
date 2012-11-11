//flashpak by Simran...
//Some crappy code.. but it works...

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
    
//What to add:
//*Work on devices that use a different command to reboot into recovery mode.


char pakDir[1000];
char pakDir2[1000];
char* SDCARD = NULL;
char* command = "echo '--update_package=/sdcard/%s' >> /cache/recovery/command\n";



main(int argc, char* argv[])
{	
	SDCARD = getenv("EXTERNAL_STORAGE");	
	//Check if package is a zip file, or atleast that it ends with ".zip"
	if (endsWith(argv[1], ".zip"))
	{
		//Create the complete location of the package.
		strcpy(pakDir, SDCARD);
		strcat(pakDir, "/");
		strcat(pakDir, argv[1]);

		if (fileExist(pakDir))
		{
		//Print the package file
		printf("Package file: %s\n", pakDir);

		//Recovery magic
		system("echo 'boot-recovery ' > /cache/recovery/command\n");
		setPackage(argv[1]);

		//Finished! Time to reboot into recovery so it can flash the zip! :D
		printf("Finished setting the commands\n Rebooting into recovery!\n");
		system("reboot recovery");
		}
		else
		{
			strcpy(pakDir2, SDCARD);
			strcat(pakDir2, "/ext_sd/");
			strcat(pakDir2, argv[1]);
			
			if(fileExist(pakDir2)) 
			{ 
			//Print the package file
			printf("Package file: %s\n", pakDir2);

			//Recovery magic
			system("echo 'boot-recovery ' > /cache/recovery/command\n");
			setPackage(argv[1]);

			//Finished! Time to reboot into recovery so it can flash the zip! :D
			printf("Finished setting the commands\n Rebooting into recovery!\n");
			system("reboot recovery");
			} 
			else 
			{ 
			//Yeah, man! Just gtfo!
			printf("Package doesn't exist!\n");
			} 
		}
	}
	else
	{
	//Yeah, man! Just gtfo!
	printf("Not a zip file!\n");
	}
}

int endsWith(const char* str, const char* suffix)
{
    	if (!str || !suffix)
        	return 0;
    	size_t lenstr = strlen(str);
    	size_t lensuffix = strlen(suffix);
    	if (lensuffix >  lenstr)
        	return 0;
    	return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

int fileExist (char* filename)
{
	struct stat buffer;   
	return (stat (filename, &buffer) == 0);
}

void setPackage(const char* package)
{
  	char comcommand[1000];
  	sprintf(comcommand, command, package);
	system(comcommand);
}


