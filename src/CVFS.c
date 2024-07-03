#include <CVFS.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <cJSON.h>

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
	cJSON* table;
};

struct _VFS_FILE_HANDLE {
	void* temp;
};

VFS* CreateVFS(const char* path) 
{
	// Open file in binary write mode
	FILE* handle = fopen(path, "wb");

	// Check if the file was successfully opened
	if (handle == NULL) {
    	// If not, return NULL to indicate error
    	return NULL;
	}

	// Create a new JSON object
	cJSON* root = cJSON_CreateObject();

	// Check if the JSON object was successfully created
	if (root == NULL) {
    	// If not, close the file and return NULL
    	fclose(handle);
    	return NULL;
	}

	// Add a version string to the JSON object
	cJSON* version = cJSON_AddStringToObject(root, "version", VFS_VERSION);

	// Add a vfs-size number to represent the size of the vfs JSON file
	#define TEMP_VFS_SIZE 0x0 
	cJSON* vfs_size = cJSON_AddNumberToObject(root, "vfs-size", TEMP_VFS_SIZE);

	// Add an empty array to the JSON object for the FAT (File Allocation Table)
	cJSON* FAT = cJSON_AddArrayToObject(root, "FAT");

	// Check if the JSON properties were successfully added
	if (version == NULL || vfs_size == NULL || FAT == NULL) {
    	// If not, delete the JSON object, close the file, and return NULL
    	cJSON_Delete(root);
    	fclose(handle);
    	return NULL;
	}

	// Print the JSON object to a string
	char* jsonData = cJSON_Print(root);

	// Create a buffer to store the size of the JSON data as a string
	char jsonData_size_str[sizeof(int) * 8];
	// Convert the int to a string
	snprintf(jsonData_size_str, sizeof(int) * 8, "%zu", strlen(jsonData));

	// change the "vfs-size" variable to the size of the json file
	cJSON_SetNumberValue(vfs_size, strlen(jsonData) + strlen(jsonData_size_str));

	//formate the jsonData on to a string
	jsonData = cJSON_Print(root);
	// Write the actual JSON data to the vfs file
	fwrite(jsonData, strlen(jsonData), 1, handle);

	// Free the memory allocated for the JSON string
	free(jsonData);

	// Flush the file buffer to ensure all data is written
	fflush(handle);

	// Close the file
	fclose(handle);

	// Allocate memory for a new VFS structure
	VFS* vfs = (VFS*)malloc(sizeof(VFS));

	// Check if the memory allocation was successful
	if (vfs == NULL) {
    	return NULL;
	}

	// Parse the JSON data back into a cJSON object and assign it to the VFS structure
	vfs->table = root;

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
	if(vfs)
	{
		if(vfs->table)
		{
			//delete the root
			cJSON_Delete(vfs->table);
		}
		//free the memory vfs prt is point to
		free(vfs);
	}

}

bool FileExists(VFS* vfs, const char* path) {
	//will find this out later

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
	// // ret false if no macth
    // return false;
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