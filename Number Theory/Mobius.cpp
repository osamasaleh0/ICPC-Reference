class mobius{
    public:
    vector<int> p;
    vector<bool> is_prime;
    
    mobius(){
        p.resize(MAX);
        is_prime.resize(MAX);
        
        for (int i = 1; i < MAX; i ++){
            p[i] = 1;
            is_prime[i] = true;
        }
        
        for (int i = 2; i < MAX; i ++)
            if (is_prime[i]){
                for (int j = i; j < MAX; j += i){
                    if (j != i)
                        is_prime[j] = false;
                    if ((j / i) % i == 0)
                        p[j] = 0;
                    p[j] *= - 1;
                }
            }
        
        for (int i = 1; i < MAX; i ++)
            p[i] = (p[i] + MOD) % MOD;
    }
    
    int operator [](int x){
        return p[x];
    }
};
