#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Function prototypes
Node* createNode(int value);
Node* insert(Node* node, int value);
int search(Node* node, int value);
int getSmallest(Node* node);
int getLargest(Node* node);
void inOrderTraversal(Node* node);
void preOrderTraversal(Node* node);
void postOrderTraversal(Node* node);
void levelOrderTraversal(Node* root);
void revOrderTraversal(Node* node);
void displayTreeLike(Node* root, int space);
int getHeight(Node* node);
int getNumNodes(Node* node);
int getNumLeaves(Node* node);
int isFull(Node* node);
Node* removeNode(Node* node, int value);
int checkInput(char* str);

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insert(Node* node, int value) {
    if (node == NULL) {
        return createNode(value);
    }
    if (value < node->data) {
        node->left = insert(node->left, value);
    } else if (value > node->data) {
        node->right = insert(node->right, value);
    }
    return node;
}

int search(Node* node, int value) {
    if (node == NULL) {
        return 0;
    }
    if (node->data == value) {
        return 1;
    } else if (value < node->data) {
        return search(node->left, value);
    } else {
        return search(node->right, value);
    }
}

void inOrderTraversal(Node* node) {
    if (node != NULL) {
        inOrderTraversal(node->left);
        printf("%d ", node->data);
        inOrderTraversal(node->right);
    }
}

void preOrderTraversal(Node* node) {
    if (node != NULL) {
        printf("%d ", node->data);
        preOrderTraversal(node->left);
        preOrderTraversal(node->right);
    }
}

void postOrderTraversal(Node* node) {
    if (node != NULL) {
        postOrderTraversal(node->left);
        postOrderTraversal(node->right);
        printf("%d ", node->data);
    }
}

void revOrderTraversal(Node* node) {
    if (node != NULL) {
        revOrderTraversal(node->right);
        printf("%d ", node->data);
        revOrderTraversal(node->left);
    }
}

void levelOrderTraversal(Node* root) {
    if (root == NULL) {
        return;
    }
    Node* queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = root;
    while (front < rear) {
        Node* current = queue[front++];
        printf("%d ", current->data);
        if (current->left != NULL) queue[rear++] = current->left;
        if (current->right != NULL) queue[rear++] = current->right;
    }
    printf("\n");
}

void displayTreeLike(Node* root, int space) {
    if (root == NULL) return;
    space += 10;
    displayTreeLike(root->right, space);
    printf("\n");
    for (int i = 10; i < space; i++) printf(" ");
    printf("%d\n", root->data);
    displayTreeLike(root->left, space);
}

int getHeight(Node* node) {
    if (node == NULL) {
        return -1;
    }
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int getNumNodes(Node* node) {
    if (node == NULL) {
        return 0;
    }
    return getNumNodes(node->left) + getNumNodes(node->right) + 1;
}

int getNumLeaves(Node* node) {
    if (node == NULL) {
        return 0;
    }
    if (node->left == NULL && node->right == NULL) {
        return 1;
    }
    return getNumLeaves(node->left) + getNumLeaves(node->right);
}

int isFull(Node* node) {
    if (node == NULL) {
        return 1;
    }
    if (node->left == NULL && node->right == NULL) {
        return 1;
    }
    if (node->left != NULL && node->right != NULL) {
        return isFull(node->left) && isFull(node->right);
    }
    return 0;
}

int getSmallest(Node* node) {
    if (node == NULL) {
        printf("The tree is empty.\n");
        return -1;
    }
    Node* current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current->data;
}

int getLargest(Node* node) {
    if (node == NULL) {
        printf("The tree is empty.\n");
        return -1;
    }
    Node* current = node;
    while (current->right != NULL) {
        current = current->right;
    }
    return current->data;
}

Node* removeNode(Node* node, int value) {
    if (node == NULL) {
        return node;
    }
    if (value < node->data) {
        node->left = removeNode(node->left, value);
    } else if (value > node->data) {
        node->right = removeNode(node->right, value);
    } else {
        if (node->left == NULL || node->right == NULL) {
            Node* temp = (node->left != NULL) ? node->left : node->right;
            if (temp == NULL) {
                temp = node;
                node = NULL;
            } else {
                *node = *temp;
            }
            free(temp);
        } else {
            Node* temp = node->right;
            while (temp && temp->left != NULL) temp = temp->left;
            node->data = temp->data;
            node->right = removeNode(node->right, temp->data);
        }
    }
    return node;
}

int checkInput(char* str) {
    int yes = 0, no = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == 'y' || str[i] == 'Y') yes++;
        if (str[i] == 'n' || str[i] == 'N') no++;
    }
    if (yes > 0 && no == 0) return 1;
    if (no > 0 && yes == 0) return 0;
    // Ambiguous or incorrect input
    printf("Input is unclear. Did you mean 'yes' (y/Y) or 'no' (n/N)? ");
    fgets(str, 256, stdin); // Read again using fgets to handle spaces and newlines
    return checkInput(str); // Recursively check the corrected input
}

