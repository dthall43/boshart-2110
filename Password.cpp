#include "Password.h"
#include <iostream>

using namespace std;
using namespace CSC2110;

int Password::getNumMatches(String* curr_word, String* word_guess)
{
	int matches = 0;
	for(int x = 0; x < curr_word->length(); x++ )
	{

		if(curr_word->charAt(x) == word_guess->charAt(x))
		{		
			matches++;
		}
	}
	return matches;
}


int Password::bestGuess()
{
   int best_guess_index = -1;
   int best_num_eliminated = -1;
   int num_viable_passwords = getNumberOfPasswordsLeft();

   //loop over ALL words, even if they have been eliminated as the password
   int count = 1;
   ListArrayIterator<String>* all_iter = all_words->iterator();
   while(all_iter->hasNext())
   {
      String* original_word = all_iter->next();

      //loop over only those words that could still be the password
      //count up the number of matches between a possible password and a word in the original list
      int* count_num_matches = new int[len + 1];

      for (int i = 0; i < len; i++) 
      {
         count_num_matches[i] = 0;
      }

      ListArrayIterator<String>* viable_iter = viable_words->iterator();
      while(viable_iter->hasNext())
      {
         String* viable_word = viable_iter->next();
         int num_matches = getNumMatches(viable_word, original_word);
         count_num_matches[num_matches]++;
      }
      delete viable_iter;

      //find the largest number in the count_num_matches array
      //the largest number indicates the guess that will generate the most eliminations
      int most_num_matches = 0;
      for (int j = 0; j < len; j++) 
      {
         int curr_num_matches = count_num_matches[j];
         if (curr_num_matches > most_num_matches)
         {
            most_num_matches = curr_num_matches;
         }
      }

      //compute the fewest that can possibly be eliminated by guessing the current word (original list)
      int num_eliminated = num_viable_passwords - most_num_matches;

      //select the word to guess that maximizes the minimum number of eliminations (minimax)
      if (num_eliminated > best_num_eliminated)
      {
         best_num_eliminated = num_eliminated;
         best_guess_index = count;
      }
      
      count++;
      delete[] count_num_matches;
	}
   
   delete all_iter;
   return best_guess_index;  //return a 1-based index into the all_words list of words (careful)
}




void Password::addWord( String* word )
{

	if ( len == 0 )
	{
		len = word->length();
	}
	
   if ( len != word->length())
   {
		cout << "You have words of different length." << endl;
		return;
   }
   else 
   {
		viable_words->add(word);
		all_words->add(word);

   }
   
   
}
   
void Password::guess(int try_password, int num_matches )
{ 
	
	//Change this function to use the iterator, thanks

	int size = viable_words->size();
	ListArray<String>* temp_words = new ListArray<String>();


			for(int i = 1; i <= size ; i++ )
	{	
			temp_words->add( viable_words->get(i)  );
	}

	delete viable_words;
	viable_words = new ListArray<String>();

	
	for(int i = 1; i <= size ; i++ )
	{	
		if ( getNumMatches( temp_words->get(i), all_words->get(try_password)) == num_matches )
		{
			
			viable_words->add( all_words->get(i) );
			
		}
		
	}

	

	
	
	
}
	
	
int Password::getNumberOfPasswordsLeft()
{
	return viable_words->size();
}
	
void Password::displayViableWords()
{

	ListArrayIterator<String>* iter = viable_words->iterator();
	while(iter->hasNext())
	{
		cout << endl;
		iter->next()->displayString();
	}

	cout << endl;
	cout << endl;
}

String* Password::getOriginalWord(int index)
{
	
	return all_words->get(index);

}
   
//Constructor
Password::Password()
{
	viable_words = new ListArray<String>();
	all_words = new ListArray<String>();
	len = 0;
}

Password::~Password()
{

	for(int i = 1; i <= viable_words->size() ; i++ )
	{	
		viable_words->remove(i);
	}
	
	for(int i = 1; i <= all_words->size() ; i++ )
	{	
		all_words->remove(i);
	}
	
	delete viable_words;
	delete all_words;


}