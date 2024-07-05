#include <CVFS.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <cJSON.h>
#include "ht.h"

typedef const char* allocated_ccp;

#define duplicate_ccp(retname, src) allocated_ccp retname = strdup(src);

void allocated_ccp_ht_dtor(allocated_ccp key) {
	free(key);
}

bool allocated_ccp_ht_equals(allocated_ccp key1, allocated_ccp key2) {
	return strcmp(key1, key2) == 0;	
}

__define_ht_main(allocated_ccp, allocated_ccp);

#define CVFS_MAX_PATH 260
#define TEMP_VFS_SIZE 0x0 
/*
The File's format
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

struct _VFS 
{
	// The table is here temporary, it will be re-constructed into a recursive hash table for increased perfomance
	cJSON* table;
	FILE* main_vfs_file;
};

struct _VFS_FILE_HANDLE {
	cJSON* metaData;
};

VFS* CreateVFS(const char* path) 
{
	// Open file in binary write mode
	FILE* handle = fopen(path, "wb");
	// Check if the file was successfully opened
	if (handle == NULL || path == NULL) {
    // If not, return NULL to indicate error
    return NULL;
	}

	VFS* vfs = (VFS*)malloc(sizeof(VFS));
	if (vfs == NULL) {

    return NULL;
	}
	vfs->main_vfs_file = path;
	// Return the pointer to the new VFS structure
	return vfs;
}

VFS* LoadVFS(const char* path) 
{
	// Open file in read mode
	FILE* file = fopen(path, "r");
	if (file == NULL){
		return NULL;
	}

	//gets the file lenght in characters
	fseek(file, 0, SEEK_END);
	long file_size = ftell(file);
	//reset our file pointer
	fseek(file, 0, SEEK_SET);

	//malloc memory to hold the json data as a string
	char *json_buffer = (char *)malloc(file_size + 1);
	if(json_buffer == NULL) {
		return NULL; 
	}
	//write the json file data into the string
	fread(json_buffer, 1, file_size, file);

	//close file
	fclose(file);

	//null-terminating our string for safety
	json_buffer[file_size] = '\0'; 

	//malloc memory for the VFS handle
	VFS* vfs = malloc(sizeof(VFS));
	if (vfs == NULL){
		free(json_buffer);
		return NULL;//a bad alloc
	}

	//get the json root object
	cJSON *root = cJSON_Parse(json_buffer);
	vfs->table = root; 
	// free the buffer after parsing
	free(json_buffer);
	
	return vfs;
}

void DestroyVFS(VFS* vfs) {
	if(!vfs) return;
	if(vfs->table) cJSON_Delete(vfs->table);
	free(vfs);
}

bool FileExists(VFS* vfs, const char* path) {

	// // bro, Check for NULL pointers
    // if (vfs == NULL || path == NULL) {
    //     return false;
    // }
	// cJSON* FAT = cJSON_GetObjectItem(vfs->table, "FAT");
	// if (FAT == NULL) {
    //     return false;
    // }
    // cJSON* fileEntry;
 	// cJSON_ArrayForEach(fileEntry, FAT) {
    //     // Get the "path" field of the current file entry
    //     cJSON* filePath = cJSON_GetObjectItem(fileEntry, "path");
    //     if (filePath != NULL && cJSON_IsString(filePath)) {
    //         // Compare the current file's path with the given path
    //         if (strcmp(filePath->valuestring, path) == 0) {
    //             return true; // File exists
    //         }
    //     }
    // }
	// //ret false if no macth
    return false;
}

VFS_FILE_HANDLE* OpenFile(VFS* vfs, const char* path, VFS_FILE_MODE mode) {
    //! NOTICE: THE WHOLE FUNCTION HAS TO BE REWRITTEN DUE TO THE NEW STRUCTURE OF THE VFS
		//! HOW THIS WILL WORK: THE STR WILL BE SEARCHED IN THE HASH TABLE USING allocated_ccp_ht_exists(key <- this one doesn't have to be allocated)
		// Check for NULL pointers
    if (vfs == NULL || path == NULL) {
        return NULL;
    }

    cJSON* root = vfs->table;
    FILE* file = NULL;

    // Translate enum file modes
    switch (mode) {
        case VFS_FILE_MODE_READ:
            file = fopen(path, "r");
            break;
        case VFS_FILE_MODE_WRITE:
            file = fopen(path, "r+");
            break;
        case VFS_FILE_MODE_APPEND:
            file = fopen(path, "a+");
            break;
        case VFS_FILE_MODE_CREATE:
            file = fopen(path, "w");
            break;
        default:
            return NULL;
    }

    if (file == NULL) {
        return NULL;
    }

    // Get the array called 'FAT'
    cJSON* FAT = cJSON_GetObjectItem(root, "FAT");
    if (FAT == NULL) {
        fclose(file);
        return NULL;
    }

    // Create an object to hold the metadata
    cJSON* metaData = cJSON_CreateObject();
    if (metaData == NULL) {
        fclose(file);
        return NULL;
    }

    // Add the file path to the object
    char absolute_path[CVFS_MAX_PATH];
    #if defined(CVFS_WINDOWS)
        if (_fullpath(absolute_path, path, CVFS_MAX_PATH) == NULL) {
            fclose(file);
            return NULL;
        }
    #else // Linux and Apple
        if (realpath(path, absolute_path) == NULL) {
            fclose(file);
            return NULL;
        }
    #endif
    if (!cJSON_AddStringToObject(metaData, "file-path", absolute_path)) {
        cJSON_Delete(metaData);
        fclose(file);
        return NULL;
    }

    // Add the file size to the object
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    if (!cJSON_AddNumberToObject(metaData, "file-size", size)) {
        cJSON_Delete(metaData);
        fclose(file);
        return NULL;
    }

    // Add the metadata to the array called 'FAT'
    if (!cJSON_AddItemToArray(FAT, metaData)) {
        cJSON_Delete(metaData);
        fclose(file);
        return NULL;
    }

    // Print the JSON data onto a string buffer
    char* jsonData = cJSON_Print(root);
    if (jsonData == NULL) {
        fclose(file);
        return NULL;
    }

    // Get the length of the string
    size_t jsonData_size = strlen(jsonData);

    // Update the 'vfs-size' with the actual JSON size
    cJSON* vfs_size = cJSON_GetObjectItem(root, "vfs-size");
    if (!vfs_size) {
        fclose(file);
        free(jsonData);
        return NULL;
    }
    cJSON_SetNumberValue(vfs_size, jsonData_size);
	cJSON* fatCountItem = cJSON_GetObjectItem(root, "FAT-count");
	// Update the 'FAT-count' variable
 	if (fatCountItem == NULL) {
		fclose(file);
        free(jsonData);
        return NULL;
    }
	int fatCountValue = fatCountItem->valueint;	
	fatCountValue++;
	cJSON_SetNumberValue(fatCountItem, fatCountValue);	

    // Print the JSON data again after updating the size
    char* updatedJsonData = cJSON_Print(root);
    if (updatedJsonData == NULL) {
        fclose(file);
        free(jsonData);
        return NULL;
    }

    // Get the updated JSON size
    jsonData_size = strlen(updatedJsonData);

		
    // Write the actual JSON data to the VFS file
    /*
		FILE* vfs_file = fopen(vfs->json_file, "r+");
    if (vfs_file == NULL) {
        fclose(file);
        free(jsonData);
        free(updatedJsonData);
        return NULL;
    }

    fwrite(updatedJsonData, jsonData_size, 1, vfs_file);

    // Free resources
    //fclose(file); -> use CloseFile to close the file
    fclose(vfs_file);
    */
		free(jsonData);
    free(updatedJsonData);

    VFS_FILE_HANDLE* handle = (VFS_FILE_HANDLE*)malloc(sizeof(VFS_FILE_HANDLE));
    if (handle == NULL) {
        return NULL;
    }
    handle->metaData = metaData;
    return handle;
}


