
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NUM_BARS 75
#define MAX_HEIGHT 15

#define W 71
#define H 31

#define WIDTH 61
#define HEIGHT 31

#define WALL 219
#define PATH ' '

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

int maze[HEIGHT][WIDTH];

//kruskal
void initialize_Maze();
void print_Maze();
bool isValid_Move(int row, int col);
bool generate_Maze(int row, int col);

void initialize_Maze() {
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            maze[row][col] = WALL;
        }
    }
}

void print_Maze() {
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            printf("%c", maze[row][col]);
        }
        printf("\n");
    }
}

bool isValid_Move(int row, int col) {
    return (row >= 1 && row < HEIGHT - 1 && col >= 1 && col < WIDTH - 1 && maze[row][col] == WALL);
}

bool generate_Maze(int row, int col) {
    maze[row][col] = PATH;

    // Array to shuffle directions
    int directions[4] = {NORTH, EAST, SOUTH, WEST};
    for (int i = 0; i < 4; i++) {
        int randomIndex = rand() % 4;
        int temp = directions[i];
        directions[i] = directions[randomIndex];
        directions[randomIndex] = temp;
    }

    for (int i = 0; i < 4; i++) {
        int newRow = row, newCol = col;
        switch (directions[i]) {
            case NORTH:
                newRow -= 2;
                break;
            case EAST:
                newCol += 2;
                break;
            case SOUTH:
                newRow += 2;
                break;
            case WEST:
                newCol -= 2;
                break;
        }

        if (isValid_Move(newRow, newCol)) {
            maze[newRow][newCol] = PATH;
            maze[(newRow + row) / 2][(newCol + col) / 2] = PATH;

            if (generate_Maze(newRow, newCol)) {
                return true;
            }
        }
    }

    return false;
}

void printKruskal(){
	srand(time(NULL));
    initialize_Maze();
    generate_Maze(1, 1);
    print_Maze();
}

//backtracking maze
void initializeMaze();
void printMaze();
bool isValidMove(int row, int col);
bool generateMaze(int row, int col);

void initializeMaze() {
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            maze[row][col] = WALL;
        }
    }
}

void printMaze() {
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            printf("%c", maze[row][col]);
        }
        printf("\n");
    }
}

bool isValidMove(int row, int col) {
    return (row >= 1 && row < HEIGHT - 1 && col >= 1 && col < WIDTH - 1 && maze[row][col] == WALL);
}

bool generateMaze(int row, int col) {
    maze[row][col] = PATH;

    // Array to shuffle directions
    int directions[4] = {NORTH, EAST, SOUTH, WEST};
    for (int i = 0; i < 4; i++) {
        int randomIndex = rand() % 4;
        int temp = directions[i];
        directions[i] = directions[randomIndex];
        directions[randomIndex] = temp;
    }

    for (int i = 0; i < 4; i++) {
        int newRow = row, newCol = col;
        switch (directions[i]) {
            case NORTH:
                newRow -= 2;
                break;
            case EAST:
                newCol += 2;
                break;
            case SOUTH:
                newRow += 2;
                break;
            case WEST:
                newCol -= 2;
                break;
        }

        if (isValidMove(newRow, newCol)) {
            maze[newRow][newCol] = PATH;
            maze[(newRow + row) / 2][(newCol + col) / 2] = PATH;

            if (generateMaze(newRow, newCol)) {
                return true;
            }
        }
    }

    return false;
}

void printBacktracking(){
	srand(time(NULL));
    initializeMaze();
    generateMaze(1, 1);
    printMaze();
}

//prim maze
struct Node {
    int x, y;
};

int dirX[] = {0, 2, 0, -2};
int dirY[] = {-2, 0, 2, 0};

char map[H + 1][W + 1];

void initMap() {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            map[i][j] = 219;
        }
    }
}

void printMap() {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            printf("%c", map[i][j]);
        }
        puts("");
    }
}

