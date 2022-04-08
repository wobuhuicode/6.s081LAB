#include "../kernel/types.h"
#include "../user/user.h"

int main(int argc, char *argv[])
{
    
    if (argc != 2)
    {
        fprintf(2, "Error!\n");
        exit(1);
    }
    int ticks = atoi(argv[1]);
    fprintf(1, "Usage: sleep ticks...\n");
    sleep(ticks);
    exit(0);
    
}