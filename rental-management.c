#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct
{
	char immatriculation[20];
	char marque[20];
    int etat;
	float prix;
}voiture;

typedef struct
{
	char cin[20];
	char nom[20];
	long int  numero;
	
}client;

typedef struct
{
	int annee;
	int mois;
	int jour;
}date;

typedef struct
{
	char cin[20];
	char immatriculation[20];
	float prix;
	date dateSortie;
	date dateRetour;
}gestion;


void afficherVoiture(FILE *f,voiture v)
{
	f=fopen("voitures.bin","r");
	if(f==NULL)
		printf("le fichier nexiste pas\n");
	else
	{	
		printf("Liste des voitures :\n\n");
		do
		{
			fread(&v,sizeof(voiture),1,f);
			if(!feof(f))
				printf("Immatriculation : %s\t\tMarque : %s\t\tEtat : %d\t\tPrix :  %f\n",v.immatriculation,v.marque,v.etat,v.prix);
		}while(!feof(f));
	}
	fclose(f);
}

void afficherClient(FILE *t,client cl)
{
	t=fopen("clients.bin","r");
	if(t==NULL)
		printf("le fichier nexiste pas\n");
	else
	{	
		printf("\n\nListe des locataires :\n\n");
		do
		{
			fread(&cl,sizeof(client),1,t);
			if(!feof(t))
				printf("CIN : %s\tNOM : %s\tNumero : %ld\n",cl.cin,cl.nom,cl.numero);
		}while(!feof(t));
	}
	fclose(t);
}

void ajouterVoiture(FILE *f,voiture v)
{
	char rep;
	f=fopen("voitures.bin","a");

	do
	{
		printf("entrez les info des voitures : \n");
		printf("Immatriculation : \n");
		scanf(" %s",v.immatriculation);
		printf("Marque : \n");
		scanf(" %s",v.marque);
		printf("etat :\n");
		scanf("%d",&v.etat);
		printf("Prix :\n");
		scanf("%f",&v.prix);
		fwrite(&v,sizeof(voiture),1,f);
		printf("Ajouter une voiture o/n :");
		scanf(" %c",&rep);
	}while(rep=='o' || rep=='O');
	fclose(f);
}

void ajouterClient(FILE *t,client cl)
{
	char rep;
	t=fopen("clients.bin","a");

		printf("CIN : \n");
		scanf(" %s",cl.cin);
		printf("Nom : \n");
		scanf(" %s",cl.nom);
		printf("Numero : \n");
		scanf("%ld",&cl.numero);
		fwrite(&cl,sizeof(client),1,t);

	fclose(t);
}
int rechercheclient(FILE *t,client cl,char NM[])
{	
	t=fopen("clients.bin","r");
		do
		{
			fread(&cl,sizeof(client),1,t);
			if(strcmp(NM,cl.cin)==0)
			{
				fclose(t);
				return 1;
			}
		}while(!feof(t));
	fclose(t);
}

int recherchevoiture(FILE *f,voiture v,char IM[])
{
	
	f=fopen("voitures.bin","r");
		do
		{
			fread(&v,sizeof(voiture),1,f);
			if(strcmp(IM,v.immatriculation)==0)
			{
				fclose(f);
				return 1;//Voiture existe
			}
		}while(!feof(f));
		fclose(f);
}
void afficherclientCon(FILE *t,client cl,char IM[])
{
	t=fopen("clients.bin","r");	
		printf("le client :\n");
		do
		{
			fread(&cl,sizeof(client),1,t);
			if(strcmp(IM,cl.cin)==0)
				printf("NOM : %s\tNumero : %ld\n",cl.nom,cl.numero);
		}while(!feof(t));
	fclose(t);
}

void afficherVoitureCon(FILE *f,voiture v,char IM[])
{
	f=fopen("voitures.bin","r");	
		printf("la voiture :\n");
		do
		{
			fread(&v,sizeof(voiture),1,f);
			if(strcmp(IM,v.immatriculation)==0)
				printf("Marque : %s\t\tEtat : %d\t\tPrix : %f\n",v.marque,v.etat,v.prix);
		}while(!feof(f));
	fclose(f);
}
void supprimerVoiture(FILE *f,voiture v,char IM[])
{	

	printf("entrez l'imm a supprimer : ");
	scanf(" %s",IM);
	if(recherchevoiture(f,v,IM)==1)
	{
		FILE * TMP ;
		f=fopen("voitures.bin","r");
		TMP=fopen("etd.bin","w");
		do
		{
			fread(&v,sizeof(voiture),1,f);
			if(strcmp(IM,v.immatriculation)==0)
			{
				printf(".");
			}
			else
			{
				if(!feof(f))
					fwrite(&v,sizeof(voiture),1,TMP);
			}
		}while(!feof(f));
		
		fclose(TMP);
		fclose(f);
		remove("voitures.bin");
		rename("etd.bin","voitures.bin");
			printf("Donnee supp");
	}
	else
	{
		printf("n'existe pas");
	}
}

