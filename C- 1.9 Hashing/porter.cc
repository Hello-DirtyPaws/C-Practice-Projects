/**********************************************************
    File:          porter.cc                       
    Description:   Functions for applying the Porter 
                   transformation to a word.

                                                         
    Author:        Dana Vrajitoru  and Stuart J. Barr                      
    Organization:  IUSB                                    
    Updated:       October 1, 2018
***********************************************************/

#include <cstdio>
#include <cstring>
#include "porter.h"

// extract word stem
void stripAffixes ( char *text)
{
    toLowerCase(text);
    clean(text);
    stripPrefixes(text);
    stripSuffixes(text);
    text[KEYWORDSIZE] = '\0';
} // stripAffixes()

// turn all the letters in the word to lower case
void toLowerCase (char *kwd)
{
    int i;
    for ( i=0 ; i < strlen(kwd) ; i++ )
        if ( (kwd[i] >= 'A') && (kwd[i] <= 'Z') )
            kwd[i] += 'a' - 'A';
} // toLowerCase()

// remove everything that is not a letter or a digit
void clean (char *kwd)
{
    int i,j,last=strlen(kwd);
    for ( i=0 ; i < last ; i++ ) 
    {
        if ( isvalid(kwd[i]) != 0 ) 
        {
            for ( j = i ; j < last-1 ; j++ )
                kwd[j] = kwd[j+1];
            kwd[last-1] = '\0';
            last--;
            i--;
        }
    }
} // clean

// returns 0 if the character is a letter or a digit, 1 otherwise
int isvalid(char l)
{
    if ( (l >= 'a') && (l <= 'z') )
        return(0);
    if ( (l >= 'A') && (l <= 'Z') )
        return(0);
    if ( (l >= '0') && (l <= '9') )
        return(0);
    return(1);
} // isvalid()

// remove composing prefixes such as "kilo".
void stripPrefixes (char *text )
{
    static char *prefixes[] = { "kilo", "micro", "milli", "intra", "ultra",
                                "mega", "nano", "pico", "pseudo", 0 };
    int i;
    for ( i=0 ; prefixes[i] != 0 ; i++ ) 
    {
        if ( strncmp(prefixes[i],text,strlen(prefixes[i])) == 0 ) 
        {
            int j;
            for ( j=0 ; j<strlen(text)-strlen(prefixes[i]) ; j++ )
                text[j] = text[j+strlen(prefixes[i])];
            text[j] = '\0';
            return;
        }
    }
} // stripPrefixes()

// remove composing pieces at the end of the text, such as "ly"
void stripSuffixes ( char *text )
{
    step_1 ( text );
    step_2 ( text );
    step_3 ( text );
    step_4 ( text );
    step_5 ( text );
} // stripSuffixes()

void step_1 ( char *text )
{
    char stem[BIG_KEYWORDSIZE];
    if ( text[strlen(text)-1] == 's' ) 
    {
        if ( (hasSuffix(text,"sses",stem) == true) ||
             (hasSuffix(text,"ies",stem) == true ) )
            text[strlen(text)-2] = '\0';
        else
            if ( text[strlen(text)-2] != 's' )
                text[strlen(text)-1] = '\0';
    }
    if ( hasSuffix(text,"eed",stem) == true ) 
    {
        if ( measure(stem) > 0 )
            text[strlen(text)-1] = '\0';
    }
    else 
    {
        if ( ( (hasSuffix(text,"ed",stem) == true )
               || (hasSuffix(text,"ing",stem) == true ) )
             && (containsVowel(stem) == true ) ) 
        {
            text[strlen(stem)] = '\0';
            if ( ( hasSuffix(text,"at",stem) == true )
                 || ( hasSuffix(text,"bl",stem) == true )
                 || ( hasSuffix(text,"iz",stem) == true ) ) 
            {
                text[strlen(text)+1] = '\0';
                text[strlen(text)] = 'e';
            }
            else 
            {
                int length = strlen(text);
                if ( (text[length-1] == text[length-2])
                     && (text[length-1] != 'l')
                     && (text[length-1] != 's')
                     && (text[length-1] != 'z') )
                    text[length-1] = '\0';
                else
                    if ( measure(text) == 1 ) 
                    {
                        if ( cvc(text) == true ) 
                        {
                            text[strlen(text)+1] = '\0';
                            text[strlen(text)] = 'e';
                        }
                    }
            }
        }
    }
    if ( (hasSuffix(text,"y",stem) == true) &&
         (containsVowel(stem) == true) )
        text[strlen(text)-1] = 'i';
} // step_1()

void step_2 ( char *text )
{
    static char *suffixes[][2] =  { { "ational", "ate" },
                                    { "tional",  "tion" },
                                    { "enci",    "ence" },
                                    { "anci",    "ance" },
                                    { "izer",    "ize" },
                                    { "iser",    "ize" },
                                    { "abli",    "able" },
                                    { "alli",    "al" },
                                    { "entli",   "ent" },
                                    { "eli",     "e" },
                                    { "ousli",   "ous" },
                                    { "ization", "ize" },
                                    { "isation", "ize" },
                                    { "ation",   "ate" },
                                    { "ator",    "ate" },
                                    { "alism",   "al" },
                                    { "iveness", "ive" },
                                    { "fulness", "ful" },
                                    { "ousness", "ous" },
                                    { "aliti",   "al" },
                                    { "iviti",   "ive" },
                                    { "biliti",  "ble" },
                                    {  0,        0     } };
    char stem[BIG_KEYWORDSIZE];
    register int index;
    for ( index = 0 ; suffixes[index][0] != 0 ; index++ ) 
    {
        if ( hasSuffix ( text, suffixes[index][0], stem ) == true ) 
        {
            if ( measure ( stem ) > 0 ) 
            {
                mysprintf ( text, KEYWORDSIZE, "%s%s", stem, suffixes[index][1] );
                return;
            }
        }
    }
    return;
} // step_2()