bool ExtractFile(VFS* vfs, const char* src, const char* dst) {
return 0;
}

void DeleteFile(VFS* vfs, const char* path) {

}

int CloseFile(VFS_FILE_HANDLE* handle) {
	//! NOTICE: SAME HERE
	//Check if the pointer is null
	if(handle == NULL){
		return -1;
	}
	//get the file-path variable, which happens to be in index zero
	cJSON* index0 = cJSON_GetObjectItem(handle->metaData, "file-path");
	//reinterpret the data as a string
	const char * file_path = cJSON_GetStringValue(index0);
	if(!file_path){
		return -1;
	}
	//using the string close the file
	//return fclose(file_path);
	return 0;
}

size_t ReadFile(VFS_FILE_HANDLE* handle, void* buffer, size_t size) {
return 0;
}

size_t WriteFile(VFS_FILE_HANDLE* handle, const void* buffer, size_t size) {
return 0;
}


size_t GetFileSize(VFS_FILE_HANDLE* handle) {
return 0;
}

size_t GetFileName(VFS_FILE_HANDLE* handle, char* buffer, size_t size) {
return 0;
}

bool   SetFileName(VFS_FILE_HANDLE* handle, const char* name) {
	return 0;
}

#if _DEBUG

void PrintVFSTable(VFS* vfs) 
{	
	//get json data as a string
	const char * json_buffer = cJSON_Print(vfs->table);
	if (json_buffer){
		//print string
		printf(json_buffer);
	}
	else{
		printf("FAILD: to print the VFS Table");
	}

}

#endif

__define_ht_main_impl(allocated_ccp, allocated_ccp);