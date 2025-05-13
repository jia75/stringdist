#include <string.h>

int min3(int a, int b, int c) {
    return a < b ? a < c ? a : c : c < b ? c : b;
}

int levenshteinDistance(char *s, char *t) {
    // degenerate cases
    if (strcmp(s, t) == 0) return 0;
    if (strlen(s) == 0) return strlen(t);
    if (strlen(t) == 0) return strlen(s);

    int *v0 = malloc(((strlen(t)+1) * sizeof(int)));
    int *v1 = malloc(((strlen(t)+1) * sizeof(int)));

    for (int i = 0; i < strlen(t)+1; i++)
        v0[i] = i;

    for (int i = 0; i <  strlen(s); i++)
    {
        v1[0] = i + 1;

        for (int j = 0; j <  strlen(t); j++)
        {
            int cost = (s[i] == t[j]) ? 0 : 1;
            v1[j + 1] = min3(v1[j] + 1, v0[j + 1] + 1, v0[j] + cost);
        }

        for (int j = 0; j <  strlen(t)+1; j++)
            v0[j] = v1[j];
    }
    int distance =  v1[strlen(t)];
    free(v0);
    free(v1);
    return distance;
}

int characterLink(char *str1, char *str2, int level) {
    //Order the strings
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int tempInt;
    char *tempStr;
    
    int equalHeadLength = 0;
    if (len2 < len1) {
        tempInt = len1;
        len1 = len2;
        len2 = tempInt;
        tempStr = str1;
        str1 = str2;
        str2 = tempStr;
    } else if (len1 == len2) {
        //Order alphabetically to ensure commutativity
        if (str1 == str2) {
            return 0;
        }
        int characterDifference;
        while ((characterDifference = str1[equalHeadLength] - str2[equalHeadLength]) == 0) {
            ++equalHeadLength;
        }
        if (characterDifference > 0) {
            tempInt = len1;
            len1 = len2;
            len2 = tempInt;
            tempStr = str1;
            str1 = str2;
            str2 = tempStr;
        }
    }

    //Define Variables
    int offset2 = equalHeadLength;
    int str2Pointer;
    int isMatched;
    int removedCharacterCount = 0;

    //Loop for every charcter in the smaller string
    for (int str1Pointer = offset2; str1Pointer < len1;)
    {
        isMatched = 0;

        if ((str2Pointer = str1Pointer + offset2) < len2 && str1[str1Pointer] == str2[str2Pointer])
        {
            ++str1Pointer;
            continue;
        }

        //Secondary loop for each extra level of depth
        for (int lookaheadDistance = 1; lookaheadDistance <= level; ++lookaheadDistance)
        {
            //falling case
            if (str2Pointer + lookaheadDistance < len2 && str1[str1Pointer] == str2[str2Pointer + lookaheadDistance])
            {
                //independent pointer movement
                offset2 += lookaheadDistance;
                ++str1Pointer;
                isMatched = 1;
                break;
            }
            //rising case
            if (str1Pointer + lookaheadDistance < len1 && str2Pointer < len2 && str1[str1Pointer + lookaheadDistance] == str2[str2Pointer])
            {
                removedCharacterCount += lookaheadDistance;
                //parallel pointer movement
                str1Pointer += lookaheadDistance + 1;
                isMatched = 1;
                break;
            }
        }
        if (!isMatched)
        {
            ++str1Pointer;
            ++removedCharacterCount;
        }
    }
    //Console.WriteLine(str1);
    return len2 - len1 + removedCharacterCount;

}