void supprimerClient(FILE *t,client cl)
{	
	char CIN[20];
	printf("Entrez le CIN du client a supprimer : ");
	scanf(" %s",CIN);
	if(rechercheclient(t,cl,CIN)==1)
	{
		FILE * TMP ;
		t=fopen("clients.bin","r");
		TMP=fopen("etd1.bin","w");
		do
		{
			fread(&cl,sizeof(client),1,t);
			if(strcmp(CIN,cl.cin)==0)
			{
				printf(".");
			}
			else
			{
				if(!feof(t))
					fwrite(&cl,sizeof(client),1,TMP);
			}
		}while(!feof(t));
		
		fclose(TMP);
		fclose(t);
		remove("clients.bin");
		rename("etd1.bin","clients.bin");
		printf("Donnee supp");
	}
	else
	{
		printf("n'existe pas");
	}
}

int CalculJours(date date1, date date2)
{
	int dateSortie, dateRetour, duree;
	
	switch(date1.mois)
	{
		case 1:(date1.mois)=0;
			break;
		case 2:(date1.mois)=31;
			break;
		case 3:(date1.mois)=59;
			break;
		case 4:(date1.mois)=90;
			break;
		case 5:(date1.mois)=120;
			break;
		case 6:(date1.mois)=151;
			break;
		case 7:(date1.mois)=181;
			break;
		case 8:(date1.mois)=212;
			break;
		case 9:(date1.mois)=243;
			break;
		case 10:(date1.mois)=273;
			break;
		case 11:(date1.mois)=304;
			break;
		case 12:(date1.mois)=334;
			break;
	}
	dateSortie=365*((date1.annee)-2021)+(date1.mois)+(date1.jour);
	
	switch(date2.mois)
	{
		case 1:(date2.mois)=0;
			break;
		case 2:(date2.mois)=31;
			break;
		case 3:(date2.mois)=59;
			break;
		case 4:(date2.mois)=90;
			break;
		case 5:(date2.mois)=120;
			break;
		case 6:(date2.mois)=151;
			break;
		case 7:(date2.mois)=181;
			break;
		case 8:(date2.mois)=212;
			break;
		case 9:(date2.mois)=243;
			break;
		case 10:(date2.mois)=273;
			break;
		case 11:(date2.mois)=304;
			break;
		case 12:(date2.mois)=334;
			break;
	}
	dateRetour=365*((date2.annee)-2021)+(date2.mois)+(date2.jour);
	duree=dateRetour-dateSortie;
	return duree;
}

void ecrireg(FILE *x,gestion g,char CN[],char IM[],float PP,date D1,date D2)
{
	x=fopen("location.bin","a");
	printf("\nLe CIN : %s\n",CN);
	strcpy(g.cin,CN);
	printf("IMM : %s\n",IM); 
	strcpy(g.immatriculation,IM);
	printf("Le prix a payer : %.2f\n",PP); 
	g.prix=PP;
	printf("Date sortie : %d/%d/%d\n",D1.jour,D1.mois,D1.annee); 
	g.dateSortie.jour=D1.jour; g.dateSortie.mois=D1.mois; g.dateSortie.annee=D1.annee;
	printf("Date rentree : %d/%d/%d\n",D2.jour,D2.mois,D2.annee); 
	g.dateRetour.jour=D2.jour; g.dateRetour.mois=D2.mois; g.dateRetour.annee=D2.annee;
	fwrite(&g,sizeof(gestion),1,x);
	fclose(x);
}

