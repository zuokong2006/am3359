
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <math.h>

#include <libxml/parser.h>
#include <libxml/xmlmemory.h>
//#include <libxml/xpath.h>
//#include <libxml/xmlschemastypes.h>

#include "deftype.h"
#include "debug.h"

/*! ÎÄ¼þÃüÁî */
#define XML_NAME        "./config/hardware.xml"

int main(int argc, char *argv[])
{
    int res = 0;
    xmlDocPtr doc;
    xmlNodePtr cur;
    xmlChar *str;

    doc = xmlParseFile(XML_NAME);
    if(NULL == doc)
    {
        DEBUG_MSG("E:document not parsed successfully.\r\n");
        exit(0);
    }

    cur = xmlDocGetRootElement(doc);
    if(NULL == cur)
    {
        DEBUG_MSG("E:empty document.\r\n");
        xmlFreeDoc(doc);
        exit(0);
    }
    if(xmlStrcmp(cur->name, (const char *)"root"))
    {
        DEBUG_MSG("E:document of the wrong type, root node != root.\r\n");
        xmlFreeDoc(doc);
        exit(0);
    }

    cur = cur->xmlChildrenNode;
    while(NULL != cur)
    {
        if((!xmlStrcmp(cur->name, (const xmlChar *)"hardware")))
        {
            str = xmlNodeGetContent(cur);
            DEBUG_MSG("D:hardware-> %s\r\n", str);
            xmlFree(str);
        }
        cur = cur->next;
    }

    xmlFreeDoc(doc);

    //double answer;
    //answer = pow(2, 10);
    //printf("2^10 = %f\n", answer);

    exit(0);
}



