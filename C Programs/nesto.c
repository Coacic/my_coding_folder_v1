/*

 This program calculate the mean score of an user 4 individual scores,
 and outputs the mean and a final grade
 Input: score1, score2,score2, score3
 Output: Mean, FinalGrade

*/
#include <stdio.h>
//#include <stdlib.h>

int main(void){
  int userScore = 0; //Stores the scores that the user inputs
  float meanValue = 0.0f; //Stores the user mean of all the notes
  char testChar = 'f'; //Used to avoid that the code crashes
  char grade = 'E'; //Stores the final 
  int i = 0; //Auxiliar used in the for statement

  printf("\nWelcome to the program \n Tell me if Im clever enough! \n Designed for humans \n\n\n");
  printf("Enter your 4 notes between 0 and 100 to calculate your course grade\n\n");

  // Asks the 4 notes. 
  for ( ; i<=3 ; i++ ){
    printf("Please, enter your score number %d: ", i+1);

    //If the note is not valid, ask for it again

    //This is tests if the user input is a valid integer.
    if ( ( scanf("%d%c", &userScore, &testChar)!=2 || testChar!='\n')){
      i-=1;
      scanf("%*[^\n]%*c");

    }else{ //Enter here if the user input is an integer
      if ( userScore>=0 && userScore<=100 ){
    //Add the value to the mean
    meanValue += userScore;
      }else{ //Enter here if the user input a non valid integer
    i-=1;
    //scanf("%*[^\n]%*c");
      }    
    }
  }

  //Calculates the mean value of the 4 scores
  meanValue = meanValue/4;

  // Select your final grade according to the final mean
  if (meanValue>= 90 && meanValue <=100){
    grade = 'A';
  } else if(meanValue>= 80 && meanValue <90){
    grade = 'B';
  } else if (meanValue>= 70 && meanValue <80){
    grade = 'C';
  } else if(meanValue>= 60 && meanValue <70){
    grade = 'D';
  }
  printf("Your final score is: %2.2f --> %c \n\n" , meanValue, grade);

  return 0;
}