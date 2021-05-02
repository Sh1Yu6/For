#include <stdio.h>
#include "mxml.h"

int main(int argc, const char* argv[])
{
    if(argc < 2)
    {
        printf("./a.out filename\n");
        return 0;
    }
    // 加载xml文件
    FILE* fp = fopen(argv[1], "r");
    mxml_node_t* root = mxmlLoadFile(NULL, fp, MXML_NO_CALLBACK);

    // 找到第一个factory节点
    mxml_node_t* factory = mxmlFindElement(root, root, "factory", "name", NULL, MXML_DESCEND);
    // 循环查找
    while( factory  )
    {
        // 打印几点的属性值
        printf("factory attr: %s\n", mxmlElementGetAttr(factory, "name"));

        // 向下移动一个节点
        mxml_node_t* brand = mxmlWalkNext(factory, root, MXML_DESCEND);
        while( brand )
        {
            // name
            mxml_node_t* node = mxmlWalkNext(brand, root, MXML_DESCEND_FIRST);
            printf("    name: %s\n", mxmlGetText(node, 0));
            // color
            node = mxmlWalkNext(node, root, MXML_NO_DESCEND);
            printf("    color: %s\n", mxmlGetText(node, 0));
            // price
            node = mxmlWalkNext(node, root, MXML_NO_DESCEND);
            printf("    price: %s\n", mxmlGetText(node, 0));
            printf("    =========================================\n");

            // 找到下一个品牌节点
            brand = mxmlFindElement(brand, root, "brand", NULL, NULL, MXML_NO_DESCEND);
        }
        // 打印该厂家对应的车辆品牌和属性信息
        // 查找下一个节点
        factory = mxmlFindElement(factory, root, "factory", "name", NULL, MXML_NO_DESCEND);
    }
    mxmlDelete(root);
    fclose(fp);

    return 0;
}
