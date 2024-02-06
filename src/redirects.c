#include "_sh.h"

/**
 * single_right - Function for handling right redirects
 * @filename: file to search for
 * @content: Output to write to file
 * THESE ARE PLACEHOLDERS!!!! REPLACE
*/

void single_right(filename, content)
{
/* SUDO CODE FOR FUNCTION*/

	if (!filename)
		return;
	if (open(filename, O_RDWR) == -1)
	{
		open(filename, O_CREAT, O_RDWR);
		write(filename, content, 1024);
		close(filename);
	}
	else
	{
		/*Somehow clear the file*/
		write(filename, content, 1024);
		close(filename);
	}
}

/**
 * double_right - Function for handling right redirects
 * @filename: file to search for
 * @content: Output to write to file
 * THESE ARE PLACEHOLDERS!!!! REPLACE
*/

void double_right(filename, content)
{
/* SUDO CODE FOR FUNCTION*/

	if (!filename)
		return;
	if (open(filename, O_APPEND) == -1)
	{
		open(filename, O_CREAT, O_RDWR);
		write(filename, content, 1024);
		close(filename);
	}
	else
	{
		write(filename, content, 1024);
		close(filename);
	}
}