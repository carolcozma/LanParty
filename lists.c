#include "lists.h"

void add_team(Team **team_head,int nr_players, char *team_name)
{

    Team* new_team = (Team*)calloc(1,sizeof(Team));
    new_team->team_name = (char*)calloc(strlen(team_name)+1,sizeof(char));
    new_team->nr_players = nr_players;
    strcpy(new_team->team_name,team_name);

    new_team->next = *team_head;
    *team_head = new_team;

}

void add_player(Player_list **player_head, char *first_name, char *second_name, int points)
{
    Player_list* new_player = (Player_list*)calloc(1,sizeof(Player_list));

    new_player->player.first_name = (char*)calloc(strlen(first_name)+1, sizeof(char));
    new_player->player.second_name = (char*)calloc(strlen(second_name)+1, sizeof(char));

    strcpy(new_player->player.first_name, first_name);
    strcpy(new_player->player.second_name, second_name);
    new_player->player.points = points;
    new_player->next = *player_head;
    *player_head = new_player;
}

void display_teams(Team *team_head, FILE *file)
{
    while (team_head!=NULL)
    {
        fprintf (file, "%s\n", team_head->team_name);
        team_head=team_head->next;
    }
}

void free_team(Team* team)
{    
    while (team->player_head != NULL)
    {
        Player_list* p = team->player_head->next;
        free(team->player_head->player.first_name);
        free(team->player_head->player.second_name);
        free(team->player_head);
        team->player_head = p;
    }
    free(team);
}

Queue_teams* create_queue()
{
    Queue_teams *q;
    q = (Queue_teams*)malloc(sizeof(Queue_teams));
    if(q==NULL) return NULL;
    q->front=q->rear=NULL;
    return q;
}

void en_queue(Queue_teams *q, Team *team_head)
{
    Team* new_team = (Team*)calloc(1,sizeof(Team));
    new_team->team_name = (char*)calloc(strlen(team_head->team_name)+1,sizeof(char));
    new_team->nr_players = team_head->nr_players;
    strcpy(new_team->team_name,team_head->team_name);
    new_team->team_score = team_head->team_score;

    while(team_head->player_head!=NULL)
    {
        add_player(&(new_team->player_head), team_head->player_head->player.first_name, team_head->player_head->player.second_name, team_head->player_head->player.points);
        team_head->player_head = team_head->player_head->next;
    }

    if(q->rear==NULL)
        q->rear=new_team;
    else
    {
        (q->rear)->next=new_team;
        (q->rear)=new_team;
    }
    if(q->front==NULL)
        q->front=q->rear;
}

Team* de_queue(Queue_teams *q)
{
    if(is_empty(q)) return NULL;
    Team *de_queuedTeam = q->front;
    q->front=(q->front)->next;
    return de_queuedTeam;
}

int is_empty(Queue_teams *q)
{
    return (q->front==NULL);
}

void list_to_queue(Queue_teams *q, Team *team_head)
{
    while(team_head != NULL)
    {
        en_queue(q,team_head);
        team_head = team_head->next;
    }
}

void display_queue(Queue_teams *q, FILE *file)
{
    display_teams(q->front,file);
}

void delete_queue(Queue_teams *q)
{
    Team *team = q->front;
    while(!is_empty(q))
    {
         team = q->front;
         q->front=(q->front)->next;
         free(team);
    }
    free(q);
}

void select_winner(Team *team1, Team *team2, Team **winnersTop, Team **losersTop)
{
    int score_team1 = 0;
    int score_team2 = 0;
    Player_list *p1 = team1->player_head;
    Player_list *p2 = team2->player_head;

    while (p1 != NULL)
        {
            score_team1 += p1->player.points;
            p1 = p1->next;
        }
    while (p2 != NULL)
        {
            score_team2 += p2->player.points;
            p2 = p2->next;
        }
    if(score_team1 > score_team2)
    {
        team1->team_score++;
        push(winnersTop,team1);
        push(losersTop,team2);
    }
    else
    {
         team2->team_score++;
        push(winnersTop,team2);
        push(losersTop,team1);
    }
        
}

void push(Team **stackTop, Team *team)
{
    Team* new_team = (Team*)calloc(1,sizeof(Team));
    new_team->team_name = (char*)calloc(strlen(team->team_name)+1,sizeof(char));
    new_team->nr_players = team->nr_players;
    strcpy(new_team->team_name,team->team_name);
    new_team->team_score = team->team_score;


    while(team->player_head!=NULL)
    {
        add_player(&(new_team->player_head), team->player_head->player.first_name, team->player_head->player.second_name, team->player_head->player.points);
        team->player_head = team->player_head->next;
    }

    new_team->next = *stackTop;
    *stackTop = new_team;
}

