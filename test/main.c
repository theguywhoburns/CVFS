#include <CVFS.h>
int main(int argc, char** argv) {
	VFS* vfs = VFS_Create("./vfs.json");
	VFS_OpenFile(vfs, "WAG.txt", VFS_FILE_MODE_CREATE);
	return 0;
}