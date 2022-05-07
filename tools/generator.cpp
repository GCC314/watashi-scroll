#include <cstdio>
#include <cstring>
using namespace std;
typedef struct __map_block_info{
    int type;
} Map_BLinfo;
const int XN = 640 / 32;
const int YN = 480 / 32;
Map_BLinfo mp[XN][YN];
int main(){
    FILE* f = fopen("level-1","wb");
    memset(mp,0,sizeof(mp));
    for(int y = 10;y < YN;y++){
        for(int x = 0;x < XN;x++){
            mp[x][y].type = 1;
        }
    }
    for(int x = 0;x < XN;x++){
        fwrite((char*)(mp[x]),sizeof(Map_BLinfo) * YN,1,f);
    }
    fclose(f);
    return 0;
}