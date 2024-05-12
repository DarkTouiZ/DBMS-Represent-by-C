// false/true :: This Column contain with String/Integer
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "csv_io.c"

// define a color value (ANSI)
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

#define MAX 100
#define MAX_VERTICES 1000
#define INFINITY 999999

//struct for the each vertice of the graph
struct Vertice {
    char label[MAX]; // vertice name
    int index; // vertice index
};

//struct for the edges of the graph
struct Edge {
  struct Vertice u;  //start vertex of the edge
  struct Vertice v;  //end vertex of the edge
  int weight;  //weight of the edge (u,v
};

//Graph - it consists of edges
struct Graph {
  int V;        //total number of vertices in the graph
  int E;        //total number of edges in the graph
  struct Edge *edge;  //array of edges
  struct Vertice *vertice; //array of vertice
};

void GetShortestPathOF(Node *Initial_vertex_HEADER, Node *Terminal_vertex_HEADER, Node* weight_HEADER);
struct Graph *graphCreation(Node *Initial_vertex_HEADER, Node *Terminal_vertex_HEADER, Node* weight_HEADER);
struct Edge *getAllEdges(Node *Initial_vertex_HEADER, Node *Terminal_vertex_HEADER, Node* weight_HEADER, int size);
struct Vertice *getAllVertices(Node *Initial_vertex_HEADER, Node *Terminal_vertex_HEADER);
bool isUnique(char* data, struct Vertice *unique_data_set, int unique_count);
int getTotalSize_Vertices(struct Vertice *arr);
int getTotalSize_Edges(Node *HEADER);
struct Graph *InitIndex(struct Graph *graph);
void bellmanford(struct Graph *g, char source[]);
void display(int dst[], int pre[], int size, int initial, struct Vertice *vertice);

int main(){
    FILE *file = read_csv("../bin/test.csv");
    if (file == NULL)
    {
        return 1;
    }

    Node *head = csv_to_linked_list(file);

    
    
    // case example
    Node *initial = head;
    Node *terminal = head->Next;
    Node *weight = terminal->Next;
    //debug
    // printf("%d %d\n", Size_edges, Size_vertices);
    // for(int i = 0; i< Size_vertices; i++){
    //     printf("%s ", VerticesArr[i].label);
    // }
    GetShortestPathOF(initial, terminal, weight);
    

    return 0; 
}

void GetShortestPathOF(Node *Initial_vertex_HEADER, Node *Terminal_vertex_HEADER, Node* weight_HEADER){
    struct Graph *graph = graphCreation(Initial_vertex_HEADER, Terminal_vertex_HEADER, weight_HEADER);
    char source[MAX];
    printf("Enter your strating point (no space) > ");
    scanf(" %s", source);
    bellmanford(graph, source);
    // free(graph->edge);
    // free(graph->vertice);
    // free(graph);
    return;
}

struct Graph *graphCreation(Node *Initial_vertex_HEADER, Node *Terminal_vertex_HEADER, Node* weight_HEADER){
    Node *u = Initial_vertex_HEADER;
    Node *v = Terminal_vertex_HEADER;
    Node *weight = weight_HEADER;

    // Handle weight information
    if (!weight->Type) {
        printf(RED "Error : The weight must be an integer.\n" RESET);
        return NULL;
    }

//find shortest path
    if (u->Type != v->Type) {
        // Check if types are invalid
        printf(RED "Error : Types are invalid.\n" RESET);
        return NULL;
    }
    else {
        // get a total rows of each header
        int uSize, vSize, weightSize;
        uSize =  getTotalSize_Edges(u);
        vSize =  getTotalSize_Edges(v);
        weightSize =  getTotalSize_Edges(weight);

        // every header should have a same total of rows
        if( uSize==vSize && vSize == weightSize){
            // Graph creation
            struct Graph *graph = (struct Graph*)malloc(sizeof(struct Graph));
            if (graph == NULL) {
                printf(RED "Error : Memory allocation failed\n" RESET);
                return NULL;
            }

            graph->E = vSize;
            graph->vertice = getAllVertices(u, v);
            graph->V = getTotalSize_Vertices(graph->vertice);
            graph->edge = getAllEdges(u, v, weight, graph->E);
            graph = InitIndex(graph);

            // for(int i = 0; i < graph->E; i++) {
            //     printf("%d -> %d <%d>\n", graph->edge[i].u.index, graph->edge[i].v.index, graph->edge[i].weight);
            // }

            return graph;
        }
        //diffetent total rows of each header
        else{
            printf(RED "Error : The data does not match.\n" RESET);
            return NULL;
        }
    }
}

struct Edge *getAllEdges(Node *Initial_vertex_HEADER, Node *Terminal_vertex_HEADER, Node* weight_HEADER, int size) {
    struct Edge *edge = (struct Edge*)malloc(sizeof(struct Edge) * size);
    if (edge == NULL) {
        printf(RED "Error : Memory allocation failed\n" RESET);
        return NULL;
    }

    Adjacent_Node *u_adj, *v_adj, *w_adj;
    u_adj = Initial_vertex_HEADER->Head;
    v_adj = Terminal_vertex_HEADER->Head;
    w_adj = weight_HEADER->Head;

    int i = 0;
    while(u_adj != NULL && v_adj != NULL && w_adj != NULL) {
        strcpy(edge[i].u.label, u_adj->Data);
        strcpy(edge[i].v.label, v_adj->Data);
        edge[i].weight = atoi(w_adj->Data);

        u_adj = u_adj->Next;
        v_adj = v_adj->Next;
        w_adj = w_adj->Next;
        i++;
    }

    // for(int i = 0; i < size; i++) {
    //     printf("%s -> %s <%d>\n", edge[i].u.label, edge[i].v.label, edge[i].weight);
    // }

