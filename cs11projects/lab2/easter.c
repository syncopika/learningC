#include <stdio.h>
#include <stdlib.h>

/*function to calculate the date of Easter given a specific year */
/*return value should be either a negative int or positive int.
  positive = April; negative = March */
  
int calculate_Easter_date(int year){

    /*check if year value is in range*/
    if(year < 1582 || year > 39999){
        return 0;
    }

    /*take the year and calculate the "Golden year"*/
    int goldenYear = (year % 19) + 1;

    /*calculate the century*/
    int century = (year / 100) + 1;

    /*calculate skipped leap years*/
    int skippedLeapYears = (3*century / 4) - 12;

    /*calculate the correction factor for the moon's orbit*/
    int moonOrbit = ((8*century + 5) / 25) - 5;

    /*some correction factor for a day in March being a Sunday??*/
    int marchFactor = ((5*year)/4) - skippedLeapYears - 10;

    /*calculate "epact"*/
    int epact = ((11*goldenYear) + 20 + moonOrbit - skippedLeapYears) % 30;
    /*some conditions affecting epact
      Use 0 or 1 for booleans!!!
    */
    int cond1 = ((epact == 25) && (goldenYear > 11)) ? 1 : 0;
    int cond2 = (epact == 24) ? 1 : 0;
    if(cond1 || cond2){
        epact++;
    }

    /*calculate calendar full moon*/
    int fullMoon = 44 - epact;
    if(fullMoon < 21){
        fullMoon = fullMoon + 30;
    }

    /*calculate Sunday after full moon*/
    fullMoon = fullMoon + 7 - ((marchFactor + fullMoon)%7);

    /*finally calculate the date*/
    if(fullMoon > 31){
        /*return a date in APRIL (positive value!)*/
        return fullMoon - 31;
    }else{
        /* otherwise a date in MARCH */
        return 0 - fullMoon;
    }
}


int main()
{
    printf("Please enter a year to find out when Easter occurred that year. \n");

    int year;
    scanf("%d", &year);

    int easterDate = calculate_Easter_date(year);
    if(easterDate == 0){
        /* if invalid year, print an error message! */
        fprintf(stderr, "not a valid year. \n");
    }else{
        if(easterDate > 0){
            printf("Easter was on April %d, %d", easterDate, year);
        }else{
            int marchDate = 0 - easterDate; /* correct the negative sign */
            printf("Easter was on March %d, %d", marchDate, year);
        }
    }
    return 0;
}