Team* pop(Team** stackTop)
{
    if(*stackTop==NULL) return NULL;

    Team *poppedTeam = *stackTop;
    *stackTop=(*stackTop)->next;

    return poppedTeam;
}


void matches(Queue_teams *q,Team **winnersTop, Team **losersTop, FILE *file)
{   
    Team* team1=(Team*)malloc(sizeof(Team));
    Team* team2=(Team*)malloc(sizeof(Team));
    while(!is_empty(q))
    {
        team1 = de_queue(q);
        team2 = de_queue(q);
        team1->team_name[strlen(team1->team_name)] = '\0';
        team1->team_name[strlen(team1->team_name)] = '\0';
        fprintf(file,"%-33s-%33s\n",team1->team_name,team2->team_name);
        select_winner(team1,team2,winnersTop,losersTop);
    }
}

Queue_teams* tournament(Queue_teams *q, Team **first8_head,int nr_teams,FILE* file)
{
    Team* winnersTop=(Team*)malloc(sizeof(Team));
    Team* losersTop=(Team*)malloc(sizeof(Team));
    Queue_teams *q_copy;
    Queue_teams *q_temp;
    
    int round = 1;
    winnersTop = NULL;
    losersTop = NULL;
    int i,j;
    
    while(nr_teams != 1)
    {   
        if(nr_teams == 8)
        { 
            q_copy = copy_queue(q);
            *first8_head = queue_to_list(q_copy);
        }
        
        fprintf(file,"--- ROUND NO:%d\n",round);
        matches(q,&winnersTop,&losersTop,file);
        delete_stack(&losersTop);
        fprintf(file,"\n");
        stack_to_queue(q,&winnersTop);
        q_copy = copy_queue(q);
        fprintf(file,"WINNERS OF ROUND NO:%d\n",round);
        while(!is_empty(q_copy))
        {
            fprintf(file,"%-33s -  %.2f\n",q_copy->front->team_name,q_copy->front->team_score);
            q_copy->front = q_copy->front->next;
        }
        if(nr_teams>2)
            fprintf(file,"\n");
        round++;
        nr_teams /= 2;
    }
    delete_queue(q_copy);
    delete_stack(&losersTop);
    return q;
}

void display_stack(Team **stackTop, FILE* file)
{
    display_teams(pop(stackTop),file);
}

void delete_stack(Team **stackTop)
{
    Team* temp;
    while((*stackTop)!=NULL)
    {
        temp = *stackTop;
        *stackTop=(*stackTop)->next;
        free(temp);
    }
}

float calculate_score(Team* team_head)
{
    float score = 0;
    Player_list *p = team_head->player_head;
    while(p != NULL)
    {
        score += p->player.points;
        p = p->next;
    }
    score = score/(team_head->nr_players);
    return score;
}

void stack_to_queue(Queue_teams *q,Team **stackTop)
{
    Team* temp;
    while ((*stackTop) != NULL)
    {
        temp = pop(stackTop);
        en_queue(q, temp);
    }
}

Team* queue_to_list(Queue_teams* q)
{
    Team* list_head = (Team*)calloc(1,sizeof(Team));
    list_head = NULL;
    while(!is_empty(q))
        { 
            Team* team = de_queue(q);
            add_team(&list_head, team->nr_players, team->team_name);
            list_head->team_score=team->team_score;
            Player_list* p = list_head->player_head;
           
            while(p != NULL)
                {
                    add_player(&list_head->player_head,p->player.first_name, p->player.second_name,p->player.points);
                    p = p->next;
                }
        }
    return list_head;
}
Queue_teams* copy_queue(Queue_teams* original)
{
    Queue_teams* copied = create_queue();
    Queue_teams* tempQueue = create_queue();  
    
    while (!is_empty(original))
    {
        Team* team = de_queue(original);
        en_queue(tempQueue, team);
    }
    
    while (!is_empty(tempQueue))
    {
        Team* team = de_queue(tempQueue);
        en_queue(original, team);  
        en_queue(copied, team);
    }
    
    delete_queue(tempQueue);
    
    return copied;
}

NodeBST* new_node_BST(char *team_name,float team_score)
{
    NodeBST* node = (NodeBST*)malloc(sizeof(NodeBST));
    node->team_name = (char*)calloc(strlen(team_name)+1,sizeof(char));
    (node)->left = (node)->right = NULL;
    strcpy(node->team_name,team_name);
    node->team_score = team_score;
    return node;
}

