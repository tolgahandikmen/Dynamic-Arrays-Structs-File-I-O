#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct { 		/* hero struct */
	char name[100];
	int hp;
	int attackDamage;
	int xp;
} Hero;

typedef struct { 		/* monster struct */
	char name[100];
	int hp;
	int attackDamage;
} Monster;

typedef struct {		/* map struct */
	char charName[100];
} Map;


void getPlayerCounts (char *, int *, int *);

int main (int argc, char **argv)
{
    char *input1 = argv[1];
    char *input2 = argv[2];
    char *input3 = argv[3];
    char *charsFile, *commandsFile;
	int *heroCount, *monsterCount;
		
	/* select input files */
	if ( strstr( input1, "chars") ) {
		charsFile = input1;
		commandsFile = input2;
	}
	else {
		charsFile = input2;
		commandsFile = input1;	
	}
	
	/* count heroes and monsters according to input file */
	getPlayerCounts(charsFile, &heroCount, &monsterCount);
	
	/* creating memory space for heroes and monsters dynamically */
	Hero *heroes = (Hero*) malloc (sizeof(Hero) * (int)heroCount);
	Monster *monsters = (Monster*) malloc (sizeof(Monster) * (int)monsterCount);
	
	/* setting characters */
	setChars(charsFile, heroes, monsters);
	
	/* set map and execute the commands */
	runCommands(commandsFile, input3, heroes, monsters, &heroCount, &monsterCount);
	
	return 0;
}

