#include "lists.h"

Team *read_file(Team *team_head, int *nr_teams,FILE *file)
{
    int i,j,k;
    int nr_players;
    char team_name[256],first_name[256],second_name[256];
    int points;
    if(file == NULL)
    {
        printf("Error opening file");
        return NULL;
    }
    fscanf(file,"%d",nr_teams);
    fgetc(file);
    for(i=0;i<*nr_teams;i++)
    {

        fscanf(file,"%d",&nr_players);
        fgetc(file);
        fgets(team_name,256,file);

        team_name[strcspn(team_name, "\r\n")] = '\0';
        
        if(team_name[strlen(team_name)-1] == ' ')
             team_name[strlen(team_name)-1] = '\0';

        add_team(&team_head, nr_players, team_name);

        for(j=0; j<nr_players; j++)
        {
            fscanf(file,"%s",first_name);
            fscanf(file,"%s",second_name);
            fscanf(file,"%d",&points);
            add_player(&team_head->player_head, first_name, second_name,points);
        }
        team_head->team_score = calculate_score(team_head);
    }
    return team_head;
}

