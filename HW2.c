#include <stdio.h>
#include <stdlib.h>
#include <math.h>  //to use INFINITY
#include <string.h>

#define numberOfCities 7


int DFS( int adjMatrix[][numberOfCities], int state[], FILE *fptr, int source, int final, char* allCities[], int *flag)
{
	state[source] = 1;  // state[source]=1 means visited node, state[source]=0 means unvisited node

	if(*flag == 0)   // I created a flag to write Path() only in a one time once when we call the DFS function
	{
		if (source == final)  // when the distance in the same city is requested
	    {
	        fprintf(fptr, "Path (%s to %s): \nPath Found! \n", allCities[source], allCities[final], allCities[final]);
	        return adjMatrix[source][final];  // the distance value in the adjacency matrix is returned
	    }
	    else // when traveling to a different city
	    {
	        fprintf(fptr, "Path (%s to %s):", allCities[source], allCities[final]);
	    }
	    fprintf(fptr, "\n%s ", allCities[source]);  //the name of the first city is printed to output file
	}
	else if(*flag > 0)
	{
		if (source == final)
	    {
	        fprintf(fptr, "-> %s \nPath Found! \n", allCities[source]); //the name of the same city is printed to output file
	        return adjMatrix[source][final];  // the distance value in the adjacency matrix is returned
	    }
	    else
	    {
	        fprintf(fptr, "-> %s", allCities[source]);  // required city is printed to output file each time DFS is called
	    }
	}

    int distance = INFINITY;  // minimum distance
    int index = -1;  // another flag I created to call DFS
    for (int j = 0; j < numberOfCities; j++)  // traverse all cities
    {
        if (adjMatrix[source][j] != 0 && adjMatrix[source][j] < distance && !state[j])  // if this city is unvisited and there is a route to any city except its or there is no route to another city and this distance is smaller the older distance
        {
            distance = adjMatrix[source][j];  // new distance is created
            index = j; // index is refreshed
        }
    }

    if (index != -1)  //in all cases except the first
    {
        int length = DFS(adjMatrix, state, fptr, index, final, allCities, &flag);  // length variable is created and DFS function called recursively
        (*flag)++;  //flag is increased to write Path() only in a one time
        if (length != INFINITY)  // there is a route to another city
            return distance + length;  // increase the distance by length variable
    }

    return INFINITY;  // else INFINITY returned
}


int main()
{
    int flag = 0; //flag is initialized
	char* allCities[numberOfCities] = {"Prague", "Helsinki", "Tokyo", "Jakarta", "London", "NewYork", "Beijing"}; //city map is created

    int adjMatrix[numberOfCities][numberOfCities] =   // adjacency matrix is created
        {
            {0, 1845, INFINITY, INFINITY, 1264, INFINITY, INFINITY},
            {INFINITY, 0, 7815, INFINITY, INFINITY, INFINITY, INFINITY},
            {INFINITY, INFINITY, 0, 5782, INFINITY, 10838, INFINITY},
            {INFINITY, INFINITY, INFINITY, 0, INFINITY, INFINITY, 4616},
            {INFINITY, INFINITY, 9566, INFINITY, 0, INFINITY, INFINITY},
            {INFINITY, INFINITY, INFINITY, INFINITY, 5567, 0, INFINITY},
            {INFINITY, INFINITY, 1303, INFINITY, 8132, 11550, 0},
		};

    int state[numberOfCities] = {0}; // initialize state array to all zeros means unvisited
	
	FILE* fptr;  // file operator is created
	

	fptr = fopen("output.txt", "w+");  	// creating the text file
    if (fptr == NULL)
    {
	  printf("Problem about file opening!");  // this message was put in order to find out whether file can be opened correctly
      return -1;
    }
    
	int distance_1 = DFS(adjMatrix, state, fptr, 0, 4, allCities, &flag);  // calculating Prague-London route
    if(distance_1 == INFINITY)
		fprintf(fptr, "\nPath not found!");
	else
		fprintf(fptr, "Total Distance: %d km\n\n", distance_1);  //print total distance to output file
	
	flag = 0;  // flag is rearranged to 0 again
    int distance_2 = DFS(adjMatrix, state, fptr, 4, 4, allCities, &flag);    // calculating London-London route   
    if(distance_2 == INFINITY)
		fprintf(fptr, "\nPath not found!");
	else
		fprintf(fptr, "Total Distance: %d km\n\n", distance_2);   //print total distance to output file
	
	flag = 0;  // flag is rearranged to 0 again
    int distance_3 = DFS(adjMatrix, state, fptr, 4, 0, allCities, &flag);   // calculating London-Prague route
    if(distance_3 == INFINITY)
		fprintf(fptr, "\nPath not found!");
	else
		fprintf(fptr, "\nTotal Distance (this distance will have strange results as any distance is not equal to infinity): %d km\n\n", distance_3);   //print total distance to output file
		
	printf("You should check output.txt!"); 

    return 0;
}