int attack (char *outputFile, Map **map, char* attackerRace, int x, int y, Hero *heroes, Monster *monsters, int *heroCount, int *monsterCount){
	FILE *output;
	output = fopen (outputFile, "a");
	
	int t,k,i,j, alive;
	char p[100];
	x=x-1;
	y=y-1;
	
	/* attack command for heroes */
	if ( !strcmp(attackerRace, "HERO") ){
		for (t=0; t<*heroCount; t++) {
			for (i=0; i<x+1; i++){
				for (j=0; j<y+1; j++){
					if (!strcmp(heroes[t].name,map[i][j].charName)){
						if ( (i!=0) && (strcmp(map[i-1][j].charName,"."))) {	/* hero does not next to the wall and next to an enemy */
							/* point 1 */
							for (k=0; k<*monsterCount; k++){
								if (!strcmp(map[i-1][j].charName, monsters[k].name)) {
									monsters[k].hp -= heroes[t].attackDamage;
									if (monsters[k].hp <= 0) {
										monsters[k].hp = 0;
										strcpy (map[i-1][j].charName,".");
										heroes[t].xp++;
									}
								}
							}
						}
						if ( (i!=0) && (j!=y) && (strcmp(map[i-1][j+1].charName,"."))) {	/* hero does not next to the wall and next to an enemy */
							/* point 2 */
							for (k=0; k<*monsterCount; k++){
								if (!strcmp(map[i-1][j+1].charName, monsters[k].name)) {
									monsters[k].hp -= heroes[t].attackDamage;
									if (monsters[k].hp <= 0) {
										monsters[k].hp = 0;
										strcpy (map[i-1][j+1].charName,".");
										heroes[t].xp++;
									}
								}
							}
						}
						if ( (j!=y) && (strcmp(map[i][j+1].charName,"."))) {	/* hero does not next to the wall and next to an enemy */
							/* point 3 */
							for (k=0; k<*monsterCount; k++){
								if (!strcmp(map[i][j+1].charName, monsters[k].name)) {
									monsters[k].hp -= heroes[t].attackDamage;
									if (monsters[k].hp <= 0) {
										monsters[k].hp = 0;
										strcpy (map[i][j+1].charName,".");
										heroes[t].xp++;
									}
								}
							}
						}
						if ( (i!=x) && (j!=y) && (strcmp(map[i+1][j+1].charName,"."))) {	/* hero does not next to the wall and next to an enemy */
							/* point 4 */
							for (k=0; k<*monsterCount; k++){
								if (!strcmp(map[i+1][j+1].charName, monsters[k].name)) {
									monsters[k].hp -= heroes[t].attackDamage;
									if (monsters[k].hp <= 0) {
										monsters[k].hp = 0;
										strcpy (map[i+1][j+1].charName,".");
										heroes[t].xp++;
									}
								}
							}
						}
						if ( (i!=x) && (strcmp(map[i+1][j].charName,"."))) {	/* hero does not next to the wall and next to an enemy */
							/* point 5 */
							for (k=0; k<*monsterCount; k++){
								if (!strcmp(map[i+1][j].charName, monsters[k].name)) {
									monsters[k].hp -= heroes[t].attackDamage;
									if (monsters[k].hp <= 0) {
										monsters[k].hp = 0;
										strcpy (map[i+1][j].charName,".");
										heroes[t].xp++;
									}
								}
							}
						}
						if ( (i!=x) && (j!=0) && (strcmp(map[i+1][j-1].charName,"."))) {	/* hero does not next to the wall and next to an enemy */
							/* point 6 */
							for (k=0; k<*monsterCount; k++){
								if (!strcmp(map[i+1][j-1].charName, monsters[k].name)) {
									monsters[k].hp -= heroes[t].attackDamage;
									if (monsters[k].hp <= 0) {
										monsters[k].hp = 0;
										strcpy (map[i+1][j-1].charName,".");
										heroes[t].xp++;
									}
								}
							}
						}
						if ( (j!=0) && (strcmp(map[i][j-1].charName,"."))) {	/* hero does not next to the wall and next to an enemy */
							/* point 7 */
							for (k=0; k<*monsterCount; k++){
								if (!strcmp(map[i][j-1].charName, monsters[k].name)) {
									monsters[k].hp -= heroes[t].attackDamage;
									if (monsters[k].hp <= 0) {
										monsters[k].hp = 0;
										strcpy (map[i][j-1].charName,".");
										heroes[t].xp++;
									}
								}
							}
						}
						if ( (i!=0) && (j!=0) && (strcmp(map[i-1][j-1].charName,"."))) {	/* hero does not next to the wall and next to an enemy */
							/* point 8 */
							for (k=0; k<*monsterCount; k++){
								if (!strcmp(map[i-1][j-1].charName, monsters[k].name)) {
									monsters[k].hp -= heroes[t].attackDamage;
									if (monsters[k].hp <= 0) {
										monsters[k].hp = 0;
										strcpy (map[i-1][j-1].charName,".");
										heroes[t].xp++;
									}
								}
							}
						}
						
						alive = 1;
						for (k=0; k<*monsterCount;k++){
							if (monsters[k].hp != 0){
								alive = 0;
								break;
							}
						}
						
						if (alive) {
							return 1;
						}
					}
				}
			}					
		}
	}
	
	/* attack command for monsters */
	else {
		for (t=0; t<*monsterCount; t++) {
			for (i=0; i<x+1; i++){
				for (j=0; j<y+1; j++){
					if (!strcmp(monsters[t].name,map[i][j].charName)){
						if ( (i!=0) && (strcmp(map[i-1][j].charName,"."))) {	/* monster does not next to the wall and next to an enemy */
							/* point 1 */
							for (k=0; k<*heroCount; k++){
								if (!strcmp(map[i-1][j].charName, heroes[k].name)) {
									heroes[k].hp -= monsters[t].attackDamage;
									if (heroes[k].hp <= 0) {
										heroes[k].hp = 0;
										strcpy (map[i-1][j].charName,".");
									}
								}
							}
						}
						if ( (i!=0) && (j!=y) && (strcmp(map[i-1][j+1].charName,"."))) {	/* monster does not next to the wall and next to an enemy */
							/* point 2 */
							for (k=0; k<*heroCount; k++){
								if (!strcmp(map[i-1][j+1].charName, heroes[k].name)) {
									heroes[k].hp -= monsters[t].attackDamage;
									if (heroes[k].hp <= 0) {
										heroes[k].hp = 0;
										strcpy (map[i-1][j+1].charName,".");
									}
								}
							}
						}
						if ( (j!=y) && (strcmp(map[i][j+1].charName,"."))) {	/* monster does not next to the wall and next to an enemy */
							/* point 3 */
							for (k=0; k<*heroCount; k++){
								if (!strcmp(map[i][j+1].charName, heroes[k].name)) {
									heroes[k].hp -= monsters[t].attackDamage;
									if (heroes[k].hp <= 0) {
										heroes[k].hp = 0;
										strcpy (map[i][j+1].charName,".");
									}
								}
							}
						}
						if ( (i!=x) && (j!=y) && (strcmp(map[i+1][j+1].charName,"."))) {	/* monster does not next to the wall and next to an enemy */
							/* point 4 */
							for (k=0; k<*heroCount; k++){
								if (!strcmp(map[i+1][j+1].charName, heroes[k].name)) {
									heroes[k].hp -= monsters[t].attackDamage;
									if (heroes[k].hp <= 0) {
										heroes[k].hp = 0;
										strcpy (map[i+1][j+1].charName,".");
									}
								}
							}
						}
						if ( (i!=x) && (strcmp(map[i+1][j].charName,"."))) {	/* monster does not next to the wall and next to an enemy */
							/* point 5 */
							for (k=0; k<*heroCount; k++){
								if (!strcmp(map[i+1][j].charName, heroes[k].name)) {
									heroes[k].hp -= monsters[t].attackDamage;
									if (heroes[k].hp <= 0) {
										heroes[k].hp = 0;
										strcpy (map[i+1][j].charName,".");
									}
								}
							}
						}
						if ( (i!=x) && (j!=0) && (strcmp(map[i+1][j-1].charName,"."))) {	/* monster does not next to the wall and next to an enemy */
							/* point 6 */
							for (k=0; k<*heroCount; k++){
								if (!strcmp(map[i+1][j-1].charName, heroes[k].name)) {
									heroes[k].hp -= monsters[t].attackDamage;
									if (heroes[k].hp <= 0) {
										heroes[k].hp = 0;
										strcpy (map[i+1][j-1].charName,".");
									}
								}
							}
						}
						if ( (j!=0) && (strcmp(map[i][j-1].charName,"."))) {	/* monster does not next to the wall and next to an enemy */
							/* point 7 */
							for (k=0; k<*heroCount; k++){
								if (!strcmp(map[i][j-1].charName, heroes[k].name)) {
									heroes[k].hp -= monsters[t].attackDamage;
									if (heroes[k].hp <= 0) {
										heroes[k].hp = 0;
										strcpy (map[i][j-1].charName,".");
									}
								}
							}
						}
						if ( (i!=0) && (j!=0) && (strcmp(map[i-1][j-1].charName,"."))) {	/* monster does not next to the wall and next to an enemy */
							/* point 8 */
							for (k=0; k<*heroCount; k++){
								if (!strcmp(map[i-1][j-1].charName, heroes[k].name)) {
									heroes[k].hp -= monsters[t].attackDamage;
									if (heroes[k].hp <= 0) {
										heroes[k].hp = 0;
										strcpy (map[i-1][j-1].charName,".");
									}
								}
							}
						}
						alive = 1;
						for (k=0; k<*heroCount;k++){
							if (heroes[k].hp != 0){
								alive = 0;
								break;
							}
						}
						if (alive) {
							return 1;
						}
					}
				}
			}					
		}
	}

	return 0;
}

