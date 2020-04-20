#include<iostream>
#include<cstdlib>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

using namespace std;

typedef struct{
    string num;
    string binary;
    int cnt;
}terms;

terms* min_arr; terms* care_arr;
terms* all_arr; terms* Primes;
int min_num;int care_num;
int all_num;

void PrimeImplicant();
int SetCnt(string num);
string ChangeBinary(string num);
string ChangeBinary(string bin1,string bin2);
int Diff(string bin1, string bin2);
void PrintGraph();
void PrintMinimumSolution(string ans);

void PrintMinimumSolution(string ans){
    int i;
    for(i = 0; i < ans.length(); i++){
        if(ans[i] == '_')
            continue;
        printf("%c",'A'+i);
        if(ans[i] == '0')
            cout << "'" ;
        cout << ' ';
    }
    cout << endl;
}

string ChangeBinary(string bin1,string bin2){
    string result= "";
    int i;
    for(i = 0; i < 4; i++){
        if(bin1[i] == bin2[i])
            result += bin1[i];
        else
            result += "_";
    }
    return result;
}

int Diff(string bin1, string bin2){
    int i;
    int result = 0;
    for(i = 0; i < 4; i++)
        if(bin1[i] != bin2[i])
            result += 1;
    return result;
}



void PrimeImplicant(){
    int size;
    int i; int j; int k;
    while(true){
        bool conti = false;
        size = 0;
        Primes = (terms*)malloc(sizeof(terms)*size);

        for(i = 0; i < all_num; i++){
            for(j = i+1; j < all_num; j++){
                if(Diff(all_arr[i].binary,all_arr[j].binary) == 1){
                    conti = true;
                    string temp = ChangeBinary(all_arr[i].binary,all_arr[j].binary);
                    for(k = 0; k < size; k++){
                        if(temp == Primes[k].binary)
                            break;
                    }
                    if(k == size){
                        Primes = (terms*)realloc(Primes,sizeof(terms)*(++size));
                        Primes[size-1].cnt = MAX(all_arr[i].cnt,all_arr[j].cnt);
                        Primes[size-1].num = all_arr[i].num + ' ' + all_arr[j].num;
                        Primes[size-1].binary = temp;
                    }
                }
            }
        }
        if(conti == false)
            break;
        all_arr = Primes;
        all_num = size;
        for(i = 0; i <=4 ;i++){
            printf("%d ========\n",i);
            for(j = 0; j < all_num; j++){
                if(all_arr[j].cnt == i)
                    cout << all_arr[j].num << ' ' << all_arr[j].binary << endl;
            }
        }
        cout << endl;
    }
}

int SetCnt(string num){
    int result = 0;
    int i;
    for(i = 0; i < 4; i++){
        if(num[i] == '1' || num[i] == '_')
            result += 1;
    }

    return result;
}

string ChangeBinary(string num){
    string result;
    int temp = atoi(num.c_str());
    int i;
    while(temp){
        if(temp%2 == 1)
            result += '1';
        else
            result += '0';
        temp /= 2;
    }

    string reverse_result= "";
    for(i = result.length()-1; i >= 0; i--)
        reverse_result += result[i];
    result = reverse_result;
    string final = "";

    for(i = 0; i < 4-(result.length()); i++){
        final += '0';
    }
    final += result;
    return final;
}

void PrintGraph(){
    int map[all_num][min_num];
    int i,j,k;
    for(i = 0; i < all_num; i++){
        for(j = 0; j < min_num; j++)
            map[i][j] = 0;
    }

    for(i = 0; i < all_num; i++){
        for(j = 0; j < all_arr[i].num.length(); j++){
            string temp = "";
            while(all_arr[i].num[j] != ' ' && j < all_arr[i].num.length())
                temp+= all_arr[i].num[j++];
            //cout << all_arr[i].num << ' ' << temp << endl;
            for(k = 0; k < min_num; k++){
                if(temp == min_arr[k].num)
                    map[i][k] = 1;
            }
        }
    }

    string Stack[min_num];
    int top = 0;
    for(i = 0; i < min_num; i++){
        int cnt = 0; int idx;
        for(j = 0; j < all_num; j++){
            if(map[j][i] == 1){
                cnt += 1;
                idx = j;
            }
                
        }
        if(cnt == 1)
            Stack[top++] = all_arr[idx].binary;
    }

    for(i = 0; i < top; i++)
        PrintMinimumSolution(Stack[i]);
}


int main(void){
    int i; int j;
    printf("입력하실 minterm의 개수를 입력하시오 : ");
    scanf("%d",&min_num);

    min_arr = (terms*)malloc(sizeof(terms)*min_num);
    printf("minterm을 입력해주세요 : ");

    for(i = 0; i < min_num; i++){
        cin >> min_arr[i].num;
        min_arr[i].binary = ChangeBinary(min_arr[i].num);
        min_arr[i].cnt = SetCnt(min_arr[i].binary);
    }
        
    
    printf("입력하실 dont't care 개수를 입력하시오 : ");
    scanf("%d",&care_num);

    care_arr = (terms*)malloc(sizeof(terms)*care_num);
    printf("minterm을 입력해주세요 : ");

    for(i = 0; i < care_num; i++){
        cin >> care_arr[i].num;
        care_arr[i].binary = ChangeBinary(care_arr[i].num);
        //cout << care_arr[i].num << ' ' << care_arr[i].binary << endl;
        care_arr[i].cnt = SetCnt(care_arr[i].binary);
    }

    all_num = care_num + min_num;
    all_arr = (terms*)malloc(sizeof(terms)*all_num);

    int idx = 0;
    for(i = 0; i < min_num; i++){
        all_arr[idx].binary = min_arr[i].binary;
        all_arr[idx].cnt = min_arr[i].cnt;
        all_arr[idx++].num = min_arr[i].num;
    }
    for(i = 0; i < care_num; i++){
        all_arr[idx].binary = care_arr[i].binary;
        all_arr[idx].cnt = care_arr[i].cnt;
        all_arr[idx++].num = care_arr[i].num;
    }

    PrimeImplicant();
    PrintGraph();

    return 0;
}
