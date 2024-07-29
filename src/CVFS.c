#include "defines.h"
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define VERSION TOSTRING(VFS_VERSION_MAJOR) "." TOSTRING(VFS_VERSION_MINOR) "." TOSTRING(VFS_VERSION_PATCH)
#include <CVFS.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <cJSON.h>
#include <ht.h>


/*
A Normal File's format
+---------------------------------+
| Metadata (FAT, Inodes, etc.)    | -> meta data to track
+---------------------------------+
|                                 |
| File Data                       | 
| ...                             |
| ...                             |
| ...              		            |
| ...                             |
+---------------------------------+
*/

#define TEMP_VFS_SIZE 0x0 

typedef VFS_FILE* VFS_FILE_ref;

typedef char* FILE_NAME;

#define FILE_NAME_ht_dtor(fn) free(fn)

#define VFS_FILE_ref_ht_dtor(VFS_FILE_ref) free(VFS_FILE_ref)

#define FILE_NAME_ht_value(v) (&v)

#define VFS_FILE_ref_ht_value(VFS_FILE_ref) (&VFS_FILE_ref)

#define FILE_NAME_ht_equal(cp1, cp2) strcmp(cp1, cp2) == 0

FILE_NAME FILE_NAME_copy(FILE_NAME cp) 
{
	size_t len = strlen(cp) + 1;
	char* ret = malloc(len); 
	ret[len - 1] = '\0';
	strncpy(ret, cp, len - 1);
	return ret; 
}

struct VFS_FILE {
	//slow access meta-data
	cJSON* json_metaData;
	//quick access meta-data
	FILE_NAME file_name;
	size_t file_size;
	bool is_dir;
};

VFS_FILE_ref VFS_FILE_ref_copy(VFS_FILE_ref origin) 
{
	VFS_FILE_ref cpy = malloc(sizeof(VFS_FILE));
	memcpy(cpy, origin, sizeof(VFS_FILE));
	return cpy;
}
//Might change this up a bit
size_t FILE_NAME_ht_hash(FILE_NAME cp) {
   size_t ret = 0;
   const size_t len = strlen(cp);
   __HASHFUNC_FNV1A(ret, cp, len);
   return ret;  
}

define_ht_all(FILE_NAME, VFS_FILE_ref);
define_ht_all_impl(FILE_NAME, VFS_FILE_ref);

struct VFS 
{
	// The table is here temporary, it will be re-constructed into a hash table for increased perfomance
	cJSON* table;
	FILE_NAME_VFS_FILE_ref_ht_t FAT;
	FILE_NAME vfs_file_path;
};


VFS* VFS_Create(char* const vfs_file_path) 
{
	'!'
	if (vfs_file_path == NULL) return NULL;
	// Open file in binary write mode
	FILE* vfs_file = fopen(vfs_file_path, "wb");

	// Check if the file was successfully opened
	if (vfs_file == NULL) { 
		// If not, return NULL to indicate error
		return NULL; 
	}

	//malloc + memset
	VFS * vfs = calloc(1, sizeof(VFS));

	if (!vfs) return NULL;
	vfs->FAT = FILE_NAME_VFS_FILE_ref_ht_create();

	vfs->table = cJSON_CreateObject();
	if (vfs->table == NULL) return NULL;

	cJSON* version = cJSON_AddStringToObject(vfs->table, "version", VERSION);
	cJSON* fat_count = cJSON_AddNumberToObject(vfs->table, "fat-count", TEMP_VFS_SIZE);
	cJSON* fat = cJSON_AddArrayToObject(vfs->table, "fat");

	if (version == NULL || fat_count == NULL || fat == NULL) {
		// If not, delete the JSON object, close the file, and return NULL
		cJSON_Delete(vfs->table);
		fclose(vfs_file);
		return NULL;
	}

	vfs->vfs_file_path = vfs_file_path; 

	//formate the jsonData on to a string
	char * vfs_data = cJSON_Print(vfs->table);
	// Write the actual JSON data to the vfs file
	fwrite(vfs_data, strlen(vfs_data), 1, vfs_file);

	// Free the memory allocated for the JSON string
	free(vfs_data);

	// Flush the file buffer to ensure all data is written
	fflush(vfs_file);

	// Close the file
	fclose(vfs_file);

	return vfs;
}

