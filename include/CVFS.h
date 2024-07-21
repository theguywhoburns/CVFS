#ifndef CVFS_H
#define CVFS_H

#include <stdbool.h>
#include <stdint.h>

/*
The File's format
+---------------------------------+
| Metadata (FAT, Inodes, etc.)    |
+---------------------------------+
|                                 |
| File Data                       | 
| ...                             |
| ...                             |
| ...                             |
| ...                             |
+---------------------------------+
*/


//Handle to Virtual file system
typedef struct _VFS VFS;
//Handle to a file in the Virtual file system
typedef struct _VFS_FILE_HANDLE VFS_FILE_HANDLE;


/*
Creates a Virtual file system
\n
---Example file
{
    "version":    "0.0.1",
    "vfs-size":    53,
    "FAT":    []
}
*/
VFS* CreateVFS(const char* path);
//loads an existing Virtual file system file
VFS* LoadVFS(const char* path);
//Free the memory of a Virtual file system
void DestroyVFS(VFS* vfs);

bool FileExists(VFS* vfs, const char* path);

typedef enum _VFS_FILE_MODE {
	VFS_FILE_MODE_READ = 0,
	VFS_FILE_MODE_WRITE = 1,
	VFS_FILE_MODE_APPEND = 2,
	VFS_FILE_MODE_CREATE = 4
} VFS_FILE_MODE;
//Opens a file save it's meta data in the VFS file
//@ path -> file location
// mode -> open mode (check _VFS_FILE_MODE enum for more details)
//@ returns Handle to file : VFS_FILE_HANDLE *
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