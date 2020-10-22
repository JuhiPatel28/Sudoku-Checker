//Juhi Patel
//jmp170130
//CS 1337.007

#include <fstream>
#include <string>
#include <cctype> //for isdigit
using namespace std;

const int column = 9; //const for columns
const int row = 9; //const for rows

int checkcolumn(int**, int); //column checker
int checkrow(int**, int); //row checker
int subsquare(int*); //subgrid checker

int main()
{
    bool error = false; //flag for error
    bool allnumbers = true; //flag for spaces
    fstream file; //filestream
    int sudokuname; //store sudoku name
    int inf; //store input file pointer location

    file.open("puzzles3.txt", ios::in | ios::binary); //open input file

    if(!file.fail()) //check if it opened
    {
        while(file.peek() != -1 && !file.fail()) //loop while it is not at the end of file
        {
            file >> sudokuname; //input sudoku name

            int **ary = new int*[row]; //dynamically create 2d array
            for(int counter = 0; counter < row; counter++)
            {
                ary[counter] = new int[column];
            }

            for(int counter = 0; counter < row; counter++) //fill dynamic array
            {
                for(int counter1 = 0; counter1 < column; counter1++)
                {
                    if(file.peek() == '\n' || file.peek() == '\r') //check for newlines and skip them
                    {
                        counter1--;
                        file.get();
                        continue;
                    }
                    int temp = file.get(); //get chatacter

                    if(temp == -1 || temp == EOF) //check for end of file
                    {
                        return 0;
                    }

                    if(temp == ' ') //check if temp is a space character
                    {
                        ary[counter][counter1] = 0; //replace space with 0
                        allnumbers = false; //set flag for space characters
                    }

                    if(isdigit(temp))
                    {
                        ary[counter][counter1] = temp - '0'; //convert temp to int and store in array
                    }
                }
            }

            file.seekp(2, ios::cur); //skip two spaces in file
            inf = file.tellg(); //get input file pointer location
            file.close(); //close input file

            file.open("solutions.txt", ios::out | ios::in | ios::ate); //open output file at the end and so that it doesnt delete upon being reopened

            int rowerr = 1; //row # 1 based
            for(int counter = 0; counter < row; counter++) //iterates for each row
            {
                int rowerror = checkrow(ary, counter); //send array double pointer and row to function
                if(rowerror != 0) //check for error
                {
                    error = true; //set error flag
                    file << sudokuname << "\t" << "invalid" << "\t\t" << "row " << rowerr << " has multiple " << rowerror << "s " << endl; //output error message
                    break; //leave loop
                }
                rowerr++; //row # 1 based
            }


            if(!error) //skip if already an error
            {
                int colerr = 1; //column # 1 based
                for(int counter = 0; counter < column; counter++)
                {
                    int colerror = checkcolumn(ary, counter); //send double pointer and columnm to function

                    if(colerror != 0) //check for error
                    {
                        error = true; //set error flag
                        file << sudokuname << "\t" << "invalid" << "\t\t" << "column " << colerr << " has multiple " << colerror << "s " << endl; //output error msg
                        break; //leave loop
                    }
                    colerr++; //column # 1 based
                }
            }

            if(!error) //skip if already an error
            {
                int *subsq = new int[9]; //new dynamic 1d array
                int *itr2; //copy of subsq

                int quad = 0; //quadrant counter
                for(int k = 0; k < 9; k += 3) //increments row constraints
                {
                    for(int l = 0; l < 9; l += 3) //increments column constraints
                    {
                        itr2 = subsq; //copy subsq to this pointer
                        for(int r = k; r < (k+3); r++) //increments rows
                        {
                            for(int c = l; c < (l+3); c++) //increments columns
                            {
                                *itr2 = ary[r][c]; //sets value of itr to value at array
                                itr2++; //moves to next index
                            }
                        }
                        int suberr = subsquare(subsq); //sends single pointer to function
                        quad++; //quadrant counter
                        if(suberr != 0) //checks for error
                        {
                            error = true; //set error flag
                            /* FIXING CODE ERRORS
                            old code:
                            file << sudokuname << "\t" << "invalid" << "\t\t" << "quadrent " << quad << "has " << suberr << "s " << endl;
                            */
                            if(quad == 1)
                            {
                                file << sudokuname << "\t" << "invalid" << "\t\t" << "Top left quadrent has multiple " << suberr << "s " << endl;
                            }
                            else if(quad == 2)
                            {
                                file << sudokuname << "\t" << "invalid" << "\t\t" << "Top middle quadrent has multiple " << suberr << "s " << endl;
                            }
                            else if(quad == 3)
                            {
                                file << sudokuname << "\t" << "invalid" << "\t\t" << "Top right quadrent has multiple " << suberr << "s " << endl;
                            }
                            else if(quad == 4)
                            {
                                file << sudokuname << "\t" << "invalid" << "\t\t" << "Middle left quadrent has multiple " << suberr << "s " << endl;
                            }
                            else if(quad == 5)
                            {
                                file << sudokuname << "\t" << "invalid" << "\t\t" << "Middle middle quadrent has multiple " << suberr << "s " << endl;
                            }
                            else if(quad == 6)
                            {
                                file << sudokuname << "\t" << "invalid" << "\t\t" << "Middle left quadrent has multiple " << suberr << "s " << endl;
                            }
                            else if(quad == 7)
                            {
                                file << sudokuname << "\t" << "invalid" << "\t\t" << "Bottom left quadrent has multiple " << suberr << "s " << endl;
                            }
                            else if(quad == 8)
                            {
                                file << sudokuname << "\t" << "invalid" << "\t\t" << "Bottom middle quadrent has multiple " << suberr << "s " << endl;
                            }
                            else if(quad == 9)
                            {
                                file << sudokuname << "\t" << "invalid" << "\t\t" << "Bottom right quadrent has multiple " << suberr << "s " << endl;
                            }
                            break; //leave loop
                        }

                    }
                    /* FIXING CODE ERRORS */
                    if(error == true)
                    {
                        break; //forgot to make it break out of 2nd loop after error is found
                    }
                }
                free(subsq); //free dynamic memory
            }



            if(error != true && allnumbers == true) //checks flags
            {
                file << sudokuname << "\t" << "Solved" << endl; //outputs appropraite msg
            }
            else if(error != true) //checks flags
            {
                file << sudokuname << "\t" << "Valid" << endl; //outputs appropraite msg
            }

            file.close(); //close output file

            file.open("puzzles3.txt", ios::in | ios::binary); //open input file again
            file.seekp(inf, ios::beg); //move pointer to last saved location

            for (int i = 0; i < 9; i++) //free old 2d array
            {
                free(ary[i]);
            }
            free(ary);

            error = false; //reset flags
            allnumbers = true; //reset flags
        }
    }
}


