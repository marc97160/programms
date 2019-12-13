#include <SPI.h>
#include <Ethernet.h>
#include <EEPROM.h>




byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //physical mac address

EthernetServer server(80); //server port
EthernetClient client;


char DEVID1[] = "v4FCED700272645B";        //Scenario : "La zone 1 en alarme"
char DEVID2[] = "vFF2B8A098734562";        //Scenario : "La zone 2 en alarme"
char DEVID3[] = "vB91D1E4981A8F66";        //Scenario : "La zone 3 en alarme"
char DEVID4[] = "v645090B332FBEB6";        //Scenario : "La zone 4 en alarme"
char DEVID5[] = "vAC252B79D944F5F";        //Scenario : "La zone 5 en alarme"
char DEVID6[] = "v4FD1E7F75C66B44";        //Scenario : "La zone 6 en alarme"
char DEVID7[] = "vC7146FD761EBDEA";        //Scenario : "La zone 7 en alarme"
char DEVID8[] = "v2F1DA6D970D7002";        //Scenario : "La zone 8 en alarme"


int etatSortie=0;//variable refletant la sortie de la sirene 0-> repos  1 ->active
boolean sireneActive=false;
unsigned long tempsSirene;

char serverName[] = "api.pushingbox.com";

String readString;

// variables pour stocker l'etat des zones

int etatZone1=1;
int etatZone2=1;
int etatZone3=1;
int etatZone4=1;
int etatZone5=1;
int etatZone6=1;
int etatZone7=1;
int etatZone8=1;


int etatZone1pre=1;
int etatZone2pre=1;
int etatZone3pre=1;
int etatZone4pre=1;
int etatZone5pre=1;
int etatZone6pre=1;
int etatZone7pre=1;
int etatZone8pre=1;

// variable a transmettre a l'application
int enService=0;  //variable indiquant l'etat de l'alarme (marche/arret) 0-> arret  1 ->marche
int infoZoneOuverte=0; //variable indiquant si une des zones est ouverte 0-> toutes les zones sont fermées  1-> une des zones est ouverte
int infoEnAlarme=0; // variable indiquant si l'alarme est déclencher   0-> non   1 -> oui 

String copyReadString;
String code=" ";
char code2[6]=" ";

int notificationZone1=1;  //au demarrage toutes les zones peuvent envoyer des notifications  
int notificationZone2=1;  
int notificationZone3=1;  
int notificationZone4=1;  
int notificationZone5=1;  
int notificationZone6=1;  
int notificationZone7=1;  
int notificationZone8=1;  


boolean codeok=false;
int i=0;
int cc=0;
int notif=0;
int a=0;


int cptz1=0;
int cptz2=0;
int cptz3=0;
int cptz4=0;
int cptz5=0;
int cptz6=0;
int cptz7=0;
int cptz8=0;

int zone1Alarme = 1;
int zone2Alarme = 1;
int zone3Alarme = 1;
int zone4Alarme = 1;
int zone5Alarme = 1;
int zone6Alarme = 1;
int zone7Alarme = 1;
int zone8Alarme = 1;

int zone1Ouvert = 1;
int zone2Ouvert = 1;
int zone3Ouvert = 1;
int zone4Ouvert = 1;
int zone5Ouvert = 1;
int zone6Ouvert = 1;
int zone7Ouvert = 1;
int zone8Ouvert = 1;



int sortieAlarme=4; //la sirene est branché sur la sortie numero 4

//////////////////////

void setup(){

  pinMode(4, OUTPUT);// la sortie 4 est declarée en sortie pour la sirene

// definition des zones de l'alarme en entree
  pinMode(5, INPUT); 
  pinMode(6, INPUT);
  pinMode(7, INPUT); 
  pinMode(8, INPUT);
  pinMode(9, INPUT); 
  pinMode(10, INPUT);
  pinMode(11, INPUT); 
  pinMode(12, INPUT);
 

  Serial.begin(9600);
  while (!Serial) continue;

 // Ethernet.begin(mac, ip, subnet, gateway);
  // Initialize Ethernet libary
  if (!Ethernet.begin(mac)) {
    Serial.println(F("Failed to initialize Ethernet library"));
    return;
  }

  
  server.begin();
  Serial.println(F("Server is ready."));
  Serial.print(F("Please connect to http://"));
  Serial.println(Ethernet.localIP());
  
}




