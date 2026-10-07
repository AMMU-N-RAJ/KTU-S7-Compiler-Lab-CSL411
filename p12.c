#include <stdio.h>

int nfa[10][10][10];
int visited[1024];
int queue[1024];

int main(){
     int n_states,n_symbols;
     printf("Enter number of NFA states:");
     scanf("%d",&n_states);
     printf("Enter number of input symbols:");
     scanf("%d",&n_symbols);
     printf("Enter transition table:\n");
     for(int s=0;s<n_symbols;s++){
         printf("For symbol %d:\n",s);
         for(int i=0;i<n_states;i++){
             for(int j=0;j<n_states;j++){
                 scanf("%d",&nfa[s][i][j]);
             }
         }
     }
     printf("\nEquivalent DFA:\n");
     int head=0,tail=0;
     queue[tail++]=1;
     visited[1]=1;
     while(head<tail){
         int current_mask=queue[head++];
         printf("\nDFA state {");
         int first=1;
         for (int i=0;i<n_states;i++){
             if (current_mask & (1<<i)){
                if(!first) printf(",");
                    printf("q%d",i);
                    first=0;
             }
         }
         if(current_mask==0){
              printf(" ");
         }
         printf("}\n");
         for(int s=0;s<n_symbols;s++){
            int next_mask=0;
            for(int i=0;i<n_states;i++){
                if (current_mask & (1<<i)){
                   for(int j=0;j<n_states;j++){
                        if(nfa[s][i][j]==1){
                               next_mask|=(1<<j);
                        }
                    }
                 }
            }
            printf("On input %d -> {",s);
            first=1;
            for(int j=0;j<n_states;j++){
                if(next_mask & (1<<j)){
                   if(!first) printf(",");
                   printf("q%d",j);
                   first=0;
                 }
             }
             if (next_mask==0){
                  printf(" ");
             }
             printf("}\n");
             if(!visited[next_mask]){
                  visited[next_mask]=1;
                  queue[tail++]=next_mask;
            }
         }
      }
    return 0;
}
