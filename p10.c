#include <stdio.h>

int n;
int matrix[10][10];
int visited[10];

void fClosure(int state){
     visited[state]=1;
     for (int i=0;i<n;i++){
         if (matrix[state][i]==1 && !visited[i]){
            fClosure(i);
         }
     }
}

int main(){
    printf("Enter number of states:");
    scanf("%d",&n);
    printf("Enter epsilon transition matrix:\n");
    scanf("(Enter 1 if epsilon transition exists, else 0)\n");

    for (int i=0;i<n;i++){
       for (int j=0;j<n;j++){
            scanf("%d", &matrix[i][j]);
        }
    }
    printf("\nEpsilon Closures:\n");
    for(int i=0;i<n;i++){
         for(int j=0;j<n;j++){
           visited[j]=0;
          }
          fClosure(i);
          printf("Closure(q%d)={",i);
          for(int j=0;j<n;j++){
             if(visited[j]){
                  printf("q%d",j);
             }
          }
          printf("}\n");
        }
         return 0;
}
