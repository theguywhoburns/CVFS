#ifndef CVFS_H
#define CVFS_H

#include <ht.h>
#define VFS_PATH_MAX 128
// 128 characters
// first / is unnecessary but will still be counted to the path length
// /helloworldthisisammaxpathfilesoillfillitupuntillitgetstothetiseof256characterssoicanfillitupwithjustAsiWantToSeeIfItWorksW.txt

// we'll preallocate the first filesystem size to be 1 megabyte
// if it becomes full it'll create other part of the filesystem and point to it
// they will be merged into the first one if the user wants to 

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
typedef struct VFS VFS;
//Handle to a file in the Virtual file system
typedef struct VFS_FILE VFS_FILE;

// HashTable typedefs
typedef char*  vfs_cstring; // Full path to file
typedef size_t vfs_size_t;  // offset to the file in the VFS, the size of the header is always the same so we don't need to store it in the HT
define_ht_all(vfs_cstring, vfs_size_t); 

/**
 * Creates a Virtual file system
 * ---Example file
 *	{
 * 		"version":    "0.0.1",
 *		"vfs-size":    53,
 *		"FAT":    []
 *	}
 */
VFS* VFS_Create(char* const path);
//loads an existing Virtual file system file
VFS* LoadVFS(const char* path);
//Free the memory of a Virtual file system
void DestroyVFS(VFS* vfs);

bool FileExists(VFS* vfs, const char* path);

typedef enum VFS_FILE_MODE {
	VFS_FILE_MODE_READ = 0,
	VFS_FILE_MODE_WRITE = 1,
	VFS_FILE_MODE_APPEND = 2,
	VFS_FILE_MODE_CREATE = 4
} VFS_FILE_MODE;
//Opens a file save it's meta data in the VFS file
//@ path -> file location
// mode -> open mode (check VFS_FILE_MODE enum for more details)
//@ returns Handle to file : VFS_FILE *
VFS_FILE* VFS_OpenFile(VFS* vfs, const char* path, VFS_FILE_MODE mode);
bool VFS_ExtractFile(VFS* vfs, const char* src, const char* dst);
void VFS_DeleteFile(VFS* vfs, const char* path);
int VFS_CloseFile(VFS_FILE* handle);

size_t VFS_ReadFile(VFS_FILE* handle, void* buffer, size_t size);
size_t VFS_WriteFile(VFS_FILE* handle, const void* buffer, size_t size);

size_t VFS_GetFileSize(VFS_FILE* handle);
size_t GetFileName(VFS_FILE* handle, char* buffer, size_t size);
bool   SetFileName(VFS_FILE* handle, const char* name);



#if _DEBUG
void PrintVFSTable(VFS* vfs);
#endif

#endif//__CVFS_H__