#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#define MAX_STRING_LENGTH 999
#define MAX_NUMBER_LENGTH 100

#define TRUE  1
#define FALSE 0

#define INPUT_FILE_NAME "D:/input.txt"
#define OUTPUT_FILE_NAME "D:/output123.txt"

typedef enum ColorType {RED, BLACK} ColorType;
typedef struct node {
	int key;
	ColorType color;
	struct node* p;
	struct node* left;
	struct node* right;
} node;

node* root = NULL;
node* nil  = NULL;

node* create_Node(int key, ColorType color) {
	node* new_Node = (node*)(malloc(sizeof(node)));
	new_Node -> key   = key;
	new_Node -> color = color;
	new_Node -> p     = nil;
	new_Node -> left  = nil;
	new_Node -> right = nil;
	return new_Node;
}

void left_Rotate(node* x) {
	node* y = x -> right;

	x -> right = y -> left;

	if(y -> left != nil)
		y -> left -> p = x;
	y -> p = x -> p;

	if(x -> p == nil)
		root = y;
	else if(x == x -> p -> left)
		x -> p -> left = y;
	else
		x -> p -> right = y;

	y -> left = x;
	x -> p = y;
}

void right_Rotate(node* x) {
	node* y = x -> left;

	x -> left = y -> right;

	if(y -> right != nil)
		y -> right -> p = x;
	y -> p = x -> p;

	if(x -> p == nil)
		root = y;
	else if(x == x -> p -> right)
		x -> p -> right = y;
	else
		x -> p -> left = y;

	y -> right = x;
	x -> p = y;
}

void Red_Black_Insert_Fixup(node* z) {
	while(z -> p -> color == RED) {
		// p = g -> L
		if(z -> p == z -> p -> p -> left) {
			node* y = z -> p -> p -> right;
			if(y -> color == RED) {
				z -> p -> color = BLACK;
				y -> color = BLACK;
				z -> p -> p -> color = RED;
				z = z -> p -> p;
			}
			else {
				// n = g -> L -> R
				if(z == z -> p -> right) {
					z = z -> p;
					// n = g -> L -> L
					left_Rotate(z);
				}
				z -> p -> color = BLACK;
				z -> p -> p -> color = RED;
				right_Rotate(z -> p -> p);
			}
		}
		// p = g -> R
		else {
			node* y = z -> p -> p -> left;
			if(y -> color == RED) {
				z -> p -> color = BLACK;
				y -> color = BLACK;
				z -> p -> p -> color = RED;
				z = z -> p -> p;
			}
			else {
				// n = g -> R -> L
				if(z == z -> p -> left) {
					z = z -> p;
					// n = g -> L -> L
					right_Rotate(z);
				}
				z -> p -> color = BLACK;
				z -> p -> p -> color = RED;
				left_Rotate(z -> p -> p);
			}
		}
	}
	root -> color = BLACK;
}

void insert_Node(int insert_Key) {
	node* z = create_Node(insert_Key, RED);

	node* y = nil;
	node* x = root;

	while(x != nil) {
		y = x;
		if((z -> key) < (x -> key))
			x = x -> left;
		else
			x = x -> right;
	}
	z -> p = y;

	if(y == nil)
		root = z;
	else if((z -> key) < (y -> key))
		y -> left = z;
	else
		y -> right = z;

	Red_Black_Insert_Fixup(z);
}

void Red_Black_Transplant(node* u, node* v) {
	// replace node(u) to node(v)
	if(u -> p == nil)
		root = v;
	else if(u == u -> p -> left)
		u -> p -> left = v;
	else
		u -> p -> right = v;

	v -> p = u -> p;
}

node* Tree_Minimum(node* input_Node) {
	node* tmp_Node = input_Node;
	while(tmp_Node -> left != nil) {
		tmp_Node = tmp_Node -> left;
	}
	return tmp_Node;
}

