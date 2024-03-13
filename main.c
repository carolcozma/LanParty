#include "files.h"

int nr_teams;

int find_index_min(Team* team_head)
{
   int index=1, index_min = 1;
   int nr_teams_after_elimination = 1;
   int i;
   float score = 0, min_score = 0;
   Player_list* p;
    
    Team* headcopy = team_head;

    p = headcopy->player_head;
    min_score = headcopy->team_score;
    index++;
    headcopy = headcopy->next;
    while (headcopy != NULL)
    {
        score = headcopy->team_score;
        if(score < min_score)
        {
            min_score = score;
            index_min = index;
        }
        headcopy = headcopy->next;
        index++;
    }
    
  return index_min;
}

Team* Task2(Team** team_head)
{
    int index = 1, i;
    int index_min;
    int score;
    int nr_teams_after_elimination = 1;

    while(nr_teams_after_elimination*2 <= nr_teams)
        nr_teams_after_elimination *= 2;
        
    int teams_to_eliminate = nr_teams - nr_teams_after_elimination;
    nr_teams = nr_teams_after_elimination;

    Team* headcopy = *team_head;
    Team* prev = *team_head;

    while (headcopy != NULL && teams_to_eliminate != 0)
    {
        index_min = find_index_min(*team_head);
        if (index == index_min)
        {
            if (headcopy != prev)
                prev->next = headcopy->next;
            else
                *team_head = (*team_head)->next;

            free_team(headcopy);
            headcopy = *team_head;
            prev = *team_head;
            teams_to_eliminate--;
            index = 1;
            continue;
        }
        if (headcopy != prev)
            prev = prev->next;
        headcopy = headcopy->next;
        index++;
    }
    return *team_head;
}

int main(int argc, char **argv)
{
    FILE* file_c;
    file_c = fopen(argv[1], "r");
    FILE* file_d;
    file_d = fopen(argv[2], "r");
    FILE* file_r;
    file_r = fopen(argv[3], "w");

    Team *team_head=NULL;
    Queue_teams *team_queue = (Queue_teams*)malloc(sizeof(Queue_teams));
    team_queue->front = NULL;
    team_queue->rear = NULL;
    Queue_teams *winner_team = (Queue_teams*)malloc(sizeof(Queue_teams));
    winner_team->front = NULL;
    winner_team->rear = NULL;
    Team* first8_head=(Team*)malloc(sizeof(Team));
    first8_head = NULL;
    int i, ok = 0;

    for(i=0; i<5; i++)
    {
        fscanf(file_c,"%d",&ok);
        if(i == 0 && ok == 1)
        {
            team_head = read_file(team_head,&nr_teams,file_d);
        }
        if(i == 1 && ok == 1)
        {   
            team_head = Task2(&team_head);
            list_to_queue(team_queue,team_head);
            display_queue(team_queue,file_r);
        }
        else if(i == 1 && ok == 0)
        {
            display_teams(team_head,file_r);
        }
        if(i == 2 && ok == 1)
        {   
            fprintf(file_r,"\n");
            tournament(team_queue, &first8_head, nr_teams,file_r);
        }
        if(i == 3 && ok == 1)
        {
            fprintf(file_r,"\n");
            NodeBST *rootBST = create_BST(first8_head);
            fprintf(file_r,"TOP 8 TEAMS:\n");
            preorder(rootBST,file_r);
        }
        if(i == 4 && ok == 1)
        {
            fprintf(file_r,"\n");
            AVLNode *rootAVL = create_AVL(first8_head);
            fprintf(file_r,"THE LEVEL 2 TEAMS ARE: \n"); 
            print_level2_nodes(rootAVL,file_r,2);
        }
    }
    free_team(team_head);
    delete_queue(team_queue);
    fclose(file_r);
    fclose(file_c);
    fclose(file_d);
    return 0;
}
