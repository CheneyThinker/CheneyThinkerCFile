#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define START(type, mode, handler)\
	FILE* type = NULL;\
	errno_t type##_err = fopen_s(&type, "CheneyThinkerCFile.txt", mode);\
	if (type##_err != 0)\
	{\
		exit(0);\
	}\
	handler\
	fclose(type);\
	type = NULL;
	
#define WRITE_BASE(type, value)\
	type write_##type = value;\
	fwrite(&write_##type, sizeof(type), 1, writer);
	
#define READ_BASE(type, format)\
	type read_##type = 0;\
	fread(&read_##type, sizeof(type), 1, reader);\
	printf(format, read_##type);
	
#define WRITE_POINTER(type, count)\
	type * write_p##type = (type *) malloc(sizeof(type) * count);\
	memset(write_p##type, 0, count);\
	int i##type = 0;\
	for(; i##type < count; i##type++)\
		write_p##type[i##type] = i##type + 1;\
	fwrite(write_p##type, sizeof(type *), count, writer);\
	free(write_p##type);
	
#define READ_POINTER(type, count, format)\
	type * read_p##type = (type *) malloc(sizeof(type) * count);\
	memset(read_p##type, 0, count);\
	fread(read_p##type, sizeof(type *), count, reader);\
	int i##type = 0;\
	for(; i##type < count; i##type++)\
		printf(format, read_p##type[i##type]);\
	free(read_p##type);
	
int main(void)
{
	START(writer, "wb", {
		WRITE_BASE(short, 127)
		WRITE_BASE(int, 10)
		WRITE_BASE(float, 134.5)
		WRITE_BASE(double, 123.5)
		WRITE_BASE(long, 123456789)
		WRITE_POINTER(int, 10)
		WRITE_POINTER(float, 10)
		WRITE_POINTER(double, 10)
		WRITE_POINTER(long, 10)
	})
	START(reader, "rb", {
		READ_BASE(short, "%d\n")
		READ_BASE(int, "%d\n")
		READ_BASE(float, "%0.1f\n")
		READ_BASE(double, "%0.1f\n")
		READ_BASE(long, "%ld\n")
		READ_POINTER(int, 10, "%d\n")
		READ_POINTER(float, 10, "%0.1f\n")
		READ_POINTER(double, 10, "%f\n")
		READ_POINTER(long, 10, "%ld\n")
	})
	return 0;
}