void runCommands (char *commandsFile, char *outputFile, Hero *heroes, Monster *monsters, int *heroCount, int *monsterCount){
	FILE *input, *output;
	char c[1000];
	char p[100];
	char *token;
	int i=0, j=0, x, y, k, a, b, tempx, tempy, alive;	
	Map	**map;
	
	output = fopen (outputFile, "w");
	
	input = fopen (commandsFile, "r");
	while (fgets (c, 1000, input) != NULL) {
		/* first words of each line (p) */
		strcpy (p, strtok (c, " "));
		
		if(!strcmp(p, "LOADMAP")){										/* LOADMAP commands */
			strcpy (p, strtok (NULL, " "));
			x = atoi(p);
			strcpy (p, strtok (NULL, " "));
			y = atoi(p);

			map = (Map**) malloc (x * sizeof(Map));							
			for(i=0; i<x; i++){							
			map[i] = (Map*) malloc (y * sizeof(Map));
			}			
			for (i=0; i<x; i++){
				for (j=0; j<y; j++){
					strcpy (map[i][j].charName, ".");
				}
			}			
		}																/* LOADMAP commands */

		else if ( !strcmp(p, "SHOW") ){
			/* 'SHOW' realized */ 										/* SHOW commands */	
			strcpy (p, strtok (NULL, " "));
			if ( !strcmp (p, "MAP") || !strcmp (p, "MAP\r\n")){
				fprintf(output,"MAP STATUS \r\n");
				for (i=0; i<x; i++){
					for (j=0; j<y; j++){
						fprintf(output,"%c ",map[i][j].charName[0]);					
					}
					fprintf(output,"\r\n");
				}			
				fprintf(output,"\r\n");
			}
			else if (!strcmp (p, "HERO") || !strcmp (p, "HERO\r\n")){
				fprintf(output,"HERO STATUS \r\n");
				for (i=0; i< *heroCount; i++){
					fprintf(output,"%s HP: %d XP: %d \r\n",heroes[i].name, heroes[i].hp, heroes[i].xp);
				}
				fprintf(output,"\r\n");
			}
			else if (!strcmp (p, "MONSTER") || !strcmp (p, "MONSTER\r\n")){
				fprintf(output,"MONSTER STATUS \r\n");
				for (i=0; i<*monsterCount; i++){
					fprintf(output,"%s HP: %d \r\n",monsters[i].name, monsters[i].hp);
				}
				fprintf(output,"\r\n");				
			}
		}																/* SHOW commands */
				
		else if ( !strcmp(p, "PUT") ){									/* PUT commands */
			/* 'PUT' realized */
			strcpy (p, strtok (NULL, " "));
			if ( !strcmp(p, "HERO") ){
				for (k=0; k< *heroCount; k++){

					/* check name and find correct hero to put on the map */
					strcpy (p, strtok (NULL, " "));
					i=0;
					while (strcmp(p, heroes[i].name)){
						i++;
					}
					
					/* put the found hero on the map */
					strcpy (p, strtok (NULL, " "));
					a = atoi(p);
					strcpy (p, strtok (NULL, " "));
					b = atoi(p);					
					
					strcpy (map[a][b].charName, heroes[i].name); 
				}
			}
			else if ( !strcmp(p, "MONSTER") ){
				for (k=0; k< *monsterCount; k++){

					/* check name and find correct monsters to put on the map */
					strcpy (p, strtok (NULL, " "));
					i=0;
					while (strcmp(p, monsters[i].name)){
						i++;
					}
					
					/* put the found monsters on the map */
					strcpy (p, strtok (NULL, " "));
					a = atoi(p);
					strcpy (p, strtok (NULL, " "));
					b = atoi(p);					
					
					strcpy (map[a][b].charName, monsters[i].name); 
				}
			}
		}																/* PUT commands */
		
		else if ( !strcmp(p, "ATTACK") ){								/* ATTACK commands */
			/* 'ATTACK' realized */
			strcpy (p, strtok (NULL, " "));
			if ( !strcmp(p, "HERO") || !strcmp(p, "HERO\r\n")){
				fprintf(output,"HEROES ATTACKED \r\n\r\n");
				if (attack (outputFile, map, "HERO", x, y, heroes, monsters, heroCount, monsterCount)){
					fprintf(output,"ALL MONSTERS ARE DEAD! ");
					fclose(output);
					exit (1);
				}
			}
			else if (!strcmp (p, "MONSTER") || !strcmp (p, "MONSTER\r\n")){
				fprintf(output,"MONSTERS ATTACKED \r\n\r\n");
				if (attack (outputFile, map, "MONSTER", x, y, heroes, monsters, heroCount, monsterCount)) {
					fprintf(output,"ALL HEROES ARE DEAD! ");
					fclose(output);
					exit(1);
				}
				
			}			
		}																/* ATTACK commands */
		
		else if ( !strcmp(p, "MOVE") ){									/* MOVE commands */
			/* 'MOVE' realized */
			fprintf(output,"HEROES MOVED \r\n");
			strcpy (p, strtok (NULL, " "));
			if ( !strcmp(p, "HERO") ){
				while (1) {
					token = strtok (NULL, " ");
					if(token == NULL) break;
					
					for (i=0; i<x; i++){
						for (j=0; j<y; j++){
							if (!strcmp (map[i][j].charName, token)) {
								a=i;
								b=j;
							}					
						}
					}			
					strcpy (p, strtok (NULL, " "));
					tempx = atoi(p);
					
					strcpy (p, strtok (NULL, " "));
					tempy = atoi(p);
					
					alive = 1;
					for (i=0; i<*heroCount; i++){
						if ( !strcmp(heroes[i].name, token) ){
							if (heroes[i].hp == 0) {
								fprintf(output,"%s can't move. Dead. \r\n",token);
								alive = 0;
							}
						}
					}
					if (!alive) continue;

					if ((tempx<x) && (tempx>=0) && (tempy<y) && (tempy>=0)) {
						if(strcmp(map[tempx][tempy].charName,".")){
							fprintf(output,"%s can't move. Place is occupied. \r\n",token);
							continue;
						}
					}
					else {
						fprintf(output,"%s can't move. There is a wall. \r\n",token);
						continue;
					}
					
					strcpy (map[a][b].charName, ".");
					strcpy (map[tempx][tempy].charName, token);
				}				
			}
			fprintf(output,"\r\n"); 
		}																/* MOVE commands */
	}
	fclose (input);
	fclose (output);
}	