void louer(FILE * f,FILE * t,FILE * x,voiture v,client cl,date D1,date D2)
{
	char IM[20];
	char IM1[20];
	int duree;
	gestion g;
	float pp;
	f=fopen("voitures.bin","r+");
	t=fopen("clients.bin","r");
	x=fopen("location.bin","a");
	
	printf("Entrez le cin du client  : ");
		scanf(" %s",IM1);
		
	if(rechercheclient(t,cl,IM1)==1)
	{
		printf("\nVoitures disponibles : \n");
		do
		{
			fread(&v,sizeof(voiture),1,f);
			if(v.etat==0)
			{
				if(!feof(f))
					printf("Immatriculation : %s\t\tMarque : %s\t\tPrix : %.2f\n",v.immatriculation,v.marque,v.prix);
			}
		}while(!feof(f));
		
		printf("Entrez l'imm de la voiture voulue : ");
		scanf(" %s",IM);
		if(recherchevoiture(f,v,IM)==1)
		{
			printf("\n Entrez la date de sortie : (jj MM AA) ");
			scanf("%d%d%d",&D1.jour,&D1.mois,&D1.annee);
			printf("\n Entrez la date de rentree : (jj MM AA) ");
			scanf("%d%d%d",&D2.jour,&D2.mois,&D2.annee);
			duree=CalculJours(D1,D2);
			printf("\n la duree est de %d jrs",duree);
			f=fopen("voitures.bin","r+");
			fseek(f,0,0);
			int i=0;
			do
			{
				fread(&v,sizeof(voiture),1,f);
				if(strcmp(IM,v.immatriculation)==0)
				{
					pp=duree*(v.prix);
					fseek(f,i*(sizeof(voiture)),SEEK_SET);
					v.etat=1;
					fwrite(&v,sizeof(voiture),1,f);
					break;
				}
				i++;
			}while(!feof(f));
			fclose(f);
		}
		ecrireg(x,g,IM1,IM,pp,D1,D2);
		
	fclose(f);
	fclose(t);
	fclose(x);
	}
	else
	{
		printf("\nCe client ne figure pas dans la liste \n");
		ajouterClient(t,cl);	
		printf("\nVoitures disponibles : \n");
		do
		{
			fread(&v,sizeof(voiture),1,f);
			if(v.etat==0)
			{
				if(!feof(f))
					printf("Immatriculation : %s\t\tMarque : %s\t\tPrix : %.2f\n",v.immatriculation,v.marque,v.prix);
			}
		}while(!feof(f));
		
		printf("Entrez l'imm de la voiture voulue : ");
		scanf(" %s",IM);
		if(recherchevoiture(f,v,IM)==1)
		{
			printf("\n Entrez la date de sortie : (jj/MM/AA) ");
			scanf("%d%d%d",&D1.jour,&D1.mois,&D1.annee);
			printf("\n Entrez la date de rentree : (jj/MM/AA) ");
			scanf("%d%d%d",&D2.jour,&D2.mois,&D2.annee);
			duree=CalculJours(D1,D2);
			printf("\n la duree est de %d jrs",duree);
			f=fopen("voitures.bin","r+");
			fseek(f,0,0);
			int i=0;
			do
			{
				fread(&v,sizeof(voiture),1,f);
				if(strcmp(IM,v.immatriculation)==0)
				{
					pp=duree*(v.prix);
					fseek(f,i*(sizeof(voiture)),SEEK_SET);
					v.etat=1;
					fwrite(&v,sizeof(voiture),1,f);
					break;
				}
				i++;
			}while(!feof(f));
			fclose(f);
		}
		ecrireg(x,g,IM1,IM,pp,D1,D2);
	}
	fclose(f);
	fclose(t);
	fclose(x);
}

void VoitureLibre(FILE * f,voiture v)
{
	f=fopen("voitures.bin","r");
		printf("\nVoitures Libres : \n");
		do
		{
			fread(&v,sizeof(voiture),1,f);
			if(v.etat==0)
			{
				if(!feof(f))
					printf("Immatriculation : %s\t\tMarque : %s\t\tPrix : %.2f\n",v.immatriculation,v.marque,v.prix);
			}
		}while(!feof(f));
}
void VoitureLouee(FILE *f,voiture v)
{
		f=fopen("voitures.bin","r+");
		printf("\nVoitures louees : \n");
		do
		{
			fread(&v,sizeof(voiture),1,f);
			if(v.etat==1)
			{
				if(!feof(f))
					printf("Immatriculation : %s\t\tMarque : %s\t\tPrix : %.2f\n",v.immatriculation,v.marque,v.prix);
			}
		}while(!feof(f));
}

void afficherG(FILE *x,gestion g)
{
	x=fopen("location.bin","r");
	
	if(x==NULL)
		printf("le fichier nexiste pas\n");
	else
	{	
		printf("Listes :\n\n");
		do
		{
			fread(&g,sizeof(gestion),1,x);
			if(!feof(x))
				printf("CIN : %s\tIMM : %s\t Le prixP : %.2f\t DATESOR : %d/%d/%d\t DATERET : %d/%d/%d\n",g.cin,g.immatriculation,g.prix,g.dateSortie.jour,g.dateSortie.mois,g.dateSortie.annee,g.dateRetour.jour,g.dateRetour.mois,g.dateRetour.annee);
		}while(!feof(x));
	}
	fclose(x);
}


