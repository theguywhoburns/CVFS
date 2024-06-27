#ifndef __CVFS_H__
#define __CVFS_H__

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

typedef struct _VFS VFS;
typedef struct _VFS_FILE_HANDLE VFS_FILE_HANDLE;

VFS  LoadVFS(const char* path);
void DestroyVFS(VFS* vfs);

bool FileExists(VFS* vfs, const char* path);

VFS_FILE_HANDLE* OpenFile(VFS* vfs, const char* path, const char* mode);
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