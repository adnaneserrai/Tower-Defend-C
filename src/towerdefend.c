#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "SDL.h"
#include "maSDL.h"
#include "towerdefend.h"
#include <time.h>


//typedef Tunite* ** TplateauJeu;


TplateauJeu AlloueTab2D(int largeur, int hauteur){
    TplateauJeu jeu;
    jeu = (Tunite***)malloc(sizeof(Tunite**)*largeur);
    for (int i=0;i<largeur;i++){
        jeu[i] = (Tunite**)malloc(sizeof(Tunite*)*hauteur);
    }
    return jeu;  //tab2D contenant des pointeurs
}
void initPlateauAvecNULL(TplateauJeu jeu,int largeur, int hauteur){
    for (int i=0;i<largeur;i++){
        for (int j=0;j<hauteur;j++){
            jeu[i][j] = NULL;
        }
    }
}


/*
void ecritCheminVersleHaut  : permet d'initilaiser le tab chemin de distance cases (avec des coord x y) dans une direction, à partir d'un point x y donné

int **chemin  : tab de coordonnées x y du chemin
int *ichemin  : indice de la case du chemin d'où on part
int *xdepart, int *ydepart : valeur en x y de départ pouri la premiere case
int distance  : distance sur laquelle on va écrire des coordonnées dans le tab chemin
int *distanceMaxRestante : securité pour ne pas sortir de la plage d'indice de chemin
*/

void afficheCoordonneesParcours(int **chemin, int nbcoord){
    printf("Liste coordonnees: ");
    for (int i=0; i<nbcoord; i++){
        printf("(%d, %d)",chemin[i][X], chemin[i][Y]);
    }
    printf("\nfin liste coordonnées\n");
}

void freeChemin(int **tab){
    for (int j=0;j<NBCOORDPARCOURS;j++){
        free(tab[j]);  //libere chaque case, qui est un tableau de 2 cases
    }
    free(tab);
}

void affichePlateauConsole(TplateauJeu jeu, int largeur, int hauteur){
    //pour un affichage sur la console, en relation avec enum TuniteDuJeu
    const char* InitialeUnite[7]={"s", "a", "r", "A", "C", "D", "G"};

    printf("\n");
    for (int j=0;j<hauteur;j++){
        for (int i=0;i<largeur;i++){
                // A ne pas donner aux etudiants
            if (jeu[i][j] != NULL){
                    printf("%s",InitialeUnite[jeu[i][j]->nom]);
            }
            else printf(" ");  //cad pas d'unité sur cette case
        }
        printf("\n");
    }
}

Tunite *creeTourSol(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tourSol;
    nouv->cibleAttaquable = sol;
    nouv->maposition = sol;
    nouv->pointsDeVie = 500;
    nouv->vitesseAttaque = 1.5;
    nouv->degats = 120;
    nouv->portee = 5;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}
Tunite *creeTourAir(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tourAir;
    nouv->cibleAttaquable = air;
    nouv->maposition = sol;
    nouv->pointsDeVie = 500;
    nouv->vitesseAttaque = 1.0;
    nouv->degats = 100;
    nouv->portee = 3;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}
Tunite *creeTourRoi(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tourRoi;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 800;
    nouv->vitesseAttaque = 1.2;
    nouv->degats = 180;
    nouv->portee = 4;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}
Tunite *creeDragon(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = dragon;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = air;
    nouv->pointsDeVie = 200;
    nouv->vitesseAttaque = 1.1;
    nouv->degats = 180;
    nouv->portee = 2;
    nouv->vitessedeplacement = 2;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}

Tunite *creeArcher(int posx, int posy)
{
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = archer;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 80;
    nouv->vitesseAttaque = 0.7;
    nouv->degats = 120;
    nouv->portee = 3;
    nouv->vitessedeplacement = 1.0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}

Tunite *creeGargouille(int posx, int posy)
{
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = gargouille;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = air;
    nouv->pointsDeVie = 80;
    nouv->vitesseAttaque = 0.6;
    nouv->degats = 90;
    nouv->portee = 1;
    nouv->vitessedeplacement = 3.0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}

Tunite *creeChevalier(int posx, int posy)
{
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = chevalier;
    nouv->cibleAttaquable = sol;
    nouv->maposition = sol;
    nouv->pointsDeVie = 400;
    nouv->vitesseAttaque = 1.5;
    nouv->degats = 250;
    nouv->portee = 1;
    nouv->vitessedeplacement = 2.0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}



