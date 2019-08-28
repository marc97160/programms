#include <ArduinoJson.h>
#include <Ethernet.h>
#include <SPI.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
EthernetServer server(80);

  
  int S0,S1,S2,S3,S4,S5,S6,S7;//sortie relais reel
  int etat_1,etat_2,etat_3,etat_4,etat_5,etat_6,etat_7,etat_8;//mode des sortie S0...S8
  int ev_1,ev_2,ev_3,ev_4,ev_5,ev_6,ev_7,ev_8;
  int E1,E2,E3,E4,E5,E6,E7,E8;
  int C0,C1,C2,C3;//code arduino de connexion
  int S0P,S1P,S2P,S3P,S4P,S5P,S6P,S7P; //variables utiliser pour gerer le Mode Momentané
  int SRF_1,SRF_2,SRF_3,SRF_4,SRF_5,SRF_6,SRF_7,SRF_8; // Sortie Relais Final;

  int etatBt0,etatBt1,etatBt2,etatBt3,etatBt4,etatBt5,etatBt6,etatBt7;
  
  
          // Allocate a temporary JsonDocument
  // Use arduinojson.org/v6/assistant to compute the capacity.

   int sortie1 = 2;
   int sortie2 = 3;
   int sortie3 = 4;
   int sortie4 = 5;
   int sortie5 = 6;
   int sortie6 = 7;
   int sortie7 = 8;
   int sortie8 = 9;

   int k=0;
   int j=0;

   int sp0=0;
   
   unsigned long tempoSortie;//variable utiliser pour generer une seconde
   unsigned long mesureTemps;
   int varTempo=0;
 
   StaticJsonDocument<500> doc;
 
  // Wait for an incomming connection
  EthernetClient client ;



void setup() {


 


  
  doc["data"] ="ARDUINO";
  doc["S1"]=0;
  doc["S2"]=0;
  doc["S3"]=0;
  doc["S4"]=0;
  doc["S5"]=0;
  doc["S6"]=0;
  doc["S7"]=0;
  doc["S8"]=0;
  doc["C0"]=1;//code de connection a modifier
  doc["C1"]=5;//entree le code souhaiter sur 4 digit
  doc["C2"]=2;//
  doc["C3"]=0;//



   
  S0P=0;// UTILISER POUR LE MODE MOMENTANE
  S1P=0;//etat t-1 sert pour detecter un front montant de la sortie
  S2P=0;//et lancer la tempo d'une seconde
  S3P=0;
  S4P=0;
  S5P=0;
  S6P=0;
  S7P=0;

  S0=0;
  S1=0;
  S2=0;
  S3=0;
  S4=0;
  S5=0;
  S6=0;
  S7=0;
  
  
  ev_1=0;
  ev_2=0;
  ev_3=0;
  ev_4=0;
  ev_5=0;
  ev_6=0;
  ev_7=0;
  ev_8=0;
  


  

   pinMode (sortie1, OUTPUT);
   pinMode (sortie2, OUTPUT);
   pinMode (sortie3, OUTPUT);
   pinMode (sortie4, OUTPUT);
   pinMode (sortie5, OUTPUT);
   pinMode (sortie6, OUTPUT);
   pinMode (sortie7, OUTPUT);
   pinMode (sortie8, OUTPUT);

   pinMode (30 , INPUT);
   pinMode (31 , INPUT);
   pinMode (32 , INPUT);
   pinMode (33 , INPUT);
   pinMode (34 , INPUT);
   pinMode (35 , INPUT);
   pinMode (36 , INPUT);
   pinMode (37 , INPUT);
   
  

  
  // Initialize serial port
  Serial.begin(9600);
  while (!Serial) continue;

  // Initialize Ethernet libary
  if (!Ethernet.begin(mac)) {
    Serial.println(F("Failed to initialize Ethernet library"));
    return;
  }

  // Start to listen
  server.begin();

  Serial.println(F("Server is ready."));
  Serial.print(F("Please connect to http://"));
  Serial.println(Ethernet.localIP());
 
 etat_1=0;//au demarrage on est en mode momentane
 etat_2=0;//change avec les parametres programmer de l'application
 etat_3=0;//domodom
 etat_4=0;//lorsqu'on se connecte
 etat_5=0;
 etat_6=0;
 etat_7=0;
 etat_8=0;

 digitalWrite (sortie1,HIGH);
 digitalWrite (sortie2,HIGH);
 digitalWrite (sortie3,HIGH);
 digitalWrite (sortie4,HIGH);
 digitalWrite (sortie5,HIGH);
 digitalWrite (sortie6,HIGH);
 digitalWrite (sortie7,HIGH);
 digitalWrite (sortie8,HIGH);
 
 etatBt0=1;
 etatBt1=1;
 etatBt2=1;
 etatBt3=1;
 etatBt4=1;
 etatBt5=1;
 etatBt6=1;
 etatBt7=1;

 
 }

