/* File: Cardtrick.cpp
 * Programmer: Christopher Becker
 * Date: March 21, 2017
 * Course: COP 2931
 *
 * Purpose:
 * Write a program that performs a cardtrick. The program will create a
 * random deck of cards, deal them out, pick them up, and determine the
 * secret card.
 *
 */

#include <iostream>
#include <iomanip>
using namespace std;

// Function prototypes
void BuildDeck( int deck[], const int size );
void PrintDeck( int deck[], const int size );
void PrintCard( int card );
void Deal( int deck[], int play[][3] );
void PickUp( int deck[], int play[][3], int column );
void SecretCard( int deck[] );

int main(void){
    
    /* declare and initialize variables */
    int column = 0, i = 0;
    int playAgain = 0;
    
    string choice = "";
    string name = "";
    /* Declare a 52 element array of integers to be used as the deck of cards */
    int deck[52] = {0};
    
    /* Declare a 7 by 3 array to receive the cards dealt to play the trick */
    int play[7][3] = {0};
    
    /* Generate a random seed for the random number generator. */
    srand ((int)time(NULL));
    
    /* Openning message.  Ask the player for his/her name */
    cout << "Hello, I am a really tricky computer program and " << endl
    << "I can even perform a card trick.  Here's how." << endl
    << "To begin the card trick type in your name: " <<endl;
    cin >> name;
    
    /* Capitalize the first letter of the person's name. */
    
    // could also create a pointer to the name string and add 32 (or the difference between 'a' and 'A')
    name[0] = toupper(name[0]);
    
    cout << endl << "Thank you " << name << endl;
    
    do
    {
        /* Build the deck */
        BuildDeck(deck, 52);
        
        /* Ask if the player wants to see the entire deck. If so, print it out. */
        cout << "Ok " << name << ", first things first.  Do you want to see what "
        << "the deck of cards looks like (y/n)? " << endl;
        cin>> choice;
        //accepts y or other variations the user might use
        if(choice[0] == 'y'){
            //prints the deck by passing the array and the size of 52 cards
            PrintDeck( deck, 52);
        }
        
        
        cout << endl << name << " pick a card and remember it..." << endl;
        
        /* Begin the card trick loop */
        //run through the trick 3 times
        for(i = 0; i < 3; i++){
            /* Begin the trick by calling the function to deal out the first 21 cards */
            
            Deal(deck, play);
            
            
            /* Include error checking for entering which column */
            do{
                /* Ask the player to pick a card and identify the column where the card is */
                cout << endl <<"Which column is your card in (0, 1, or 2)?: " <<endl;
                cin >> column;
                
            } while(column < 0 || column > 2);
            
            /* Pick up the cards, by column, with the selected column second */
            PickUp(deck, play, column);
            
            
        }
        
        /* Display the top ten cards, then reveal the secret card */
        
        
         SecretCard(deck);
        
        /* if the player wants to play again */
        cout << name << ", would you like to play again (1 = yes, 0 = no)? ";
        cin >> playAgain;
    } while(playAgain == 1);
    
    /* Exiting message */
    cout << endl << endl << "Thank you for playing the card trick!" << endl;
  //  return;
}



void BuildDeck( int deck[], const int size){
    int used[52] = {0};
    int card = 0, i = 0;
    
    /* Generate cards until the deck is full of integers */
    while(i < size){
        /* generate a random number between 0 and 51 */
        card = rand()%52 ;
        /* Check the used array at the position of the card.
         If 0, add the card and set the used location to 1.  If 1, generate another number */
        if(used[card] == 0){
            used[card] = 1;
            deck[i] = card;
            i++;
        }
  }

    return;
}

void PrintCard( int card ){
    int rank = 0;
    int suit = 0;
    rank = card % 13;
    suit = card / 13;
    // Determine the rank of the card and print it out i.e. Queen
    // Determine the suit of the card and print it out i.e. of Clubs
    switch(rank){
        case 0:
            cout << "  King";
            break;
            
        case 1:
            cout << "   Ace";
            break;
            
        case 11:
            cout << "  jack";
            break;
            
        case 12:
            cout << " queen";
            break;
            
        default:
            cout << setw(6)<<rank;
            break;
    }
    
    switch(suit){
        case 0:
            cout<< " of clubs    ";
            break;
        case 1:
            cout<< " of hearts   ";
            break;
        case 2:
            cout<< " of diamonds ";
            break;
        case 3:
            cout<< " of spades   ";
            break;
    }
    
    return;
}

void PrintDeck( int deck[], const int size ){
    int counter;
    /* Print out each card in the deck */
    for(int i = 0; i < size; i++){
        cout << endl;
        PrintCard(deck[i]);
        counter++;
    }
    return;
}


void Deal( int deck[], int play[][3]){
    
    int row = 0, col = 0, card = 0;
    
    
    cout << endl;
    
    /*im sure this was the right spacing before but i messed it up and had to realign it to start at
     "of" suit*/
    cout << "       Column 0           Column 1           Column 2       ";
    cout << "================================================================"
    << endl;
    
    /* deal cards by passing addresses of cardvalues from
     the deck array to the play array                   */
    
    //for every row
    for(row = 0; row < 7; row++){
        //and column..
        for(col = 0; col < 3 ; col++){
            //putting the value of deck[card] into the play array
            play[row][col] = deck[card];
            
            //printing that value
            PrintCard(play[row][col]);
            
            //adding one to card after all that so it goes to the next card in the deck (shuffled before this is called)
            card++;
        }
        cout << endl;
    }
    return;
}

void PickUp( int deck[], int play[][3], int column ){
 int card = 0, row = 0;
 int first, last;
 
    switch(column){
        //your card will be in one of the rows, this dictates how the cards will get picked up.
        case 0:
            first = 1;
            last = 2;
            break;
            
        case 1:
            first = 2;
            last = 0;
            break;
            
        case 2:
            first = 0;
            last = 1 ;
            break;
    }
 
    
    for( row = 0; row < 7; row++){
        deck[card] = play[row][first];
        card++;
    }
  
    for(row = 0; row < 7; row++){
        deck[card] = play[row][column];
        card++;
    }
    //this was missing, and what was causing causing douplicate cards to appear.
    for( row = 0; row < 7; row++){
        deck[card] = play[row][last];
        card++;
    }

 return;
}

void SecretCard( int deck[] )
{
    int card = 0;
    
    cout << endl <<"Finding secret card...";
    for(card = 0; card < 10; card++)
    {
        PrintCard(deck[card]);
        cout << endl;
    }
    
    cout << endl <<"Your secret card is: ";
    PrintCard(deck[card]);
    cout << endl;
    return;
}



