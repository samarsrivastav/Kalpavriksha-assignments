#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    int age;
} User;

void createFile() {
    FILE *file = fopen("users.txt", "w");
    if (file == NULL) {
        printf("Error creating file.\n");
        return;
    }
    fclose(file);
}

void addUser() {
    FILE *file = fopen("users.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    User user;
    printf("Enter user ID: ");
    scanf("%d", &user.id);
    printf("Enter user name: ");
    getchar(); 
    fgets(user.name, sizeof(user.name), stdin);
    user.name[strcspn(user.name, "\n")] = '\0';  
    printf("Enter user age: ");
    scanf("%d", &user.age);

    fprintf(file, "%d,%s,%d\n", user.id, user.name, user.age);
    fclose(file);
}

void displayUsers() {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    User user;
    printf("ID\tName\tAge\n");
    while (fscanf(file, "%d,%49[^,],%d\n", &user.id, user.name, &user.age) != EOF) {
        printf("%d\t%s\t%d\n", user.id, user.name, user.age);
    }
    fclose(file);
}

void updateUser(int id) {
     FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }

    User user;
    int found = 0;
    while (fscanf(file, "%d,%49[^,],%d\n", &user.id, user.name, &user.age) != EOF) {
        if (user.id == id) {
            found = 1;
            printf("Enter user ID: ");
            scanf("%d", &user.id);
            printf("Enter user name: ");
            getchar(); 
            fgets(user.name, sizeof(user.name), stdin);
            user.name[strcspn(user.name, "\n")] = '\0';  
            printf("Enter user age: ");
            scanf("%d", &user.age);
        }
        fprintf(tempFile, "%d,%s,%d\n", user.id, user.name, user.age);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("users.txt");
        rename("temp.txt", "users.txt");
        printf("User deleted successfully.\n");
    } else {
        printf("User not found.\n");
    }
}

void deleteUser(int id) {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }

    User user;
    int found = 0;
    while (fscanf(file, "%d,%49[^,],%d\n", &user.id, user.name, &user.age) != EOF) {
        if (user.id == id) {
            found = 1;
            continue; 
        }
        fprintf(tempFile, "%d,%s,%d\n", user.id, user.name, user.age);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("users.txt");
        rename("temp.txt", "users.txt");
        printf("User deleted successfully.\n");
    } else {
        printf("User not found.\n");
    }
}

int main() {
    int choice, id;
    createFile(); 

    while (1) {
        printf("\n1. Add User\n2. Display Users\n3. Update User\n4. Delete User\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addUser();
                break;
            case 2:
                displayUsers();
                break;
            case 3:
                printf("Enter user ID to update: ");
                scanf("%d", &id);
                updateUser(id);
                break;
            case 4:
                printf("Enter user ID to delete: ");
                scanf("%d", &id);
                deleteUser(id);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