void loop() {





  if (millis() >= tempoSortie && etat_1==0 && S0P == 1) //quand on atteint une seconde on remet la sortie a "0",et la variable S..P a "0" pour pouvoir relancer une nouvelle tempo
 {
     
      digitalWrite (sortie1,HIGH);
      ev_1=0;
      S0P=0;
      S0=0;
 
 }
  if (millis() >= tempoSortie && etat_2==0 && S1P == 1) //quand on atteint une seconde on remet la sortie a "0",et la variable S..P a "0" pour pouvoir relancer une nouvelle tempo
 {
     
      digitalWrite (sortie2,HIGH);
      ev_2=0;
      S1P=0;
      S1=0;
 
 }

   if (millis() >= tempoSortie && etat_3==0 && S2P == 1) //quand on atteint une seconde on remet la sortie a "0",et la variable S..P a "0" pour pouvoir relancer une nouvelle tempo
 {
     
      digitalWrite (sortie3,HIGH);
      ev_3=0;
      S2P=0;
      S2=0;
 
 }

    if (millis() >= tempoSortie && etat_4==0 && S3P == 1) //quand on atteint une seconde on remet la sortie a "0",et la variable S..P a "0" pour pouvoir relancer une nouvelle tempo
 {
     
      digitalWrite (sortie4,HIGH);
      ev_4=0;
      S3P=0;
      S3=0;
 
 }

     if (millis() >= tempoSortie && etat_5==0 && S4P == 1) //quand on atteint une seconde on remet la sortie a "0",et la variable S..P a "0" pour pouvoir relancer une nouvelle tempo
 {
     
      digitalWrite (sortie5,HIGH);
      ev_5=0;
      S4P=0;
      S4=0;
 
 }

     if (millis() >= tempoSortie && etat_6==0 && S5P == 1) //quand on atteint une seconde on remet la sortie a "0",et la variable S..P a "0" pour pouvoir relancer une nouvelle tempo
 {
     
      digitalWrite (sortie6,HIGH);
      ev_6=0;
      S5P=0;
      S5=0;
 
 }

      if (millis() >= tempoSortie && etat_7==0 && S6P == 1) //quand on atteint une seconde on remet la sortie a "0",et la variable S..P a "0" pour pouvoir relancer une nouvelle tempo
 {
     
      digitalWrite (sortie7,HIGH);
      ev_7=0;
      S6P=0;
      S6=0;
 
 }

      if (millis() >= tempoSortie && etat_8==0 && S7P == 1) //quand on atteint une seconde on remet la sortie a "0",et la variable S..P a "0" pour pouvoir relancer une nouvelle tempo
 {
     
      digitalWrite (sortie8,HIGH);
      ev_8=0;
      S7P=0;
      S7=0;
 
 }



   
   if (S0==0 && etat_1 == 1)
   digitalWrite (sortie1,HIGH);
   if (S0==1 && etat_1 == 1)
   digitalWrite (sortie1,LOW);
   
   if (S1==0 && etat_2 == 1)
   digitalWrite (sortie2,HIGH);
   if (S1==1 && etat_2 == 1)
   digitalWrite (sortie2,LOW);
   
   if (S2==0 && etat_3 == 1)
   digitalWrite (sortie3,HIGH);
   if (S2==1 && etat_3 == 1)
   digitalWrite (sortie3,LOW);
   
   if (S3==0 && etat_4 == 1)
   digitalWrite (sortie4,HIGH);
   if (S3==1 &&  etat_4 == 1)
   digitalWrite (sortie4,LOW);
   
   if (S4==0 && etat_5 == 1)
   digitalWrite (sortie5,HIGH);
   if (S4==1 && etat_5 == 1)
   digitalWrite (sortie5,LOW);
   
   if (S5==0 && etat_6 == 1)
   digitalWrite (sortie6,HIGH);
   if (S5==1 && etat_6 == 1)
   digitalWrite (sortie6,LOW);
   
   if (S6==0 && etat_7 == 1)
   digitalWrite (sortie7,HIGH);
   if (S6==1 && etat_7 == 1)
   digitalWrite (sortie7,LOW);
  
   if (S7==0 && etat_8 == 1)
   digitalWrite (sortie8,HIGH);
   if (S7==1 && etat_8 == 1)
   digitalWrite (sortie8,LOW);



      char carlu = 0;
/* 
  // Wait for an incomming connection
  EthernetClient client = server.available();*/
  client =server.available();
/*
  // Do we have a client?
  if (!client) return;
*/  
  int j=0;
   
   // Read the request (we ignore the content in this example)

 
  while (client.available()){
     
  // decodage des sorties envoyer par l'application domodom

  
    carlu = client.read();
    delay(1);
 
      
        //décodage du mode des sorties  77->M 84->T
        if (carlu=='&')
         {
              for (j=1;j<=8;j++)
          {
          
          carlu=client.read();
          delay(1);
          
          if (j==1)
             {
              etat_1=int(carlu);
             }
          
          if (j==2)
             {
               etat_2=int(carlu); 
             }
             
          if (j==3)
             {
              etat_3=int(carlu);
             }
          
          if (j==4)
             {
               etat_4=int(carlu); 
             }
         if (j==5)
             {
              etat_5=int(carlu);
             }
          
          if (j==6)
             {
               etat_6=int(carlu); 
             }
          
          if (j==7)
             {
              etat_7=int(carlu);
             }
          
          if (j==8)
             {
               etat_8=int(carlu); 
             }
                  
          }
          }
          if (etat_1 == 77)
             etat_1=0;
          if (etat_1 == 84)
             etat_1=1;   

          if (etat_2 == 77)
             etat_2=0;
          if (etat_2 == 84)
             etat_2=1;  

          if (etat_3 == 77)
             etat_3=0;
          if (etat_3 == 84)
             etat_3=1;     

          if (etat_4 == 77)
             etat_4=0;
         if (etat_4 == 84)
             etat_4=1; 

          if (etat_5 == 77)
             etat_5=0;
          if (etat_5 == 84)
             etat_5=1;  
         
          if (etat_6 == 77)
             etat_6=0;
          if (etat_6 == 84)
             etat_6=1;  
         
           if (etat_7 == 77)
             etat_7=0;
          if (etat_7 == 84)
             etat_7=1;   
           
           if (etat_8 == 77)
             etat_8=0;
          if (etat_8 == 84)
             etat_8=1;      

// decodage de l'evenement declenchant

           if (carlu=='*')
         {
              for (j=1;j<=8;j++)
          {
          
          carlu=client.read();
          delay(1);
          
          if (j==1)
             {
              ev_1=int(carlu);
             }
          
          if (j==2)
             {
               ev_2=int(carlu); 
             }
             
          if (j==3)
             {
              ev_3=int(carlu);
             }
          
          if (j==4)
             {
               ev_4=int(carlu); 
             }
         if (j==5)
             {
              ev_5=int(carlu);
             }
          
          if (j==6)
             {
               ev_6=int(carlu); 
             }  
          
          if (j==7)
             {
              ev_7=int(carlu);
             }
          
          if (j==8)
             {
               ev_8=int(carlu); 
             }
                  
          }
          }      

          if (ev_1 == 48)  //0
             ev_1=0;
          if (ev_1 == 49)  //1
             ev_1=1;   

          if (ev_2 == 48)
             ev_2=0;
          if (ev_2 == 49)
             ev_2=1;  

          if (ev_3 == 48)
             ev_3=0;
          if (ev_3 == 49)
             ev_3=1;     

          if (ev_4 == 48)
             ev_4=0;
         if (ev_4 == 49)
             ev_4=1; 

          if (ev_5 == 48)
             ev_5=0;
          if (ev_5 == 49)
             ev_5=1;  
         
          if (ev_6 == 48)
             ev_6=0;
          if (ev_6 == 49)
             ev_6=1;  
         
           if (ev_7 == 48)
             ev_7=0;
          if (ev_7 == 49)
             ev_7=1;   
           
           if (ev_8 == 48)
             ev_8=0;
          if (ev_8 == 49)
             ev_8=1;                 

       
   }
   //affichage au serial print arduino de l'evenement declencheur.
   /*
    Serial.println("Evenement Declenchant !");
    Serial.print(ev_1);
    Serial.print(ev_2);
    Serial.print(ev_3);
    Serial.print(ev_4);
    Serial.print(ev_5);
    Serial.print(ev_6);
    Serial.print(ev_7);
    Serial.print(ev_8);

  */       


    //MODE TOGGLE T ON/OFF
 if (ev_1 == 1 && etat_1 == 1)
 {
    switch (S0P)
      {
        case 0:
        S0=1;
        S0P=1;
        ev_1=0;
        SRF_1=1;
        digitalWrite (sortie1,LOW);
        break;

        case 1:
        S0=0;
        S0P=0;
        ev_1=0;
        SRF_1=0;
        digitalWrite (sortie1,HIGH);
        break;       
        
      }
  }

   if (ev_2 == 1 && etat_2==1)
 {
    switch (S1P)
      {
        case 0:
        S1=1;
        S1P=1;
        ev_2=0;
        SRF_2=1;
        digitalWrite (sortie2,LOW);
        break;

        case 1:
        S1=0;
        S1P=0;
        ev_2=0;
        SRF_2=0;
        digitalWrite (sortie2,HIGH);
        break;       
        
      }
  }

    if (ev_3 == 1 && etat_3==1)
 {
    switch (S2P)
      {
        case 0:
        S2=1;
        S2P=1;
        ev_3=0;
        SRF_3=1;
        digitalWrite (sortie3,LOW);
        break;

        case 1:
        S2=0;
        S2P=0;
        ev_3=0;
        SRF_3=0;
        digitalWrite (sortie3,HIGH);
        break;       
        
      }
  }

     if (ev_4 == 1 && etat_4==1)
 {
    switch (S3P)
      {
        case 0:
        S3=1;
        S3P=1;
        ev_4=0;
        SRF_4=1;
        digitalWrite (sortie4,LOW);
        break;

        case 1:
        S3=0;
        S3P=0;
        ev_4=0;
        SRF_4=0;
        digitalWrite (sortie4,HIGH);
        break;       
        
      }
  }

      if (ev_5 == 1 && etat_5 ==1)
 {
    switch (S4P)
      {
        case 0:
        S4=1;
        S4P=1;
        ev_5=0;
        SRF_5=1;
        digitalWrite (sortie5,LOW);
        break;

        case 1:
        S4=0;
        S4P=0;
        ev_5=0;
        SRF_5=0;
        digitalWrite (sortie5,HIGH);
        break;       
        
      }
  }

        if (ev_6 == 1 && etat_6 ==1)
 {
    switch (S5P)
      {
        case 0:
        S5=1;
        S5P=1;
        ev_6=0;
        SRF_6=1;
        digitalWrite (sortie6,LOW);
        break;

        case 1:
        S5=0;
        S5P=0;
        ev_6=0;
        SRF_6=0;
        digitalWrite (sortie6,HIGH);
        break;       
        
      }
  }

          if (ev_7 == 1 && etat_7==1)
 {
    switch (S6P)
      {
        case 0:
        S6=1;
        S6P=1;
        ev_7=0;
        SRF_7=1;
        digitalWrite (sortie7,LOW);
        break;

        case 1:
        S6=0;
        S6P=0;
        ev_7=0;
        SRF_7=0;
        digitalWrite (sortie7,HIGH);
        break;       
        
      }
  }

 if (ev_8 == 1 && etat_8==1)
 {
    switch (S7P)
      {
        case 0:
        S7=1;
        S7P=1;
        ev_8=0;
        SRF_8=1;
        digitalWrite (sortie8,LOW);
        break;

        case 1:
        S7=0;
        S7P=0;
        ev_8=0;
        SRF_8=0;
        digitalWrite (sortie8,HIGH);
        break;       
        
      }
  }


    // MODE M MOMENTANNEE

  

 
 // SORTIE S1
  if (ev_1==1 && S0P==0 && etat_1==0)
           {
                       
                       tempoSortie = millis() + 1000;
                      // tempoSortie=millis();//on mesure le temps t ou c'est declencher l'evenement
                       S0P=1;//on fixe la variable a "1" pour ne plus entrer dans cet boucle sera remis a zero quand le temps va atteindre "1" seconde  
                       digitalWrite (sortie1,LOW);
                              switch (SRF_1)
                                {
                                  case 0:
                                  SRF_1=1;
                                  break;

                                  case 1:
                                  SRF_1=0;
                                  break; 
                                   
                                  default:
                                  break;     
                                 }
           }

           // SORTIE S2
  if (ev_2==1 && S1P==0 && etat_2==0)
           {
                       
                       tempoSortie = millis() + 1000;
                      // tempoSortie=millis();//on mesure le temps t ou c'est declencher l'evenement
                       S1P=1;//on fixe la variable a "1" pour ne plus entrer dans cet boucle sera remis a zero quand le temps va atteindre "1" seconde  
                       digitalWrite (sortie2,LOW);
                              switch (SRF_2)
                                {
                                  case 0:
                                  SRF_2=1;
                                  break;

                                  case 1:
                                  SRF_2=0;
                                  break; 
                                   
                                  default:
                                  break;     
                                 }
           }

                      // SORTIE S3
  if (ev_3==1 && S2P==0 && etat_3==0)
           {
                       
                       tempoSortie = millis() + 1000;
                      // tempoSortie=millis();//on mesure le temps t ou c'est declencher l'evenement
                       S2P=1;//on fixe la variable a "1" pour ne plus entrer dans cet boucle sera remis a zero quand le temps va atteindre "1" seconde  
                       digitalWrite (sortie3,LOW);
                              switch (SRF_3)
                                {
                                  case 0:
                                  SRF_3=1;
                                  break;

                                  case 1:
                                  SRF_3=0;
                                  break; 
                                   
                                  default:
                                  break;     
                                 }
           }

                                 // SORTIE S4
  if (ev_4==1 && S3P==0 && etat_4==0)
           {
                       
                       tempoSortie = millis() + 1000;
                      // tempoSortie=millis();//on mesure le temps t ou c'est declencher l'evenement
                       S3P=1;//on fixe la variable a "1" pour ne plus entrer dans cet boucle sera remis a zero quand le temps va atteindre "1" seconde  
                       digitalWrite (sortie4,LOW);
                              switch (SRF_4)
                                {
                                  case 0:
                                  SRF_4=1;
                                  break;

                                  case 1:
                                  SRF_4=0;
                                  break; 
                                   
                                  default:
                                  break;     
                                 }
           }

                                           // SORTIE S5
  if (ev_5==1 && S4P==0 && etat_5==0)
           {
                       
                       tempoSortie = millis() + 1000;
                      // tempoSortie=millis();//on mesure le temps t ou c'est declencher l'evenement
                       S4P=1;//on fixe la variable a "1" pour ne plus entrer dans cet boucle sera remis a zero quand le temps va atteindre "1" seconde  
                       digitalWrite (sortie5,LOW);
                              switch (SRF_5)
                                {
                                  case 0:
                                  SRF_5=1;
                                  break;

                                  case 1:
                                  SRF_5=0;
                                  break; 
                                   
                                  default:
                                  break;     
                                 }
           }

                                           // SORTIE S6
  if (ev_6==1 && S5P==0 && etat_6==0)
           {
                       
                       tempoSortie = millis() + 1000;
                      // tempoSortie=millis();//on mesure le temps t ou c'est declencher l'evenement
                       S5P=1;//on fixe la variable a "1" pour ne plus entrer dans cet boucle sera remis a zero quand le temps va atteindre "1" seconde  
                       digitalWrite (sortie6,LOW);
                              switch (SRF_6)
                                {
                                  case 0:
                                  SRF_6=1;
                                  break;

                                  case 1:
                                  SRF_6=0;
                                  break; 
                                   
                                  default:
                                  break;     
                                 }
           }

           
                                           // SORTIE S7
  if (ev_7==1 && S6P==0 && etat_7==0)
           {
                       
                       tempoSortie = millis() + 1000;
                      // tempoSortie=millis();//on mesure le temps t ou c'est declencher l'evenement
                       S6P=1;//on fixe la variable a "1" pour ne plus entrer dans cet boucle sera remis a zero quand le temps va atteindre "1" seconde  
                       digitalWrite (sortie7,LOW);
                              switch (SRF_7)
                                {
                                  case 0:
                                  SRF_7=1;
                                  break;

                                  case 1:
                                  SRF_7=0;
                                  break; 
                                   
                                  default:
                                  break;     
                                 }
           }  

                                          // SORTIE S8
  if (ev_8==1 && S7P==0 && etat_8==0)
           {
                       
                       tempoSortie = millis() + 1000;
                      // tempoSortie=millis();//on mesure le temps t ou c'est declencher l'evenement
                       S7P=1;//on fixe la variable a "1" pour ne plus entrer dans cet boucle sera remis a zero quand le temps va atteindre "1" seconde  
                       digitalWrite (sortie8,LOW);
                              switch (SRF_8)
                                {
                                  case 0:
                                  SRF_8=1;
                                  break;

                                  case 1:
                                  SRF_8=0;
                                  break; 
                                   
                                  default:
                                  break;     
                                 }
           }  

          
            
                  
 
    doc["S1"]=SRF_1;
    doc["S2"]=SRF_2;
    doc["S3"]=SRF_3;
    doc["S4"]=SRF_4;
    doc["S5"]=SRF_5;
    doc["S6"]=SRF_6;
    doc["S7"]=SRF_7;
    doc["S8"]=SRF_8;


/* 
  Serial.print(F("Sending2: "));
  serializeJson(doc, Serial);
  Serial.println();
*/

  // Write response headers
  client.println(F("HTTP/1.0 200 OK"));
  client.println(F("Content-Type: application/json"));
  client.println(F("Connection: close"));
  client.print(F("Content-Length: "));
  client.println(measureJsonPretty(doc));
  client.println();

  // Write JSON document
  
  serializeJsonPretty(doc, client);
/*
  if (!client.connected()) {
    Serial.println();
    Serial.println("Deconnexion !");
    // On ferme le client
     }



  // Disconnect
  client.stop();
 */  
    
}