void Red_Black_Delete_Fixup(node* x) {
	while(x != root && x -> color == BLACK) {
		if(x == x -> p -> left) {
			node* w = x -> p -> right;

			// case 1
			if(w -> color == RED) {
				w -> color = BLACK;
				x -> p -> color = RED;
				left_Rotate(x -> p);
				w = x -> p -> right;
			}
			// case 2
			if(w -> left -> color == BLACK && w -> right -> color == BLACK) {
				w -> color = RED;
				x = x -> p;
			}
			else {
				// case 3
				if(w -> right -> color == BLACK) {
					w -> left -> color = BLACK;
					w -> color = RED;
					right_Rotate(w);
					w = x -> p -> right;
				}
				// case 4
				w -> color = x -> p -> color;
				x -> p -> color = BLACK;
				w -> right -> color = BLACK;
				left_Rotate(x -> p);
				x = root;
			}
		}
		else {
			node* w = x -> p -> left;

			// case 1
			if(w -> color == RED) {
				w -> color = BLACK;
				x -> p -> color = RED;
				right_Rotate(x -> p);
				w = x -> p -> left;
			}
			// case 2
			if(w -> right -> color == BLACK && w -> left -> color == BLACK) {
				w -> color = RED;
				x = x -> p;
			}
			else {
				// case 3
				if(w -> left -> color == BLACK) {
					w -> right -> color = BLACK;
					w -> color = RED;
					left_Rotate(w);
					w = x -> p -> left;
				}
				// case 4
				w -> color = x -> p -> color;
				x -> p -> color = BLACK;
				w -> left -> color = BLACK;
				right_Rotate(x -> p);
				x = root;
			}
		}
	}
	x -> color = BLACK;
}

void delete_Node(int delete_Key) {
	node* x = NULL;
	node* y = NULL;
	node* z = NULL;

	z = root;

	while(z -> key != delete_Key) {
		if(delete_Key < z -> key)
			z = z -> left;
		else
			z = z -> right;
	}

	y = z;

	ColorType y_Origin_Color = y -> color;

	if(z -> left == nil) {
		x = z -> right;
		Red_Black_Transplant(z, z -> right);
	}
	else if(z -> right == nil) {
		x = z -> left;
		Red_Black_Transplant(z, z -> left);
	}
	else {
		y = Tree_Minimum(z -> right);

		y_Origin_Color = y -> color;
		x = y -> right;

		if(y -> p == z) {
			x -> p = y;
		}
		else {
			Red_Black_Transplant(y, y -> right);
			y -> right = z -> right;
			y -> right -> p = y;
		}

		Red_Black_Transplant(z, y);
		y -> left = z -> left;
		y -> left -> p = y;
		y -> color = z -> color;
	}

	if(y_Origin_Color == BLACK) {
		Red_Black_Delete_Fixup(x);
	}
}


int main(void) {
    FILE* file = fopen(INPUT_FILE_NAME, "r");
	FILE *file_out = fopen(OUTPUT_FILE_NAME, "a");
    void print_Tree(node* tmp_Node) {
        if(tmp_Node -> left != nil) {
            print_Tree(tmp_Node -> left);
        }

        printf("key: %d ", tmp_Node -> key);
        fprintf(file_out,"key: %d ", tmp_Node -> key);

        if(tmp_Node -> p != nil){
            printf("parent: %d ", tmp_Node -> p -> key);
            fprintf(file_out,"parent: %d ", tmp_Node -> p -> key);
        }

        else{
            printf("parent:   ");
            fprintf(file_out,"parent:   ", tmp_Node -> p -> key);
        }


        if(tmp_Node -> color == RED){
            printf("color: red");
            fprintf(file_out,"color: red", tmp_Node -> p -> key);
        }

        else{
            printf("color: black");
            fprintf(file_out,"color: black");
        }


        printf("\n");
        fprintf(file_out,"\n");

        if(tmp_Node -> right != nil) {
            print_Tree(tmp_Node -> right);
        }
    }



	char* line = NULL;
	size_t length = MAX_STRING_LENGTH;

	// get number_Of_Works
	getline(&line, &length, file);
	int number_Of_Works = atoi(line);

	nil  = create_Node(0, BLACK);
	root = nil;
	root -> p = nil;

	for(int works = 1; works <= number_Of_Works; works++) {
		// get operation_Mode
		getline(&line, &length, file);
		int operation_Mode = atoi(line);

		// get input_String
		getline(&line, &length, file);
		char* input_String = line;

		if(operation_Mode == 1){
            printf("Insert:");
            fprintf(file_out,"Insert:");
		}

		if(operation_Mode == 2){
			printf("Delete:");
			fprintf(file_out,"Delete:");
		}
		char* space = " ";
		char* input_Number = strtok(input_String, space);

		int first_Number = TRUE;
		while(input_Number != NULL) {
			int node_Key = atoi(input_Number);

			if(first_Number == TRUE){
                printf("%s%d",  " ", node_Key);
                fprintf(file_out,"%s%d",  " ", node_Key);
			}

			else{
				printf("%s%d", ", ", node_Key);
				fprintf(file_out,"%s%d", ", ", node_Key);
			}

			first_Number = FALSE;

			if(operation_Mode == 1)
				insert_Node(node_Key);
			else
				delete_Node(node_Key);

			input_Number = strtok(NULL, space);
		}
		printf("\n");
		fprintf(file_out,"\n");




		print_Tree(root);



	}
}
