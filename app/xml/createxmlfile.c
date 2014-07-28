
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

    /* �����ӽڵ�1 */
    cur = xmlNewChild(rootnode, NULL, "items", NULL);
    /* ����ӽڵ�1���� */
    xmlSetProp(cur, "id", "1");
    /* ������ڵ�1 */
    curchildren = xmlNewChild(cur, NULL, "item", NULL);
    xmlSetProp(curchildren, "id", "1");
    xmlSetProp(curchildren, "steps", "100");
    xmlSetProp(curchildren, "opt", "1");
    /* ������ڵ�2 */
    curchildren = xmlNewChild(cur, NULL, "item", NULL);
    xmlSetProp(curchildren, "id", "2");
    xmlSetProp(curchildren, "steps", "50");
    xmlSetProp(curchildren, "opt", "2");

    /* �����ӽڵ�2 */
    cur = xmlNewChild(rootnode, NULL, "items", NULL);
    /* ����ӽڵ�1���� */
    xmlSetProp(cur, "id", "2");

    /* �����ӽڵ�3 */
    cur = xmlNewChild(rootnode, NULL, "items", NULL);
    /* ����ӽڵ�3���� */
    xmlSetProp(cur, "id", "3");
    /* ������ڵ�1 */
    curchildren = xmlNewChild(cur, NULL, "item", NULL);
    xmlSetProp(curchildren, "id", "1");
    xmlSetProp(curchildren, "steps", "211");
    xmlSetProp(curchildren, "opt", "4");
    /* ������ڵ�2 */
    curchildren = xmlNewChild(cur, NULL, "item", NULL);
    xmlSetProp(curchildren, "id", "2");
    xmlSetProp(curchildren, "steps", "555");
    xmlSetProp(curchildren, "opt", "5");
    /* ������ڵ�3 */
    curchildren = xmlNewChild(cur, NULL, "item", NULL);
    xmlSetProp(curchildren, "id", "3");
    xmlSetProp(curchildren, "steps", "322");
    xmlSetProp(curchildren, "opt", "6");
    /* ������ڵ�4 */
    curchildren = xmlNewChild(cur, NULL, "item", NULL);
    xmlSetProp(curchildren, "id", "4");
    xmlSetProp(curchildren, "steps", "456");
    xmlSetProp(curchildren, "opt", "7");
    /* ������ڵ�5 */
    curchildren = xmlNewChild(cur, NULL, "item", NULL);
    xmlSetProp(curchildren, "id", "5");
    xmlSetProp(curchildren, "steps", "299");
    xmlSetProp(curchildren, "opt", "8");
    /* ������ڵ�6 */
    curchildren = xmlNewChild(cur, NULL, "item", NULL);
    xmlSetProp(curchildren, "id", "6");
    xmlSetProp(curchildren, "steps", "96");
    xmlSetProp(curchildren, "opt", "10");


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



