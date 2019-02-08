#include <dirent.h>
#include <stdio.h>
#include <string.h>

#define MAX_WORD_LEN 100
#define MAX_DIR_LEN 1000

void recFindLetter(char letter, char* dir_path){

    char delimetr = '/';
    char* point;
    char new_dir[MAX_DIR_LEN];

    DIR* dir_meta = opendir(dir_path);
    struct dirent* next = readdir(dir_meta);
    while (next){
        if (strcmp(next->d_name, ".") && strcmp(next->d_name, "..")) {
            switch (next->d_type) {
                case DT_DIR:
                    sprintf(new_dir, "%s/%s", dir_path, next->d_name);
                    recFindLetter(letter, new_dir);
                    break;
                case DT_REG:
                    point = strpbrk(next->d_name, ".");
                    if (point && point[1] && !strcmp(point+1, "txt")){
                        *point = '\0';
                        if (strlen(next->d_name) == 1 && next->d_name[0] == letter) {
                            *point = '.';
                            printf("%s/%s\n", dir_path, next->d_name);
                        }
                    }
                    break;
            }
        }
        next = readdir(dir_meta);
    }
    closedir(dir_meta);

}

int main(){

    freopen("result.txt", "w", stdout);
    int words_count;
    scanf("%d", &words_count);

    for(int i=0; i<words_count; i++){

        char str[MAX_WORD_LEN];
        scanf("%s", str);

        DIR* dir = opendir("tmp");
        if (!dir){
            printf("Error in open directory\n");
        }

        for (int i=0; str[i]; i++){
            recFindLetter(str[i], "tmp");
        }

    }

    return 0;
}