NodeBST* insert_BST(NodeBST* node, char *team_name, float team_score)
{
    if(node == NULL) return new_node_BST(team_name,team_score);

    if(team_score < node->team_score)
        node->left = insert_BST(node->left,team_name, team_score);
    else if(team_score > node->team_score)
        node->right = insert_BST(node->right,team_name, team_score);
    else if(team_score == node->team_score)
        if(strcmp(team_name,node->team_name) < 0)
            node->left = insert_BST(node->left,team_name, team_score);
        else if(strcmp(team_name,node->team_name) > 0)
            node->right = insert_BST(node->right,team_name, team_score);
    
    return node;
}

NodeBST* create_BST(Team* team)
{
    NodeBST* root = NULL;
    while(team!=NULL)
    {
        root = insert_BST(root,team->team_name,team->team_score);
        team = team->next;
    }
    return root;
}

void preorder(NodeBST* root, FILE *file)
{
	if (root)
    {
		preorder(root->right,file);
        fprintf(file,"%-33s -  %.2f\n",root->team_name,root->team_score);
		preorder(root->left,file);
	}
}

int get_height(AVLNode* node)
{
    if(node == NULL)
        return -1;
    return node->height;
}

int max_height(int a, int b) 
{
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

AVLNode* create_node(char* team_name,float team_score) 
{
    AVLNode* newNode = (AVLNode*)malloc(sizeof(struct AVLNode));
    newNode->team_name = (char*)malloc((strlen(team_name)+1)*sizeof(char));
    strcpy(newNode->team_name,team_name);
    newNode->team_score = team_score;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 0;
    return newNode;
}

AVLNode* right_rotate(AVLNode* z) 
{
    AVLNode* y = z->left;
    AVLNode* T3 = y->right;

    y->right = z;
    z->left = T3;

    z->height = max_height(get_height(z->left), get_height(z->right)) + 1;
    y->height = max_height(get_height(y->left), get_height(y->right)) + 1;

    return y;
}

AVLNode* left_rotate(AVLNode* z) 
{
    AVLNode* y = z->right;
    AVLNode* T2 = y->left;

    y->left = z;
    z->right = T2;

    z->height = max_height(get_height(z->left), get_height(z->right)) + 1;
    y->height = max_height(get_height(y->left), get_height(y->right)) + 1;

    return y;
}

AVLNode* LR_rotate(AVLNode* Z)
{
    Z->left = left_rotate(Z->left);
    return right_rotate(Z); 
}

AVLNode* RL_rotate(AVLNode* Z)
{
    Z->right = right_rotate(Z->right);
    return left_rotate(Z); 
}

int get_balance(AVLNode* node) 
{
    if (node == NULL)
        return 0;
    return get_height(node->left) - get_height(node->right);
}

AVLNode* insert_AVL(AVLNode* node, char *team_name, float team_score) 
{
    if(node == NULL) return create_node(team_name,team_score);

    if(team_score < node->team_score)
        node->left = insert_AVL(node->left,team_name, team_score);
    else if(team_score > node->team_score)
        node->right = insert_AVL(node->right,team_name, team_score);
    else if(team_score == node->team_score)
        if(strcmp(team_name,node->team_name) < 0)
            node->left = insert_AVL(node->left,team_name, team_score);
        else if(strcmp(team_name,node->team_name) > 0)
            node->right = insert_AVL(node->right,team_name, team_score);
    
    node->height = 1 + max_height(get_height(node->left), get_height(node->right));

    int balance = get_balance(node);

    if (balance > 1 && team_score < node->left->team_score)
        return right_rotate(node);

    if (balance < -1 && team_score > node->right->team_score)
        return left_rotate(node);

    if (balance > 1 && team_score > node->left->team_score) 
    {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    if (balance < -1 && team_score < node->right->team_score) 
    {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    if (balance > 1 && team_score == node->left->team_score && strcmp(team_name,node->left->team_name) > 0)
        return right_rotate(node);

    if (balance < -1 && team_score == node->right->team_score && strcmp(team_name,node->right->team_name) < 0)
        return left_rotate(node);

   
    if (balance > 1 && team_score == node->left->team_score && strcmp(team_name,node->left->team_name) < 0) 
    {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    if (balance < -1 && team_score == node->right->team_score && strcmp(team_name,node->right->team_name) > 0) 
    {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}

AVLNode* create_AVL(Team* team)
{
    AVLNode* root = NULL;
    while(team!=NULL)
    {
        root = insert_AVL(root,team->team_name,team->team_score);
        team = team->next;
    }
    return root;
}
void print_level2_nodes(AVLNode *root, FILE* file, int level)
{
    if (root == NULL)
        return;

    if (level == 0)
    {
        fprintf(file, "%s\n", root->team_name);
        return;
    }

    print_level2_nodes(root->right, file, level - 1);
    print_level2_nodes(root->left, file, level - 1);
}