bool tourRoiDetruite(TListePlayer playerRoi)
{
    TListePlayer courant = playerRoi;
    while (courant != NULL)
    {
        if (courant -> pdata -> nom == tourRoi)
        {
            return (courant -> pdata -> pointsDeVie <= 0);
        }
        courant = courant -> suiv;
    }
    return true;
}

void PositionnePlayerOnPlateau(TListePlayer player, TplateauJeu jeu)
{
    TListePlayer courant = player;
    while (courant != NULL)
    {
        int x = courant -> pdata -> posX;
        int y = courant -> pdata -> posY;
        if (x >= 0 && x < LARGEURJEU && y >= 0 && y < HAUTEURJEU)
        {
            jeu[x][y] = courant -> pdata;
        }
        courant = courant -> suiv;
    }
}


TListePlayer quiEstAPortee(TplateauJeu jeu, Tunite *UniteAttaquante)
{
    TListePlayer listeCibles = NULL;
    int xA = UniteAttaquante -> posX;
    int yA = UniteAttaquante -> posY;
    int portee = UniteAttaquante -> portee;

    for (int i = 0; i < LARGEURJEU; i++)
    {
        for (int j = 0; j < HAUTEURJEU; j++)
        {
            Tunite *cible = jeu[i][j];
            if (cible != NULL && cible != UniteAttaquante)
            {
                float dist = sqrt(pow(i - xA, 2) + pow(j - yA, 2));  //calcul de la distance

                if (dist <= portee)
                {
                    //est ce que l'attaquant peut toucher la cible ?
                    bool matchPosition = (UniteAttaquante -> cibleAttaquable == solEtAir) ||
                                         (UniteAttaquante -> cibleAttaquable == sol && cible -> maposition == sol) ||
                                         (UniteAttaquante -> cibleAttaquable == air && cible -> maposition == air);

                    //la horde tape que la tour du roi
                    bool campOk = false;
                    bool attaquantEstHorde = (UniteAttaquante -> nom >= archer);

                    if (attaquantEstHorde && cible -> nom == tourRoi) campOk = true;
                    if (!attaquantEstHorde && (cible -> nom >= archer)) campOk = true;

                    if (matchPosition && campOk)
                    {
                        AjouterUnite(&listeCibles, cible);
                    }
                }
            }
        }
    }
    return listeCibles;
}


void AjouterUnite(TListePlayer *player, Tunite *nouvelleUnite)
{
    TListePlayer nouv = (TListePlayer)malloc(sizeof(struct T_cell));

    if (nouv != NULL)
    {
        nouv -> pdata = nouvelleUnite;
        nouv -> suiv = NULL;
        if (*player == NULL)
        {
           *player = nouv;
        }
        else
        {
            TListePlayer courant = *player;
            while (courant -> suiv != NULL)
            {
                courant = courant -> suiv;
            }
            courant -> suiv = nouv;
        }
    }
}


void combat(SDL_Surface *surface , Tunite * UniteAttaquante, Tunite * UniteCible)  //qui utilise dessineAttaque (de maSDL.h)
{
    UniteCible -> pointsDeVie -= UniteAttaquante -> degats;

    dessineAttaque(surface, UniteAttaquante, UniteCible);

    UniteAttaquante -> peutAttaquer = 0;
}


void supprimerUnite(TListePlayer *player, Tunite *UniteDetruite, TplateauJeu jeu)
{
    jeu[UniteDetruite -> posX][UniteDetruite -> posY] = NULL;

    TListePlayer courant = *player;
    TListePlayer precedent = NULL;

    while (courant != NULL)
    {
        if (courant -> pdata == UniteDetruite)
        {
            if (precedent == NULL)
            {
                *player = courant -> suiv;    // si c le premier de la liste
            }
            else
            {
                precedent -> suiv = courant -> suiv;    // on saute le maillon
            }

            free(courant -> pdata);
            free(courant);
            return;
        }
        precedent = courant;
        courant = courant -> suiv;
    }
}


int estSurLeChemin(int x, int y, int** tabParcours)
{
    for (int k = 0; k < NBCOORDPARCOURS; k++)
    {
        if (tabParcours[k][X] == x && tabParcours[k][Y] == y) return 1;
    }
    return 0;
}

int calculScore(int x, int y, int** tabParcours){

    int score = 0;

    for(int k = 0; k < NBCOORDPARCOURS; k++){

        int dx = abs(x - tabParcours[k][X]);
        int dy = abs(y - tabParcours[k][Y]);

        int distance = dx + dy;

        if(distance <= 3)
            score += 2;   // très proche du chemin
        else if(distance <= 5)
            score += 1;   // proche
    }

    return score;
}