void loop(){

//cette boucle active la sirene si il y a un déclenchement
  
  if (sireneActive)//si il y a une alarme

   {
        etatSortie=1;//on passe la variable a 1 pour activer la sirene
       
       if ((millis()-tempsSirene)>10000)  //temps de declenchement sirene 10 secondes 
          {
            sireneActive=false;
            etatSortie=0;
       }
   }

    etatZone1pre=etatZone1;
    etatZone2pre=etatZone2;
    etatZone3pre=etatZone3;
    etatZone4pre=etatZone4;
    etatZone5pre=etatZone5;
    etatZone6pre=etatZone6;
    etatZone7pre=etatZone7;
    etatZone8pre=etatZone8;


    delay(10); 


    //lecture de l'etat des entrees de l'alarme
    etatZone1=digitalRead(5);
    etatZone2=digitalRead(6);
    etatZone3=digitalRead(7);
    etatZone4=digitalRead(8);
    etatZone5=digitalRead(9);
    etatZone6=1;
    etatZone7=1;
    etatZone8=1;

    zone1Ouvert=etatZone1;
    zone2Ouvert=etatZone2;
    zone3Ouvert=etatZone3;
    zone4Ouvert=etatZone4;
    zone5Ouvert=etatZone5;
    zone6Ouvert=etatZone6;
    zone7Ouvert=etatZone7;
    zone8Ouvert=etatZone8;

    if (etatZone1&&etatZone2&&etatZone3&&etatZone4&&etatZone5&&etatZone6&&etatZone7&&etatZone8) 
    infoZoneOuverte = 0;

//zone 1
   if ((etatZone1 != etatZone1pre) && enService == 1)
      { 
        infoEnAlarme = 1;
        infoZoneOuverte = 0;
        sireneActive = true;
        tempsSirene = millis ();
        zone1Alarme=0;
              
   if (notificationZone1 == 1)  //si il y a une alarme on transmet la memoire
          {
           sendToPushingBox(DEVID1);
           cptz1=1;
          }
      }
//zone 2

  if ((etatZone2 != etatZone2pre) && enService == 1)
      { 
        infoEnAlarme = 1;
        infoZoneOuverte = 0;
        sireneActive = true;
        tempsSirene = millis ();
        zone2Alarme=0;
              
   if (notificationZone2 == 1)  //si il y a une alarme on transmet la memoire
          {
           sendToPushingBox(DEVID2);
           cptz2=1;
          }
      }

//zone 3

  if ((etatZone3 != etatZone3pre) && enService == 1 )
      { 
        infoEnAlarme = 1;
        infoZoneOuverte = 0;
        sireneActive = true;
        tempsSirene = millis ();
        zone3Alarme=0;
              
   if (notificationZone3 == 1 )  //si il y a une alarme on transmet la memoire
          {
           sendToPushingBox(DEVID3);
           cptz3=1;
          }
      }

//zone 4

  if ((etatZone4 != etatZone4pre) && enService == 1 )
      { 
        infoEnAlarme = 1;
        infoZoneOuverte = 0;
        sireneActive = true;
        tempsSirene = millis ();
        zone4Alarme=0;
              
   if (notificationZone4 == 1 )  //si il y a une alarme on transmet la memoire
          {
           sendToPushingBox(DEVID4);
           cptz4=1;
          }
      }

//zone 5

  if ((etatZone5 != etatZone5pre) && enService == 1)
      { 
        infoEnAlarme = 1;
        infoZoneOuverte = 0;
        sireneActive = true;
        tempsSirene = millis ();
        zone5Alarme=0;
              
   if (notificationZone5 == 1)  //si il y a une alarme on transmet la memoire
          {
           sendToPushingBox(DEVID5);
           cptz5=1;
          }
      }

//zone 6

  if ((etatZone6 != etatZone6pre) && enService == 1)
      { 
        infoEnAlarme = 1;
        infoZoneOuverte = 0;
        sireneActive = true;
        tempsSirene = millis ();
        zone6Alarme=0;
              
   if (notificationZone6 == 1)  //si il y a une alarme on transmet la memoire
          {
           sendToPushingBox(DEVID6);
           cptz6=1;
          }
      }

//zone 7

  if ((etatZone7 != etatZone7pre) && enService == 1)
      { 
        infoEnAlarme = 1;
        infoZoneOuverte = 0;
        sireneActive = true;
        tempsSirene = millis ();
        zone7Alarme=0;
              
   if (notificationZone7 == 1)  //si il y a une alarme on transmet la memoire
          {
           sendToPushingBox(DEVID7);
           cptz7=1;
          }
      }


//zone 8

  if ((etatZone8 != etatZone8pre) && enService == 1)
      { 
        infoEnAlarme = 1;
        infoZoneOuverte = 0;
        sireneActive = true;
        tempsSirene = millis ();
        zone8Alarme=0;
              
   if (notificationZone8 == 1)  //si il y a une alarme on transmet la memoire
          {
           sendToPushingBox(DEVID8);
           cptz8=1;
          }
      }
//Zone ouverte

//zone 1
 if (etatZone1 == 0 && !enService)
     {
      infoZoneOuverte = 1;
      zone1Ouvert= 0;
      
     }  

      //zone 2
 if (etatZone2 == 0 && !enService)
     {
      infoZoneOuverte = 1;
      zone2Ouvert= 0;
      
     }  
      //zone 3
 if (etatZone3 == 0 && !enService)
     {
      infoZoneOuverte = 1;
      zone3Ouvert= 0;
      
     }  
      //zone 4
 if (etatZone4 == 0 && !enService)
     {
      infoZoneOuverte = 1;
      zone4Ouvert= 0;
      
     }  
      //zone 5
 if (etatZone5 == 0 && !enService)
     {
      infoZoneOuverte = 1;
      zone5Ouvert= 0;
      
     }  
      //zone 6
 if (etatZone6 == 0 && !enService)
     {
      infoZoneOuverte = 1;
      zone6Ouvert= 0;
      
     }  
      //zone 7
 if (etatZone7 == 0 && !enService)
     {
      infoZoneOuverte = 1;
      zone7Ouvert= 0;
      
     }  
      //zone 8
 if (etatZone8 == 0 && !enService)
     {
      infoZoneOuverte = 1;
      zone8Ouvert= 0;
      
     }  
      




   
        if (etatSortie == 0)
        digitalWrite(sortieAlarme,HIGH);

        if (etatSortie == 1)
        digitalWrite(sortieAlarme,LOW);     
        
    
  
 

  // Regarde si un client est connecté et attend une réponse
  EthernetClient client = server.available();
 
  if (client) {
     // Quelqu'un est connecté !
    Serial.println("On envoi !");
    // On fait notre en-tête
    // Tout d'abord le code de réponse 200 = réussite
    client.println("HTTP/1.1 200 OK");
    // Puis le type mime du contenu renvoyé, du json
    client.println("Content-Type: application/json");
    // Et c'est tout !
    // On envoie une ligne vide pour signaler la fin du header
    client.println();

 
   //on recupere la commande envoyer par l'application
   
      while(client.available()) { // A-t-il des choses à dire ?
 
      char c = client.read();
 
   //read char by char HTTP request
      if (readString.length() < 400) {

   //store characters to string
      readString += c;

      }
    }


    //on decode l'information recu
  Serial.println(readString); 

      if(readString.indexOf("PROG") >=0) { //si on trouve  CODE dans readString 
          
           char lettre = ' ';
           boolean verif=false;
           i=0;
         
           for(int j=0;j<readString.length();j++)
                {

                 lettre=readString.charAt(j);
        
                 if (lettre == '*') //indique le debut de readString
                    {
                      verif=true;//signale que le debut est vérifié
                    } 
               
                 if (verif && i<4 && lettre != '*')  // i < 4 car le code contient 4 digits on saute le caractére * car il ne fait pas partie du code
                 
                   {
                    code2[i]=lettre; //on stocke le premier digit du code dans le tableau code2
                    sscanf(code2, "%d", &cc);  //conversion en decimal de la valeur lu
                    i++;
                    } 
                 if (i==4)         //quand i =4 on termine la lecture 
                    verif = false;    //
                   }
        
          sauverInt(0, cc);
          client.println("code programmer");
          delay(10);
          
          // Ferme la connexion avec le client
          client.stop(); 
                    
          }

         ///////////////////////
         //    envoi code     // 
         ///////////////////////

          if(readString.indexOf("ENVOI") >=0) { //si on trouve  CODE dans readString 
 
          int code = lireInt1(0); // on lit le code enregistrer dans la memoire morte de l'arduino
   
          client.println(code);
          delay(10);
          
          // Ferme la connexion avec le client
          client.stop(); 
                    
          }




          ////////////////////
          //   envoi etat   //
          //////////////////// 

          if(readString.indexOf("ETAT") >=0) { //si on trouve  CODE dans readString 

           Serial.println("infoenalarme!");
           Serial.println(infoEnAlarme); 
           if (!infoEnAlarme)
           {
            client.print(enService);
            client.print(infoZoneOuverte);
            client.print(infoEnAlarme);
            client.print(zone1Ouvert);
            client.print(zone2Ouvert);
            client.print(zone3Ouvert);
            client.print(zone4Ouvert);
            client.print(zone5Ouvert);
            client.print(zone6Ouvert);
            client.print(zone7Ouvert);
            client.print(zone8Ouvert);
           }

            if (infoEnAlarme)
           {
            infoZoneOuverte=0;
            client.print(enService);
            client.print(infoZoneOuverte);
            client.print(infoEnAlarme);
            client.print(zone1Alarme);
            client.print(zone2Alarme);
            client.print(zone3Alarme);
            client.print(zone4Alarme);
            client.print(zone5Alarme);
            client.print(zone6Alarme);
            client.print(zone7Alarme);
            client.print(zone8Alarme);
           }

            delay(10);
          
            // Ferme la connexion avec le client
            client.stop(); 
                    
          }


      ///////////////////////////////////////////////////////////////////
      //      activation du systeme si on recois le mot marche         //  
      ///////////////////////////////////////////////////////////////////
      
      if(readString.indexOf("MARCHE") >=0) { //L'application nous demande d'envoyer le code de connection pour verification
    
       enService=1;    
       client.print(enService);
       client.print(infoZoneOuverte);
       client.print(infoEnAlarme);
       client.print(etatZone1);
       client.print(etatZone2);
       client.print(etatZone3);
       client.print(etatZone4);
       client.print(etatZone5);
       client.print(etatZone6);
       client.print(etatZone7);
       client.print(etatZone8);
         
    }

      /////////////////////////////////////////////////////
      //     REMISE A ZERO DE LA MEMOIRE D'ALARME        //  
      /////////////////////////////////////////////////////
      
      if(readString.indexOf("RESETALARME") >=0) { 

       infoEnAlarme=0; 
       cptz1=0;
       cptz2=0;
       cptz3=0;
       cptz4=0;
       cptz5=0;
       cptz6=0;
       cptz7=0;
       cptz8=0;
      
       zone1Alarme=1;
       zone2Alarme=1;
       zone3Alarme=1;
       zone4Alarme=1;
       zone5Alarme=1;
       zone6Alarme=1;
       zone7Alarme=1;
       zone8Alarme=1;
              
       client.print(enService);
       client.print(infoZoneOuverte);
       client.print(infoEnAlarme);
       client.print(etatZone1);
       client.print(etatZone2);
       client.print(etatZone3);
       client.print(etatZone4);
       client.print(etatZone5);
       client.print(etatZone6);
       client.print(etatZone7);
       client.print(etatZone8);
         
    }

 

          ////////////////////////////////
          //  GESTION DES NOTIFICATION  //
          ////////////////////////////////
          
     if(readString.indexOf("NOTIFICATION") >=0) { //si on trouve  CODE dans readString 
          
           char lettre = ' ';
           boolean verif=false;
           i=0;
         
           for(int j=0;j<readString.length();j++)
                {

                 lettre=readString.charAt(j);
        
                 if (lettre == '*') //indique le debut de readString
                    {
                      verif=true;//signale que le debut est vérifié
                    } 
               
                 if (verif && i<8 && lettre != '*')  // i < 4 car le code contient 4 digits on saute le caractére * car il ne fait pas partie du code
                 
                   {
                    if (i == 0)
                     notificationZone1 = (int)lettre - 48;
                  
                    if (i == 1)
                    notificationZone2 = (int)lettre - 48;

                    if (i == 2)
                    notificationZone3 = (int)lettre - 48;

                    if (i == 3)
                    notificationZone4 = (int)lettre - 48;
                    
                    if (i == 4)
                    notificationZone5 = (int)lettre - 48;

                    if (i == 5)
                    notificationZone6 = (int)lettre - 48;

                    if (i == 6)
                    notificationZone7 = (int)lettre - 48;

                    if (i == 7)
                    notificationZone8 = (int)lettre - 48;
    
                    i++;
          
                    } 
                    
                    if (i==8)         //quand i =4 on termine la lecture 
                    verif = false; //
                    
                   }
        
 
          
          delay(10);
          
          // Ferme la connexion avec le client
          client.stop(); 
                    
          }

    

      //////////////////////////////////////////////////////////////////////
      //      desactivation du systeme si on recois le mot arret          //  
      /////////////////////////////////////////////////////////////////////
      
      if(readString.indexOf("ARRET") >=0) { //L'application nous demande d'envoyer le code de connection pour verification
    
       enService=0;  
       client.print(enService);
       client.print(infoZoneOuverte);
       client.print(infoEnAlarme);
       client.print(etatZone1);
       client.print(etatZone2);
       client.print(etatZone3);
       client.print(etatZone4);
       client.print(etatZone5);
       client.print(etatZone6);
       client.print(etatZone7);
       client.print(etatZone8);
         
    }
          ///////////////////////

       delay(10);
    
          // Ferme la connexion avec le client
          
          client.stop(); 
          readString ="";
}
}



