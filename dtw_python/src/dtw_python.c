
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h> // only for the memcpy
#include <errno.h>

/*
    Note: 
    Using ctypes, numpy arrays always look like a vector in C, not a matrix (even if the numpy array IS a matrix)
    The reason is that numpy matrices are always arrays also inside numpy :)    
*/

float path_cost(int len_x, int len_y, float *accumulated_cost, float *distances);
void generates_accumulated_cost(int len_x, int len_y, float *accumulated_cost, float *distances);
void generates_distances(int len_x, int len_y, int dim, float *distances, float *x, float *y);
void returns_path(int *output, int size);

int *path = NULL;
int path_counter = 0;


int returns_path_length(){
    return path_counter;
}

void returns_path(int *output, int size){
    memcpy(output,path,2*sizeof(int)*size);
    free(path);
    path = NULL;
}

float path_cost(int len_x, int len_y, float *accumulated_cost, float *distances)
{
    int i = len_x-1;
    int j = len_y-1;
    int n_malloc_i = 1;
    float min_value = 0;
    float cost = 0;

    path_counter = 0;
    
    if (path == NULL)
    {
        path = malloc(100*2*sizeof(int));
        if (path==NULL)
            return EXIT_FAILURE;
    }
    else
    {
        free(path);
        path = NULL;
        path = malloc(100*2*sizeof(int));
        if (path==NULL)
            return EXIT_FAILURE;        
    }
    
    *path = i;
    *(path+1) = j;
    path_counter++;
    
    while((i>0)||(j>0))
    {        
        if(i==0)
            j = j - 1;
        else if(j==0)
            i = i - 1;
        else
        {
            // Calculates the min value
            if (*(accumulated_cost+((i-1)*len_y)+(j-1))>*(accumulated_cost+((i-1)*len_y)+j))
                min_value = *(accumulated_cost+len_y*(i-1)+j);
            else if (*(accumulated_cost+((i-1)*len_y)+(j-1))>*(accumulated_cost+(i*len_y)+(j-1)))
                min_value = *(accumulated_cost+(i*len_y)+(j-1));
            else
                min_value = *(accumulated_cost+((i-1)*len_y)+(j-1));

            // Calculates the next step based on the min value
            if (*(accumulated_cost+len_y*(i-1)+j) == min_value)
                i = i - 1;
            else if (*(accumulated_cost+len_y*i+(j-1)) == min_value)
                j = j - 1;
            else
            {
                i = i - 1;
                j = j - 1;
            }
        }
                         
        if (((float)path_counter/n_malloc_i)<100)
        {
            *(path+path_counter*2)=i;
            *(path+path_counter*2+1)=j;
            path_counter++;
        }
        else
        {
            n_malloc_i++;
            path = realloc(path,n_malloc_i*100*2*sizeof(int));
            
            if (path==NULL)
                return EXIT_FAILURE;            
            
            *(path+path_counter*2)=i;
            *(path+path_counter*2+1)=j;
            path_counter++;
        }
    }
    for (int i=0; i<path_counter; i++)
    {
        const int x = *(path+i*2);
        const int y = *(path+i*2+1);        
        cost = cost + *(distances+len_y*x+y);
    }
                         
    return cost;
}


void generates_accumulated_cost(int len_x, int len_y, float *accumulated_cost, float *distances)
{
    float min_value = 0;
    
    *(accumulated_cost)= *(distances);
    
    for (int i=1; i<len_y; i++)
        *(accumulated_cost+i) = *(distances+i) + *(accumulated_cost+i-1);
    
    for (int j=1; j<len_x; j++)
        *(accumulated_cost+(j*len_y)) = *(distances+(j*len_y)) + *(accumulated_cost+((j-1)*len_y));    

    for (int i=1; i<len_x; i++)
    {
        for (int j=1; j<len_y; j++)
        {
            // Calculates the min value
            if (*(accumulated_cost+((i-1)*len_y)+(j-1))>*(accumulated_cost+((i-1)*len_y)+j))
                min_value = *(accumulated_cost+len_y*(i-1)+j);
            else if (*(accumulated_cost+((i-1)*len_y)+(j-1))>*(accumulated_cost+(i*len_y)+(j-1)))
                min_value = *(accumulated_cost+(i*len_y)+(j-1));
            else
                min_value = *(accumulated_cost+((i-1)*len_y)+(j-1));

            *(accumulated_cost+(i*len_y)+j)= min_value + *(distances+(i*len_y)+j);
        }
        
    }
}

void generates_distances(int len_x, int len_y, int dim, float *distances, float *x, float *y)
{
    for (int i=0; i<len_x; i++)
    {
        for (int j=0; j<len_y; j++)
        {
            *(distances+(i*len_y)+j) = 0; //initialises
            
            if (dim>1)
                for (int d=0; d<dim; d++)
                {
                    *(distances+(i*len_y)+j) += pow(*(x+(i*dim)+d)-*(y+(j*dim)+d),2);
                }
            else
                *(distances+(i*len_y)+j) += pow(*(x+i)-*(y+j),2);
            
            *(distances+(i*len_y)+j) = sqrt(*(distances+(i*len_y)+j));
            
        }
    }
}