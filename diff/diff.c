#include <stdio.h>
#include <stdlib.h>
#include "diff.h"
#include <ctype.h>
#include <string.h>

// Create a t_file object from a .txt file
t_file* file_create(char* file_name)
{

    // Alloc memory for the file
    t_file* file = (t_file*)malloc(sizeof(t_file));

    // init variable
    FILE* f_file;
    int nb_line = 1;
    int char_ascii = 0;
    int nb_char = 0;
    int i;

    // if file is readable -> we can work !
    if ((f_file = fopen(file_name,"r")))
    {

        // get the number of line
        while((char_ascii=fgetc(f_file))!= EOF)
        {
            if(char_ascii==10)
                nb_line++;
        }

        // alloc the number of line
        file->size_line = calloc(nb_line,sizeof(int));

        // Initialize the number of line in t_file
        file->nb_line = nb_line;

        // Initialize the size of each line at 0 in t_file
        for(i = 0; i < nb_line; i++)
        {
            file->size_line[i] = 0;
        }

        // Got back to init
        fseek(f_file,0,SEEK_SET);
        nb_char = 0;
        nb_line = 0;

        // Get the size of each line in t_file
        while((char_ascii=fgetc(f_file))!= EOF)
        {
            nb_char++;
            file->size_line[nb_line] = nb_char;
            if(char_ascii==10)
            {
                nb_line++;
                nb_char = 0;
            }
        }

        // Alloc the number of line in the lines object
        char** lines = calloc((nb_line+1),sizeof(char*));

        int i;
        // Alloc each line in the lines object
        for(i = 0 ; i < nb_line+1 ; i++)
        {
            char* line = calloc(file->size_line[i]*(nb_line+1),sizeof(char));
            lines[i] = &line[i*file->size_line[i]];
        }

        // Put the lines object in the t_file
        file->lines = lines;

        // Got back to init
        fseek(f_file,0,SEEK_SET);
        nb_char = 0;
        nb_line = 0;

        // Get the every char of the txt in the t_file
        while((char_ascii=fgetc(f_file))!= EOF)
        {
            file->lines[nb_line][nb_char] = char_ascii;
            nb_char++;
            if(char_ascii==10)
            {
                nb_char = 0;
                nb_line++;
            }
        }

        // Work is done, close the file !
        fclose(f_file);
    }
    else{
      return NULL;
    }
    // return the t_file created
    return file;
}

// get the lcs of the two file
t_file* get_lcs(t_file* file_1, t_file* file_2)
{
    // init variable
    int size_x = file_1->nb_line;
    int size_y = file_2->nb_line;
    int i;
    int j;
    int lcs_matrix[size_x+1][size_y+1];

    // We complete the matrix with O
    for(i=0 ; i <= size_x ; i++)
    {
        for (j = 0; j <= size_y; j++)
        {
            lcs_matrix[i][j] = 0;
        }
    }

    // loop on row
    for(i = 1 ; i <= size_x ; i++)
    {
        // loop on columns
        for(j = 1 ; j <= size_y ; j++)
        {
            // if same line on both file :
            // the case of the matrix is previous in diagonal + 1
            if(strcmp(get_line(file_1,i-1),get_line(file_2,j-1)) == 0)
            {
                lcs_matrix[i][j] = (lcs_matrix[i-1][j-1]) + 1;
            }
            // else : we get the biggest number between the case
            // on the left or the top
            else if(lcs_matrix[i][j-1] > lcs_matrix[i-1][j])
            {
                lcs_matrix[i][j] = lcs_matrix[i][j-1];
            }
            else
            {
                lcs_matrix[i][j] = lcs_matrix[i-1][j];
            }
        }
    }

    // init the loop back
    int size = lcs_matrix[i-1][j-1];
    char** lcs_string = calloc(size, sizeof(char*));
    int k = size - 1;
    int prc[k];

    // loop on row from bottom
    for(i = i-1 ; i > 0 ; i--)
    {
        // loop on columns from right
        for(j = j-1 ; j > 0 ; j--)
        {
            // if up case is the same :
            // we decrease i but stay in same j so :
            // break the second loop but add + 1 to j
            // for the for line : j = j-1
            if(lcs_matrix[i][j] == lcs_matrix[i-1][j])
            {
                j++;
                break;
            }
            // if left case is the same :
            // we decrease j so :
            // continue loop to use the line for (j = j-1)
            else if(lcs_matrix[i][j] == lcs_matrix[i][j-1])
            {
                continue;
            }
            // else... bingo ! we save i-1 (the index of one line of lcs)
            // in the index array prc by the end (because the loop is backward)
            else
            {
                prc[k--] = i-1;
                break;
            }
        }
    }

    // We get the line at the index array prc of file 1 and save them
    // in the good order in the lcs
    for(i=0 ; i < size ; i++)
    {
        char* lcs_line = calloc(file_1->size_line[prc[i]]*size, sizeof(char));
        lcs_string[i] = get_line(file_1,prc[i]);
    }

    // we create a t_file for getting the size !
    t_file* lcs = (t_file*)malloc(sizeof(t_file));
    lcs->lines = lcs_string;
    lcs->nb_line = size;

    return lcs;
}

