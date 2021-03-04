#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const int max_count_char = 20;
void free_string(char *string);

void enter_str(char** osn_str, char* vsp_str, int* size) {

    int q = 0;
    int n = 1;
    *osn_str = (char *) calloc(*size, sizeof(char));
    printf("Enter string: ");
    while (1) {
        n = scanf("%9[^\n]s", vsp_str);
        if (n == 0) { break; }
        *size += 10;
        *osn_str = (char *) realloc(*osn_str, *size * sizeof(char));
        strcpy(*(osn_str) + q, vsp_str);

        q += 9;
    }
}

int get_start_index(char *current_str){
    int start_index = 0;
    for(start_index; start_index< strlen(current_str); start_index++) {
        if (current_str[start_index] != ' '  && current_str[start_index] != '\t') break;
    }
    return start_index;
}

void add_number (int i, int start_index_number, char *current_str, char *return_str){
    char temp_char[] = "0";
    for (int k=i-1; k >= start_index_number; k-=1) {
        if (k == i-1 && current_str[k] == '0') continue;
        temp_char[0] = current_str[k];
        strncat(return_str, temp_char, 1);
    }
    if (!(i-1 == start_index_number && (current_str[i-1] == '0' || current_str[i-1] == '\t'))) return_str[strlen(return_str)] = ' ';
}

int end_of_number (char *current_str, int flag_end_number, int i){
    int end_of_number = 0;
    if (((*(current_str + i) ==  ' ' || *(current_str + i) == '\t') && flag_end_number == 0)) {
        end_of_number = 1;
    }
    else if (flag_end_number == 0 && *(current_str + i) ==  '\0'){
        end_of_number = 1;
    }
    return end_of_number;

}

void print_string(char *string){
    printf("New string: %s\n", string);

}

void free_string(char *string){
    free(string);
    string = NULL;
}

void logic(char* current_str) {
    int flag_end_number = 0;
    int start_index_number = get_start_index(current_str);
    int start_index = start_index_number;
    char* return_str = (char*)calloc(max_count_char, sizeof(char)) ;
    for (int i=start_index; i< strlen(current_str) + 1; i++) {
        if (end_of_number(current_str, flag_end_number, i)) {
            add_number(i, start_index_number, current_str, return_str);
            flag_end_number = 1;
        } else if (flag_end_number == 1 && (current_str[i] !=  ' ' && current_str[i] != '\t')){
            flag_end_number = 0;
            start_index_number = i;
        }
    }
    print_string(return_str);
    free_string(return_str);
}

int main(){
    int flag_end = 0;
    char* current_str = NULL;
    int size = 0;
    char vsp_str[10];

    char answerEnd = 'Y';
    while (answerEnd == 'Y' ) {
        enter_str(&current_str, vsp_str, &size);
        if (strlen(current_str) != 0){
            logic(current_str);
            scanf("%*c");
        }

        printf("Continue? Y/N: ");
        scanf("%c", &answerEnd);
        fflush(stdin);

    }
    free_string(current_str);
    return 0;
}

