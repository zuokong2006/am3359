
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <math.h>
#include <libxml/parser.h>
#include <libxml/xmlmemory.h>
#include "deftype.h"
#include "debug.h"

/*! 文件路径 */
#define XML_DIR        "./config/"



/* 主函数 */
int main(int argc, char *argv[])
{
    int res = 0;
    char *filedir;
    xmlDocPtr doc;
    xmlNodePtr rootnode, cur, curchildren;
    xmlChar *str;
    xmlAttrPtr attrPtr;

    /* 输入参数检查 */
    if(2 != argc)
    {
        DEBUG_MSG("E:input param error.\r\n");
        exit(0);
    }
    filedir = malloc(strlen(argv[1]) + strlen(XML_DIR) + 4);
    strcpy(filedir, XML_DIR);
    strcat(filedir, argv[1]);
    DEBUG_MSG("D:create file dir = %s\r\n", filedir);

    /* 文档、节点指针 */
    doc = xmlNewDoc(BAD_CAST"1.0");
    if(NULL == doc)
    {
        DEBUG_MSG("E:xml new doc error.\r\n");
        goto errproc;
    }
    rootnode = xmlNewNode(NULL, BAD_CAST"root");
    if(NULL == rootnode)
    {
        DEBUG_MSG("E:xml new node error.\r\n");
        goto errproc;
    }
    /* 设置根节点 */
    xmlDocSetRootElement(doc, rootnode);

    /* todo... */

    /* 存储xml文件 */
    res = xmlSaveFile(filedir, doc);
    if(-1 != res)
    {
        DEBUG_MSG("D:xml save ok.\r\n");
    }
    else
    {
        ERROR_MSG("E:xml save fail!\r\n");
    }
    DEBUG_MSG("D:parse xml file ok.\r\n");

    /* 错误处理 */
errproc:
    /* 释放xml文档 */
    xmlFreeDoc(doc);
    free(filedir);
    exit(0);
}



