#define N 5           // количество философов 
#define LEFT (i-1)%N  // номер левого соседа для i-го философа 
#define RIGHT (i+1)%N // номер правого соседа для i-го философа

#define THINKING 0
#define HUNGRY 1
#define EATING 2


// массив состояний каждого из философов, инициализированный нулями
int state[N];

// семафор для доступа в критическую секцию 
semaphore mutex = 1;

// семафоры для философов
semaphore s[N];

/* Процесс-философ (i = 0..N-1) */
void Philosopher(int i)
{
    while(1)
    {
        Think();
        TakeForks(i);
        Eat();
        PutForks(i);
    }
}

/* получение вилок */
void TakeForks(int i)
{
    /* вход в критическую секцию */
    down(&mutex);
    state[i] = HUNGRY;
    Test(i);
    /* выход из критической секции */
    up(&mutex);
    down(&s[i]);
}

/* освобождение вилок */
void PutForks(int i)
{
    /* вход в критическую секцию */
    down(&mutex);
    state[i] = THINKING;
    Test(LEFT);
    Test(RIGHT);
    /* выход из критической секции */
    up(&mutex);
}

/* функция проверки возможности получения вилок –
проверяется состояние соседей данного философа */
void Test(int i)
{
    if(state[i] == HUNGRY &&
       state[LEFT] != EATING &&
       state[RIGHT] != EATING)
    {
        state[i] = EATING;
        up(&s[i]);
    }
}