int main() {
    Node* root = NULL;
    int num, value, count = 0;
    char input[256];

    printf("Enter the number of integers (up to 100): ");
    scanf("%d", &num);

    printf("Enter %d integers:\n", num);
    while (count < num) {
        int result = scanf("%d", &value);
        if (result == 1) {
            root = insert(root, value);
            count++;
        } else {
            printf("Invalid input detected, stopping input.\n");
            break;
        }
    }

    if (count < num) {
        printf("You have entered %d integers, but you need %d. Missing %d integers.\n", count, num, num - count);
        printf("Do you want to add the missing integers? (y/n): ");
        scanf("%s", input);
        int response = checkInput(input);
        if (response == 1) {
            printf("Enter the remaining %d integers:\n", num - count);
            while (count < num) {
                scanf("%d", &value);
                root = insert(root, value);
                count++;
            }
        }
    }

    printf("Tree structure:\n");
    displayTreeLike(root, 0);

    printf("In-order traversal: ");
    inOrderTraversal(root);
    printf("\n");

    printf("Pre-order traversal: ");
    preOrderTraversal(root);
    printf("\n");

    printf("Post-order traversal: ");
    postOrderTraversal(root);
    printf("\n");

    printf("Reverse-order traversal: ");
    revOrderTraversal(root);
    printf("\n");

    printf("Level-order traversal: ");
    levelOrderTraversal(root);
    printf("\n");

    printf("Height of the tree: %d\n", getHeight(root));
    printf("Number of nodes in the tree: %d\n", getNumNodes(root));
    printf("Number of leaf nodes in the tree: %d\n", getNumLeaves(root));
    printf("Largest node in the tree: %d\n", getLargest(root));
    printf("Smallest node in the tree: %d\n", getSmallest(root));
    printf("Is the tree full: %s\n", isFull(root) ? "Yes" : "No");

    char choice;
    do {
        printf("Do you want to look for an item in the tree? (y/n): ");
        scanf("%s", input);
        int searchResponse = checkInput(input);
        if (searchResponse == 1) {
            int searchValue;
            printf("Enter the value you want to search for: ");
            scanf("%d", &searchValue);
            if (search(root, searchValue)) {
                printf("%d is found in the tree.\n", searchValue);
            } else {
                printf("%d is not found in the tree.\n", searchValue);
            }
        }

        printf("Do you want to add anything to the tree? (y/n): ");
        scanf("%s", input);
        int addResponse = checkInput(input);
        if (addResponse == 1) {
            do {
                int addValue;
                printf("Enter the value you want to add: ");
                scanf("%d", &addValue);
                root = insert(root, addValue);
                printf("Value %d added to the tree.\n", addValue);
                printf("Updated tree:\n");
                displayTreeLike(root, 0);

                printf("Do you want to add more? (y/n): ");
                scanf("%s", input);
                addResponse = checkInput(input);
            } while (addResponse == 1);
        }

        printf("Do you want to remove anything from the tree? (y/n): ");
        scanf("%s", input);
        int removeResponse = checkInput(input);
        if (removeResponse == 1) {
            int removeValue;
            printf("Enter the value you want to remove: ");
            scanf("%d", &removeValue);
            root = removeNode(root, removeValue);
            printf("Value %d removed from the tree.\n", removeValue);
            printf("Updated tree:\n");
            displayTreeLike(root, 0);
        }

        printf("Do you want to perform more actions? (y/n): ");
        scanf("%s", input);
        choice = checkInput(input);
    } while (choice == 1);

    return 0;
}
