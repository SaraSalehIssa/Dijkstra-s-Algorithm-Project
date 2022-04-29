#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Sara Saleh Issa Issa, 1190673, section NO.1

// A structure to represent a vertex in undirected weighted Graph
struct VertexInGraph
{
    int destination; //Vertex ID of the 2nd of the segment(destination)
    int distance; //Distance in Kilometer
    char *Town; //Name of the town
    struct VertexInGraph *next;
};

// A structure to represent an adjacent Graph
struct adjacentGraph
{
    struct VertexInGraph *head;
    int source; //Vertex ID of the 1st end of the segment(source)
};

// A structure to represent a graph (an array of adjacent Graph)
struct Graph
{
    int V; //Number of vertices in graph
    struct adjacentGraph *array; //An array of adjacent Graph
};

// To create a new vertex in Graph
struct VertexInGraph *newVertexInGraph(int destination, int distance, char *Town)
{

    struct VertexInGraph *newNode = (struct VertexInGraph *) malloc(sizeof(struct VertexInGraph));

    newNode->destination = destination;
    newNode->distance = distance;
    newNode->Town = Town;
    newNode->next = NULL;

    return newNode;
}

// To create a graph of V vertices
struct Graph *createGraph(int V, int idOfVertex[])
{
    struct Graph *graph = (struct Graph *) malloc(sizeof(struct Graph));
    graph->V = V;

    // To create an array with size V of adjacent Graph
    graph->array = (struct adjacentGraph *) malloc(V * sizeof(struct adjacentGraph));

    // Initialize each adjacent Graph as empty by making head as NULL
    for (int i = 0; i < V; ++i)
    {
        graph->array[i].head = NULL;
        graph->array[i].source = idOfVertex[i];
    }
    return graph;
}

// A structure to represent prevent source
struct PreventSource
{
    struct NodePreventSource *head;
};

// A structure to represent node prevent source
struct NodePreventSource
{
    int srcValue;
    struct NodePreventSource *next;
};

// To find the value of index for vertex in graph
int findIndexInGraph(struct Graph *graph, int vertexID)
{
    for (int v = 0; v < graph->V; ++v)
    {
        if (vertexID == graph->array[v].source)
            return v;
    }
    return -1;
}

// To add an edge to an undirected weighted Graph
void addEdge(struct Graph *graph, int source, int destination, int distance, char *Town)
{
    // To add an edge from source to destination (new node is added to the adjacent Graph of source)
    int indexSource = findIndexInGraph(graph, source); // find the value of index for source in graph
    struct VertexInGraph *newNode = newVertexInGraph(destination, distance, Town);
    newNode->next = graph->array[indexSource].head;
    graph->array[indexSource].head = newNode;

    // To add an edge from destination to source (because graph is undirected)
    int indexDestination = findIndexInGraph(graph, destination); // find the value of index for destination in graph
    newNode = newVertexInGraph(source, distance, Town);
    newNode->next = graph->array[indexDestination].head;
    graph->array[indexDestination].head = newNode;
}


// To store in all index in vertex array -1
void initiateArray(int vertex[])
{
    for (int i = 0; i < 500; ++i)
    {
        vertex[i] = -1;
    }
}

// To check if the vertex is already exist in graph or not
int CheckIfExist(int vertex[], int vertexID)
{
    for (int i = 0; i < 500; ++i)
    {
        if (vertex[i] == vertexID)
        {
            return 1;
        }
    }
    return 0;
}

