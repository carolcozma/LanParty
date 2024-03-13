#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Player
{
    char* first_name;
    char* second_name;
    int points;
};

struct Team
{
    int nr_players;
    char *team_name;
    float team_score;
    struct Player_list *player_head;
    struct Team *next;
};

struct NodeBST
{
    char *team_name;
    float team_score;
    struct NodeBST *left, *right;
};

struct AVLNode
{
    char *team_name;
    float team_score;
    struct AVLNode *left, *right;
    int height;
};

struct Player_list
{
    struct Player player;
    struct Player_list *next;
};

struct Queue_teams
{
    struct Team *front,*rear;
};

typedef struct Player Player;
typedef struct Team Team;
typedef struct Player_list Player_list;
typedef struct Queue_teams Queue_teams;
typedef struct NodeBST NodeBST;
typedef struct AVLNode AVLNode;

void add_team(Team **team_head,int nr_players, char *team_name);
void add_player(Player_list **player_head, char *first_name, char *second_name, int points);
void display_teams(Team *team_head, FILE *file);
void free_team(Team* team);
void en_queue(Queue_teams *q, Team *team_head);
int is_empty(Queue_teams *q);
Team* de_queue(Queue_teams *q);
void list_to_queue(Queue_teams *q, Team *team_head);
void display_queue(Queue_teams *q, FILE* file);
void select_winner(Team *team1, Team *team2, Team **winnersTop, Team **losersTop);
void push(Team **stackTop, Team *team);
Team* pop(Team** stackTop);
void matches(Queue_teams *q,Team **winnersTop, Team **losersTop, FILE* file);
void display_stack(Team **stackTop, FILE* file);
float calculate_score(Team* team_head);
Queue_teams* tournament(Queue_teams *q, Team **first8_head,int nr_teams,FILE* file);
void stack_to_queue(Queue_teams *q,Team **stackTop);
void delete_queue(Queue_teams *q);
Team* queue_to_list(Queue_teams* q);
Queue_teams* copy_queue(Queue_teams* original);
NodeBST* new_node_BST(char *team_name,float team_score);
NodeBST* insert_BST(NodeBST* node, char *team_name, float team_score);
NodeBST* create_BST(Team* team);
void preorder(NodeBST* root, FILE* file);
int get_height(AVLNode* node);
int max_height(int a, int b); 
AVLNode* create_node(char* team_name,float team_score); 
AVLNode* right_rotate(AVLNode* y); 
struct AVLNode* left_rotate(struct AVLNode* x); 
int get_balance(struct AVLNode* node); 
AVLNode* insert_AVL(AVLNode* node, char *team_name, float team_score); 
AVLNode* create_AVL(Team* team);
void print_level2_nodes(AVLNode *root, FILE* file, int level);
void delete_stack(Team **stackTop);