int main()
{
	FILE * f;
	FILE * t;
	FILE * x;
	voiture v;
	client cl;
	gestion g;
	int choix1;
	char choix2;
	char IM[20],IM1[20],IM2[20];
	int s,z,i,w;
	date date1, date2;
		system("COLOR 1E");
	
	printf("\n\n\n\n\n\n\n");
	printf("        **     *********  *********  **********  **   ******   **       **\n");       
	printf("      ******   *********  *********  **********  **  ********  ***      **\n");
	printf("     ********  **         **             **      **  **    **  ****     **\n");
	printf("    ***        **         **             **      **  **    **  ** **    **\n");
	printf("    **         *********  *********      **      **  **    **  **  **   **\n");
	printf("    **         *********  *********      **      **  **    **  **   **  **\n");
	printf("    **    ***  **                **      **      **  **    **  **    ** **\n");
	printf("    ***   ***  **                **      **      **  **    **  **     ****\n");
	printf("     ********  *********  *********      **      **  ********  **      ***\n");
	printf("      *****    *********  *********      **      **   ******   **       **\n");
	printf("\n\n\n\n\n\n\n");
//	Sleep(1500);
	system("cls");
	printf("\n\n\n\n\n\n\n");
	printf("                             ********    *********                         \n");
	printf("                             *********   *********                         \n");
	printf("                             **     ***  **                                \n");
	printf("                             **     ***  **                                \n");
	printf("                             **     ***  *********                         \n");
	printf("                             **     ***  *********                         \n");
	printf("                             **     ***  **                                \n");
	printf("     	                     **     ***  **                                \n");
	printf("                             *********   *********                         \n");
	printf("                             ********    *********                         \n");
	printf("\n\n\n\n\n\n\n");
//	Sleep(1500);
	system("cls");
	printf("\n\n\n\n\n\n\n");
	printf("	**         ******    *******   ********** ********  **   ******    **       ** \n");         
	printf("	**        *********  *******   ********** ********  **  ********   ***      ** \n");      
	printf("	**        **     **  **        **      **    **     **  **    **   ***      ** \n");
	printf("	**        **     **  **        **      **    **     **  **    **   ** **    ** \n");
	printf("	**        **     **  **        **********    **     **  **    **   **  **   ** \n");
	printf("	**        **     **  **        **      **    **     **  **    **   **   **  ** \n");
	printf("	**        **     **  **        **      **    **     **  **    **   **    ** ** \n");
	printf("	**        **     **  **        **      **    **     **  **    **   **     **** \n");
	printf("	******    *********  ******    **      **    **     **  ********   **      *** \n");
	printf("	******     *******   *******   **      **    **     **   ******    **       ** \n");
	printf("\n\n\n\n\n\n\n");
	//Sleep(1500);
	system("cls");

	system("COLOR 1E");

	printf("\n\n\n\n                 GESTION LOCATION DE VOITURE \n\n");printf("\n\n");
	for(s=0;s<80;s++)
			putchar(260);
	printf("\n");
        printf("                      ________________                           \n");
		printf("                    /                  --<---<---<--             \n");
		printf("             _ ___/                     --<---<---<--            \n");
		printf("            |__ __                  ______ --<---<---<--         \n");
	    printf("                  (__)----------(__)                             \n");
		for(z=0;z<80;z++)
			putchar(260);printf("\n\n");

		
	
    printf("\n\n\n\tChargement");
	for(i=1;i<20;i++)
	{
		
		//Sleep(200);//attente
			printf(".");
		
	}system("cls");
	
	do
	{
		system("cls");
		printf("      ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ MENU ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\n");
		printf("      º   -----------------------------------------------------  º\n");
		printf("      º  (  | 1 | Gestion des clients                          ) º\n");
        printf("      º                                                          º\n");
        printf("      º  (  | 2 | Gestion des voitures                         ) º\n");
        printf("      º                                                          º\n");
        printf("      º  (  | 3 | Gestion de location                          ) º\n");
        printf("      º                                                          º\n");
        printf("      º  (  | 4 | EXIT                                         ) º\n");
        printf("      º   -----------------------------------------------------  º\n");
        printf("      ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼\n");

    	printf("      *        Entrer Votre Choix                    *\t");
    	scanf("%d",&choix1);
		switch(choix1)
		{
			case 1 :   do
						{						 
						 system("cls");
				       	 printf("      ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ GESTION DES CLIENTS ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\n");
					   	 printf("      º   -----------------------------------------------------  º\n");
						 printf("      º  (  | A | Afficher les Clients                         ) º\n");
						 printf("      º                                                          º\n");
						 printf("      º  (  | B | Chercher Client                              ) º\n");
						 printf("      º                                                          º\n");
						 printf("      º  (  | C | Supprimer Client                             ) º\n");
						 printf("      º                                                          º\n");
						 printf("      º  (  | E | RETOUR                                       ) º\n");
						 printf("      º   -----------------------------------------------------  º\n");
       					 printf("      ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼\n");

    					 printf("      *        Entrer Votre Choix                    *\t");					 
						 scanf(" %c",&choix2);
						 switch(choix2)
						 {
						 	case 'A' :  afficherClient(t,cl);
						 				break;
						 	case 'B' :  printf("entrez le CIN du client : ");
										scanf(" %s",IM2);
							 			if(rechercheclient(t,cl,IM2)==1)
							 			{
											afficherclientCon(t,cl,IM2);
										}
										else
											printf("Le client n'existe pas ");
						 				break;
						 	case 'C' : supprimerClient(t,cl);
						 				break;
						 	case 'E' : printf(" retourner au menu principal\n") ;
						 				break;
						 	default  : printf("Choix errone\n");
						 }
						 getch();
						}
						while(choix2!='E');
					 break;			 
			case 2 :   do
						{						 
						 system("cls");
				         printf("      ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ GESTION DES VOITURES ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\n");
					   	 printf("      º   -----------------------------------------------------  º\n");
						 printf("      º  (  | A | Ajouter Voitures                             ) º\n");
						 printf("      º                                                          º\n");
						 printf("      º  (  | B | Afficher les Voitures                        ) º\n");
						 printf("      º                                                          º\n");
						 printf("      º  (  | C | Chercher voiture                             ) º\n");
						 printf("      º                                                          º\n");
						 printf("      º  (  | D | Supprimer voiture                            ) º\n");
						 printf("      º                                                          º\n");
						 printf("      º  (  | E | RETOUR                                       ) º\n");
						 printf("      º   -----------------------------------------------------  º\n");
       					 printf("      ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼\n");

    				   	 printf("      *        Entrer Votre Choix                    *\t");							 
						 scanf(" %c",&choix2);
						 switch(choix2)
						 {
						 	case 'A' :  ajouterVoiture(f,v);
						 				break;
						 	case 'B' :  afficherVoiture(f,v);
						 				break;
						 	case 'C' :	printf("Entrez IMM : ");
										scanf(" %s",IM);
								 		if(recherchevoiture(f,v,IM)==1)//voiture trouvee
										{
											afficherVoitureCon(f,v,IM);
										}
										else
											printf("La voiture n'existe pas ");
										break;
						 	case 'D' : supprimerVoiture(f,v,IM1);
						 				break;
						 	case 'E' : printf(" retourner au menu principal\n") ;
						 				break;
						 	default  : printf("Choix errone\n");
						 }
						 getch();
						}
						while(choix2!='E');
					 break;			 
			case 3 :  do
						{						 
						 system("cls");
						  printf("      ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ GESTION DES VOITURES ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\n");
					   	 printf("      º   -----------------------------------------------------  º\n");
						 printf("      º  (  | A | Afficher les voitures libres                 ) º\n");
						 printf("      º                                                          º\n");
						 printf("      º  (  | B | Afficher les Voitures prises                 ) º\n");
						 printf("      º                                                          º\n");
						 printf("      º  (  | C | Louer voiture                                ) º\n");
						 printf("      º                                                          º\n");
						 printf("      º  (  | D | Afficher toutes les donnees en cours         ) º\n");
						 printf("      º                                                          º\n");
						 printf("      º  (  | E | RETOUR                                       ) º\n");
						 printf("      º   -----------------------------------------------------  º\n");
       					 printf("      ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼\n");

    					 printf("      *        Entrer Votre Choix                    *\t");			 
						 scanf(" %c",&choix2);
						 switch(choix2)
						 {
						 	case 'A' :	VoitureLibre(f,v);	
						 				break;
						 	case 'B' : VoitureLouee(f,v);
						 				break;
						 	case 'C' : louer(f,t,x,v,cl,date1,date2);
						 				break;
						 	case 'D' : afficherG(x,g);
						 				break;
						 	case 'E' : printf(" retourner au menu principal\n") ;
						 				break;
						 	default  : printf("Choix errone\n");
						 }
						 getch();
						}
						while(choix2!='E');
					 break;			 
			case 4 : printf("Vous avez choisi de quitter\n");
					 break;				 				 	
			default :printf("Choix errone"); 	 
		}
		getch();
	}
	while(choix1!=4);	
}