// To count number of vertices according to the values in input file
int CountNumberOfVertices(int vertexID[])
{
    FILE *input = fopen("segments.txt", "r");
    if (input == NULL)
    {
        printf("Error: Unable to open this file!");
        exit(1);
    }

    char line[70];
    int source, destination, countVertex = 0;
    while (fgets(line, 70, input))
    {
        char *DataOfGraph = strtok(line, " ");
        int flag = 1;
        while (DataOfGraph != NULL)
        {
            switch (flag)
            {
                case 1:
                    source = (int) strtol(DataOfGraph, NULL, 10); //To convert the value of source from string to int (Decimal base)
                    if (CheckIfExist(vertexID, source) == 0)
                    {
                        vertexID[countVertex] = source; //If it was not previously in the vertexID array, its value will be added to index No. countVertex
                        countVertex++; //increment the value of countVertex
                    }
                    DataOfGraph = strtok(NULL, " ");
                    break;

                case 2:
                    destination = (int) strtol(DataOfGraph, NULL, 10); //To convert the value of source from string to int (Decimal base)
                    if (CheckIfExist(vertexID, destination) == 0)
                    {
                        vertexID[countVertex] = destination; //If it was not previously in the vertexID array, its value will be added to index No. countVertex
                        countVertex++; //increment the value of countVertex
                    }
                    DataOfGraph = strtok(NULL, " ");
                    break;

                default:
                    DataOfGraph = strtok(NULL, " ");
                    break;
            }
            flag++;
        }
    }
    fclose(input);
    return countVertex; //return the value of countVertex
}

// Read the input file "segments.txt" and load the data in Graph
int FillGraph(struct Graph *graph)
{
    FILE *input = fopen("segments.txt", "r");
    if (input == NULL)
    {
        printf("Error: Unable to open this file!");
        exit(1);
    }
    char line[70];
    int source, destination, distance;
    char *townName;
    char *distanceValue;
    char *part[20]; //To store the parts of town name if exist
    int count = 0;
    int maxValue = 0; //Max value of vertex ID

    while (fgets(line, 70, input))
    {
        // Line will be parted based on space
        char *DataOfGraph = strtok(line, " ");
        int flag = 1;
        while (DataOfGraph != NULL)
        {
            switch (flag)
            {
                case 1:
                    source = (int) strtol(DataOfGraph, NULL, 10); //To convert the value of source from string to int (Decimal base)
                    if (source > maxValue)
                        maxValue = source;
                    DataOfGraph = strtok(NULL, " ");
                    break;

                case 2:
                    destination = (int) strtol(DataOfGraph, NULL, 10); //To convert the value of destination from string to int (Decimal base)
                    if (destination > maxValue)
                        maxValue = destination;
                    DataOfGraph = strtok(NULL, " ");
                    break;

                default:
                    part[count] = DataOfGraph;
                    DataOfGraph = strtok(NULL, " ");
                    count++; //increment the value of count
                    break;
            }
            flag++;
        }
        char *result = malloc(10); //To save name of town

        for (int i = 0; i < count - 1; i++)
        {
            if (i == 0)
                strcpy(result, part[i]);
            else
                strcat(result, part[i]); //To concatenates the result string and the part[i] string, and the result is stored in the result string

            if (i != (count - 2))
                strcat(result, " "); //To concatenates the result string and space, and the result is stored in the result string

            if (i == count - 2)
            {
                townName = result; //To put all parts of town name in townName variable
            }
        }
        distanceValue = strtok(part[count - 1], "\n");
        distance = (int) strtol(distanceValue, NULL, 10); //To convert the value of distance from string to int (Decimal base)
        addEdge(graph, source, destination, distance, townName); // To add an edge with values read from input file to an undirected weighted Graph
        count = 0;
    }
    fclose(input);
    return maxValue;
}

// To check if this source has been passed to this destination before or not
int isPassage(struct PreventSource *arrayPreventSource, int index, int dest)
{
    struct NodePreventSource* check = arrayPreventSource[index].head;
    while(check != NULL)
    {
        if(check->srcValue == dest)
            return 1;
        check = check->next;
    }
    return 0;
}

// To print the name of town of the shortest distance to screen
void printTownName(struct Graph *graph,int src, int dest,FILE *output)
{
    int exit = 0;
    for (int v = 0; v < graph->V; ++v)
    {
        struct VertexInGraph *PrintGraph = graph->array[v].head;
        while (PrintGraph)
        {
            if((graph->array[v].source == src && PrintGraph->destination == dest) ||(graph->array[v].source == dest && PrintGraph->destination == src) )
            {
                printf("%s", PrintGraph->Town);
                fprintf(output,"%s", PrintGraph->Town);
                exit =1;
                break;
            }
            PrintGraph = PrintGraph->next;
        }
        if(exit == 1)
            break;
    }
}

