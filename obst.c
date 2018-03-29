#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n = 0;

/*We have created a struct to store the nodes of tree*/
typedef struct obst
{

    int key;
    struct obst *left, *right;

} obst;

obst * root;

int height =0;


/* Print nodes at a given depth */
void depthPrint(obst * root, int level)
{

    if (root == NULL)
    {
        if(level > 1)
        {
            while(level != 0){
               printf("0 ");
               //printf("0 ");
               level--;
            }
        }
        else if(level == 1)
        {
            printf("0 ");
        }

        return;
    }
    if (level == 1)
    {
        printf("%d ", root->key);
    }
    else if(level > 1)
    {
        depthPrint(root->left, level-1);
        depthPrint(root->right, level-1);
    }
}

/*printOrder functoin makes use of height of tree to run a loop starting from root node
and with the use of helper function named depthPrint to print out the keys on all depths*/
void printOrder(obst * root)
{

    for (int i=1; i<=height; i++)
    {
        printf("depth %d: ",i-1);
        depthPrint(root, i);

    }
    printf("\n");
}

/*This here is a Struct type function which makes use of reccursion to build
a tree using r matrix value lookup and returns the node value*/
obst * construct(int i, int j, int r[n+1][n+1])
{

    obst *p= malloc(sizeof(obst)* n);

    if(r[i][j]==0)
    {
        p->key = 0;
        p->left = NULL;
        p->right = NULL;
        return NULL;
    }

    else
    {

        p->left = malloc(sizeof(obst));
        p->right = malloc(sizeof(obst));
        p->key = r[i][j];

        p->left = construct(i,(r[i][j]-1),r);
        p->right = construct((r[i][j]+1),j,r);

        return p;

    }

}


/*This is a helper function that calculates the sum of all the probabilities
of the keys*/

float sum(float p[n], int i, int j)
{
    float pn =0;
    for(int x = i; x <= j; x++)
    {

        pn = p[x-1] + pn;

    }
    return pn;
}


int getK(int i, int j,float a[n+1][n+1], float p[n])
{


    int k = 0;
    int cnt = 0;
    int val = 0;
    float pn = 0.0;
    float min[n+1];


//-------------------Calculation of values for min array---------------------------
    /*In this loop we are calculating the values for the required field and storing
    them in a array and we are using helper function named sum to get the sum of
    probabilities*/

    for(k = i; k <= j; k++)
    {

        min[k] = (a[i][k-1] + a[k+1][j]) + sum(p,i,j);

    }




//-------------------Search of min value in array----------------------------------

    /*In here we are making comparison of values in the min array to find the
    smallest one and returning the location that is K value from which we found
    minimum value*/

    float minimum = min[k-1];
    int location = k-1;

    for (int x = i; x <=j; x++)
    {
        if(min[x] <= minimum)
        {

            minimum = min[x];
            location = x;

        }
    }


    return location;

}
int maxDepth(obst * node)
{
    if(node == NULL)
    {
        return 0;
    }
    else
    {
        int ldepth = maxDepth(node->left);
        int rdepth = maxDepth(node->right);

        if(ldepth > rdepth)
            return (ldepth+1);
        else
            return(rdepth+1);
    }
}

void optsearchtree(int k, float p[n], float minavg)
{

    int i,j,diag;
    float a[n+1][n+1];
    int r[n+1][n+1];
    int cnt = 0;


//---------------------------------------Initialize with all 0 values-------------------------------

    /*As we have created two matrix for storing A and R values. Here, we have initialized both the
    arrays with zero*/

    for (i = 0; i <=n+1; i++)
    {
        for (j = 0; j <=n+1; j++)
        {
            a[i][j] = 0.0;
            r[i][j] = 0;

        }
    }

//---------------------------------------Initialize with diagonal values-----------------------------

    /*Here we have initialized 1'st diagonal from the given values*/
    for (i = 1; i <= n; i++)
    {

        a[i][i] = p[i-1];
        r[i][i] = i;

    }

    a[n+1][n] = 0;
    r[n+1][n] = 0;


//-----------------------------Diagonal and min calculation------------------------------------------

    /*In this part we will populate the rest of the diagonals in a and r matrix by calculating all
    the values with helper funcation named getk*/

    for(diag = 1; diag <= n-1; diag++)
    {

        for(i = 1; i <= n-diag; i++)
        {

            int m = i + diag;
            int f =getK(i,m,a,p);
            a[i][m] = (a[i][f-1] + a[f+1][m]) + sum(p,i,m);

            r[i][m] = f;

        }

        minavg = a[1][n];
    }


    /*This part here makes use of construct function to build the tree and printOrder function
    prints the constructed by depth order*/
    printf("--------------------------Tree values-------------------------\n");

    printf("\n");
    root = construct(1,n,r);
    height = maxDepth(root);
    printOrder(root);

    printf("--------------------------------------------------------------\n");

}



int main(int argc, char * argv[])
{

    // Filling up the arrays from the user arguments
    int key = atoi(argv[1]);
    float p[key];
    int index[key][key];
    float minavg = 0.0;

    n = atoi(argv[1]);

    for(int i = 0; i < key; i++)
    {

        p[i] = atof(argv[2+i]);


    }

    // Call to method to calculate the Matrix values
    optsearchtree(key, p, minavg);

    return 0;

}