void getPlayerCounts (char *charsFile, int *heroCount, int *monsterCount) {
	FILE *input;
	char c[1000];
	char word[4][100];
	
	*heroCount=0;
	*monsterCount=0;
	input = fopen (charsFile, "r");
	
	if (input == 0){
		/* fopen returns 0, the NULL pointer, on failure */
        printf ("Error! Can not open input file. \r\n");
        exit (1);
	}
	else 
	{
		while (fgets (c, 1000, input) != NULL) {
			strcpy (word[0], strtok (c, ","));
			
			if ( !strcmp(word[0], "HERO") ){
				/* hero realized, increase number */
				*heroCount = *heroCount+1;
			}
			else {
				/* monster realized, increase number */
				*monsterCount= *monsterCount+1;
			}			
		}	
	}
	fclose (input);	
	return ;
}

void setChars (char *charsFile, Hero *heroes, Monster *monsters) {
	FILE *input;
	char c[1000];
	char word[4][100];
	char p[100];
	int i=0, j=0;	
	
	
	input = fopen (charsFile, "r");
	while (fgets (c, 1000, input) != NULL) {
		strcpy (word[0], strtok (c, ","));
		
		if ( !strcmp(word[0], "HERO") ){
			/* hero realized */
			/* set hero name */
			strcpy (p, strtok (NULL, ","));
			strcpy (heroes[i].name, p);
			heroes[i].xp = 0;
			
			/* set hero hp */
			strcpy (p, strtok (NULL, ","));
			heroes[i].hp = atoi(p);
			
			/* set hero ad */
			strcpy (p, strtok (NULL, ","));
			heroes[i].attackDamage = atoi(p);			
			i++;
			}		
		else {
			/* monster realized */
			/* set monster name */
			strcpy (p, strtok (NULL, ","));
			strcpy (monsters[j].name, p);
			
			/* set monster hp */
			strcpy (p, strtok (NULL, ","));
			monsters[j].hp = atoi(p);
			
			/* set monster ad */
			strcpy (p, strtok (NULL, ","));
			monsters[j].attackDamage = atoi(p);
			j++;
		}			
	}			
	fclose (input);
	return ;
}