//Print the t_file
void file_print(t_file* file)
{
    //init variable
    int i = 0;
    //Print each line
    for(; i < file->nb_line; i++)
    {
        //Print each char
        fprintf(fp, "%s",get_line(file,i));
    }
}

// lower all the file
t_file * to_lower_case(t_file* file)
{
    //init variable
    int i;
    int j;
    // file must be good
    if(file)
    {

        //for each line
        for(i=0; i < file->nb_line; i++)
        {
            //for each char
            for(j=0; j < file->size_line[i]; j++)
            {
                //lower the char
                file->lines[i][j] = tolower(file->lines[i][j]);
            }
        }
    }

    return file;
}

// boolean if file are different
int is_file_different(t_file * file1, t_file * file2)
{
    int i;
    int j;
    //both file must be good
    if(file1 && file2)
    {
        //compare the number of line
        if(file1->nb_line!=file2->nb_line)
            return 1;
        //compare the number of char for a line
        for(i=0; i<file1->nb_line; i++)
        {
          if(file1->size_line[i]!=file2->size_line[i])
            return 1;
        }

        //compare every char of every line
        for(i=0; i < file1->nb_line; i++)
        {
            for(j=0; j < file1->size_line[i]; j++)
            {
                if(file1->lines[i][j]!= file2->lines[i][j])
                    return 1;
            }
        }
    }

    return 0;
}

// ignore blank space
t_file* ignore_blank(t_file * file)
{
    t_file* new_file;
    if (file != NULL)
    {
        new_file = file;
        if (new_file != NULL)
        {
            int i;
            int j;

            for(i=0; i < file->nb_line; i++)
            {
                int y=0;
                for(j=0; j < file->size_line[i]; j++)
                {

                    if((file->lines[i][j]!=' ')&&(file->lines[i][j]!='\t'))
                    {
                        new_file->lines[i][y]=file->lines[i][j];
                        y++;
                    }
                }
                new_file->lines[i][y]='\0';
            }
        }
    }
    return new_file;
}


//Return a line of file at index
char* get_line(t_file* file,int index)
{
    return file->lines[index];
}

//Print of diff depending of files and line
void print_line_file(t_file* file, int num_file, int start, int end)
{
    //file is file 1 the char is < else is >
    char file_sign = (num_file==1)?'<':'>';
    int i;

    //we print line between the index in param
    for(i = start; i < end ; i++)
        fprintf(fp, "%s", get_line(file,i));
}