// To find the number of times destination appears in the graph from sources so that we can loop over all the values ​​and calculate the minimum distance
int findNumberDestinationExistInSource(struct Graph *graph, int dest)
{
    int counterDest = 0;
    for (int v = 0; v < graph->V; ++v)
    {
        struct VertexInGraph *scrHead = graph->array[v].head;
        while (scrHead)
        {
            if(scrHead->destination == dest)
                counterDest++;
            scrHead =scrHead->next;
        }
    }
    return counterDest;
}

// To find the shortest paths between two input points in a graph, using Dijkstra’s algorithm
void Dijkstra(struct Graph *graph, int src, int dest, int maxValue,FILE *output)
{
    //if source id = destination id, then the minimum distance between them equals 0
    if(src == dest)
    {
        printf("Start point = End point, this means that the minimum value of the distance = 0.");
    }

    else
    {
        int minDistance[maxValue];
        int parent[maxValue];

        //the number of appearance of destination(counterDestExist)
        int counterDestExist = findNumberDestinationExistInSource(graph,dest);
        int ourCounterCheck = 0;
        int indexDest = findIndexInGraph(graph, dest); // To find the value of index for dest in graph

        //it's array of L.L, it contains the values of the sources that were previously passed in this path to prevent passing through them again
        struct PreventSource *arrayPreventSource;
        arrayPreventSource = (struct PreventSource *) malloc(maxValue*1000 * sizeof(struct PreventSource));
        for (int i = 0; i < maxValue*1000; ++i)
        {
            arrayPreventSource[i].head = NULL;
        }

        //It contains the values ​​of the sources that I want to pass through
        int pathArray[maxValue*1000];
        int pathCounter = 0;

        for (int v = 0; v < maxValue; ++v)
            minDistance[v] = INT_MAX; //To store the minimum distance for all values ​​in the graph is INT_MAX = +2147483647
        minDistance[src] = 0; //To store the minimum distance for source is 0

        //Start with source
        int indexSrc = findIndexInGraph(graph, src); // To find the value of index for src in graph

        //if vertex id does not exist in graph
        if(indexSrc==-1 || indexDest==-1){
            printf("ERROR: this vertex does not exist in graph!");
        }

        else{
            struct VertexInGraph *mySrc = graph->array[indexSrc].head;
            while (mySrc) // loop on destinations
            {
                if (minDistance[mySrc->destination] >= mySrc->distance + minDistance[graph->array[indexSrc].source])
                    minDistance[mySrc->destination] = mySrc->distance + minDistance[graph->array[indexSrc].source];
                parent[mySrc->destination] = graph->array[indexSrc].source;

                pathArray[pathCounter] = mySrc->destination;
                struct NodePreventSource *newNode = (struct NodePreventSource *) malloc(sizeof(struct NodePreventSource));
                newNode->srcValue = graph->array[indexSrc].source;
                newNode->next = NULL;
                arrayPreventSource[pathCounter].head = newNode;

                pathCounter++;

                mySrc = mySrc->next;
            }

            int pathIndexCount = 0;
            int v = 0;
            while(1) // while true(To go to the values inside PathArray)
            {
                if (v == indexSrc)
                {
                    v++;
                    continue;
                }

                int srcPathIndex = findIndexInGraph(graph, pathArray[pathIndexCount]);
                struct VertexInGraph *scrHead = graph->array[srcPathIndex].head;
                while (scrHead)
                {
                    //if destination does not Exist in Prevent Array
                    if (isPassage(arrayPreventSource, pathIndexCount,scrHead->destination) == 1)
                    {
                        scrHead = scrHead->next;
                        v++;
                        continue;
                    }

                    if (minDistance[scrHead->destination] >= scrHead->distance + minDistance[graph->array[srcPathIndex].source])
                    {
                        minDistance[scrHead->destination] = scrHead->distance + minDistance[graph->array[srcPathIndex].source];
                        parent[scrHead->destination] = graph->array[srcPathIndex].source;
                    }

                    pathArray[pathCounter] = scrHead->destination;

                    struct NodePreventSource *newNode = (struct NodePreventSource *) malloc(sizeof(struct NodePreventSource));
                    newNode->srcValue = graph->array[srcPathIndex].source;
                    newNode->next = NULL;
                    arrayPreventSource[pathCounter].head = newNode;

                    struct NodePreventSource* read = arrayPreventSource[pathIndexCount].head;
                    while(read != NULL)
                    {
                        struct NodePreventSource *newNode = (struct NodePreventSource *) malloc(sizeof(struct NodePreventSource));
                        newNode->srcValue = read->srcValue;
                        newNode->next = NULL;
                        newNode->next = arrayPreventSource[pathCounter].head;
                        arrayPreventSource[pathCounter].head = newNode;
                        read = read->next;
                    }

                    pathCounter++;
                    scrHead = scrHead->next;
                }

                /*
                if source in while loop equal my dest plus counter by 1
                 if counter equals number of dest Exist, break and show parent
                */
                if (srcPathIndex == indexDest)
                    ourCounterCheck++;

                if(counterDestExist == ourCounterCheck)
                    break;
                pathIndexCount++;
                v++;
            }

            int finalPrintArray[maxValue];
            int counterFinalPrintArray =0;

            int finalParentIndex = parent[dest];

            finalPrintArray[counterFinalPrintArray]=dest;
            counterFinalPrintArray++;

            finalPrintArray[counterFinalPrintArray]=finalParentIndex;
            counterFinalPrintArray++;
            while (finalParentIndex != src)
            {
                finalParentIndex = parent[finalParentIndex];
                finalPrintArray[counterFinalPrintArray]=finalParentIndex;
                counterFinalPrintArray++;
            }

            printf("\nFrom source %d to destination %d the minimum distance is: %d ", src, dest, minDistance[dest]);
            printf("\nThe shortest paths between them is:  " );
            fprintf(output,"\nFrom source %d to destination %d the minimum distance is: %d ", src, dest, minDistance[dest]);
            fprintf(output,"\nThe shortest paths between them is:  " );
            for (int i = counterFinalPrintArray-1; i>=0 ; --i)
            {
                if(i>0)
                {
                    int nextIndex = i-1;
                    printTownName(graph,finalPrintArray[i],finalPrintArray[nextIndex],output);
                    if(i>1){
                        printf(" ->");
                        fprintf(output," ->");
                    }
                }

            }
        }
    }
}

