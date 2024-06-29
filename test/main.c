#include <CVFS.h>
#include "console.h"
int main() {
	SetConsoleColor(ConsoleColorDarkGray, ConsoleColorWhite, ConsoleAttributeNormal);
	printf("Hello World!\n");
	VFS* vfs = CreateVFS("./test.vfs");

	// TODO: Implement tests
	ResetConsoleColor();
	return 0;
}