//ecriture dans la memoire eeprom
void sauverInt(int adresse, int val)
{   
    //découpage de la variable val qui contient la valeur à sauvegarder en mémoire
    unsigned char faible = val & 0x00FF; //récupère les 8 bits de droite (poids faible)
    unsigned char fort = (val >> 8) & 0x00FF;  //décale puis récupère les 8 bits de gauche (poids fort)
    //puis on enregistre les deux variables obtenues en mémoire
    EEPROM.write(adresse, fort) ; //on écrit les bits de poids fort en premier
    EEPROM.write(adresse+1, faible) ; //puis on écrit les bits de poids faible à la case suivante
}

//lecture dans la memoire eeprom
int lireInt1(int adresse)
{
    int val1 = 0 ; // int, vide qui va contenir le résultat de la lecture
    unsigned char fort = EEPROM.read(adresse);     //récupère les 8 bits de gauche (poids fort)
    unsigned char       faible = EEPROM.read(adresse+1); //récupère les 8 bits de droite (poids faible)
    //assemblage des deux variable précédentes
    val1 = fort ;         
    val1 = val1 << 8 ;     
    val1 = val1 | faible ;
   // boutdeligne = val1;
   return val1;
}


  //Function for sending the request to PushingBox
void sendToPushingBox(char devid[]){
  client.stop();
  Serial.println("connecting...");

  if (client.connect(serverName, 80)) {
    Serial.println("connected");

    Serial.println("sendind request");
    client.print("GET /pushingbox?devid=");
    client.print(devid);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(serverName);
    client.println("User-Agent: Arduino");
    client.println();

  } 
  else {
    Serial.println("connection failed");
  }
}
