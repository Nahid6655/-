#include <iostream>
#include <cstring>

using namespace std;

int main() {
    setlocale(LC_ALL, "RU");
    char sent[1000];
    
    cout << "Введите строку из 10 слов: ";
    cin.getline(sent, 1000);
    cout << "Строка:" << sent << endl;
    
    // 1. Количество слов, оканчивающихся на 'a'
    int countEndA = 0;
    const char* ptr1 = sent;

    while (*ptr1 != '\0') {
        // Пропускаем пробелы
        while (*ptr1 == ' ') {
            ptr1++;
        }

        if (*ptr1 == '\0') break;

        const char* wordStart = ptr1;
        
        // Находим конец слова
        while (*ptr1 != ' ' && *ptr1 != '\0') {
            ptr1++;
        }
           
        char lastChar = *(ptr1 - 1);
        // Учитываем как строчную, так и заглавную 'a'
        if (lastChar == 'a' || lastChar == 'A') {
            countEndA++;
        }

        if (*ptr1 == '\0') break;
        ptr1++;
    }
    cout << "1. Количество слов, оканчивающихся на 'a': " << countEndA << endl;

    // 2. Длина самого короткого слова
    int minlength = 1000;
    const char* ptr2 = sent;

    while (*ptr2 != '\0') {
        while (*ptr2 == ' ') {
            ptr2++;
        }

        if (*ptr2 == '\0') break;

        const char* wordStart = ptr2;
        int wordLength = 0;

        while (*ptr2 != ' ' && *ptr2 != '\0') {
            wordLength++;
            ptr2++;
        }

        if (wordLength > 0 && wordLength < minlength) {
            minlength = wordLength;
        }

        if (*ptr2 == '\0') break;
        ptr2++;
    }

    cout << "2. Длина самого короткого слова: " << minlength << endl;

    // 3. Количество букв 'b' во втором слове
    int countB = 0;
    int wordCount = 0;
    const char* ptr3 = sent;

    while (*ptr3 != '\0' && wordCount < 2) {
        while (*ptr3 == ' ') {
            ptr3++;
        }

        if (*ptr3 == '\0') break;

        wordCount++;

        if (wordCount == 2) {
            while (*ptr3 != ' ' && *ptr3 != '\0') {
                // Учитываем как строчную, так и заглавную 'b'
                if (*ptr3 == 'b' || *ptr3 == 'B') {
                    countB++;
                }
                ptr3++;
            }
            break;
        } else {
            while (*ptr3 != ' ' && *ptr3 != '\0') {
                ptr3++;
            }
        }

        if (*ptr3 == '\0') break;
        ptr3++;
    }
    cout << "3. Количество букв 'b' во втором слове: " << countB << endl;

    // 4. Замена заглавных букв на строчные
    char lowerSent[1000];
    strcpy_s(lowerSent, sent);
        
    char* ptr4 = lowerSent;
    while (*ptr4 != '\0') {
        if (*ptr4 >= 'A' && *ptr4 <= 'Z') {
            *ptr4 = *ptr4 + ('a' - 'A');
        }
        ptr4++;
    }
    cout << "4. Строка в нижнем регистре: " << lowerSent << endl;

    // 5. Количество слов с одинаковыми первым и последним символами
    int countFirstLast = 0;
    const char* ptr5 = sent;

    while (*ptr5 != '\0') {
        while (*ptr5 == ' ') {
            ptr5++;
        }

        if (*ptr5 == '\0') break;

        const char* wordStart = ptr5;
        char firstChar = *ptr5;

        while (*ptr5 != ' ' && *ptr5 != '\0') {
            ptr5++;
        }

        if (ptr5 > wordStart) {
            char lastChar = *(ptr5 - 1);
            
            // Приводим оба символа к нижнему регистру для корректного сравнения
            char firstLower = (firstChar >= 'A' && firstChar <= 'Z') ? 
                            firstChar + ('a' - 'A') : firstChar;
            char lastLower = (lastChar >= 'A' && lastChar <= 'Z') ? 
                           lastChar + ('a' - 'A') : lastChar;

            if (firstLower == lastLower) {
                countFirstLast++;
            }
        }

        if (*ptr5 == '\0') break;
        ptr5++;
    }
    cout << "5. Количество слов с одинаковыми первым и последним символами: " << countFirstLast << endl;

    // 6. Поиск самой короткой общей подстроки
    char words[10][100];
    int wordCountTotal = 0;
    const char* ptr = sent;

    // Разбиваем строку на слова
    while (*ptr != '\0' && wordCountTotal < 10) {
        while (*ptr == ' ') ptr++;
        if (*ptr == '\0') break;

        int i = 0;
        while (*ptr != ' ' && *ptr != '\0' && i < 99) {
            words[wordCountTotal][i++] = *ptr++;
        }
        words[wordCountTotal][i] = '\0';
        wordCountTotal++;
    }

    // Проверяем, что найдено достаточно слов
    if (wordCountTotal < 2) {
        cout << "6. Недостаточно слов для поиска общей подстроки" << endl;
        return 0;
    }

    char shortest[100] = "";
    int minLen = 1000;
    bool found = false;

    // Ищем самую короткую общую подстроку
    for (int i = 0; i < wordCountTotal; i++) {
        for (int j = i + 1; j < wordCountTotal; j++) {
            // Для каждой пары слов ищем общие подстроки
            int len1 = strlen(words[i]);
            int len2 = strlen(words[j]);
            
            // Перебираем все возможные подстроки первого слова
            for (int start = 0; start < len1; start++) {
                for (int end = start; end < len1; end++) {
                    int currentLen = end - start + 1;
                    
                    // Если текущая подстрока длиннее уже найденной минимальной, пропускаем
                    if (currentLen >= minLen) continue;
                    
                    // Извлекаем подстроку
                    char substr[100];
                    strncpy_s(substr, words[i] + start, currentLen);
                    substr[currentLen] = '\0';
                    
                    // Проверяем, содержится ли подстрока во втором слове
                    if (strstr(words[j], substr) != nullptr) {
                        minLen = currentLen;
                        strcpy_s(shortest, substr);
                        found = true;
                    }
                }
            }
        }
    }

    if (found) {
        cout << "6. Самая короткая общая подстрока: \"" << shortest << "\" (длина: " << minLen << ")" << endl;
    } else {
        cout << "6. Общая подстрока не найдена" << endl;
    }
    
    return 0;
}
