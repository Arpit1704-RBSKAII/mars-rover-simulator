#include <stdio.h>

#define GRID_SIZE 10
#define BATTERY_MOVE_COST 2
#define BATTERY_SCAN_COST 5
#define BATTERY_LOW_WARNING 30

// Structure to store rover data
struct Rover {
    int x;           // X coordinate (column)
    int y;           // Y coordinate (row)
    int battery;     // Battery percentage
    int distance;    // Total distance travelled
};

// Function to initialize the map with obstacles
void initializeMap(char map[GRID_SIZE][GRID_SIZE]) {
    int row, col;
    
    // First, fill the entire map with empty spaces
    for (row = 0; row < GRID_SIZE; row++) {
        for (col = 0; col < GRID_SIZE; col++) {
            map[row][col] = '.';
        }
    }
    
    // Now place fixed obstacles at specific positions
    map[2][2] = 'X';   // Obstacle at (2,2)
    map[2][3] = 'X';   // Obstacle at (3,2)
    map[3][2] = 'X';   // Obstacle at (2,3)
    map[5][5] = 'X';   // Obstacle at (5,5)
    map[7][8] = 'X';   // Obstacle at (8,7)
}

// Function to check if a position has an obstacle
int isObstacle(char map[GRID_SIZE][GRID_SIZE], int x, int y) {
    if (map[y][x] == 'X') {
        return 1;  // Yes, there is an obstacle (return 1 for TRUE)
    } else {
        return 0;  // No obstacle (return 0 for FALSE)
    }
}

// Function to check battery level and print warning if low
void checkBattery(struct Rover rover) {
    if (rover.battery <= 0) {
        printf("\n!!! CRITICAL: BATTERY DEPLETED !!!\n");
        printf("The rover cannot move without battery power!\n\n");
    } else if (rover.battery < BATTERY_LOW_WARNING) {
        printf("\n*** WARNING: BATTERY LOW ***\n");
        printf("Current battery: %d%%\n", rover.battery);
        printf("Recommended to conserve power!\n\n");
    }
}

// Function to display the menu
void displayMenu() {
    printf("\n========== MARS ROVER MISSION ==========\n");
    printf("1. Move North\n");
    printf("2. Move South\n");
    printf("3. Move East\n");
    printf("4. Move West\n");
    printf("5. Display Map\n");
    printf("6. Show Rover Status\n");
    printf("7. Exit\n");
    printf("========================================\n");
    printf("Enter your choice (1-7): ");
}

// Function to display the 10x10 map
void displayMap(struct Rover rover, char map[GRID_SIZE][GRID_SIZE]) {
    int row, col;
    
    printf("\n========== MARS MAP ==========\n");
    printf("Legend: R=Rover, T=Target, X=Obstacle, .=Empty\n\n");
    
    // Print column numbers at top
    printf("   ");  // Space for row labels
    for (col = 0; col < GRID_SIZE; col++) {
        printf("%d ", col);
    }
    printf("\n");
    
    // Print each row
    for (row = 0; row < GRID_SIZE; row++) {
        printf("%d: ", row);  // Row label
        
        for (col = 0; col < GRID_SIZE; col++) {
            // Check what should be at this position
            if (rover.x == col && rover.y == row) {
                printf("R ");  // R for Rover
            } else if (col == 9 && row == 9) {
                printf("T ");  // T for Target
            } else {
                printf("%c ", map[row][col]);  // Print whatever is on the map
            }
        }
        printf("\n");
    }
    printf("==============================\n");
}

// Function to display rover's current status
void displayStatus(struct Rover rover) {
    printf("\n--- ROVER STATUS ---\n");
    printf("Position: (%d, %d)\n", rover.x, rover.y);
    printf("Battery: %d%%\n", rover.battery);
    printf("Distance Travelled: %d units\n", rover.distance);
    printf("Target Position: (9, 9)\n");
    printf("-------------------\n");
    
    // Check battery after displaying status
    checkBattery(rover);
}

// Function to move rover North (decrease Y)
void moveNorth(struct Rover *rover, char map[GRID_SIZE][GRID_SIZE]) {
    // Check if rover has battery
    if (rover->battery <= 0) {
        printf("Cannot move! Battery is depleted.\n");
        return;
    }
    
    int newY = rover->y - 1;
    
    // Check if rover can move north (not at top edge)
    if (newY < 0) {
        printf("Cannot move North! Already at the northern edge.\n");
        return;
    }
    
    // Check if there is an obstacle in the way
    if (isObstacle(map, rover->x, newY)) {
        printf("Obstacle detected! Movement cancelled.\n");
        return;
    }
    
    // Movement is valid
    rover->y = newY;
    rover->battery = rover->battery - BATTERY_MOVE_COST;
    rover->distance = rover->distance + 1;
    printf("Rover moved North!\n");
    
    // Check battery after movement
    checkBattery(*rover);
}

