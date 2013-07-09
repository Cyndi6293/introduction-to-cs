#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "tree.h"
#include "forest.h"
#include "huffile.h"

int main(int argc, char* argv[])
{
	// ensure proper usage
	if (argc != 3 )
	{
		printf("Corect usage is: %s huffiletoopen.bin outasciifile.txt\n", argv[0]);
		return 1;
	}
	
	// open input
    Huffile* input = hfopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open %s for reading.\n", argv[1]);
        return 1;
    }

    // read in header
    Huffeader header;
    if (hread(&header, input) == false)
    {
        hfclose(input);
        printf("Could not read header.\n");
        return 1;
    }

    // check for magic number
    if (header.magic != MAGIC)
    {
        hfclose(input);
        printf("File was not huffed.\n");
        return 1;
    }

    // check checksum
    int checksum = header.checksum;
    for (int i = 0; i < SYMBOLS; i++)
    {
        checksum -= header.frequencies[i];
    }
    if (checksum != 0)
    {
        hfclose(input);
        printf("File was not huffed.\n");
        return 1;
    }
	
	/*
	 *1. Making a Huff-tree
	 */
	//1.1. Populating Forest with one-node Trees
	Forest* forest = mkforest();
	for (int i = 0; i < SYMBOLS; i++)
	{
		//Put only non-0 freq chars into forest
		if (header.frequencies[i] != 0)
		{	
			//create tree
			Tree *newTree = mktree();
			newTree->symbol = i;
			newTree->frequency = header.frequencies[i];
			//plant tree
			if ( !plant(forest, newTree) )
			{
				printf("Couldn't plant tree in forest, closing program\n");
				hfclose(input);
				rmforest(forest);
				rmtree(newTree);
				return 1;
			}
		}
	}
	
	//1.2. Connecting all trees in forest to make the 1 and only hufftree
	while (forest->first->next != NULL )
	{
		Tree* tree1 = pick(forest);
		Tree* tree2 = pick(forest);
		Tree* newTree =  mktree();
		newTree->left = tree1;
		newTree->right = tree2;
		newTree->frequency = tree1->frequency + tree2->frequency;
		if ( !plant(forest, newTree) )
		{
			printf("Couldn't plant tree in forest, closing program\n");
			hfclose(input);
			rmforest(forest);
			rmtree(newTree);
			rmtree(tree1);
			rmtree(tree2);
			return 1;
		}
	}
	
	/*
	 * 2. Writing message to txt file
	 */
	FILE* fp = fopen( argv[2], "w");
	if (fp ==NULL)
	{
		printf("Couldn't open outfile to write\n");
		hfclose(input);
		rmforest(forest);
		return 1;
	}
	int bit;
	//pointer to parse tree
	Tree* wp = forest->first->tree;
    while ((bit = bread(input)) != EOF)
    {        
        //found leaf, time to print                
        if ( (wp->left == NULL) && (wp->right == NULL) )
        {  
        	fprintf(fp, "%c", wp->symbol);        	
        	wp = forest->first->tree;
        }
        //not leaf yet, go right or left
        if ( (bit == 0) && (wp->left != NULL) )
        {
        	wp = wp->left;
        }
        else if ( (bit == 1) && (wp->right != NULL) )
        {
        	wp = wp->right;
        }
    }
    //if file had more that one unique characters there would be last char left after while loop
    if ( (wp != NULL) && (forest->first->tree->left != NULL) && (forest->first->tree->right != NULL) )
 	   fprintf(fp, "%c", wp->symbol);
    rmforest(forest);
    hfclose(input);
    fclose(fp);
	return 0;
}
