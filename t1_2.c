#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* qsort C-string comparison function */ 
int cstring_cmp(const void *a, const void *b) 
{ 
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);
	/* strcmp functions works exactly as expected from
	comparison function */ 
}
void append(char* s, char c)
{
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
} 
void bubble_sort(long list[], long x)
{
  int c, d, t;
 
  for (c = 0 ; c < ( x - 1 ); c++)
  {
    for (d = 0 ; d < x - c - 1; d++)
    {
      if (list[d] > list[d+1])
      {
         
        t         = list[d];
        list[d]   = list[d+1];
        list[d+1] = t;
      }
    }
  }
}
int main()
{
   char ch, word[25], *words[10000000], *swords[10000000];
   long i, j=0, k=0, rp[10000000], rpt, le[10000000], l=0, m=0, len, n=0;
   int isspace(int c);
   double median;
   FILE *fin, *fout;
    
   fin = fopen("/tweet_input/tweets.txt","r");
 
   if( fin == NULL )
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }
   //getting the array of words from the tweets.txt
   while( ( ch = fgetc(fin) ) != EOF )
      {
       
       if (!isspace(ch)) append(word,ch);
         
       else
         {
          strcpy(words[n],word);
          n++;
          strcpy(word,  "");
		  l++;
		  if (ch == '\n' || ch == '\r' || ch == EOF) 
		    {
			 le[m]=l;
			 m++;
			 l=0;
			}
         }
      }
   fclose(fin);
   //Sorting the array of words
   qsort(words, n, sizeof(char *), cstring_cmp);
   //Calculating the median
   bubble_sort(le,m-1);
   len=sizeof(le)/sizeof(le[0]);
   if (len  % 2 == 0)
    {
      median = (le[len / 2 - 1] + le[len / 2]) / 2;
    }
   else 
    {
      median = le[len / 2];
    }
   //getting an array of unique words into swords and number of repetitions to rp	
   i=0;
   while (i < n)
      {
	   j=i+1;
	   if (words[i]!=words[j]) k++;
	   rpt=1;
	   while (words[i]==words[j])
	      {
		   j++;
		   rpt++;
		   if (words[i]!=words[j]) k++;
		  }
	  swords[k-1]=words[i];
	  rp[k-1]=rpt;
      i=j;	  
	  }
   //writing the results to files
   fout = fopen("/tweet_output/ft1.txt", "w");
   if( fout == NULL )
    {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
    }
   fwrite(swords,1,sizeof(swords),fout);
   fwrite(rp,1,sizeof(rp),fout);
   fclose(fout);
   fout = fopen("/tweet_output/ft2.txt", "w");
   if( fout == NULL )
    {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
    }
   fprintf(fout,"%f",median);
   fclose(fout);
   
   return 0;
}