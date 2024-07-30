#include "defines.h"
#include <CVFS.h>
#include <cJSON.h>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define VFS_VERSION_STR TOSTRING(VFS_VERSION_MAJOR) "." TOSTRING(VFS_VERSION_MINOR) "." TOSTRING(VFS_VERSION_PATCH)
#define vfs_cstring_ht_dtor(str) free(str)
#define vfs_cstring_ht_equal(cp1, cp2) strcmp(cp1, cp2) == 0
#define vfs_size_t_ht_dtor(size) 
#define vfs_size_t_ht_equal(size1, size2) (size1 == size2)
#define vfs_size_t_ht_copy(size) size
size_t vfs_cstring_ht_hash(vfs_cstring cp) {
	size_t ret = 0;
	const size_t len = strlen(cp);
	__HASHFUNC_FNV1A(ret, cp, len);
	return ret;
}

vfs_cstring vfs_cstring_ht_copy(vfs_cstring cp) {
	size_t len = strlen(cp);
	char* ret = malloc(len + 1);
	ret[len] = '\0';
	strncpy(ret, cp, len);
	return ret;
}
define_ht_all_impl(vfs_cstring, vfs_size_t);

const vfs_cstring vfs_version = VFS_VERSION_STR;


struct VFS {
	FILE* vfs_file_handle;
	vfs_cstring_vfs_size_t_ht_t table;
};

void construct_hashtable_for_vfs(VFS* vfs, cJSON* fat_arr) {
	for(int i = 0; i < cJSON_GetArraySize(fat_arr); i++) {
		cJSON* cur = cJSON_GetArrayItem(fat_arr, i);
		char* path = cur->string;
		if(cJSON_IsArray(cur)) {
			vfs_cstring_vfs_size_t_ht_set(&vfs->table, path, (size_t)0); // Means it's a directory
			construct_hashtable_for_vfs(vfs, cur);
		} else if(cJSON_IsNumber(cur)) {
			vfs_cstring_vfs_size_t_ht_set(&vfs->table, path, (size_t)cur->valuedouble);
		} else {
			assert(false && "Unknown type in fat array");
		}
	}
}

VFS* VFS_Create(char* const path) {
	VFS* vfs = malloc(sizeof(VFS));
	vfs->table = vfs_cstring_vfs_size_t_ht_create();
	vfs->vfs_file_handle = fopen(path, "wb");
	if (vfs->vfs_file_handle == NULL) {
		vfs_cstring_vfs_size_t_ht_destroy(&vfs->table);
		free(vfs);
		return NULL;
	}
	cJSON* fat = cJSON_CreateObject();
	cJSON_AddStringToObject(fat, "version", vfs_version);
	cJSON *fat_arr = cJSON_AddArrayToObject(fat, "fat");
	char* fat_str = cJSON_Print(fat);
	size_t fat_str_len = strlen(fat_str);
	char fat_str_len_str[10] = {0};
	for(int i = 9; i >= 0; i--) {
		fat_str_len_str[i] = fat_str_len % 10 + '0';
		fat_str_len /= 10;
	}
	fwrite(fat_str_len_str, 1, 10, vfs->vfs_file_handle);
	fwrite(fat_str, 1, fat_str_len, vfs->vfs_file_handle);
	construct_hashtable_for_vfs(vfs, fat_arr);
	free(fat_str);
	cJSON_Delete(fat);
	return vfs;
}

VFS* LoadVFS(const char* path) {
	VFS* vfs = malloc(sizeof(VFS));
	vfs->table = vfs_cstring_vfs_size_t_ht_create();
	vfs->vfs_file_handle = fopen(path, "r+b");
	if (vfs->vfs_file_handle == NULL) {
		vfs_cstring_vfs_size_t_ht_destroy(&vfs->table);
		free(vfs);
		return NULL;
	}
	char fat_str_len_str[10] = {0};
	fread(fat_str_len_str, 1, 10, vfs->vfs_file_handle);
	size_t fat_str_len = atoi(fat_str_len_str);
	char* fat_str = malloc(fat_str_len + 1);
	fread(fat_str, 1, fat_str_len, vfs->vfs_file_handle);
	fat_str[fat_str_len] = '\0';
	cJSON* fat = cJSON_Parse(fat_str);
	if (fat == NULL) {
		vfs_cstring_vfs_size_t_ht_destroy(&vfs->table);
		free(vfs);
		free(fat_str);
		return NULL;
	}
	cJSON* fat_array = cJSON_GetObjectItem(fat, "fat");
	construct_hashtable_for_vfs(vfs, fat_array);
	cJSON_Delete(fat);
	return vfs;
}

void DestroyVFS(VFS* vfs) {

}

bool FileExists(VFS* vfs, const char* path) {
	return vfs_cstring_vfs_size_t_ht_exists(&vfs->table, (char*)path);
}

VFS_FILE* VFS_OpenFile(VFS* vfs, const char* path, VFS_FILE_MODE mode) {
	TODO("Implement VFS_OpenFile");
	return NULL;
}

bool VFS_ExtractFile(VFS* vfs, const char* src, const char* dst) {
	TODO("Implement VFS_ExtractFile");
}

void VFS_DeleteFile(VFS* vfs, const char* path) {
	TODO("Implement VFS_DeleteFile");
}

int VFS_CloseFile(VFS_FILE* handle) {
	TODO("Implement VFS_CloseFile");
}


size_t VFS_ReadFile(VFS_FILE* handle, void* buffer, size_t size) {
	TODO("Implement VFS_ReadFile");
}

size_t VFS_WriteFile(VFS_FILE* handle, const void* buffer, size_t size) {
	TODO("Implement VFS_WriteFile");
}


size_t VFS_GetFileSize(VFS_FILE* handle) {
	TODO("Implement VFS_GetFileSize");
}

size_t GetFileName(VFS_FILE* handle, char* buffer, size_t size) {
	TODO("Implement GetFileName");
}

bool   SetFileName(VFS_FILE* handle, const char* name) {
	TODO("Implement SetFileName");
}

#if _DEBUG
void PrintVFSTable(VFS* vfs) {
	ht_foreach(vfs->table, iter, index, vfs_cstring, vfs_size_t) {
		printf("%s %zu\n", iter->key, iter->val);
	} ht_foreach_end;
}
#endif