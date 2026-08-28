#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GRID_SIZE 10
#define BATTERY_MOVE_COST 2
#define BATTERY_SCAN_COST 5
#define BATTERY_LOW_WARNING 30
#define TARGET_X 9
#define TARGET_Y 9

// Structure to store rover data
struct Rover {
    int x;           // X coordinate (column)
    int y;           // Y coordinate (row)
    int battery;     // Battery percentage
    int distance;    // Total distance travelled
};

// ============================================
// HELPER FUNCTIONS
// ============================================

// Initialize the map with obstacles
void initializeMap(char map[GRID_SIZE][GRID_SIZE]) {
    int row, col;
    
    for (row = 0; row < GRID_SIZE; row++) {
        for (col = 0; col < GRID_SIZE; col++) {
            map[row][col] = '.';
        }
    }
    
    // Place 5 fixed obstacles
    map[2][2] = 'X';
    map[2][3] = 'X';
    map[3][2] = 'X';
    map[5][5] = 'X';
    map[7][8] = 'X';
}

// Check if a position has an obstacle
int isObstacle(char map[GRID_SIZE][GRID_SIZE], int x, int y) {
    return map[y][x] == 'X';
}

// Check if rover reached the target
int reachedTarget(struct Rover rover) {
    return (rover.x == TARGET_X && rover.y == TARGET_Y);
}

// Calculate Manhattan distance to target
int distanceToTarget(struct Rover rover) {
    int dx = TARGET_X - rover.x;
    int dy = TARGET_Y - rover.y;
    
    if (dx < 0) dx = -dx;
    if (dy < 0) dy = -dy;
    
    return dx + dy;
}

// Check battery and print warnings
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

// ============================================
// DISPLAY FUNCTIONS
// ============================================

// Display the main menu
void displayMenu() {
    printf("\n========== MARS ROVER MISSION ==========\n");
    printf("1. Move North\n");
    printf("2. Move South\n");
    printf("3. Move East\n");
    printf("4. Move West\n");
    printf("5. Display Map\n");
    printf("6. Scan Area\n");
    printf("7. Show Rover Status\n");
    printf("8. Check Mission Status\n");
    printf("9. Exit\n");
    printf("========================================\n");
    printf("Enter your choice (1-9): ");
}

// Display the 10x10 map grid
void displayMap(struct Rover rover, char map[GRID_SIZE][GRID_SIZE]) {
    int row, col;
    
    printf("\n========== MARS MAP ==========\n");
    printf("Legend: R=Rover, T=Target, X=Obstacle, .=Empty\n\n");
    
    // Print column headers
    printf("   ");
    for (col = 0; col < GRID_SIZE; col++) {
        printf("%d ", col);
    }
    printf("\n");
    
    // Print each row
    for (row = 0; row < GRID_SIZE; row++) {
        printf("%d: ", row);
        
        for (col = 0; col < GRID_SIZE; col++) {
            if (rover.x == col && rover.y == row) {
                printf("R ");
            } else if (col == TARGET_X && row == TARGET_Y) {
                printf("T ");
            } else {
                printf("%c ", map[row][col]);
            }
        }
        printf("\n");
    }
    printf("==============================\n");
}

// Display rover's current status
void displayStatus(struct Rover rover) {
    printf("\n--- ROVER STATUS ---\n");
    printf("Position: (%d, %d)\n", rover.x, rover.y);
    printf("Battery: %d%%\n", rover.battery);
    printf("Distance Travelled: %d units\n", rover.distance);
    printf("Target Position: (%d, %d)\n", TARGET_X, TARGET_Y);
    printf("-------------------\n");
    
    checkBattery(rover);
}

// Display mission status and progress
void checkMission(struct Rover rover) {
    int dist_to_target;
    
    printf("\n========== MISSION STATUS ==========\n");
    printf("Current Position: (%d, %d)\n", rover.x, rover.y);
    printf("Target Position: (%d, %d)\n", TARGET_X, TARGET_Y);
    
    if (reachedTarget(rover)) {
        printf("\n*** MISSION COMPLETE! ***\n");
        printf("Target reached!\n");
        printf("Total distance travelled: %d units\n", rover.distance);
        printf("Battery remaining: %d%%\n", rover.battery);
    } else {
        dist_to_target = distanceToTarget(rover);
        printf("Distance to target: %d units\n", dist_to_target);
        printf("Total distance travelled: %d units\n", rover.distance);
        printf("Battery: %d%%\n", rover.battery);
    }
    
    printf("===================================\n");
}

// ============================================
// ACTION FUNCTIONS
// ============================================

// Scan the area and get random sensor data
void scanArea(struct Rover *rover) {
    int temperature;
    int terrain_type;
    int rocks_detected;
    
    if (rover->battery < BATTERY_SCAN_COST) {
        printf("Not enough battery to scan! Need %d%%, have %d%%\n", 
               BATTERY_SCAN_COST, rover->battery);
        return;
    }
    
    printf("\n========== SCANNING AREA ==========\n");
    printf("Location: (%d, %d)\n", rover->x, rover->y);
    
    // Generate random data
    temperature = 50 + rand() % 60;
    terrain_type = rand() % 3;
    rocks_detected = rand() % 5;
    
    printf("Temperature: %d°C\n", temperature);
    
    printf("Terrain: ");
    if (terrain_type == 0) {
        printf("Rocky\n");
    } else if (terrain_type == 1) {
        printf("Sandy\n");
    } else {
        printf("Mixed\n");
    }
    
    printf("Rocks Detected: %d\n", rocks_detected);
    printf("===================================\n");
    
    rover->battery = rover->battery - BATTERY_SCAN_COST;
    printf("Scan completed! Battery reduced by %d%%\n", BATTERY_SCAN_COST);
    
    checkBattery(*rover);
}