void step_3 ( char *text )
{
    static char *suffixes[][2] = { { "icate", "ic" },
                                   { "ative", "" },
                                   { "alize", "al" },
                                   { "alise", "al" },
                                   { "iciti", "ic" },
                                   { "ical",  "ic" },
                                   { "ful",   "" },
                                   { "ness",  "" },
                                   { 0,       0 } };
    char stem[BIG_KEYWORDSIZE];
    register int index;
    for ( index = 0 ; suffixes[index][0] != 0 ; index++ ) 
    {
        if ( hasSuffix ( text, suffixes[index][0], stem ) == true )
            if ( measure ( stem ) > 0 ) 
            {
                mysprintf ( text, KEYWORDSIZE, "%s%s", stem, suffixes[index][1] );
                return;
            }
    }
    return;
} // step_3

void step_4 ( char *text )
{
    static char *suffixes[] = { "al", "ance", "ence", "er", "ic", "able",
                                "ible", "ant", "ement", "ment", "ent", "sion", "tion",
                                "ou", "ism", "ate", "iti", "ous", "ive", "ize", "ise", 0 };
    char stem[BIG_KEYWORDSIZE];
    register int index;
    for ( index = 0 ; suffixes[index] != 0 ; index++ ) 
    {
        if ( hasSuffix ( text, suffixes[index], stem ) == true )
            if ( measure ( stem ) > 1 ) 
            {
                mystrcpy( text, KEYWORDSIZE, stem );
                return;
            }
    }
    return;
} // step_4()

void step_5 ( char *text )
{
    if ( text[strlen(text)-1] == 'e' ) 
    {
        if ( measure(text) > 1 )
            /* measure(text)==measure(stem) if ends in vowel */
            text[strlen(text)-1] = '\0';
        else
            if ( measure(text) == 1 ) 
            {
                char stem[BIG_KEYWORDSIZE];
                mystrcpy(stem, KEYWORDSIZE, "");
                mystrncat( stem, KEYWORDSIZE, text, strlen(text)-1 );
                if ( cvc(stem) == false )
                    text[strlen(text)-1] = '\0';
            }
    }
    if ( (text[strlen(text)-1] == 'l')
         && (text[strlen(text)-2] == 'l')
         && (measure(text) > 1) )
        text[strlen(text)-1] = '\0';
} // step_5()

// checks if the word has a given suffix
bool hasSuffix ( char *word, char *suffix, char *stem )
{
    char tmp[BIG_KEYWORDSIZE];
    if ( strlen(word) <= strlen(suffix) )
        return(false);
    if ( (strlen(suffix) > 1) &&
         ( word[strlen(word)-2] != suffix[strlen(suffix)-2] ) )
        return(false);
    mystrcpy ( stem, KEYWORDSIZE, "" );
    //mystrncat ( stem, sizeof(stem), word, strlen(word) - strlen(suffix) );
	mystrncat(stem, KEYWORDSIZE, word, strlen(word) - strlen(suffix));
    mystrcpy ( tmp, KEYWORDSIZE, stem );
    mystrncat ( tmp, KEYWORDSIZE, suffix, strlen(suffix) );
    if ( strcmp (  tmp, word ) == 0 )
        return(true);
    else
        return(false);
} // hasSuffix()

bool cvc ( char *text )
{
    int length=strlen(text);
    if ( length < 3 )
        return(false);
    if ( (vowel(text[length-1],text[length-2]) == false)
         && (text[length-1] != 'w')
         && (text[length-1] != 'x')
         && (text[length-1] != 'y')
         && (vowel(text[length-2],text[length-3]) == true)
         && ( ( (length==3) && (vowel(text[0],'a') == false) )
              || (vowel(text[length-3],text[length-4])==false) ) )
        return(true);
    else
        return(false);
} // cvc()

// returns true if the character is a vowel. It needs the previous
// character because y is considered a vowel only when preceded by a
// vowel.
bool vowel ( char ch, char prev )
{
    switch ( ch ) 
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u': return(true);
        break;
    case 'y': return( vowel(prev,'?') == true );
        break;
    default : return(false);
        break;
    }
} // vowel()

int measure ( char *stem )
{
    register int i=0, count = 0;
    int length=strlen(stem);
    while ( i < length ) 
    {
        for ( ; i < length ; i++ ) 
        {
            if ( i > 0 ) 
            {
                if ( vowel(stem[i],stem[i-1]) == true )
                    break;
            }
            else 
            {
                if ( vowel(stem[i],'a') == true )
                    break;
            }
        }
        for ( i++ ; i < length ; i++ ) {
            if ( i > 0 ) 
            {
                if ( vowel(stem[i],stem[i-1]) == false )
                    break;
            }
            else 
            {
                if ( vowel(stem[i],'?') == false )
                    break;
            }
        }
        if ( i < length ) 
        {
            count++;
            i++;
        }
    }
    return(count);
} // measure()

// checks if the word contains a vowel
bool containsVowel ( char *word )
{
    register int i;
    for ( i=0 ; i < strlen(word) ; i++ )
        if ( i > 0 ) 
        {
            if ( vowel(word[i],word[i-1]) == true )
                return(true);
        }
        else 
        {
            if ( vowel(word[0],'a') == true )
                return(true);
        }
    return(false);
} // containsVowel()
