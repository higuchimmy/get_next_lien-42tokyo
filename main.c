#include "get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include <stdio.h>
# include <fcntl.h>

int main(int argc, char **argv)
{
    int fd[argc];
    int ret;
    int line_count;
    char *line; //ここにディスクリプタから読み込んだ文字列を入れていく
    int i;
    clock_t start,end;

    i = 1;
    line_count = 0;
    if (argc >= 2)
    {
        while (i < argc) //複数のファイルディスクリプタを受け付けた場合、コマンドライン引数で順番が若い者が先に呼ばれる
		//コマンドライン引数が1個ならargcは2,etc. ./a.out hogeならhogeはargv[1]
        {
            start = clock(); //時間計測
            line_count = 0;
            fd[i] = open(argv[i], O_RDONLY); // open("filename", 読み込みオプション)
            printf("==============================\nFD=%d: %s\n==============================\n\n", fd[i], argv[i]);
            while ((ret = get_next_line(fd[i], &line)) > 0) //get_next_lineが1を返している間ループ つまり、EOFまでこのループが回る
            {
                printf("[Return: %d] Line#%4d: %s$\n", ret, ++line_count, line); //1 getnextlineの戻り値, 2 行数カウント（？), 3 行の内容
                line = NULL; //なぜNULLポインタを入れるのか？-> *lineにデータをつめていくので、一旦NULLでリセットする
            }
            printf("[Return: %d] Line#%4d: %s$\n", ret, ++line_count, line); //EOFに到達して読み終わったあとの行？？
            if (ret == -1) //getnextlineが失敗すると-1を返す
                printf("-----------\nError\n");
            else if (ret == 0) //EOFにgetnextlineが到達したら0を返す
                printf("\n\n");
            i++;
            free(line); //普段はget_next_lineでfreeしてるけど、おそらくEOFにきたときにfreeするため？？
            end = clock(); //時間計測
            printf("\n%.2f Sconds\n",(double)(end-start)/CLOCKS_PER_SEC);
        }
    }
    else if (argc == 1) //コマンドライン引数がないとき
    {
        while ((ret = get_next_line(0, &line)) > 0) //fd 0、つまり標準入力から受け取っている
            printf("[Return: %d] Line#%4d: %s\n", ret, ++line_count, line); //なぜこの場合NULLポインタを入れる必要がないのか？
        if (ret == -1)
            printf("-----------\nError\n");
        else if (ret == 0)
            printf("-----------\nEnd of stdin\n");
    }
    while (argc >= 0) //最後にファイルを閉じていく
        close(fd[argc--]);
    while (1) //メモリリーク確認？？
	return (0);
}
