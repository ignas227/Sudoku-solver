
#include <bits/stdc++.h>


using namespace std;

int number = 0; /// occupied square count

void stop_app (){
    string temp;
    while(true){
        cin >> temp;
    }


}

vector < int > square_poss(int x, int y, int arr_poss[9][9][9]){
    vector < int > answer = vector < int > ();
    for(int c = 0; c < 9; c++){
        if(arr_poss[x][y][c] == 1){
            answer.push_back(c);
        }
    }
    return answer;
}

int print_gamestate(int arr[9][9]){
    for(int a = 0; a < 9; a++){
        for(int b = 0; b < 9; b++){
            cout << arr[a][b] + 1 << " ";
        }
        cout << endl;
    }
}

int arr_insert(int x, int y, int c, int arr[9][9], int arr_poss[9][9][9]){
    arr[x][y] = c;
    for(int a = 0; a < 9; a++){
        arr_poss[x][y][a] = 0;
        arr_poss[x][a][c] = 0;
        arr_poss[a][y][c] = 0;
        int x1 = (x / 3) * 3;
        int y1 = (y / 3) * 3;
        int x2 = a / 3;
        int y2 = a % 3;
        arr_poss[x1 + x2][y1 + y2][c] = 0;
    }
    number++;
}



int square_check(int x, int y, int c, int arr[9][9], int arr_poss[9][9][9]){
    int hor_count = 0;
    int ver_count = 0;
    int sqr_count = 0;
    for(int a = 0; a < 9; a++){
        hor_count += arr_poss[x][a][c];
        ver_count += arr_poss[a][y][c];
        int x1 = (x / 3) * 3;
        int y1 = (y / 3) * 3;
        int x2 = a / 3;
        int y2 = a % 3;
        sqr_count += arr_poss[x1 + x2][y1 + y2][c];
    }
    if((hor_count == 1) || (ver_count == 1) || (sqr_count == 1)){
        if(arr_poss[x][y][c] == true){
            return 1;
        }
    }
    return 0;
}

int main(){

    ifstream cin("input.txt");

    int arr[9][9];
    for(int a = 0; a < 9; a++){
        for(int b = 0; b < 9; b++){
            int temp;
            cin >> temp;
            arr[a][b] = temp - 1;
        }
    }

    int arr_poss[9][9][9];
    for(int a = 0; a < 9; a++){
        for(int b = 0; b < 9; b++){
            for(int c = 0; c < 9; c++){
                arr_poss[a][b][c] = 1; /// 1 - possible, 0 - impossible
            }
        }
    }

    for(int a = 0; a < 9; a++){
        for(int b = 0; b < 9; b++){
            if(arr[a][b] != -1){
                arr_insert(a, b, arr[a][b], arr, arr_poss);
            }
        }
    }

    cout << "Numbers on the sudoku: " << number << endl;
    cout << "Starting position: " << endl;
    print_gamestate(arr);

    bool change = true;

    for(int t = 0; ((t < 100) && number < 81); t++){
    if(change == false){ /// try guessing one instead?
        for(int c = 0; c < 9; c++){
            cout << c + 1 << endl;
            for(int a = 0; a < 9; a++){
                for(int b = 0; b < 9; b++){
                    cout << arr_poss[a][b][c] << " ";
                }
            cout << endl;
            }
        }
    return 0;
    }

    change = false;

    for(int a = 0; a < 9; a++){
        for(int b = 0; b < 9; b++){
            for(int c = 0; c < 9; c++){
                if(arr[a][b] == -1){
                    int answer = square_check(a, b, c, arr, arr_poss);
                    if(answer == 1){
                        arr_insert(a, b, c, arr, arr_poss);
                        change = true;
                        goto end_of_loop;
                    }else{
                        vector < int > choices = square_poss(a, b, arr_poss);
                        if(choices.size() == 1){
                        arr_insert(a, b, choices[0], arr, arr_poss);
                        change = true;
                        goto end_of_loop;
                    }
                    }
                }
            }
        }
    }
    end_of_loop:
    cout << "Numbers on the sudoku: " << number << endl;
    print_gamestate(arr);
    cout << endl;
    }





    ///print_gamestate(arr_poss)


    return 0;
}