void prim() {
    struct Node {
        int x, y;
    };

    struct Node open[H * W];
    int openSize = 0;
    bool visited[H][W];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            visited[i][j] = false;
        }
    }

    open[openSize].x = 1;
    open[openSize].y = 1;
    openSize++;

    bool first = true;
    while (openSize > 0) {
        struct Node curr = open[0];
        for (int i = 1; i < openSize; i++) {
            open[i - 1] = open[i];
        }
        openSize--;

        if (visited[curr.y][curr.x]) continue;
        visited[curr.y][curr.x] = true;

        map[curr.y][curr.x] = ' ';

        int randNeighbor;
        bool valid = true;

        if (first) {
            first = false;
        } else {
            do {
                randNeighbor = rand() % 4;

                valid = curr.x - dirX[randNeighbor] >= 0 &&
                        curr.x - dirX[randNeighbor] < W &&
                        curr.y - dirY[randNeighbor] >= 0 &&
                        curr.y - dirY[randNeighbor] < H &&
                        map[curr.y - dirY[randNeighbor]][curr.x - dirX[randNeighbor]] == ' ';
            } while (!valid);
            map[curr.y - (dirY[randNeighbor] / 2)][curr.x - (dirX[randNeighbor] / 2)] = ' ';
        }

        for (int i = 0; i < 4; i++) {
            if (curr.x - dirX[i] >= 0 && curr.x - dirX[i] < W && curr.y - dirY[i] >= 0 && curr.y - dirY[i] < H) {
                open[openSize].x = curr.x - dirX[i];
                open[openSize].y = curr.y - dirY[i];
                openSize++;
            }
        }
    }
}

void printPrim() {
    srand(time(NULL));
    initMap();

    prim();
    printMap();
}
void generateBars(int heights[], int numBars) {
    
    for (int i = 0; i < numBars; i++) {
        heights[i] = rand() % MAX_HEIGHT + 1;
    }
}

void animateBars(int heights[], int numBars, int animationDelay) {
   
    int max_height = 0;
    for (int i = 0; i < numBars; i++) {
        if (heights[i] > max_height) {
            max_height = heights[i];
        }
    }

   
    for (int h = max_height; h >= 1; h--) {
        for (int i = 0; i < numBars; i++) {
            printf("%c", (heights[i] >= h) ? 219 : ' ');
        }
        printf("\n");

        
        usleep(animationDelay);
    }
}

void generateBars(){
	int barHeights[NUM_BARS];
    int animationDelay = 100000; 

    
    srand((unsigned int)time(NULL));

    generateBars(barHeights, NUM_BARS);
    animateBars(barHeights, NUM_BARS, animationDelay);
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}


void quickSortResult(){
	int barHeights[NUM_BARS];
    int animationDelay = 100000; 


    srand((unsigned int)time(NULL));

    generateBars(barHeights, NUM_BARS);

   
    quicksort(barHeights, 0, NUM_BARS - 1);

    
    animateBars(barHeights, NUM_BARS, animationDelay);
}

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void mergeSortResult(){
	int barHeights[NUM_BARS];
    int animationDelay = 100000; 

    
    srand((unsigned int)time(NULL));

    generateBars(barHeights, NUM_BARS);

    
    mergeSort(barHeights, 0, NUM_BARS - 1);

    
    animateBars(barHeights, NUM_BARS, animationDelay);
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

void heapSortResult(){
	int barHeights[NUM_BARS];
    int animationDelay = 100000; 

    srand((unsigned int)time(NULL));

    generateBars(barHeights, NUM_BARS);

    heapSort(barHeights, NUM_BARS);

    animateBars(barHeights, NUM_BARS, animationDelay);
	
}

void sandbox(){
	
}

void mainMenu(){
	
	printf("KCVisualizer\n");
	printf("======================\n");
	printf("1. Sorting\n");
	printf("2. Maze Solving\n");
	printf("3. Sandbox\n");
	printf("4. Exit\n");

}

void sorting(){
	int chooseSort;
	generateBars();
	printf("1. Quick Sort\n");
	printf("2. Merge Sort\n");
	printf("3. Heap Sort\n");
	printf("4. Back\n");
	scanf("%d", &chooseSort);
	
	switch(chooseSort){
		case 1:
			quickSortResult();
			sorting();
			break;
		case 2:
			mergeSortResult();
			
			sorting();
			break;
		case 3:
			heapSortResult();
			
			sorting();
			break;
		case 4:
			mainMenu();
			break;
	}
	
	
}

void mazeSolving(){
	int maze;
	printf("Maze Solving\n");
	printf("==================\n");
	printf("1. Backtracking\n");
	printf("2. Prim\n");
	printf("3. Kruskal\n");
	printf("4. Back\n");
	
	scanf("%d", &maze);
	
	switch(maze){
		case 1:
			printBacktracking();
		
			mazeSolving();
			break;
		case 2:
			printPrim();
		
			mazeSolving();
			break;
		case 3:
			printKruskal();
			
			mazeSolving();
			break;
		case 4:
			mainMenu();
			break;
	
	}
	
}

int main(){
	
	mainMenu();
	int menu;
	scanf("%d", &menu);
		switch(menu){
		case 1:
			sorting();
			break;
		case 2:
			mazeSolving();
			break;
		case 3:
			sandbox();
			break;
		case 4:
			break;
	}
	return 0;
}
