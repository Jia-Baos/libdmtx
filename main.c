#include <stdio.h>
#include <stdlib.h>
#include "./dmtx.h"
#include "./image.h"
#include "./image_io.h"

int main()
{
    const char *file_name = "/home/jia-baos/Project-CPP/libdmtx/res1.ppm";
    color_image *src = color_image_load(file_name);
    printf("src: %d, %d\n", src->width, src->height);

    const int w = src->width;
    const int h = src->height;
    unsigned char *src_char = (unsigned char *)calloc(w * h, sizeof(unsigned char));

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            const int index = i * src->stride + j;
            src_char[i * w + j] = (unsigned char)src->data1[index];
        }
    }

    DmtxImage *img = dmtxImageCreate(src_char, w, h, DmtxPack8bppK);
    DmtxDecode *dec = dmtxDecodeCreate(img, 1);
    DmtxRegion *reg = dmtxRegionFindNext(dec, NULL);
    if (reg != NULL) // 如果检测到存在DM码区域
    {
        DmtxMessage *msg = dmtxDecodeMatrixRegion(dec, reg, DmtxUndefined); // 解析DM码
        if (msg != NULL)                                                    // 如果DM码解析成功
        {
            printf("DataMatrix Decode Result: %s\n", msg->output);
            dmtxMessageDestroy(&msg);
        }
        else
        {
            printf("Decode dm failed...\n");
        }
        dmtxRegionDestroy(&reg);
    }
    else
    {
        printf("Search dm failed...\n");
    }
    dmtxDecodeDestroy(&dec);
    dmtxImageDestroy(&img);

    return 0;
}