//VFS* LoadVFS(const char* path) 
//{
//	// Open file in read mode
//	FILE* file = fopen(path, "r");
//	if (file == NULL){
//		return NULL;
//	}
//
//	//gets the file lenght in characters
//	fseek(file, 0, SEEK_END);
//	long file_size = ftell(file);
//	//reset our file pointer
//	fseek(file, 0, SEEK_SET);
//
//	//malloc memory to hold the json data as a string
//	char *json_buffer = (char *)malloc(file_size + 1);
//	if(json_buffer == NULL) {
//		return NULL; 
//	}
//	//write the json file data into the string
//	fread(json_buffer, 1, file_size, file);
//
//	//close file
//	fclose(file);
//
//	//null-terminating our string for safety
//	json_buffer[file_size] = '\0'; 
//
//	//malloc memory for the VFS handle
//	VFS* vfs = malloc(sizeof(VFS));
//	if (vfs == NULL){
//		free(json_buffer);
//		return NULL;//a bad alloc
//	}
//
//	//get the json root object
//	cJSON *root = cJSON_Parse(json_buffer);
//	vfs->table = root; 
//	// free the buffer after parsing
//	free(json_buffer);
//	
//	return vfs;
//}
//
//void DestroyVFS(VFS* vfs) {
//	if(!vfs) return;
//	if(vfs->table) cJSON_Delete(vfs->table);
//	free(vfs);
//}
//
bool FileExists(VFS* vfs, const char* path) {
	// Check for NULL pointers
   if (vfs == NULL || path == NULL) {
       return false;
   }
	cJSON* FAT = cJSON_GetObjectItem(vfs->table, "FAT");
	if (FAT == NULL) {
       return false;
   }
    cJSON* fileEntry;
    cJSON_ArrayForEach(fileEntry, FAT) {
       // Get the "path" field of the current file entry
       cJSON* filePath = cJSON_GetObjectItem(fileEntry, "file-path");
       if (filePath != NULL && cJSON_IsString(filePath)) {
           // Compare the current file's path with the given path
           if (strcmp(filePath->valuestring, path) == 0) {
               return true; // File exists
           }
       }
   }
	//ret false if no macth
   return false;
}


void cjson_to_ht_entrey(FILE_NAME_VFS_FILE_ref_ht_t this, cJSON * metadata)
{

	cJSON * abs_path = cJSON_GetObjectItem(metadata, "abs-path");
	cJSON * file_size = cJSON_GetObjectItem(metadata, "file-size");
	cJSON * is_dir = cJSON_GetObjectItem(metadata, "is-dir");
	cJSON_bool dir = cJSON_IsTrue(is_dir);
	VFS_FILE file = {
		.file_name = cJSON_GetStringValue(abs_path),
		.file_size = cJSON_GetNumberValue(file_size),
		.is_dir = dir,
		.json_metaData = metadata
	};
	FILE_NAME_VFS_FILE_ref_ht_set(&this, cJSON_GetStringValue(abs_path), &file);

}

