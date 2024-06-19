#define cmd_1 _IOR('a',1,struct stats *)

struct stats
{
    int size;
    char buffer[100];
    int rw;
};
static struct stats device_stats;