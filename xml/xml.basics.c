#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml2/libxml/xmlmemory.h>
#include <libxml2/libxml/parser.h>

void parseDemo(xmlDocPtr doc, xmlNodePtr cur)
{
	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
	printf("parseDemo: %s => %s\n", cur->name,xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
	    /*if ((xmlStrcmp(cur->name, (const xmlChar *)"text"))) {
		    key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		    printf("demo: %s\n", key);
		    xmlFree(key);
 	    }*/
	cur = cur->next;
	}
    return;
}

static void parseDoc(char *docname)
{
	xmlDocPtr doc;
	xmlNodePtr cur;

	doc = xmlParseFile(docname);
	
	if (doc == NULL ) {
		fprintf(stderr,"Document not parsed successfully. \n");
		return;
	}
	
	cur = xmlDocGetRootElement(doc);
	
	if (cur == NULL) {
		fprintf(stderr,"empty document\n");
		xmlFreeDoc(doc);
		return;
	}
	
	if (xmlStrcmp(cur->name, (const xmlChar *) "demos")) {
		fprintf(stderr,"document of the wrong type, root node != demos\n");
		xmlFreeDoc(doc);
		return;
	}
	
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
	printf("parseDoc: %s\n", cur->name);
		//if ((!xmlStrcmp(cur->name, (const xmlChar *)"demo"))){
			parseDemo (doc, cur);
		//}
		 
	cur = cur->next;
	}
	
	xmlFreeDoc(doc);
	return;
}

int main(int argc, char **argv)
{
	char *docname;
		
	if (argc <= 1) {
		printf("Usage: %s docname\n", argv[0]);
		return(0);
	}

	docname = argv[1];
	parseDoc (docname);

	return 0;
}

