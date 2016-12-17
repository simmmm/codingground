#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* fileFile(){
    FILE *fp;
    long lSize;
    char *buffer;
    
    fp = fopen ( "donnees.txt" , "rb" );
    if( !fp ) perror("donnees.txt"),exit(1);
    
    fseek( fp , 0L , SEEK_END);
    lSize = ftell( fp );
    rewind( fp );
    
    /* allocate memory for entire content */
    buffer = calloc( 1, lSize+1 );
    if( !buffer ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);
    
    /* copy the file into the buffer */
    if( 1!=fread( buffer , lSize, 1 , fp) )
      fclose(fp),free(buffer),fputs("entire read fails",stderr),exit(1);
    
    /* do your work here, buffer is a string contains the whole text */
    
    fclose(fp);
    
    //free(buffer);
    
    return buffer;
}

int extractRegPattern()
{
    char* buffer;
    int err;
   
    regex_t preg;
    
    const char *str_request = fileFile();
    const char *str_regex = "(<BODY>[:space:]*)(.*?)([:space:]*</BODY>)";

    err = regcomp (&preg, str_regex, REG_EXTENDED);
   
    if (err == 0)
    {
        int match;
        size_t nmatch = 0;
        regmatch_t *pmatch = NULL;
      
        nmatch = preg.re_nsub;
        pmatch = malloc (sizeof (*pmatch) * nmatch);
        if (pmatch)
        {

            match = regexec (&preg, str_request, nmatch, pmatch, 0);

            regfree (&preg);

            if (match == 0)
            {
                char *site = NULL;
                int start = pmatch[2].rm_so;
                int end = pmatch[2].rm_eo;
                size_t size = end - start;
               
                site = malloc (sizeof (*site) * (size + 1));
                if (site)
                {
                    strncpy (site, &str_request[start], size);
                    site[size] = '\0';
                    printf ("%s\n", site);
                    free (site);
                }
            }

            else if (match == REG_NOMATCH)
            {
                printf ("%s n\'est pas une adresse internet valide\n", str_request);
            }

            else
            {
                char *text;
                size_t size;

                size = regerror (err, &preg, NULL, 0);
                text = malloc (sizeof (*text) * size);
                if (text)
                {

                    regerror (err, &preg, text, size);
                    fprintf (stderr, "%s\n", text);
                    free (text);
                }
                else
                {
                    fprintf (stderr, "Memoire insuffisante\n");
                    exit (EXIT_FAILURE);
                }
            }
        }
        else
        {
            fprintf (stderr, "Memoire insuffisante\n");
            exit (EXIT_FAILURE);
        }
    }

    return (EXIT_SUCCESS);
}

int main()
{
    char* myName;
    
    char* buffer;
    
    myName = (char*) malloc(10 * sizeof(char));
    
    strcpy(myName, "test2");
    
    printf("Hello, World! %s\n", myName);

    buffer = fileFile();
    
    printf("FILE{%s}", buffer);
    
    free(buffer);

    extractRegPattern();

    return 0;
}

