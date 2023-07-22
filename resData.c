#include <stdio.h>
#include <stdlib.h>

#include "restaurant.h"

int main(){

    Restaurant restaurants[5] = {{"Dominos", "Area1", 10,
                                  {{"PeppyPaneer", 259.0, 0},
                                         {"VeggieParadise",  279.0, 0},
                                         {"ChickenMaximus", 399.0, 0},
                                         {"CheeseDominator", 349.0, 0},
                                         {"Margherita", 109.0, 0},
                                         },
                                         "restaurant","continental",0},
                                         
                                 {"Haldiram",  "Area2", 12,
                                  {{"PaniPuri", 59.0, 0},
                                         {"Bhel",  69.0, 0},
                                         {"DahiSamosa", 69.0, 0},
                                         {"CholeSamosa", 89.0, 0},
                                         {"ChillyGarlicSpringRoll", 149.0, 0},
                                         {"Manchurian", 229.0, 0},
                                         {"CrispyVegetables", 275.0, 0},
                                         {"Chowmein", 199.0, 0},
                                         },
                                         "restaurant", "south", 0},
                                 
                                 {"Al-ZamZam", "Area3", 21,
                                  {{"TandooriChicken", 310.0, 0},
                                         {"MuttonBhuna",  350.0, 0},
                                         {"ChickenTangdi", 380.0, 0},
                                         {"Chicken65", 390.0, 0},
                                         {"ChickenAfghani", 415.0, 0},
                                         },
                                  "restaurant", "north",0},

                                 {"Panino", "Area4", 15,
                                  {{"SchezwanPaneer", 299.0, 0},
                                         {"PaneerBarbeque",  299.0, 0},
                                         {"NawabKabab", 299.0, 0},
                                         {"VeggieItlaiano", 299.0, 0},
                                         {"CheeseCorn", 199.0, 0}},
                                  "Cafe", "continental",0},
                    
                                 {"Frullato", "Area5", 25,
                                  {{"ClassicColdCoffee", 70.0, 0},
                                         {"MochaColdCoffee",  80.0, 0},
                                         {"HazelnutColdCoffee", 90.0, 0},
                                         {"BrownieKitKat", 170.0, 0},
                                         {"BrownieLoaded", 150.0, 0},
                                         {"NutellaBrownie", 170.0, 0},
                                         {"CadburyCrackle", 150.0, 0},
                                         {"FerreroRocher", 180.0, 0},
                                         {"KesarBadam", 140.0, 0},
                                  }, "Cafe", "shakes", 0 }
                                         };



    FILE *fptr1 = fopen("resData.txt","w");
    if(fptr1){
        fwrite(&restaurants,sizeof(Restaurant),5,fptr1);
    }


    return 0;
}