// Function to move rover South (increase Y)
void moveSouth(struct Rover *rover, char map[GRID_SIZE][GRID_SIZE]) {
    // Check if rover has battery
    if (rover->battery <= 0) {
        printf("Cannot move! Battery is depleted.\n");
        return;
    }
    
    int newY = rover->y + 1;
    
    // Check if rover can move south (not at bottom edge)
    if (newY >= GRID_SIZE) {
        printf("Cannot move South! Already at the southern edge.\n");
        return;
    }
    
    // Check if there is an obstacle in the way
    if (isObstacle(map, rover->x, newY)) {
        printf("Obstacle detected! Movement cancelled.\n");
        return;
    }
    
    // Movement is valid
    rover->y = newY;
    rover->battery = rover->battery - BATTERY_MOVE_COST;
    rover->distance = rover->distance + 1;
    printf("Rover moved South!\n");
    
    // Check battery after movement
    checkBattery(*rover);
}

// Function to move rover East (increase X)
void moveEast(struct Rover *rover, char map[GRID_SIZE][GRID_SIZE]) {
    // Check if rover has battery
    if (rover->battery <= 0) {
        printf("Cannot move! Battery is depleted.\n");
        return;
    }
    
    int newX = rover->x + 1;
    
    // Check if rover can move east (not at right edge)
    if (newX >= GRID_SIZE) {
        printf("Cannot move East! Already at the eastern edge.\n");
        return;
    }
    
    // Check if there is an obstacle in the way
    if (isObstacle(map, newX, rover->y)) {
        printf("Obstacle detected! Movement cancelled.\n");
        return;
    }
    
    // Movement is valid
    rover->x = newX;
    rover->battery = rover->battery - BATTERY_MOVE_COST;
    rover->distance = rover->distance + 1;
    printf("Rover moved East!\n");
    
    // Check battery after movement
    checkBattery(*rover);
}

// Function to move rover West (decrease X)
void moveWest(struct Rover *rover, char map[GRID_SIZE][GRID_SIZE]) {
    // Check if rover has battery
    if (rover->battery <= 0) {
        printf("Cannot move! Battery is depleted.\n");
        return;
    }
    
    int newX = rover->x - 1;
    
    // Check if rover can move west (not at left edge)
    if (newX < 0) {
        printf("Cannot move West! Already at the western edge.\n");
        return;
    }
    
    // Check if there is an obstacle in the way
    if (isObstacle(map, newX, rover->y)) {
        printf("Obstacle detected! Movement cancelled.\n");
        return;
    }
    
    // Movement is valid
    rover->x = newX;
    rover->battery = rover->battery - BATTERY_MOVE_COST;
    rover->distance = rover->distance + 1;
    printf("Rover moved West!\n");
    
    // Check battery after movement
    checkBattery(*rover);
}

// Main program
int main() {
    // Create a map (2D array)
    char map[GRID_SIZE][GRID_SIZE];
    
    // Initialize the map with obstacles
    initializeMap(map);
    
    // Create a rover and initialize it
    struct Rover rover;
    rover.x = 0;
    rover.y = 0;
    rover.battery = 100;
    rover.distance = 0;

    int choice;
    int running = 1;  // Flag to control the game loop

    printf("Welcome to Mars Rover Mission Simulator!\n");
    printf("Starting position: (0, 0)\n");
    printf("Target position: (9, 9)\n");
    printf("Starting battery: %d%%\n\n", rover.battery);

    // Main game loop
    while (running) {
        displayMenu();
        scanf("%d", &choice);

        // Use switch to handle menu choices
        switch (choice) {
            case 1:
                moveNorth(&rover, map);
                break;
            case 2:
                moveSouth(&rover, map);
                break;
            case 3:
                moveEast(&rover, map);
                break;
            case 4:
                moveWest(&rover, map);
                break;
            case 5:
                displayMap(rover, map);
                break;
            case 6:
                displayStatus(rover);
                break;
            case 7:
                printf("Exiting mission. Goodbye!\n");
                running = 0;  // Exit the loop
                break;
            default:
                printf("Invalid choice! Please enter a number between 1 and 7.\n");
        }
    }

    return 0;
}
