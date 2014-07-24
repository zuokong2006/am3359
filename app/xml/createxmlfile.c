
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

/*! �ļ�·�� */
#define XML_DIR        "./config/"



/* ������ */
int main(int argc, char *argv[])
{
    int res = 0;
    char *filedir;
    xmlDocPtr doc;
    xmlNodePtr rootnode, cur, curchildren;
    xmlChar *str;
    xmlAttrPtr attrPtr;

    /* ���������� */
    if(2 != argc)
    {
        DEBUG_MSG("E:input param error.\r\n");
        exit(0);
    }
    filedir = malloc(strlen(argv[1]) + strlen(XML_DIR) + 4);
    strcpy(filedir, XML_DIR);
    strcat(filedir, argv[1]);
    DEBUG_MSG("D:create file dir = %s\r\n", filedir);

    /* �ĵ����ڵ�ָ�� */
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
    /* ���ø��ڵ� */
    xmlDocSetRootElement(doc, rootnode);

    /* todo... */

    /* �洢xml�ļ� */
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

    /* ������ */
errproc:
    /* �ͷ�xml�ĵ� */
    xmlFreeDoc(doc);
    free(filedir);
    exit(0);
}



