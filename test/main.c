#include <CVFS.h>
#include "console.h"
int main() {
        SetConsoleColor(ConsoleColorDarkGray, ConsoleColorWhite, ConsoleAttributeNormal);
        printf("Hello World!\n");



        VFS* vfs_ptr = CreateVFS("./vfs.json");
        PrintVFSTable(vfs_ptr);
        OpenFile(vfs_ptr, "decl.png", VFS_FILE_MODE_CREATE); 
        VFS_FILE_HANDLE* t = OpenFile(vfs_ptr, "dec2.png", VFS_FILE_MODE_CREATE);
        int d = CloseFile(t);
        PrintVFSTable(vfs_ptr);



        VFS* vfs_ptr1 = LoadVFS("./vfs.json");
        PrintVFSTable(vfs_ptr1);

        
        // TODO: Implement tests
        ResetConsoleColor();
        return 0;
}