    return edge;
}

struct Graph *InitIndex(struct Graph *graph){
    for (int i = 0; i < graph->E; i++) {
        for(int j = 0; j < graph->V; j++) {
            if(!strcmp(graph->edge[i].u.label, graph->vertice[j].label)) { 
                graph->edge[i].u.index = graph->vertice[j].index;
            }
            if(!strcmp(graph->edge[i].v.label, graph->vertice[j].label)) { 
                graph->edge[i].v.index = graph->vertice[j].index;
            }
        }
    }
    return graph;
}

struct Vertice *getAllVertices(Node *Initial_vertex_HEADER, Node *Terminal_vertex_HEADER) {
    if (Initial_vertex_HEADER == NULL || Terminal_vertex_HEADER == NULL ) {
        printf(RED "Error : Memory allocation failed\n" RESET);
        return 0;
    }

    int unique_count = 0;
    Adjacent_Node *curr_adj_node;
    struct Vertice *unique_vertice = NULL;
    unique_vertice = malloc(MAX_VERTICES * sizeof(struct Vertice));
    if (unique_vertice == NULL) {
        printf(RED "Error : Memory allocation failed\n" RESET);
        return 0;
    }

    // Traverse the first linked list
    curr_adj_node = Initial_vertex_HEADER->Head;
    while (curr_adj_node != NULL) {
        if (isUnique(curr_adj_node->Data, unique_vertice, unique_count)) {
            strcpy(unique_vertice[unique_count].label, curr_adj_node->Data);
            unique_vertice[unique_count].index = unique_count;
            unique_count++;
        }
        curr_adj_node = curr_adj_node->Next;
    }

    // Traverse the second linked list
    curr_adj_node = Terminal_vertex_HEADER->Head;
    while (curr_adj_node != NULL) {
        if (isUnique(curr_adj_node->Data, unique_vertice, unique_count)) {
            strcpy(unique_vertice[unique_count].label, curr_adj_node->Data);
            unique_vertice[unique_count].index = unique_count;
            unique_count++;
        }
        curr_adj_node = curr_adj_node->Next;
    }
    
    unique_vertice = realloc(unique_vertice, unique_count * sizeof(struct Vertice));

    printf("%d point\n",unique_count);
    for(int i = 0 ; i< unique_count; i++){
        printf("%d. %s\n",unique_vertice[i].index , unique_vertice[i].label);
    }

    return unique_vertice;
}

// Function to check if data is already in the unique_data_set
bool isUnique(char* data, struct Vertice *unique_data_set, int unique_count) {
    for (int i = 0; i < unique_count; ++i) {
        if (strcmp(unique_data_set[i].label, data) == 0) {
            return false; // Data already exists, not unique
        }
    }
    return true; // Data is unique
}

int getTotalSize_Vertices(struct Vertice *arr){
    int size = 0;
    while (arr[size+1].index != 0) {
        size++;
    }
    // shitf 0 index
    return size+1;
}

int getTotalSize_Edges(Node *HEADER){
    // Check if head is NULL
    if (HEADER == NULL) {
        printf(RED "Error: Head node is NULL\n" RESET);
        return -1;
    }

    int size = 0;

    // Traverse the adjacency list
    Adjacent_Node *curr_adj_node = HEADER->Head;
    while (curr_adj_node != NULL) {
        size++;
        curr_adj_node = curr_adj_node->Next;
    }

    return size;
}

void bellmanford(struct Graph *g, char source[]) {
  //variables
  int i, j, u, v, w;
  // find a source index
  for(i = 0; i<g->V; i++){
    if(!(strcmp(source, g->vertice[i].label))){
        break;
    }
  }
  int Indexsource = i;
  //total vertex in the graph g
  int tV = g->V;

  //total edge in the graph g
  int tE = g->E;

  //distance array
  //size equal to the number of vertices of the graph g
  int d[tV];

  //predecessor array
  //size equal to the number of vertices of the graph g
  int p[tV];

  //step 1: fill the distance array and predecessor array
  for (i = 0; i < tV; i++) {
    d[i] = INFINITY;
    p[i] = 0;
  }

  //mark the source vertex
  d[Indexsource] = 0;

  //step 2: relax edges |V| - 1 times
  for (i = 1; i <= tV - 1; i++) {
    for (j = 0; j < tE; j++) {
      //get the edge data
      u = g->edge[j].u.index;
      v = g->edge[j].v.index;
      w = g->edge[j].weight;

      if (d[u] != INFINITY && d[v] > d[u] + w) {
        d[v] = d[u] + w;
        p[v] = u;
      }
    }
  }

  //step 3: detect negative cycle
  //if value changes then we have a negative cycle in the graph
  //and we cannot find the shortest distances
  for (i = 0; i < tE; i++) {
    u = g->edge[i].u.index;
    v = g->edge[i].v.index;
    w = g->edge[i].weight;
    if (d[u] != INFINITY && d[v] > d[u] + w) {
      printf(RED "Negative weight cycle detected!\n" RESET);
      return;
    }
  }

  //No negative weight cycle found!
  //print the distance and predecessor array
  printf(GREEN "\nAll shortest path from source: \n" RESET);
  display(d, p, tV, Indexsource, g->vertice);
}

void display(int dst[], int pre[], int size, int initial, struct Vertice *vertice) {
  int i;
  for (i = 0; i < size; i++) {
    if(i==initial || dst[i] == INFINITY){
      continue;
    }
    printf(GREEN "\n%s to %s distance = %d and check point is %s\n" RESET, 
    vertice[initial].label, vertice[i].label, 
    dst[i], vertice[pre[i]].label);
  }
  printf("\n");
}
