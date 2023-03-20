#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AdptArray.h"


typedef struct AdptArray_
{
    PElement* pelm;
    size_t sizeOfArray;
    COPY_FUNC cpy;
    DEL_FUNC del;
    PRINT_FUNC prnt;

}AdptArray;


PAdptArray CreateAdptArray(COPY_FUNC cpy, DEL_FUNC del, PRINT_FUNC prnt)
{
    PAdptArray pAdaptArray = (PAdptArray)malloc(sizeof(AdptArray));
    if (pAdaptArray == NULL)
    {
        return NULL;
    }

    pAdaptArray->sizeOfArray = 0;
    pAdaptArray->pelm = NULL;
    pAdaptArray->cpy = cpy;
    pAdaptArray->del = del;
    pAdaptArray->prnt = prnt;
    return pAdaptArray;
}

void DeleteAdptArray(PAdptArray pAdaptArray)
{
	if (pAdaptArray == NULL)
    {
        return;
    }
    
	for(int i = 0; i < pAdaptArray->sizeOfArray; i++)
	{
		if ((pAdaptArray->pelm[i]) != NULL)
        {
            pAdaptArray->del((pAdaptArray->pelm)[i]);
        }
	}
    free(pAdaptArray->pelm);
	free(pAdaptArray);
}

Result SetAdptArrayAt(PAdptArray pAdaptArray, int index, PElement newElement)
{
    if (pAdaptArray == NULL)
    {
        return FAIL;
    } 
    if (index >= pAdaptArray->sizeOfArray)
    {
        PElement* pelm = (PElement*)calloc((index+1),sizeof(PElement));
        if (pelm == NULL)
        {
            return FAIL;
        }
        memcpy(pelm, pAdaptArray->pelm, (pAdaptArray->sizeOfArray)*(sizeof(PElement))); //copy the old array to the new array
        free(pAdaptArray->pelm);
        pAdaptArray->pelm=pelm; // insert the new array to the struct
        pAdaptArray->sizeOfArray=index+1; //update the size of the array
    }
    if (((pAdaptArray->pelm)[index]) != NULL)
    {
        pAdaptArray->del(((pAdaptArray->pelm)[index]));
    }
    if (newElement != NULL)
    {
        (pAdaptArray->pelm)[index] = pAdaptArray->cpy(newElement);
    }
    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray pAdaptArray, int index)
{
    if (pAdaptArray == NULL)
    {
        return NULL;
    }

    if (index >= pAdaptArray->sizeOfArray) //if the index is greater than the size of the array
    {
        return NULL;
    }

    if ((pAdaptArray->pelm)[index] ==NULL) 
    {
        return NULL;
    }
    
    return pAdaptArray->cpy((pAdaptArray->pelm)[index]);
}

int GetAdptArraySize(PAdptArray pAdaptArray)
{
    if (pAdaptArray == NULL) 
    {
      return -1;
    }
    return pAdaptArray->sizeOfArray;
}

void PrintDB(PAdptArray pAdaptArray)
{
    if (pAdaptArray == NULL)
    {
        return;
    }

    for(int i = 0; i < pAdaptArray->sizeOfArray; i++)
	{
		if ((pAdaptArray->pelm[i]) != NULL)
        {
            (pAdaptArray->prnt(pAdaptArray->pelm[i]));
        }
	}

}

