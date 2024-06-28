#ifndef __CVFS_H__
#define __CVFS_H__

#define VFS_VERSION "0.0.1"

// TODO: Get rid of this
//!
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
//!

typedef struct _VFS VFS;
typedef struct _VFS_FILE_HANDLE VFS_FILE_HANDLE;

VFS* CreateVFS(const char* path);
VFS* LoadVFS(const char* path);
void DestroyVFS(VFS* vfs);

bool FileExists(VFS* vfs, const char* path);

typedef enum _VFS_FILE_MODE {
	VFS_FILE_MODE_READ = 0,
	VFS_FILE_MODE_WRITE = 1,
	VFS_FILE_MODE_APPEND = 2,
	VFS_FILE_MODE_CREATE = 4
} VFS_FILE_MODE;

VFS_FILE_HANDLE* OpenFile(VFS* vfs, const char* path, VFS_FILE_MODE mode);
bool ExtractFile(VFS* vfs, const char* src, const char* dst);
void DeleteFile(VFS* vfs, const char* path);
int CloseFile(VFS_FILE_HANDLE* handle);

size_t ReadFile(VFS_FILE_HANDLE* handle, void* buffer, size_t size);
size_t WriteFile(VFS_FILE_HANDLE* handle, const void* buffer, size_t size);

size_t GetFileSize(VFS_FILE_HANDLE* handle);
size_t GetFileName(VFS_FILE_HANDLE* handle, char* buffer, size_t size);
bool   SetFileName(VFS_FILE_HANDLE* handle, const char* name);



#if _DEBUG
void PrintVFSTable(VFS* vfs);
#endif

#endif//__CVFS_H__