//Comparse two file
void file_compare(t_file* file_1, t_file* file_2, t_file* file_1_print, t_file* file_2_print)
{

    fp = fopen(EDIT_FILE, "w");


    // get the lcs of the two file
    t_file* lcs = get_lcs(file_1, file_2);
    // init variable
    int index_lcs = 0;
    int index_lcs_1 = 0;
    int index_lcs_2 = 0;
    int index_file_1 = 0;
    int index_file_2 = 0;

    // loop in the lcs line -> lines who are in both file in same order
    for(index_lcs = 0 ; index_lcs < lcs->nb_line ; index_lcs++)
    {
        //get the line for both file and lcs at various index
        char * line_1 = get_line(file_1,index_file_1);
        char * line_2 = get_line(file_2,index_file_2);
        char * line_lcs = get_line(lcs,index_lcs);

        index_lcs_1 = index_file_1;
        index_lcs_2 = index_file_2;

        // line file 1 equal lcs but not file 2 : we add lines until we find lcs
        if(strcmp(line_1,line_lcs) == 0 && strcmp(line_2,line_lcs) != 0)
        {
            //until we find lcs -> get the last index
            while(strcmp(line_2,line_lcs) != 0)
            {
                index_lcs_2++;
                line_2 = get_line(file_2,index_lcs_2);
            }
            //print between the index begins and last calcul index
            if(index_lcs_2 == index_file_2+1)
                fprintf(fp, "%da%d\n",index_file_1,index_lcs_2);
            else
                fprintf(fp, "%da%d,%d\n",index_file_1,index_file_2+1,index_lcs_2);
            print_line_file(file_2_print,2,index_file_2,index_lcs_2);
        }

        // line file 2 equal lcs but not file 1 : we remove lines until we find lcs
        else if(strcmp(line_1,line_lcs) != 0 && strcmp(line_2,line_lcs) == 0)
        {
          //until we find lcs -> get the last index
            while(strcmp(line_1,line_lcs) != 0)
            {
                index_lcs_1++;
                line_1 = get_line(file_1,index_lcs_1);
            }
            //print between the index begins and last calcul index
            if(index_lcs_1 == index_file_1+1)
                fprintf(fp, "%dd%d\n",index_lcs_1,index_file_2);
            else
                fprintf(fp, "%d,%dd%d\n",index_file_1+1,index_lcs_1,index_file_2);
            print_line_file(file_1_print,1,index_file_1,index_lcs_1);
        }

        // line file 2 and line file 1 differ lcs:
        // we permute lines until we find lcs in both file
        else if(strcmp(line_1,line_lcs) != 0 && strcmp(line_2,line_lcs) != 0)
        {
          //until we find lcs in file 1 -> get the last index
            while(strcmp(line_1,line_lcs) != 0)
            {
                index_lcs_1++;
                line_1 = get_line(file_1,index_lcs_1);
            }
            //until we find lcs in file 2 -> get the last index
            while(strcmp(line_2,line_lcs) != 0)
            {
                index_lcs_2++;
                line_2 = get_line(file_2,index_lcs_2);
            }
            //print between the index begins and last calcul index
            if(index_lcs_1 == index_file_1+1 && index_lcs_2 == index_file_2+1)
                fprintf(fp, "%dc%d\n",index_lcs_1,index_lcs_2);
            else if (index_lcs_1 == index_file_1+1)
                fprintf(fp, "%dc%d,%d\n",index_lcs_1,index_file_2+1,index_lcs_2);
            else if (index_lcs_2 == index_file_2+1)
                fprintf(fp, "%d,%dc%d\n",index_file_1+1,index_lcs_1,index_lcs_2);
            else
                fprintf(fp, "%d,%dc%d,%d\n",index_file_1+1,index_lcs_1,index_file_2+1,index_lcs_2);
            print_line_file(file_1_print,1,index_file_1,index_lcs_1);
            fprintf(fp, "---\n");
            print_line_file(file_2_print,2,index_file_2,index_lcs_2);
        }
        // line file 2 and line file 1 equal lcs: nothing to do !
        //add the last index and add one to skip the lcs done
        index_file_1 = index_lcs_1+1;
        index_file_2 = index_lcs_2+1;
    }

    // IF there is still lines after last lcs :
    // do the same as before but instead of searching
    // a line of lcs we search the end of the file
    if(index_file_2 > file_2->nb_line-1 && index_file_1 > file_1->nb_line-1)
    {
      //Nothing to do ! files are over
    }

    // File 2 is the only one over : we delete rest in file 1
    else if(index_file_2 > file_2->nb_line-1)
    {
        if(index_file_1 == file_1->nb_line-1)
            fprintf(fp, "%dd%d\n",index_file_1+1,index_file_2);
        else
            fprintf(fp, "%d,%dd%d\n",index_file_1+1,file_1->nb_line,index_file_2);
        print_line_file(file_1_print,1,index_file_1,file_1->nb_line);
    }

    // File 1 is the only one over : we add rest of file 2
    else if(index_file_1 > file_1->nb_line-1)
    {
        if(index_file_2 == file_2->nb_line-1)
            fprintf(fp, "%dd%d\n",index_file_1,index_file_2+1);
        else
            fprintf(fp, "%d,%dd%d\n",index_file_1,index_file_2+1,file_2->nb_line);
        print_line_file(file_2_print,2,index_file_2,file_2->nb_line);
    }

    // File 1 and 2 are not over : we permute all the rest
    else
    {
        if(index_file_2 == file_2->nb_line-1 && index_file_1 == file_1->nb_line-1)
            fprintf(fp, "%dc%d\n",index_file_1+1,index_file_2+1);
        else if (index_file_1 == file_1->nb_line-1)
            fprintf(fp, "%dc%d,%d\n",index_file_1+1,index_file_2+1,file_2->nb_line);
        else if (index_file_2 == file_2->nb_line-1)
            fprintf(fp, "%d,%dc%d\n",index_file_1+1,file_1->nb_line-1,index_file_2+1);
        else
            fprintf(fp, "%d,%dc%d,%d\n",index_file_1+1,file_1->nb_line,index_file_2+1,file_2->nb_line);
        print_line_file(file_1_print,1,index_file_1,file_1->nb_line);
        fprintf(fp, "---\n");
        print_line_file(file_2_print,2,index_file_2,file_2->nb_line);
    }

    fclose(fp);
}

