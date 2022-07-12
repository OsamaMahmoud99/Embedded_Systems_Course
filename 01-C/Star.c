void set_star(char arr[][20], int row, int col, int star_i,int star_j)
{
    int i, j;
    for(i=0; i<row; ++i)
    {
        for(j=0; j<col; ++j)
        {
            if(star_i == i)
            {
                arr[i][j] = '*';
            }
            else if(star_j == j && i<star_i)
            {
                arr[i][j] = 'V';
            }
            else if(star_j == j && i>star_i)
            {
                arr[i][j] = '^';
            }
            else if(j<star_j && i==star_i)
            {
                arr[i][j] = '>';
            }
            else if(j>star_j && i==star_i)
            {
                arr[i][j] = '<';
            }
            else if(j<star_j && i<star_i)
            {
                arr[i][j] = 'A';
            }
            else if(j<star_j && i>star_i)
            {
                arr[i][j] = 'B';
            }
            else if(j>star_j && i<star_i)
            {
                arr[i][j] = 'C';
            }
            else if(j>star_j &&i>star_i)
            {
                arr[i][j] = 'D';
            }
        }
        printf("\n");
    }
}

void star_print(char arr[][20], int row, int col)
{
    int i, j;
    for(i=0; i<row; ++i)
    {
        for(j=0; j<col; ++j)
        {
            printf("%c ",arr[i][j]);
        }
        printf("\n");
    }
}

void star_find(char arr[][20], int row, int col, int* pstar_i,int* pstar_j)
{
    int i, j;
    for(i=0; i<row; ++i)
    {
        for(j=0; j<col; ++j)
        {
            if(arr[i][j] == '*')
            {
                *pstar_i = i;
                *pstar_j = j;
                return;
            }
        }
        printf("\n");
    }
}

void star_find_binary(char arr[][20], int row, int col, int* pstar_i,int* pstar_j)
{
    int mid_row=0 , mid_col=0 , first_row = 0,last_row=row-1;
    int first_col=0,last_col=col-1;

    while(first_row<=last_row && first_col<=last_col)
    {
        mid_row = first_row+(last_row-1) / 2;
        mid_col = first_col+(last_col-1) / 2;

        if(arr[mid_row][mid_col] == '*')
        {
            *pstar_i = mid_row;
            *pstar_j = mid_col;
        }
        else if(arr[mid_row][mid_col] == 'V')
        {
            first_row = mid_row + 1;
        }
        else if(arr[mid_row][mid_col] == '^')
        {
            last_row = mid_row - 1;
        }
        else if(arr[mid_row][mid_col] == '>')
        {
            first_col = mid_col + 1;
        }
        else if(arr[mid_row][mid_col] == '<')
        {
            last_col = mid_col - 1;
        }
        else if(arr[mid_row][mid_col] == 'A')
        {
            first_row = mid_row + 1;
            first_col = mid_col + 1;
        }
        else if(arr[mid_row][mid_col] == 'B')
        {
            last_row = mid_row - 1;
            first_col = mid_col + 1;
        }
        else if(arr[mid_row][mid_col] == 'C')
        {
            first_row = mid_row + 1;
            last_col  = mid_col - 1;
        }
        else if(arr[mid_row][mid_col] == 'D')
        {
            last_row = mid_row - 1;
            last_col = mid_col - 1;
        }

    }

}
