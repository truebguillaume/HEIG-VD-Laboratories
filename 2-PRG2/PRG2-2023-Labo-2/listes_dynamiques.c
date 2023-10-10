/*
 -----------------------------------------------------------------------------------
 Nom du fichier : listes_dynamiques.c
 Auteur(s)      : Valentin Ricard, Gwendal Piemontesi, Guillaume Trueb
 Date creation  : 03.05.2023

 Description    : Implémentation du listes_dynamiques.h correspondant.

 Remarque(s)    : Ce fichier dépend entièrement du fichier listes_dynamiques.h
                  qui ne doit pas être modifie.

 Compilateur    : Mingw-w64 gcc 12.2.0
 -----------------------------------------------------------------------------------
*/

#include <stdlib.h>
#include <stdio.h>
#include "listes_dynamiques.h"

// Fonction interne permettant de supprimer un maillon, et de retourner le suivant.
Element* supprimerMaillon(Element* element) {
	Element* suivant = element->suivant;
	free(element);
	return suivant;
}

Liste* initialiser(void) {
	Liste* element = malloc(sizeof(Liste));
	*element = (Liste) {NULL, NULL};
	return element;
}

bool estVide(const Liste* liste) {
	// NOTE D'IMPLEMENTATION :
	// Si la liste est vide <=> la tête n'est pas définie, donc le pointeur est NULL.
	// Il est inutile de vérifier la queue, car elle sera définie dès que la tête le sera
	// (du moins en théorie)
	return liste->tete == NULL;
}

size_t longueur(const Liste* liste) {

	const Element* elementActuel = liste->tete;
	size_t taille = 0;

	while (elementActuel != NULL) {
		elementActuel = elementActuel->suivant;
		++taille;
	}

	return taille;
}

void afficher(const Liste* liste, Mode mode) {
	Element* elementActuel;
	switch (mode) {
		case FORWARD:
			elementActuel = liste->tete;
			break;
		case BACKWARD:
			elementActuel = liste->queue;
			break;
	}

	bool first = true;
	printf("[");
	while (elementActuel != NULL) {
		if (!first) {
			printf(",");
		} else {
			first = false;
		}

		printf("%d", elementActuel->info);
		switch (mode) {
			case FORWARD:
				elementActuel = elementActuel->suivant;
				break;
			case BACKWARD:
				elementActuel = elementActuel->precedent;
				break;
		}
	}

	printf("]\n");
}

Status insererEnTete(Liste* liste, const Info* info) {
	Element* nouvelElement = malloc(sizeof(Element));

	// Contrôle si l'allocation a réussie
	if (nouvelElement == NULL) {
		return MEMOIRE_INSUFFISANTE;
	}

	nouvelElement->info = *info;
	nouvelElement->suivant = liste->tete;
	nouvelElement->precedent = NULL;

	// Si la liste est vide, il faut aussi mettre la queue à l'élément cree
	if (estVide(liste)) {
		liste->queue = nouvelElement;
	} else {
		liste->tete->precedent = nouvelElement;
	}

	liste->tete = nouvelElement;

	return OK;
}

Status insererEnQueue(Liste* liste, const Info* info) {
	Element* nouvelElement = malloc(sizeof(Element));

	// Contrôle si l'allocation a réussie
	if (nouvelElement == NULL) {
		return MEMOIRE_INSUFFISANTE;
	}

	nouvelElement->info = *info;
	nouvelElement->precedent = liste->queue;
	nouvelElement->suivant = NULL;

	// Si la liste est vide, il faut aussi mettre la tête à l'élément cree
	if (estVide(liste)) {
		liste->tete = nouvelElement;
	} else {
		liste->queue->suivant = nouvelElement;
	}
	liste->queue = nouvelElement;

	return OK;
}

Status supprimerEnTete(Liste* liste, Info* info) {

	if (estVide(liste)) {
		return LISTE_VIDE;
	}

	if (info != NULL) {
		*info = liste->tete->info;
	}

	// On définit la nouvelle tête de liste, et on enlève l'info du précédent.
	liste->tete = supprimerMaillon(liste->tete);

	if (liste->tete != NULL) {
		liste->tete->precedent = NULL;
	} else {
		liste->queue = NULL;
	}

	return OK;
}

Status supprimerEnQueue(Liste* liste, Info* info) {
	//si la liste est vide on retourne un status
	if (estVide(liste)) {
		return LISTE_VIDE;
	}

	Element* aSupprimer = liste->queue;
	if (info != NULL) {
		*info = aSupprimer->info;
	}

	liste->queue = aSupprimer->precedent;

	free(aSupprimer);

	// Si la queue == NULL, alors la liste est vide
	// Il faut donc mettre la tête à null.
	if (liste->queue == NULL) {
		liste->tete = NULL;
	} else {
		liste->queue->suivant = NULL;
	}

	return OK;
}

void supprimerSelonCritere(Liste* liste,
									bool (* critere)(size_t position, const Info* info)) {
	size_t position = 0;
	Element* actuel = liste->tete;
	// Pour le cas ou la liste est nulle.
	liste->tete = NULL;
	Element* dernierValide = NULL;
	while (actuel != NULL) {
		if (critere(position, &actuel->info)) {
			if (dernierValide == NULL) {
				liste->tete = actuel;
				actuel->precedent = NULL;
			} else {
				dernierValide->suivant = actuel;
				actuel->precedent = dernierValide;
			}
			dernierValide = actuel;
			actuel = actuel->suivant;
		} else {
			actuel = supprimerMaillon(actuel);
		}

		++position;
	}

	dernierValide->suivant = NULL;
	liste->queue = dernierValide;
}

void vider(Liste* liste, size_t position) {

	Element* elementDebutVider = liste->tete;

	// Décale sur le premier élément à supprimer
	// NB : si position = 0 alors on restera sur liste->tete pour elementDebutVider
	for (size_t i = 0; i < position; ++i) {
		elementDebutVider = elementDebutVider->suivant;
		if (elementDebutVider == NULL) {
			return;
		}
	}

	if (position == 0) {
		// Mets à NULL la tête et la queue de la liste
		liste->tete = liste->queue = NULL;
	} else {
		// Mets à NULL le pointeur sur le dernier élément de la liste
		Element* nouveauDernier = elementDebutVider->precedent;
		nouveauDernier->suivant = NULL;
		liste->queue = nouveauDernier;
	}

	// Supprime les éléments jusqu'à trouver un pointeur NULL
	while (elementDebutVider != NULL) {
		elementDebutVider = supprimerMaillon(elementDebutVider);
	}
}

bool sontEgales(const Liste* liste1, const Liste* liste2) {
	//Si les deux pointeurs pointent vers la même liste, elles sont égales
	if (liste1 == liste2) {
		return true;
	}

	//les listes n'ont pas la meme taille on retourne false
	if (longueur(liste1) != longueur(liste2)) {
		return false;
	}

	Element* lhs = liste1->tete;
	Element* rhs = liste2->tete;

	while (lhs != NULL) {
		if (lhs->info != rhs->info) {
			return false;
		}

		lhs = lhs->suivant;
		rhs = rhs->suivant;
	}
	return true;
}