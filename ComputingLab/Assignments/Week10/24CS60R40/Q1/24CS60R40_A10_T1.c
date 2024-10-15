#include <stdio.h>
#include <signal.h>

void signalHandler(int signalNumber) {
    printf("I am unstoppable!\n");
    fflush(stdout); 
}

int main() {
    char Character;
    

    signal(SIGINT, signalHandler);
    
    while (1) {
   
        scanf(" %c", &Character); 
        
        if (Character == 'x' || Character == 'X') {
            printf("Valar Morghulis\n");
            return 0; 
        } else if ((Character >= 'a' && Character <= 'z') || (Character >= 'A' && Character <= 'Z')) {
            printf("%c\n", Character);  
        } else {
            printf("Do you speak my language?\n");  
        }
    }
    
    return 0;
}