int checkcolumn(int **ptr, int c) //column validator
{
    int **temp = ptr; //copy 1 of 2d pointer
    int **temp2 = ptr + 1; //copy 2 of 2d pointer moved up one index

    for(int counter = 0; counter < 9; counter++) //iterate 9 times
    {
        int *ptr = *temp; //single pointer set equal to copy 1 of dereferenced 2d pointer
        ptr += c; //move index to correct column
        int *ptr2 = *temp2; //single pointer set equal to copy 2 of dereferenced 2d pointer
        ptr2 += c; //move index to correct column
        for(int counter1 = (counter + 1); counter1 < 9; counter1++) //compares values
        {
            if(*ptr == 0) //skip space values
            {
                continue;
            }
            if(*ptr == *ptr2) //check if same value
            {
                return *ptr; //returns offending value
            }
            temp2++; //move second 2d pointer to next index (down a row basically)
            ptr2 = *temp2; //reset row
            ptr2 += c; //reset column
        }
        temp++; //move first 2d pointer to next index (down a row basically)
        temp2 = temp+1; //move second 2d pointer down one more row than the 1st 2d pointer
    }
    return 0; //if no error, return zero
}


int checkrow(int **ptr, int r) //row checker
{
    int **temp = ptr + r; //copy of original 2d pointer at correct row
    int *ptr1 = *temp; //1d pointer pointing at dereferenced 2d pointer
    int *ptr2 = ptr1+1; //copy of 1d pointer up one index

    for(int counter = 0; counter < 9; counter++) //iterate 9 times
    {
        for(int counter1 = (counter + 1); counter1 < 9; counter1++) //compares values
        {
            if(*ptr1 == 0) //skip spaces
            {
                continue;
            }
            if(*ptr1 == *ptr2) //checks if they are same values
            {
                return *ptr1; //returns offending value
            }
            ptr2++; //move second 1d pointer to next index in row
        }
        ptr1++; //move first 1d pointer to next indecx in row
        ptr2 = ptr1 + 1; //move second 1d pointer to one index after first 1d pointer
    }
    return 0; //return no error
}


int subsquare(int *ptr) //check subsquares
{
    int *ptr1 = ptr; //copy of 1d pointer
    int *ptr2 = ptr + 1; //copy of 1d pointer at next index

    for(int counter = 0; counter < 9; counter++) //loop 9 times
    {
        for(int counter1 = (counter + 1); counter1 < 9; counter1++) //check values
        {
            if(*ptr1 == 0) //skip spaces
            {
                continue;
            }
            if(*ptr1 == *ptr2) //check if same value
            {
                return *ptr1; //return offending value
            }
            ptr2++; //move second pointer to next index
        }
        ptr1++; //move first 1d pointer to next indecx in row
        ptr2 = ptr1 + 1; //move second 1d pointer to one index after first 1d pointer
    }
    return 0; //return no error
}