// str_onespace
t_file* str_onespace(t_file* file)
{
    t_file* new_file;
    if (file != NULL)
    {
        int i;
        int j;
        int space = 0; //number of space
        new_file = file;
        if (new_file != NULL)
        {
            int y;
            for(i=0; i < file->nb_line; i++)
            {
                y = 0;
                for (j=0; j< file->size_line[i]; j++)
                {
                    if (file->lines[i][j] == 32 && space == 0)
                    {
                        new_file->lines[i][y] = file->lines[i][j];
                        y++;
                        space = 1;
                    } else if (file->lines[i][j] == 32 && space == 1) {
                        continue;
                    } else {
                        // si caractere non espace ou space egal 1
                        new_file->lines[i][y] = file->lines[i][j];
                        y++;
                        space = 0;
                    }
                }
                new_file->lines[i][y] = '\0';
            }
        }
    }
    return new_file;
}

//str_onetab
t_file* str_onetab(t_file* file)
{
    t_file* new_file;
    if (file != NULL)
    {
        int i;
        int j;
        int space = 0; //number of space
        new_file = file;
        if (new_file != NULL)
        {
            int y=0;
            for(i=0; i < file->nb_line; i++)
            {
                for (j=0; j< file->size_line[i]; j++)
                {
                    if (file->lines[i][j] == 9 && space == 0)
                    {
                        new_file->lines[i][y] = file->lines[i][j];
                        y++;
                        space = 1;
                    } else if (file->lines[i][j] == 9 && space == 1) {
                        continue;
                    } else {
                        // si caractere non espace ou space egal 1
                        new_file->lines[i][y] = file->lines[i][j];
                        y++;
                        space = 0;
                    }
                }
                new_file->lines[i][y] = '\0';
            }
        }
    }
    return new_file; //we return the string tweaked
}







void diff(char *file1, char *file2)
{
    // We check if the file exist
    if(file1 == NULL || file2 == NULL)
    {
      if(file1 == NULL)
        printf("diff: %s: No such file or directory\n",file1);
      if(file2 == NULL)
        printf("diff: %s: No such file or directory\n",file2);
      return;
    }

    // We create the two file to show
    t_file* file_1 = file_create(file1);
    t_file* file_2 = file_create(file2);

    // We create the two file to compare
    t_file* file_1_modif = file_create(file1);
    t_file* file_2_modif = file_create(file2);

    file_compare(file_1_modif,file_2_modif,file_1,file_2);
    
    free(file_1);
    free(file_2);
    free(file_1_modif);
    free(file_2_modif);
}
