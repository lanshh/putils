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

/* Levenshtein distance 
 */
#define minimum(a, b) (a > b ? b : a)
float match_score(const char* str1, const char *str2)
{
        char idx , idy, temp;
        float similarity;
        int len1;
        int len2;
        int v1, v2, v3;
        char dist[64][64]  = {0};

        len1 = strlen(str1);
        len2 = strlen(str2);
        len1 = len1 > 63 ? 63 : len1;
        len2 = len2 > 63 ? 63 : len2; /* only compare string less than 64 */
        for (idx = 0; idx <= len1; idx++) {
            dist[idx][0] = idx;
        }
        for (idx = 0; idx <= len2; idx++) {
            dist[0][idx] = idx;
        }
        for (idx = 1; idx <= len1; idx++) {
            for (idy = 1; idy <= len2; idy++) {
                if (str1[idx - 1] == str2[idy - 1]) {
                    temp = 0;
                } else {
                    temp = 1;
                }
                v1 = dist[idx - 1][idy - 1] + temp;
                v2 = dist[idx][idy - 1] + 1;
                v3 = dist[idx - 1][idy] + 1;
                dist[idx][idy] = minimum(minimum(v1, v2), v3);
            }
        }
        similarity =1 - (float) dist[len1][len2] / (len1 > len2 ? len1 : len2);
        return similarity;
}
#undef minimum

int main(int argc, char *argv[])
{
    float v;
    const char *stra, *strb;

    if (argc < 3) {
        printf("Usage: strA strB%s\n", argv[0]); 
    }
    stra = argv[1];
    strb = argv[2];
    v = match_score(stra, strb);
    printf("match %s with %s degree：%f\n", stra, strb, v);
    return 0;
}
