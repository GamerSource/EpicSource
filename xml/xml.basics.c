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
		if(cur->children!=NULL)
		{
		 	cur = cur->xmlChildrenNode;
			parseDemo(doc,cur);	
		}
		else
			printf("%s: %s || Line: %d\n",cur->name, xmlNodeListGetString(doc, cur->xmlChildrenNode, 1), cur->line);
		    	    
	cur = (cur->next!=NULL)?cur->next:cur->parent->next;
	}
    return;
}

static void parseDoc(char *docname, const xmlChar *root_node)
{
	int fail=1;
	xmlDocPtr doc;
	xmlNodePtr cur;

	doc = xmlParseFile(docname);
	
	if (doc == NULL )
	{
		fprintf(stderr,"Ep!c - error: Document not parsed successfully.\n");
		return;
	}	
	cur = xmlDocGetRootElement(doc);	
	if (cur == NULL)
	{
		fprintf(stderr,"Ep!c - error: Document seems to be empty!\n");
		xmlFreeDoc(doc);
		return;
	}	
	if (xmlStrcmp(cur->name, root_node))
	{
		fprintf(stderr,"Ep!c - error: Root node of the XML file must be \"%s\"!\n",root_node);
		xmlFreeDoc(doc);
		return;
	}	
	cur = cur->xmlChildrenNode;
	while (cur != NULL)
	{	
		parseDemo (doc, cur);			
		cur = cur->next;
	}
	xmlFreeDoc(doc);
	return;
}

int main(int argc, char **argv)
{
	char *docname;
		
	if (argc <= 1) {
		printf("Ep!c - info: Usage: %s docname\n", argv[0]);
		return(0);
	}
	docname = argv[1];
	
	parseDoc (docname, "demos");

	return 0;
}

