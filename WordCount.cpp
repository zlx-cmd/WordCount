// WordCount.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<io.h>

void Scan(char* Path, char Type);

int charcount(char* Path) 
{	
	FILE* file = fopen(Path, "r");
	if (file != NULL)
	{
		printf("文件打开失败！");
		exit(0);
	}
	char c;
	int count = 0;
	while ((c = fgetc(file)) != EOF)
		count = ((c != ' ') && (c != '\n') && (c != '\t')) + count;
	fclose(file);
	return count;
}

int wordcount(char* Path) 
{	
	FILE* file = fopen(Path, "r");
	if (file != NULL) 
	{
		printf("文件打开失败！");
		exit(0);
	}
	char w;
	int isword = 0;	
	int count = 0;
	while ((w = fgetc(file)) != EOF) 
	{
		if ((w >= 'a' && w <= 'z') || (w >= 'A' && w <= 'Z')) 
		{				
			count = (isword == 0) + count;
			isword = 1;	
		}
		else
			isword = 0;	
	}
	fclose(file);
	return count;
}

void Run(char Type, char Type2, char* Path) 
{
	switch (Type) 
	{
	case 'c': 
		printf("\ncode count: %d\n", charcount(Path));
		printf("word count: %d\n", wordcount(Path)); 
		break;
	case 'w': 
		printf("word count: %d\n", wordcount(Path)); 
		break;
	case 's': 
		Scan(Path, Type2); 
		break;
	default: 
		printf("type input error"); 
		break;
	}
}

void Scan(char* Path, char Type) 
{
	char* FileName = NULL;
	char* FileType = NULL;
	char Temp[30];	
	long Head;
	struct _finddata_t FileData;
	int i = 0;
	FileName = Path;
	while (*(Path + i) != '\0')
	{	
		if (*(Path + i) == '\\')
			FileName = Path + i + 1;
		if (*(Path + i) == '.')
			FileType = Path + i + 1;
		i++;
	}
	strcpy(Temp, FileType);
	*FileType = '*';
	*(FileType + 1) = '\0';
	Head = _findfirst(Path, &FileData);
	strcpy(FileType, Temp);
	do {
		if (!strcmp(FileData.name, "..") || !strcmp(FileData.name, "."))	
			continue;
		if (_A_SUBDIR == FileData.attrib)	
		{
			strcpy(Temp, FileName);	
			for (i = 0; *(FileData.name + i) != '\0'; i++)
			{
				*(FileName + i) = *(FileData.name + i);
			}
			*(FileName + i) = '\\';
			*(FileName + i + 1) = '\0';
			strcat(Path, Temp);

			Scan(Path, Type);

			strcpy(FileName, Temp);				
		}
		else 
		{
			for (i = 0; *(FileData.name + i) != '.'; i++);
			if (!strcmp(FileData.name + i + 1, FileType)) 
			{	

				strcpy(Temp, FileName);
				strcpy(FileName, FileData.name); 

				printf("%s:  ", FileData.name);
				Run(Type, NULL, Path);
				printf("\n");

				strcpy(FileName, Temp);
			}
		}
	} while (_findnext(Head, &FileData) == 0);
	_findclose(Head);
}

int main(int argc,char* argv[])
{
	char Path[100] = "*.txt";
	char Type = 's';
	char Type2 = 'c';
	Run(Type, Type2, Path);
	getchar();
	return 0;
}




// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