// Move rover North (up, decrease Y)
void moveNorth(struct Rover *rover, char map[GRID_SIZE][GRID_SIZE]) {
    if (rover->battery <= 0) {
        printf("Cannot move! Battery is depleted.\n");
        return;
    }
    
    int newY = rover->y - 1;
    
    if (newY < 0) {
        printf("Cannot move North! Already at the northern edge.\n");
        return;
    }
    
    if (isObstacle(map, rover->x, newY)) {
        printf("Obstacle detected! Movement cancelled.\n");
        return;
    }
    
    rover->y = newY;
    rover->battery = rover->battery - BATTERY_MOVE_COST;
    rover->distance = rover->distance + 1;
    printf("Rover moved North!\n");
    
    if (reachedTarget(*rover)) {
        printf("\n*** TARGET REACHED! ***\n");
        printf("Mission accomplished!\n\n");
    }
    
    checkBattery(*rover);
}

// Move rover South (down, increase Y)
void moveSouth(struct Rover *rover, char map[GRID_SIZE][GRID_SIZE]) {
    if (rover->battery <= 0) {
        printf("Cannot move! Battery is depleted.\n");
        return;
    }
    
    int newY = rover->y + 1;
    
    if (newY >= GRID_SIZE) {
        printf("Cannot move South! Already at the southern edge.\n");
        return;
    }
    
    if (isObstacle(map, rover->x, newY)) {
        printf("Obstacle detected! Movement cancelled.\n");
        return;
    }
    
    rover->y = newY;
    rover->battery = rover->battery - BATTERY_MOVE_COST;
    rover->distance = rover->distance + 1;
    printf("Rover moved South!\n");
    
    if (reachedTarget(*rover)) {
        printf("\n*** TARGET REACHED! ***\n");
        printf("Mission accomplished!\n\n");
    }
    
    checkBattery(*rover);
}

// Move rover East (right, increase X)
void moveEast(struct Rover *rover, char map[GRID_SIZE][GRID_SIZE]) {
    if (rover->battery <= 0) {
        printf("Cannot move! Battery is depleted.\n");
        return;
    }
    
    int newX = rover->x + 1;
    
    if (newX >= GRID_SIZE) {
        printf("Cannot move East! Already at the eastern edge.\n");
        return;
    }
    
    if (isObstacle(map, newX, rover->y)) {
        printf("Obstacle detected! Movement cancelled.\n");
        return;
    }
    
    rover->x = newX;
    rover->battery = rover->battery - BATTERY_MOVE_COST;
    rover->distance = rover->distance + 1;
    printf("Rover moved East!\n");
    
    if (reachedTarget(*rover)) {
        printf("\n*** TARGET REACHED! ***\n");
        printf("Mission accomplished!\n\n");
    }
    
    checkBattery(*rover);
}

// Move rover West (left, decrease X)
void moveWest(struct Rover *rover, char map[GRID_SIZE][GRID_SIZE]) {
    if (rover->battery <= 0) {
        printf("Cannot move! Battery is depleted.\n");
        return;
    }
    
    int newX = rover->x - 1;
    
    if (newX < 0) {
        printf("Cannot move West! Already at the western edge.\n");
        return;
    }
    
    if (isObstacle(map, newX, rover->y)) {
        printf("Obstacle detected! Movement cancelled.\n");
        return;
    }
    
    rover->x = newX;
    rover->battery = rover->battery - BATTERY_MOVE_COST;
    rover->distance = rover->distance + 1;
    printf("Rover moved West!\n");
    
    if (reachedTarget(*rover)) {
        printf("\n*** TARGET REACHED! ***\n");
        printf("Mission accomplished!\n\n");
    }
    
    checkBattery(*rover);
}

// ============================================
// MAIN PROGRAM
// ============================================

int main() {
    srand(time(0));
    
    char map[GRID_SIZE][GRID_SIZE];
    initializeMap(map);
    
    struct Rover rover;
    rover.x = 0;
    rover.y = 0;
    rover.battery = 100;
    rover.distance = 0;

    int choice;
    int running = 1;

    printf("========================================\n");
    printf("Welcome to Mars Rover Mission Simulator!\n");
    printf("========================================\n");
    printf("Starting position: (0, 0)\n");
    printf("Target position: (%d, %d)\n", TARGET_X, TARGET_Y);
    printf("Starting battery: %d%%\n\n", rover.battery);

    while (running) {
        displayMenu();
        scanf("%d", &choice);

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
                scanArea(&rover);
                break;
            case 7:
                displayStatus(rover);
                break;
            case 8:
                checkMission(rover);
                break;
            case 9:
                printf("\n========================================\n");
                printf("Exiting mission. Goodbye!\n");
                printf("========================================\n\n");
                running = 0;
                break;
            default:
                printf("Invalid choice! Please enter a number between 1 and 9.\n");
        }
    }

    return 0;
}
