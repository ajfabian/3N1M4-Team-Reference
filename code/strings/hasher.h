/* Doble Hash para Strings
 - Llamar a init() dentro del main
 - query(int a, int b) devuelve el hashing relativo de
   la subcadena S[a..b] en O(1). Dos hashings de este tipo
   pero pertenecientes a dos cadenas diferentes, pueden
   compararse si la base(de tipo disp) de ambos es la misma.
 - Tiempo: Preproc: O(n), Query: O(1).
 - Tested on: patterns USACO 2006 Gold
**/
struct disp{
    int64 a, b;

    disp operator + (disp p)const{
        return {(a + p.a) % MOD, (b + p.b) % MOD};
    }
    disp operator - (disp p)const{
        return {(a + MOD - p.a) % MOD, (b + MOD - p.b) % MOD};
    }
    disp operator * (disp p)const{
        return {a * p.a % MOD, b * p.b % MOD};
    }

    bool operator == (disp p){ return a == p.a && b == p.b; }
    bool operator < (disp p) const{
        return a != p.a ? a < p.a : b < p.b;
    }
};

const disp BASE = {29ll, 31ll};
disp P[MX];

void init(){
    P[0] = {1ll, 1ll};
    for(int i=1; i < MX; i++)
        P[i] = P[i-1] * BASE;
}

struct hasher{
    int N;
    disp H[MX];

    hasher(){}
    hasher(string& S){
        N = S.size();
        for(int i=0; i < N; i++){
            H[i] = P[i] * (disp){S[i] - 'a' + 1, S[i] - 'a' + 1};
            H[i] = H[i] + (i ? H[i-1] : (disp){0, 0});
        }
    }

    disp query(int a, int b){
        if( a > b ) return (disp){0, 0};
        return (H[b] - (a ? H[a-1] : (disp){0, 0})) * P[MX-a-1];
    }
    
    bool is_period(int a, int b, int k){
        return (b-a+1) % k == 0 && query(a, b-k) == query(a+k, b);    
    }
};
