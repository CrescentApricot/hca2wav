
//--------------------------------------------------
// インクルード
//--------------------------------------------------
#include <iostream>
#include <cstring>
#include "include/clHCA.h"

//--------------------------------------------------
// 文字列を10進数とみなして数値に変換(簡易版)
//--------------------------------------------------
int atoi(const char *s) {
    int r = 0;
    bool sign = false;
    if (*s == '+') { s++; }
    else if (*s == '-') {
        sign = true;
        s++;
    }
    while (*s) {
        if (*s >= '0' && *s <= '9')r = r * 10 + (*s - '0');
        else break;
        s++;
    }
    return sign ? -r : r;
}

//--------------------------------------------------
// 文字列を16進数とみなして数値に変換
//--------------------------------------------------
int atoi16(const char *s) {
    int r = 0;
    bool sign = false;
    if (*s == '+') { s++; }
    else if (*s == '-') {
        sign = true;
        s++;
    }
    while (*s) {
        if (*s >= '0' && *s <= '9')r = (r << 4) | (*s - '0');
        else if (*s >= 'A' && *s <= 'F')r = (r << 4) | (*s - 'A' + 10);
        else if (*s >= 'a' && *s <= 'f')r = (r << 4) | (*s - 'a' + 10);
        else break;
        s++;
    }
    return sign ? -r : r;
}

//--------------------------------------------------
// メイン
//--------------------------------------------------
int main(int argc, char *argv[]) {

    // コマンドライン解析
    unsigned int count = 0;
    char *filenameOut = nullptr;
    //bool decodeFlg=false;
    float volume = 1;
    unsigned int ciphKey1 = 0xE0748978;
    unsigned int ciphKey2 = 0xCF222F1F;
    int mode = 16;
    int loop = 0;
    bool info = false;
    bool decrypt = false;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            switch (argv[i][1]) {
                case 'o':
                    if (i + 1 < argc) { filenameOut = argv[++i]; }
                    break;
                    //case 'd':decodeFlg=true;break;
                case 'v':
                    volume = static_cast<float>(strtod(argv[++i], nullptr));
                    break;
                case 'a':
                    if (i + 1 < argc) { ciphKey1 = static_cast<unsigned int>(atoi16(argv[++i])); }
                    break;
                case 'b':
                    if (i + 1 < argc) { ciphKey2 = static_cast<unsigned int>(atoi16(argv[++i])); }
                    break;
                case 'm':
                    if (i + 1 < argc) { mode = static_cast<int>(strtol(argv[++i], nullptr, 10));; }
                    break;
                case 'l':
                    if (i + 1 < argc) { loop = static_cast<int>(strtol(argv[++i], nullptr, 10)); }
                    break;
                case 'i':
                    info = true;
                    break;
                case 'c':
                    decrypt = true;
                    break;
                default:break;
            }
        } else if (*argv[i]) {
            argv[count++] = argv[i];
        }
    }

    //if(decodeFlg){

    // 入力チェック
    if (!count) {
        printf("Error: 入力ファイルを指定してください。\n");
        return -1;
    }

    // デコード
    for (unsigned int i = 0; i < count; i++) {

        // 2つ目以降のファイルは、出力ファイル名オプションが無効
        if (i)filenameOut = nullptr;

        char path[256];
        if (!(filenameOut&&filenameOut[0])) {
            strcpy(path, argv[i]);
            char *d1 = strrchr(path, '\\');
            char *d2 = strrchr(path, '/');
            char *e = strrchr(path, '.');
            if (e&&d1<e&&d2<e)*e = '\0';
            strcat(path, ".wav");
            filenameOut = path;
        }

        // ヘッダ情報のみ表示
        if (info) {
            printf("%s のヘッダ情報\n", argv[i]);
            clHCA hca(0, 0);
            hca.PrintInfo(argv[i]);
            printf("\n");
        }

            // 復号化
        else if (decrypt) {
            printf("%s を復号化中...\n", argv[i]);
            clHCA hca(ciphKey1, ciphKey2);
            if (!hca.Decrypt(argv[i])) {
                printf("Error: 復号化に失敗しました。\n");
            }
        }

            // デコード
        else {
            printf("%s をデコード中...\n", argv[i]);
            clHCA hca(ciphKey1, ciphKey2);
            if (!hca.DecodeToWaveFile(argv[i], path, volume, mode, loop)) {
                printf("Error: デコードに失敗しました。\n");
            }
        }

    }

    //}

    return 0;
}
