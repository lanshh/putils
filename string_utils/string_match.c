#include <stdio.h>
#include <string.h>

struct dev_proc_info
{
    const char *cid; /* cardX/id match */
    const char *did; /* dai id match */
};

struct dev_proc_info SPEAKER_OUT_NAME[] = /* add codes& dai name here*/
{
    {"realtekrt5616c", NULL,},
    {"realtekrt5651co", "rt5651-aif1",},
    {"realtekrt5670c", NULL,},
    {"realtekrt5672c", NULL,},
    {"realtekrt5678co", NULL,},
    {"rkhdmianalogsnd", NULL,},
    {"rockchipcx2072x", NULL,},
    {"rockchipes8316c", NULL,},
    {"rockchipes8323c", NULL,},
    {"rockchipes8388c", NULL,},
    {"rockchipes8396c", NULL,},
    {"rockchiprk", NULL, },
    {"rockchiprk809co", NULL,},
    {"rockchiprk817co", NULL,},
    {"rockchiprt5640c", "rt5640-aif1",},
    {"rockchiprt5670c", NULL,},
    {"rockchiprt5672c", NULL,},
    {NULL, NULL}, /* Note! Must end with NULL, else will cause crash */
};

#define min(a, b) (a > b ? b : a)
float match_score(const char* str1, const char *str2)
{
        int idx , idy, temp;
        float similarity;
        int len1;
        int len2;
        int v1, v2, v3;
        int dif[64][64]  = {0};

        len1 = strlen(str1);
        len2 = strlen(str2);
        if (len1 > 64 || len2 > 64 ) {
            return -1; /* limit of string large than 64 */
        }
        for (idx = 0; idx <= len1; idx++) {
            dif[idx][0] = idx;
        }
        for (idx = 0; idx <= len2; idx++) {
            dif[0][idx] = idx;
        }
        for (idx = 1; idx <= len1; idx++) {
            for (idy = 1; idy <= len2; idy++) {
                if (str1[idx - 1] == str2[idy - 1]) {
                    temp = 0;
                } else {
                    temp = 1;
                }
                v1 = dif[idx - 1][idy - 1] + temp;
                v2 = dif[idx][idy - 1] + 1;
                v3 = dif[idx - 1][idy] + 1;
                dif[idx][idy] = min(min(v1, v2), v3);
            }
        }
        //printf("compare %s with %s\n", str1, str2);
        //printf("diff： %d\n", dif[len1][len2]);
        similarity =1 - (float) dif[len1][len2] / (len1 > len2 ? len1 : len2);
        //printf("degree：%f\n", similarity);
        return similarity;
}

int main(int argc, char *argv[])
{
    float v;
    int i;
    int arr_size;
    const char *str;

    printf("enter...\n");
    str = "rockchipes8316";
    arr_size =  sizeof(SPEAKER_OUT_NAME)/ sizeof(SPEAKER_OUT_NAME[0]);
    for (i = 0; i < arr_size; i ++) {
        v = match_score(SPEAKER_OUT_NAME[i].cid, str);
        printf("match %s with %s degree：%f\n", SPEAKER_OUT_NAME[i].cid, str, v);
    }
    return 0;
}
