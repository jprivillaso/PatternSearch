#include <stdio.h>

#define M 1024
#define N 2048

char p[M];
char t[N];
int b[M];

void kmp_preprocess(char *);
int kmp_algorithm(char *, char *);
void lcs(char *, char *, char *);

int main()
{
    int total;
	while(scanf("%s %s", p, t) != EOF){	    
		kmp_preprocess(p);
		total = kmp_algorithm(p,t);
		
		if (0 == total){
          puts("\nPatron no encontrado en texto\nBuscando con nuevo patron\n");
          char new_pattern[strlen(p)];
          lcs(p,t,new_pattern);
          
          kmp_preprocess(new_pattern);
          kmp_algorithm(new_pattern,t);  
        }       
		printf("\n");
    }
	return 0;
}

void kmp_preprocess(char * p)
{
     int i = 0;
     int j = -1;    
     int m = strlen(p);
      
     b[i] = j;
     while(i < m){
        while (j >= 0 && p[i] != p[j]) j = b[j];
        b[++i] = ++j;
     }
}

int kmp_algorithm(char * p, char * t)
{
     int i, j;
     int total_found = 0;
     int m = strlen(p);
     int n = strlen(t);
	
     i = 0, j = 0;
		
     while(i < n){
        while(j >= 0 && t[i] != p[j]) j = b[j];
		i++; j++;
		if (j == m){
			printf("%d\n",i-j);
			j = b[j];
			total_found++;
		}
      }
      return total_found;
}

void lcs(char * A, char * B, char * backtracking)
{
    int m = strlen(A);
    int n = strlen(B);
    
    int dp[m+1][n+1];
    
    int max_len = 0;
    int i, j, k = 0;
    
    for(i = 0; i<m; ++i){
        for (j = 0; j<n; ++j){
            if (A[i] != B[j]){
                dp[i][j] = 0;
            }else{
                if (i == 0 || j == 0){
                    dp[i][j] = 1;
                }else{
                    dp[i][j] = 1 + dp[i-1][j-1];           
                }
                if (max_len < dp[i][j]){
                    max_len = dp[i][j];
                    backtracking[k++] = A[i];
                }
            }
        }   
    }
    backtracking[k] = '\0';
}
