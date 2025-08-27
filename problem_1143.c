int longestCommonSubsequence(char* text1, char* text2) {
    int rows = strlen(text1);
    int cols = strlen(text2);

    int **dp = calloc(rows+1, sizeof(int *));
    for(int i=0; i<=rows; i++){
        dp[i] = calloc(cols+1, sizeof(int));
    }

    for(int i=1; i<=rows; i++){
        for(int j=1; j<=cols; j++){
            if(text2[j-1]==text1[i-1]){
                dp[i][j] = 1 + dp[i-1][j-1];
            }
            else{
                dp[i][j] = (dp[i-1][j]>dp[i][j-1] ? dp[i-1][j]:dp[i][j-1]);
            }
        }
    }
    return dp[rows][cols];
}