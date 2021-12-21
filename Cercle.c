#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct{
    double x;
    double y;
}Point;

typedef struct{
    Point centre;
    double rayon;
}Cercle;

void saisir_point(Point *);
void afficher_point(Point);
void equation(Cercle);
void equation2(Point, Point);
bool concentriques(Cercle, Cercle);
void generer_points_alea(Point [], int);

int nbr_points_appartenant_cercle(Point [], int, Cercle);
int nbr_points_appartenant_disque(Point [], int, Cercle);
double evaluation(int);

void main(){
    printf("pi_montecarlo = %.5f\n", evaluation(100000));
    printf("fin du programme.\n");
}

void saisir_point(Point * M){
    printf("Entrer l'absisse du point : ");
    scanf("%lf", &M->x);
    printf("Entrer l'ordonnee du point : ");
    scanf("%lf", &M->y);
}

void afficher_point(Point M){
    printf("Point (%.2f,%.2f)\n", M.x, M.y);
}

void equation2(Point C, Point M){
    Cercle cc = {C, sqrt(pow(M.x-C.x, 2)+pow(M.y-C.y, 2))};
    equation(cc);
}

void equation(Cercle c){
    printf("(x-%.2f)2 + (y-%.2f)2 = %.2f\n", 
        c.centre.x, 
        c.centre.y, 
        pow(c.rayon, 2)
    );
}

bool concentriques(Cercle c1, Cercle c2){
    return c1.centre.x == c2.centre.x && c1.centre.y == c2.centre.y;
}

void generer_points_alea(Point t[], int n){
    int i;
    for(i=0; i<n; i++){
        t[i].x = (double) rand() / ((unsigned) RAND_MAX+1);
        t[i].y = (double) rand() / ((unsigned) RAND_MAX+1);
    }
}

int nbr_points_appartenant_cercle(Point t[], int n, Cercle c){
    int i, compteur = 0;
    for(i=0; i<n; i++)
        if(pow(c.rayon, 2) == pow(t[i].x-c.centre.x, 2)+pow(t[i].y-c.centre.y, 2))
            compteur++;
    return compteur;
}

int nbr_points_appartenant_disque(Point t[], int n, Cercle c){
    int i, compteur = 0;
    for(i=0; i<n; i++)
        if(pow(c.rayon, 2) >= pow(t[i].x-c.centre.x, 2)+pow(t[i].y-c.centre.y, 2))
            compteur++;
    return compteur;
}

double evaluation(int n){
    Point t[n];
    Point p = {0.5, 0.5};
    Cercle c = {p, 0.5};
    int N; 
    generer_points_alea(t, n);
    N = nbr_points_appartenant_disque(t, n, c);
    return 4*N/(double)n;
}