int main()
{

    int vertexID[500];
    initiateArray(vertexID);
    int V = CountNumberOfVertices(vertexID); //Number of vertices according to the values in input file
    struct Graph *graph = createGraph(V, vertexID);
    int maxValue = FillGraph(graph);
    maxValue++;
    FILE *output = fopen("route.txt", "w"); // write only

    int i=0;
    int choice, extraChoice;
    int source [100];
    int des[100];
    do
    {
        printf("\nMENU:\n");
        printf("1- Enter 2 points to compute the shortest path between them.\n");
        printf("2- Print the route of the shortest distance to a file called (route.txt).\n");
        printf("3- Exit from system.\n");
        printf("Please enter The number of choice you want to do:");
        scanf("%d", &choice);

        if(choice == 1)
        {
            printf("\n");
            printf("Please enter the value of source:");
            scanf("%d", &source[i]);
            printf("Please enter the value of destination:");
            scanf("%d", &des[i]);
            Dijkstra(graph, source[i], des[i], maxValue,output);
            i++;

            do
            {
                printf("\n-------------------------------------------------");
                printf("\nAnother MENU:\n");
                printf("1- if you want enter another source and destination, please enter 2 points to compute the shortest path between them.\n");
                printf("2- Exit from system.\n");
                printf("Please enter The number of choice you want to do:");
                scanf("%d", &extraChoice);

                if(extraChoice == 1)
                {
                    printf("\nPlease enter the value of source:");
                    scanf("%d", &source[i]);
                    printf("Please enter the value of destination:");
                    scanf("%d", &des[i]);
                    Dijkstra(graph, source[i], des[i], maxValue,output);
                    i++;
                }
            }
            while (extraChoice != 2); //Exit from the second menu
        }
        else if(choice ==2)
        {
            //Do Nothing
        }
    }
    while(choice != 3); //Exit the system

    fclose(output);
    return 0;
}