VFS_FILE* VFS_OpenFile(VFS* vfs, const char* file_path, VFS_FILE_MODE mode) {
   //! NOTICE: THE WHOLE FUNCTION HAS TO BE REWRITTEN DUE TO THE NEW STRUCTURE OF THE VFS
		//! HOW THIS WILL WORK: THE STR WILL BE SEARCHED IN THE HASH TABLE USING allocated_ccp_ht_exists(key <- this one doesn't have to be allocated)
		// Check for NULL pointers
   if (vfs == NULL || vfs->table == NULL || file_path == NULL) {
       return NULL;
   }
   cJSON* root = vfs->table;
   FILE* file = NULL;
	
   // Translate enum file modes
   switch (mode) {
       case VFS_FILE_MODE_READ:
           file = fopen(file_path, "r");
           break;
       case VFS_FILE_MODE_WRITE:
           file = fopen(file_path, "r+");
           break;
       case VFS_FILE_MODE_APPEND:
           file = fopen(file_path, "a+");
           break;
       case VFS_FILE_MODE_CREATE:
           file = fopen(file_path, "w");
           break;
       default:
           return NULL;
   }

   if(!file ) return NULL;

   // Get the array called 'fat'
   cJSON* fat = cJSON_GetObjectItem(root, "fat");
   if (fat == NULL) {
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
   char* absolute_path = abs_path(file_path);

	//when absolute path is to long
	if (!absolute_path) {	
	   assert(!absolute_path);
       return NULL;
   }

	// Add the absolute file path to the object
   if (!cJSON_AddStringToObject(metaData, "abs-path", absolute_path)) {
	   free(absolute_path);
       cJSON_Delete(metaData);
       fclose(file);
       return NULL;
   }

	// Add the is_dir to the object
   cJSON_bool is_dir = is_folder(absolute_path);
   if (!cJSON_AddBoolToObject(metaData, "is-dir", is_dir)) {
		free(absolute_path);
       cJSON_Delete(metaData);
       fclose(file);
       return NULL;
   }
   free(absolute_path);

   // Add the file size to the object
   fseek(file, 0, SEEK_END);
   long size = ftell(file);
   fseek(file, 0, SEEK_SET);
   if (!cJSON_AddNumberToObject(metaData, "file-size", size)) {
       cJSON_Delete(metaData);
       fclose(file);
       return NULL;
   }

   // Add the metadata to the array called 'fat'
   if (!cJSON_AddItemToArray(fat, metaData)) {
       cJSON_Delete(metaData);
       fclose(file);
       return NULL;
   }

	cJSON* fat_count = cJSON_GetObjectItem(root, "fat-count");
	// Update the 'fat-count' variable
	if (fat_count == NULL) {
	   cJSON_Delete(metaData);
	   fclose(file);
       return NULL;
   }

   // Increment fat-count
	cJSON_SetNumberValue(fat_count, fat_count->valueint + 1);	

	// Will hold the file data
   	VFS_FILE_ref handle = (VFS_FILE_ref)calloc(1, sizeof(VFS_FILE));
   	if (handle == NULL) {
		cJSON_Delete(metaData);
	    fclose(file);
       	return NULL;
   	}
   	handle->json_metaData = metaData;

	// Print the JSON data onto a string buffer
   	char* vfs_data = cJSON_Print(root);
  	if (vfs_data == NULL) {
	   free(handle);
       cJSON_Delete(metaData);
	   fclose(file);
       return NULL;
  	}
	
	// Add the cJSON data as an object to the ht
	cjson_to_ht_entrey(vfs->FAT, metaData);

	// OPEN Vfs json file
	FILE* vfs_file = fopen(vfs->vfs_file_path, "wb");

	// Write the actual JSON data to the vfs file
	fwrite(vfs_data, strlen(vfs_data), 1, vfs_file);

	// Free the memory allocated for the JSON string
	free(vfs_data);

	// Flush the file buffer to ensure all data is written
	fflush(vfs_file);

	// Close the file
	fclose(vfs_file);

   	return handle;
}
//
//
//bool ExtractFile(VFS* vfs, const char* src, const char* dst) {
//return 0;
//}
//
//void DeleteFile(VFS* vfs, const char* path) {
//
//}
//
//int CloseFile(VFS_FILE_HANDLE* handle) {
//	//! NOTICE: SAME HERE
//	//Check if the pointer is null
//	if(handle == NULL){
//		return -1;
//	}
//	//get the file-path variable, which happens to be in index zero
//	cJSON* index0 = cJSON_GetObjectItem(handle->metaData, "file-path");
//	//reinterpret the data as a string
//	const char * file_path = cJSON_GetStringValue(index0);
//	if(!file_path){
//		return -1;
//	}
//	//using the string close the file
//	//return fclose(file_path);
//	return 0;
//}
//
//size_t ReadFile(VFS_FILE_HANDLE* handle, void* buffer, size_t size) {
//return 0;
//}
//
//size_t WriteFile(VFS_FILE_HANDLE* handle, const void* buffer, size_t size) {
//return 0;
//}
//
//
//size_t GetFileSize(VFS_FILE_HANDLE* handle) {
//return 0;
//}
//
//size_t GetFileName(VFS_FILE_HANDLE* handle, char* buffer, size_t size) {
//return 0;
//}
//
//bool   SetFileName(VFS_FILE_HANDLE* handle, const char* name) {
//	return 0;
//}
//
//#if _DEBUG
//
//void PrintVFSTable(VFS* vfs) 
//{	
//	//get json data as a string
//	const char * json_buffer = cJSON_Print(vfs->table);
//	if (json_buffer){
//		//print string
//		printf(json_buffer);
//	}
//	else{
//		printf("FAILD: to print the VFS Table");
//	}
//
//}
//
//#endif
//
////__define_ht_main_impl(allocated_ccp, allocated_ccp);