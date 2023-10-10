/*
 -----------------------------------------------------------------------------------
 Nom du fichier : main.c
 Auteur(s)      : Valentin Ricard, Gwendal Piemontesi, Guillaume Trueb
 Date creation  : 03.05.2023

 Description    : Fichier de test de l'implémentation des listes dynamiques.

 Remarque(s)    : 1. Le design des macros est forcement inspiré de la librairie https://github.com/doctest/doctest
                  2. Ce fichier génère des résultats dans la console. Il est ensuite nécessaire de le comparer à un
                  résultat attendu, disponible dans le rendu.

 Compilateur    : Mingw-w64 gcc 12.2.0
 -----------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <assert.h>
#include "listes_dynamiques.h"

#define RULER "-------------------------------\n"
// Le point virgule est souhaité pour donner une apparence de fonction aux blocs de tests
#define TEST(texte) printf("%-20s" RULER, texte);
// Affiche une liste, pour la comparaison avec un fichier texte
#define VALIDATION(texte, liste)              \
    printf(" -> " texte " : \n    ");         \
    afficher(liste, FORWARD); printf("    "); \
    afficher(liste, BACKWARD)
// Affiche un résultat OK si l'assertion passe (si elle passe pas, le programme crash, donc la ligne est pas affichée)
#define ASSERT_VERBEUX(assertion) assert(assertion); printf(" -> " #assertion " (ligne %d) OK\n", __LINE__)

/**
 * Fonction de test, utilisée pour tester la suppression par condition.
 * @param position La position de l'élément
 * @param info L'élément
 * @return `true` si l'élément doit être supprimé, `false` sinon
 */
bool positionPaire(size_t position, const Info* info);


#define TAILLE_TABLEAU_TEST 20

/**
 * Génère une liste de test, de taille TAILLE_TABLEAU_TEST
 *
 * NOTE:
 *   - La liste retournée doit être consistante (toujours identique)
 *   - La modification du retour de cette fonction nécessite une mise a jour du fichier d'assertion.
 *
 * @return Une liste de test
 */
Liste* genererListeDeTest();

Liste* genererListeAvecTaille(size_t taille);

int main() {

	TEST("Initialiser")
	{
		Liste* liste = initialiser();
		VALIDATION("Initialisation", liste);
	}

	TEST("estVide")
	{
		Liste* listeVide = initialiser();
		VALIDATION("Liste vide", listeVide);
		ASSERT_VERBEUX(estVide(listeVide));

		Liste* listeNonVide = genererListeDeTest();
		VALIDATION("Liste non vide", listeNonVide);
		ASSERT_VERBEUX(!estVide(listeNonVide));
	}

	TEST("Insertion en tete")
	{
		Liste* liste = initialiser();

		Info info = 0;

		insererEnTete(liste, &info);
		++info;
		insererEnTete(liste, &info);
		++info;
		insererEnTete(liste, &info);

		VALIDATION("Liste insertion en tete", liste);
	}

	TEST("Insertion en queue")
	{
		Liste* liste = initialiser();
		Info info = 0;

		insererEnQueue(liste, &info);
		++info;
		insererEnQueue(liste, &info);
		++info;
		insererEnQueue(liste, &info);

		VALIDATION("Liste insertion en queue", liste);
	}

	TEST("Vider liste")
	{
		Liste* liste = genererListeDeTest();
		VALIDATION("Liste a vider", genererListeDeTest());

		vider(liste, 3);
		VALIDATION("Liste videe a partir de 3", liste);

		vider(liste, 0);
		VALIDATION("Liste totalement videe", liste);
		ASSERT_VERBEUX(estVide(liste));
	}

	TEST("Longueur")
	{
		Liste* listeVide = initialiser();
		ASSERT_VERBEUX(longueur(listeVide) == 0);

		Liste* listeGeneree = genererListeDeTest();
		ASSERT_VERBEUX(longueur(listeGeneree) == TAILLE_TABLEAU_TEST);
	}

	TEST("Suppression en tete")
	{
		Liste* liste = genererListeDeTest();
		VALIDATION("Liste initiale", liste);
		Info valeurAttendue = liste->tete->info;
		Info valeurRecuperee;
		supprimerEnTete(liste, &valeurRecuperee);
		VALIDATION("Liste initiale moins 1", liste);
		ASSERT_VERBEUX(valeurRecuperee == valeurAttendue);

		Liste* listeVide = initialiser();
		VALIDATION("Liste vide", listeVide);
		ASSERT_VERBEUX(supprimerEnTete(listeVide, &valeurRecuperee) == LISTE_VIDE);

		// Un bug a été découvert quand la taille == 1
		Liste* listeTaille1 = genererListeAvecTaille(1);
		VALIDATION("Liste taille 1", listeTaille1);
		supprimerEnTete(listeTaille1, &valeurRecuperee);
		VALIDATION("Liste taille 1 moins 1", listeTaille1);
	}

	TEST("Suppression en queue")
	{
		Liste* liste = genererListeDeTest();
		VALIDATION("Liste initiale", liste);
		Info valeurAttendue = liste->queue->info;
		Info valeurRecuperee;
		supprimerEnQueue(liste, &valeurRecuperee);
		VALIDATION("Liste initiale moins 1", liste);
		ASSERT_VERBEUX(valeurRecuperee == valeurAttendue);

		Liste* listeVide = initialiser();
		VALIDATION("Liste vide", listeVide);
		ASSERT_VERBEUX(supprimerEnQueue(listeVide, &valeurRecuperee) == LISTE_VIDE);

		// Un bug a été découvert quand la taille == 1
		Liste* listeTaille1 = genererListeAvecTaille(1);
		VALIDATION("Liste taille 1", listeTaille1);
		supprimerEnQueue(listeTaille1, &valeurRecuperee);
		VALIDATION("Liste taille 1 moins 1", listeTaille1);
	}

	TEST("Suppression selon critere")
	{
		Liste* liste = genererListeDeTest();
		VALIDATION("Liste initiale", liste);
		supprimerSelonCritere(liste, positionPaire);
		VALIDATION("Liste apres suppression", liste);
	}

	TEST("Egalite")
	{
		Liste* reference = genererListeDeTest();
		VALIDATION("Liste de reference", reference);

		Liste* autre = genererListeDeTest();
		VALIDATION("Liste identique", autre);
		ASSERT_VERBEUX(sontEgales(reference, autre));
		// On change un élément à la fin
		autre->queue->info = 52;
		VALIDATION("Liste changee", autre);
		ASSERT_VERBEUX(!sontEgales(reference, autre));

		// On change la taille
		supprimerEnQueue(autre, NULL);
		VALIDATION("Liste moins un element", autre);
		ASSERT_VERBEUX(!sontEgales(reference, autre));
	}
}

Liste* genererListeAvecTaille(size_t taille) {
	Liste* liste = initialiser();
	int valeurAInserer;
	// Si on demande un nombre impair, en générer un de moins
	for (int i = 0; i < taille / 2; ++i) {
		valeurAInserer = i * 2;
		insererEnTete(liste, &valeurAInserer);
		valeurAInserer = -(i * 2 + 1);
		insererEnQueue(liste, &valeurAInserer);
	}

	if (taille % 2 != 0) {
		valeurAInserer = -(long) taille;
		insererEnQueue(liste, &valeurAInserer);
	}

	return liste;
}

Liste* genererListeDeTest() {
	return genererListeAvecTaille(TAILLE_TABLEAU_TEST);
}


bool positionPaire(size_t position, const Info* _) {
	return position % 2 == 0;
}