void placementAutoTour(TplateauJeu jeu, TListePlayer *roi, int** tabParcours){

    int bestX = -1, bestY = -1;
    int maxScore = -1;

    for(int i=0;i<LARGEURJEU;i++){
        for(int j=0;j<HAUTEURJEU;j++){

            if(jeu[i][j] == NULL && !estSurLeChemin(i,j,tabParcours)){

                int score = calculScore(i,j,tabParcours);

                if(score > maxScore){
                    maxScore = score;
                    bestX = i;
                    bestY = j;
                }
            }
        }
    }

    if(bestX != -1){

        Tunite *tour;

        //choix du type de tour à 50%
        if(rand()%2 == 0)
            tour = creeTourSol(bestX,bestY);
        else
            tour = creeTourAir(bestX,bestY);

        tour->score_emplacement = maxScore;

        AjouterUnite(roi, tour);
        jeu[bestX][bestY] = tour;
    }
}



int creeCarre(int grille[LARGEURJEU][HAUTEURJEU], int x, int y){

    // bas-droite
    if(x > 0 && y > 0){
        if(grille[x-1][y] &&
           grille[x][y-1] &&
           grille[x-1][y-1])
            return 1;
    }

    // bas-gauche
    if(x < LARGEURJEU-1 && y > 0){
        if(grille[x+1][y] &&
           grille[x][y-1] &&
           grille[x+1][y-1])
            return 1;
    }

    // haut-droite
    if(x > 0 && y < HAUTEURJEU-1){
        if(grille[x-1][y] &&
           grille[x][y+1] &&
           grille[x-1][y+1])
            return 1;
    }

    // haut-gauche
    if(x < LARGEURJEU-1 && y < HAUTEURJEU-1){
        if(grille[x+1][y] &&
           grille[x][y+1] &&
           grille[x+1][y+1])
            return 1;
    }

    return 0;
}

int **initChemin(){
    int **chemin = malloc(sizeof(int*) * NBCOORDPARCOURS);
    for(int i=0;i<NBCOORDPARCOURS;i++){
        chemin[i] = malloc(sizeof(int)*2);
    }

    int grille[LARGEURJEU][HAUTEURJEU];
    for(int i=0;i<LARGEURJEU;i++){
        for(int j=0;j<HAUTEURJEU;j++){
            grille[i][j] = 0;
        }
    }

    int x = LARGEURJEU/2; // départ au centre
    int y = HAUTEURJEU-1; // en bas

    // enregistrer la case de départ
    chemin[0][0] = x;
    chemin[0][1] = y;
    grille[x][y] = 1;

    int i = 1; // commence à 1
    int essais = 0; //pour empêcher les blocages

    // premier mouvement vers le haut
    y--;

    chemin[i][0] = x;
    chemin[i][1] = y;
    grille[x][y] = 1;

    int lastDir = 0;   // 0 = haut
    int nbVirages = 0;

    i++;

    while(i < NBCOORDPARCOURS){
        essais++;
        if(essais > 1000) return initChemin();

        int direction;

        // choix direction
        int casesRestantes = NBCOORDPARCOURS - i;
        int distanceRestante = y;
        int r = rand()%100;

        if(distanceRestante == casesRestantes){
            direction = 0; // obligation de monter pour finir le chemin tout en haut
        }
        else if(distanceRestante < casesRestantes / 2){
            direction = rand()%2 + 1; // si il reste trop de cases on force horizontal
        }
        else if(nbVirages >= 2){
            direction = 0;
        }
        else{
            if(r < 30) direction = 0;
            else direction = rand()%2 + 1;
        }

        // éviter zigzag gauche/droite
        if((lastDir == 1 && direction == 2) ||
           (lastDir == 2 && direction == 1)){
            direction = 0;
        }

        int nx = x;
        int ny = y;

        if(direction == 0) ny--;
        if(direction == 1) nx--;
        if(direction == 2) nx++;

        // validations
        if(nx < 0 || nx >= LARGEURJEU || ny < 0) continue;
        if(grille[nx][ny] == 1) continue;
        if(creeCarre(grille, nx, ny)) continue;

        // update virages
        if(direction != lastDir) nbVirages++;
        else nbVirages = 0;

        lastDir = direction;

        // valider
        x = nx;
        y = ny;
        chemin[i][0] = x;
        chemin[i][1] = y;
        grille[x][y] = 1;
        i++;
    }
    return chemin;
}



