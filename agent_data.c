#include <stdio.h>
#include <stdlib.h>

#include "agent.h"

int main(){

    Agent agents[5] = {{101, 9638461836, "Agent1", 0, 1,"Area1"},
                        {102, 9973862078, "Agent2", 0, 1,"Area2"},
                        {103, 9163412896, "Agent3", 0, 1,"Area2"},
                        {104, 9098361725, "Agent4", 0, 1,"Area3"},
                        {105, 9356204738, "Agent5", 0, 1,"Area1"},
                        };

    FILE *fptr1 = fopen("agent_data.txt","w");
    if(fptr1){
        fwrite(&agents,sizeof(Agent),5,fptr1);
    }


    return 0;
}
