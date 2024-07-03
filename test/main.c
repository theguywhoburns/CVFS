#include <CVFS.h>
#include "console.h"
int main() {
        SetConsoleColor(ConsoleColorDarkGray, ConsoleColorWhite, ConsoleAttributeNormal);
        printf("Hello World!\n");
        VFS* vfs_ptr = CreateVFS("./vfs.json");
        PrintVFSTable(vfs_ptr);
        VFS* vfs_ptr1 = LoadVFS("./vfs.json");
        PrintVFSTable(vfs_ptr1);
        // TODO: Implement tests
        ResetConsoleColor();
        return 0;
}