//gere spawn et deplacement horde
void jouerUnTour(TplateauJeu jeu, TListePlayer *horde, int** tabParcours, int tourActuel, TListePlayer *playerRoi)
{
    int probaTour = 10;
    int probaHorde = 70;

    for(int i=0; i<LARGEURJEU; i++)
    {
        for(int j=0; j<HAUTEURJEU; j++)
        {
            if(jeu[i][j] != NULL) jeu[i][j] -> peutAttaquer = 1;
        }
    }
    //spawn horde
    if(rand()%100 < probaHorde)
    {
        int sx = tabParcours[0][X], sy = tabParcours[0][Y];
        if (jeu[sx][sy] == NULL)
        {
            Tunite *m;
            int r = rand() % 4; // au hasard 4 monstres
            if (r == 0) m = creeDragon(sx, sy);
            else if (r == 1) m = creeArcher(sx, sy);
            else if (r == 2) m = creeGargouille(sx, sy);
            else m = creeChevalier(sx, sy);

            AjouterUnite(horde, m);
            jeu[sx][sy] = m;
        }
    }

    // anti collision
    TListePlayer courant = *horde;
    courant = *horde;
    while(courant)
    {
        Tunite* m = courant -> pdata;
        int idx = -1;

        for(int k=0; k<NBCOORDPARCOURS; k++)
            if(tabParcours[k][X] == m->posX && tabParcours[k][Y] == m->posY)
            {
                idx = k; break;
            }

        if(idx != -1 && idx < NBCOORDPARCOURS - 1)
        {
            int nx = tabParcours[idx+1][X], ny = tabParcours[idx+1][Y];
            if(jeu[nx][ny] == NULL)    // si case libre
            {
                jeu[m -> posX][m -> posY] = NULL;
                m -> posX = nx; m -> posY = ny;
                jeu[nx][ny] = m;
            }
        }
        courant = courant -> suiv;
    }
    //spawn tour
    if(rand()%100 < probaTour){
        placementAutoTour(jeu, playerRoi, tabParcours);

        // MAJ liste joueur
        for(int i=0; i<LARGEURJEU; i++){
            for(int j=0; j<HAUTEURJEU; j++){
                if(jeu[i][j] != NULL &&
                    (jeu[i][j]->nom == tourSol || jeu[i][j]->nom == tourAir)){
                    AjouterUnite(playerRoi, jeu[i][j]);
                }
            }
        }
    }
}

// gere tirs
void resoudreCombats(TplateauJeu jeu, TListePlayer playerRoi, TListePlayer *horde, SDL_Surface *surface)
{
    // tour tire
    TListePlayer c = playerRoi;
    while(c)
    {
        if(c -> pdata -> peutAttaquer)
        {
            TListePlayer cibles = quiEstAPortee(jeu, c -> pdata);
            if(cibles) {
                combat(surface, c -> pdata, cibles -> pdata);
                while(cibles)
                {
                    TListePlayer t = cibles; cibles = cibles -> suiv; free(t);
                }
            }
        }
        c = c -> suiv;
    }

    // horde attaque roi
    TListePlayer chCombat = *horde;
    while(chCombat)
    {
        if(chCombat -> pdata -> peutAttaquer)
        {
            TListePlayer cibles = quiEstAPortee(jeu, chCombat -> pdata);

            if(cibles)
            {
                combat(surface, chCombat -> pdata, cibles -> pdata);

                while(cibles)
                {
                    TListePlayer t = cibles; cibles = cibles -> suiv; free(t);
                }
            }
        }
        chCombat = chCombat -> suiv;
    }

    // nettoyage mort
    TListePlayer ch = *horde;
    while(ch)
    {
        TListePlayer suiv = ch -> suiv;
        if(ch -> pdata -> pointsDeVie <= 0) supprimerUnite(horde, ch -> pdata, jeu);
        ch = suiv;
    }
}

// sauvegarde
void sauvegardeBinaire(const char* filename, TListePlayer roi, TListePlayer horde)
{
    FILE *f = fopen(filename, "wb");
    if (!f) return;

    TListePlayer tmp;
    int count;

    // ===== ROI =====
    count = 0;
    tmp = roi;
    while(tmp){ count++; tmp = tmp->suiv; }
    fwrite(&count, sizeof(int), 1, f);

    tmp = roi;
    while(tmp){
        fwrite(tmp->pdata, sizeof(Tunite), 1, f);
        tmp = tmp->suiv;
    }

    // ===== HORDE =====
    count = 0;
    tmp = horde;
    while(tmp){ count++; tmp = tmp->suiv; }
    fwrite(&count, sizeof(int), 1, f);

    tmp = horde;
    while(tmp){
        fwrite(tmp->pdata, sizeof(Tunite), 1, f);
        tmp = tmp->suiv;
    }

    fclose(f);
}

