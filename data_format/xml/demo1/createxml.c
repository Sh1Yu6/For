#include <stdio.h>
#include "mxml.h"

int main(int argc, const char* argv[])
{
    // 添加文件头
    mxml_node_t* rootNode = mxmlNewXML("1.0");

    // 添加一个新节点
    mxml_node_t *bookStore = mxmlNewElement(rootNode, "bookstore");
    // 添加子节点 - book
    mxml_node_t* book = mxmlNewElement(bookStore, "book");
    // 添加book 的属性
    mxmlElementSetAttr(book, "category", "儿童");
    // 添加标题
    mxml_node_t* title = mxmlNewElement(book, "title");
    mxmlNewText(title, 0, "哈利波特");
    // 添加作者
    mxml_node_t* author = mxmlNewElement(book, "autoro");
    mxmlNewText(author, 0, "JK.Rowling");
    // 添加时间
    mxml_node_t* year = mxmlNewElement(book, "year");
    mxmlNewText(year, 0, "2005");
    // 添加价格
    mxml_node_t* price = mxmlNewElement(book, "price");
    mxmlNewText(price, 0, "29.99");

    // 保存数据到文件
    FILE* fp = fopen("book.xml", "w");
    mxmlSaveFile(rootNode, fp, MXML_NO_CALLBACK);
    fclose(fp);

    return 0;
}
