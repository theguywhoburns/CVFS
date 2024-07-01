#include <CVFS.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <cJSON.h>

/*
The File's formate
+---------------------------------+
| Metadata (FAT, Inodes, etc.)    |
+---------------------------------+
|                                 |
| File Data                       | 
| ...                             |
| ...                             |
| ...              		          |
| ...                             |
+---------------------------------+
*/

struct _VFS {
	cJSON* table;
	size_t size;
	char* data;
};

struct _VFS_FILE_HANDLE {
	void* temp;
};


VFS* CreateVFS(const char* path) {
 FILE* handle = fopen(path, "wb");
    if (handle == NULL) {
        return NULL;
    }
    cJSON* root = cJSON_CreateObject();
    if (root == NULL) {
        fclose(handle);
        return NULL;
    }
    cJSON* version = cJSON_AddStringToObject(root, "version", VFS_VERSION);
    cJSON* FAT = cJSON_AddArrayToObject(root, "FAT");
    if (version == NULL || FAT == NULL) {
        cJSON_Delete(root);
        fclose(handle);
        return NULL;
    }
    char* data = cJSON_Print(root);
    char data_size[11];
    snprintf(data_size, 11, "%zu", strlen(data));
    fwrite(data_size, strlen(data_size), 1, handle);
    fwrite(data, strlen(data), 1, handle);
    free(data);
    fflush(handle);
    cJSON_Delete(root);
    fclose(handle);

    VFS* vfs = (VFS*)malloc(sizeof(VFS));
    if (vfs == NULL) {
        return NULL;
    }
    vfs->table = cJSON_Parse(data);
    vfs->size = 0;
    vfs->data = NULL;
    return vfs;
}

// Will load the table and return the offset to read from at the end
cJSON* LoadVFSTable(FILE* file, uint64_t* offset);

VFS* LoadVFS(const char* path) {
	FILE* file = fopen(path, "rb");
	if (file == NULL) {
		return NULL;
	}

	fseek(file, 0, SEEK_END);
	size_t size = ftell(file);
	fseek(file, 0, SEEK_SET);
	uint64_t offset = 0;
	cJSON* table = LoadVFSTable(file, &offset);
	if(table == NULL || offset == 0) {
		fclose(file);
		cJSON_Delete(table);
		return NULL;
	}

	char* data = malloc(size - offset);
	if (data == NULL) {	
		fclose(file);
		free  (data);
		return NULL;
	}
	
	fseek(file, offset, SEEK_SET);
	fread(data, size, 1, file);
	fclose(file);
	VFS* vfs = malloc(sizeof(VFS));
	if (vfs == NULL) {
		free(data);
		free(vfs);
		return NULL;
	}
	vfs->size = size;
	vfs->data = data;
	return vfs;
}

cJSON* LoadVFSTable(FILE* file, uint64_t* offset) {
	char buffer[10];
	char c = fgetc(file);
	int i = 0;
	while(c >= '0' && c <= '9') {
		buffer[i] = c;
		i++;
		c = fgetc(file);
	}
	int vfs_table_size = atoi(buffer);

	*offset = ftell(file + vfs_table_size);
	char* data = malloc(vfs_table_size);
	fread(data, vfs_table_size, 1, file);
	cJSON* table = cJSON_Parse(data);
	free(data);
	return table;
}

void DestroyVFS(VFS* vfs) {

}


bool FileExists(VFS* vfs, const char* path) {

}

VFS_FILE_HANDLE* OpenFile(VFS* vfs, const char* path, VFS_FILE_MODE mode) {

}

bool ExtractFile(VFS* vfs, const char* src, const char* dst) {

}

void DeleteFile(VFS* vfs, const char* path) {

}

int CloseFile(VFS_FILE_HANDLE* handle) {

}

size_t ReadFile(VFS_FILE_HANDLE* handle, void* buffer, size_t size) {

}

size_t WriteFile(VFS_FILE_HANDLE* handle, const void* buffer, size_t size) {

}


size_t GetFileSize(VFS_FILE_HANDLE* handle) {

}

size_t GetFileName(VFS_FILE_HANDLE* handle, char* buffer, size_t size) {

}

bool   SetFileName(VFS_FILE_HANDLE* handle, const char* name) {

}

#if _DEBUG

void PrintVFSTable(VFS* vfs) {

}

#endif