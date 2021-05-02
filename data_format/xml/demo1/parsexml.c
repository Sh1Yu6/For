#include <stdio.h>
#include "mxml.h"

int main(int argc, const char* argv[])
{
    // 加载xml文件
    FILE* fp = fopen("book.xml", "r");
    mxml_node_t* root = mxmlLoadFile(NULL, fp, MXML_NO_CALLBACK);

    // 查找book节点
    mxml_node_t* book = mxmlFindElement(root, root, "book", "category", NULL, MXML_DESCEND);
    printf("book attr: %s\n", mxmlElementGetAttr(book, "category"));

    mxml_node_t* node = mxmlWalkNext(book, root, MXML_DESCEND_FIRST);
    printf("    title: %s\n", mxmlGetText(node, 0)); 

    node = mxmlWalkNext(node, root, MXML_NO_DESCEND);
    printf("    author: %s\n", mxmlGetText(node, 0)); 

    node = mxmlWalkNext(node, root, MXML_NO_DESCEND);
    printf("    year: %s\n", mxmlGetText(node, 0)); 

    node = mxmlWalkNext(node, root, MXML_NO_DESCEND);
    printf("    price: %s\n", mxmlGetText(node, 0)); 

    fclose(fp);

    mxmlDelete(root);

    return 0;
}
