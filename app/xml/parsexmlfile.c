
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

/*! �ļ����� */
#define XML_NAME        "./config/hardware.xml"


/* �����ڵ����� */
static int parse_node_attr(xmlNodePtr pNode, xmlAttrPtr pAttr)
{
    xmlChar *pStr;

    while(NULL != pAttr)
    {
        /* ��ȡ�ڵ�����ֵ   */
        pStr = xmlGetProp(pNode, (const xmlChar *)(pAttr->name));
        /* ��ӡ�ڵ����� */
        DEBUG_MSG("D:%s node attr %s=%s\r\n", pNode->name, pAttr->name, pStr);
        xmlFree(pStr);
        /* ָ����һ�� */
        pAttr = pAttr->next;
    }

    return 0;
}

/* ������ */
int main(int argc, char *argv[])
{
    int res = 0;
    xmlDocPtr doc;
    xmlNodePtr cur, curchildren;
    xmlChar *str;
    xmlAttrPtr attrPtr;
    char *filedir;

    /* ���������� */
    if(2 != argc)
    {
        DEBUG_MSG("E:input param error.\r\n");
        exit(0);
    }
    filedir = malloc(strlen(argv[1])+strlen("./config/")+4);
    strcpy(filedir, "./config/");
    strcat(filedir, argv[1]);
    DEBUG_MSG("D:file dir = %s\r\n", filedir);

    /* ����xml�ļ� */
    DEBUG_MSG("D:parse xml file.\r\n");
    doc = xmlParseFile(filedir);
    if(NULL == doc)
    {
        free(filedir);
        DEBUG_MSG("E:document not parsed successfully.\r\n");
        exit(0);
    }
    free(filedir);
    /* ��ȡ���ڵ� */
    cur = xmlDocGetRootElement(doc);
    if(NULL == cur)
    {
        DEBUG_MSG("E:empty document.\r\n");
        xmlFreeDoc(doc);
        exit(0);
    }
    /* ���ڵ������ж� */
    if(xmlStrcmp(cur->name, (const char *)"root"))
    {
        DEBUG_MSG("E:document of the wrong type, root node != root.\r\n");
        xmlFreeDoc(doc);
        exit(0);
    }

    /* root�ӽڵ� */
    cur = cur->children;
    while(NULL != cur)
    {
        /* �ڵ������ж� */
        //if(0 == xmlStrcmp(cur->name, (const xmlChar *)"items"))
        {
            /* �ڵ����� */
            attrPtr = cur->properties;
            /* �ڵ����Խ��� */
            parse_node_attr(cur, attrPtr);

            /* �ӽڵ���� */
            curchildren = cur->children;
            while(NULL != curchildren)
            {
                /* �ӽڵ����� */
                attrPtr = curchildren->properties;
                /* �ӽڵ����Խ��� */
                parse_node_attr(curchildren, attrPtr);
                
                curchildren = curchildren->next;
            }
        }
        /* ָ����һ���ֵܽڵ� */
        cur = cur->next;
    }

    /* �ͷ�xml�ĵ� */
    xmlFreeDoc(doc);
    DEBUG_MSG("D:parse xml file ok.\r\n");

    exit(0);
}



