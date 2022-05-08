#include <cstdio>
#include <cstring>
using namespace std;
typedef struct __map_block_info{
    int type;
} Map_BLinfo;
typedef struct __map_entity_info{
    int x,y,type;
} Map_ENinfo;
const int XN = 640 / 16;
const int YN = 480 / 16;
Map_BLinfo mp[XN][YN];
void ofile_1(){
    FILE* f = fopen("../map/level-1","wb");
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
}
void ofile_2(){
    FILE* f = fopen("../map/level-2","wb");
    memset(mp,0,sizeof(mp));
    for(int x = 0;x < XN;x++){
        for(int y = 0;y < YN;y++){
            mp[x][y].type = (x + y) & 1;
        }
    }
    for(int x = 0;x < XN;x++){
        fwrite((char*)(mp[x]),sizeof(Map_BLinfo) * YN,1,f);
    }
    fclose(f);
}
void ofile_e1(){
    FILE* f = fopen("../map/level-1-entity","wb");
    int ents_sz = 1;
    Map_ENinfo head = {ents_sz,0,0};
    Map_ENinfo ents[ents_sz] = {
        {50,160,0}
    };
    fwrite((char*)(&head),sizeof(Map_ENinfo),1,f);
    for(int i = 0;i < ents_sz;i++){
        fwrite((char*)(ents + i),sizeof(Map_ENinfo),1,f);
    }
    fclose(f);
}
void ofile_e2(){
    FILE* f = fopen("../map/level-2-entity","wb");
    int ents_sz = 1;
    Map_ENinfo head = {ents_sz,0,0};
    Map_ENinfo ents[ents_sz] = {
        {50,160,0}
    };
    fwrite((char*)(&head),sizeof(Map_ENinfo),1,f);
    for(int i = 0;i < ents_sz;i++){
        fwrite((char*)(ents + i),sizeof(Map_ENinfo),1,f);
    }
    fclose(f);
}
int main(){
    //ofile_1();
    //ofile_2();
    ofile_e1();
    ofile_e1();
    return 0;
}