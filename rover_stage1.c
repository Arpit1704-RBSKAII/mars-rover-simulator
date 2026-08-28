#include <stdio.h>

// Structure to store rover data
struct Rover {
    int x;           // X coordinate (column)
    int y;           // Y coordinate (row)
    int battery;     // Battery percentage
    int distance;    // Total distance travelled
};

// Function to display the menu
void displayMenu() {
    printf("\n========== MARS ROVER MISSION ==========\n");
    printf("1. Move North\n");
    printf("2. Move South\n");
    printf("3. Move East\n");
    printf("4. Move West\n");
    printf("5. Show Rover Status\n");
    printf("6. Exit\n");
    printf("========================================\n");
    printf("Enter your choice (1-6): ");
}

// Function to display rover's current status
void displayStatus(struct Rover rover) {
    printf("\n--- ROVER STATUS ---\n");
    printf("Position: (%d, %d)\n", rover.x, rover.y);
    printf("Battery: %d%%\n", rover.battery);
    printf("Distance Travelled: %d units\n", rover.distance);
    printf("-------------------\n");
}

// Function to move rover North (decrease Y)
void moveNorth(struct Rover *rover) {
    // Check if rover can move north (not at top edge, y > 0)
    if (rover->y > 0) {
        rover->y = rover->y - 1;
        rover->battery = rover->battery - 2;
        rover->distance = rover->distance + 1;
        printf("Rover moved North!\n");
    } else {
        printf("Cannot move North! Already at the northern edge.\n");
    }
}

// Function to move rover South (increase Y)
void moveSouth(struct Rover *rover) {
    // Check if rover can move south (not at bottom edge, y < 9)
    if (rover->y < 9) {
        rover->y = rover->y + 1;
        rover->battery = rover->battery - 2;
        rover->distance = rover->distance + 1;
        printf("Rover moved South!\n");
    } else {
        printf("Cannot move South! Already at the southern edge.\n");
    }
}

// Function to move rover East (increase X)
void moveEast(struct Rover *rover) {
    // Check if rover can move east (not at right edge, x < 9)
    if (rover->x < 9) {
        rover->x = rover->x + 1;
        rover->battery = rover->battery - 2;
        rover->distance = rover->distance + 1;
        printf("Rover moved East!\n");
    } else {
        printf("Cannot move East! Already at the eastern edge.\n");
    }
}

// Function to move rover West (decrease X)
void moveWest(struct Rover *rover) {
    // Check if rover can move west (not at left edge, x > 0)
    if (rover->x > 0) {
        rover->x = rover->x - 1;
        rover->battery = rover->battery - 2;
        rover->distance = rover->distance + 1;
        printf("Rover moved West!\n");
    } else {
        printf("Cannot move West! Already at the western edge.\n");
    }
}

// Main program
int main() {
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

    // Main game loop
    while (running) {
        displayMenu();
        scanf("%d", &choice);

        // Use switch to handle menu choices
        switch (choice) {
            case 1:
                moveNorth(&rover);
                break;
            case 2:
                moveSouth(&rover);
                break;
            case 3:
                moveEast(&rover);
                break;
            case 4:
                moveWest(&rover);
                break;
            case 5:
                displayStatus(rover);
                break;
            case 6:
                printf("Exiting mission. Goodbye!\n");
                running = 0;  // Exit the loop
                break;
            default:
                printf("Invalid choice! Please enter a number between 1 and 6.\n");
        }
    }

    return 0;
}