void chargementBinaire(const char* filename, TListePlayer *roi, TListePlayer *horde, TplateauJeu jeu)
{
    FILE *f = fopen(filename, "rb");
    if (!f) return;

    int count;

    // reset listes
    *roi = NULL;
    *horde = NULL;
    initPlateauAvecNULL(jeu, LARGEURJEU, HAUTEURJEU);

    // ===== ROI =====
    fread(&count, sizeof(int), 1, f);
    for(int i=0;i<count;i++){
        Tunite *u = malloc(sizeof(Tunite));
        fread(u, sizeof(Tunite), 1, f);
        AjouterUnite(roi, u);
        jeu[u->posX][u->posY] = u;
    }

    // ===== HORDE =====
    fread(&count, sizeof(int), 1, f);
    for(int i=0;i<count;i++){
        Tunite *u = malloc(sizeof(Tunite));
        fread(u, sizeof(Tunite), 1, f);
        AjouterUnite(horde, u);
        jeu[u->posX][u->posY] = u;
    }

    fclose(f);
}

void sauvegardeTexte(const char* filename, TListePlayer roi, TListePlayer horde)
{
    FILE *f = fopen(filename, "w");
    if (!f) return;

    TListePlayer tmp;

    // ROI
    tmp = roi;
    while(tmp){
        Tunite *u = tmp->pdata;
        fprintf(f, "%d %d %d %d %f %d %d %f %d %d %d\n",
            u->nom,
            u->cibleAttaquable,
            u->maposition,
            u->pointsDeVie,
            u->vitesseAttaque,
            u->degats,
            u->portee,
            u->vitessedeplacement,
            u->posX,
            u->posY,
            u->peutAttaquer);
        tmp = tmp->suiv;
    }

    fprintf(f, "END\n");

    // HORDE
    tmp = horde;
    while(tmp){
        Tunite *u = tmp->pdata;
        fprintf(f, "%d %d %d %d %f %d %d %f %d %d %d\n",
            u->nom,
            u->cibleAttaquable,
            u->maposition,
            u->pointsDeVie,
            u->vitesseAttaque,
            u->degats,
            u->portee,
            u->vitessedeplacement,
            u->posX,
            u->posY,
            u->peutAttaquer);
        tmp = tmp->suiv;
    }

    fclose(f);
}

void chargementTexte(const char* filename, TListePlayer *roi, TListePlayer *horde, TplateauJeu jeu)
{
    FILE *f = fopen(filename, "r");
    if (!f) return;

    char buffer[256];

    *roi = NULL;
    *horde = NULL;
    initPlateauAvecNULL(jeu, LARGEURJEU, HAUTEURJEU);

    // ===== ROI =====
    while(fgets(buffer, sizeof(buffer), f))
    {
        if (strncmp(buffer, "END", 3) == 0) break;

        Tunite *u = malloc(sizeof(Tunite));

        int res = sscanf(buffer, "%d %d %d %d %f %d %d %f %d %d %d",
            (int*)&u->nom,
            (int*)&u->cibleAttaquable,
            (int*)&u->maposition,
            &u->pointsDeVie,
            &u->vitesseAttaque,
            &u->degats,
            &u->portee,
            &u->vitessedeplacement,
            &u->posX,
            &u->posY,
            &u->peutAttaquer);

        if(res != 11){
            free(u);
            continue;
        }

        // sécurité coordonnées
        if(u->posX < 0 || u->posX >= LARGEURJEU ||
           u->posY < 0 || u->posY >= HAUTEURJEU){
            free(u);
            continue;
        }

        AjouterUnite(roi, u);
        jeu[u->posX][u->posY] = u;
    }

    // ===== HORDE =====
    while(fgets(buffer, sizeof(buffer), f))
    {
        Tunite *u = malloc(sizeof(Tunite));

        int res = sscanf(buffer, "%d %d %d %d %f %d %d %f %d %d %d",
            (int*)&u->nom,
            (int*)&u->cibleAttaquable,
            (int*)&u->maposition,
            &u->pointsDeVie,
            &u->vitesseAttaque,
            &u->degats,
            &u->portee,
            &u->vitessedeplacement,
            &u->posX,
            &u->posY,
            &u->peutAttaquer);

        if(res != 11){
            free(u);
            continue;
        }

        if(u->posX < 0 || u->posX >= LARGEURJEU ||
           u->posY < 0 || u->posY >= HAUTEURJEU){
            free(u);
            continue;
        }

        AjouterUnite(horde, u);
        jeu[u->posX][u->posY] = u;
    }

    fclose(f);
}


